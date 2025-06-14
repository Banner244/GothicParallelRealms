#include "MessageHandler.h"

MessageHandler::MessageHandler(AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket)
{
    this->clients = &clients;
    this->pSocket = &socket;
}

void MessageHandler::handleBuffer(udp::endpoint &clientEndpoint, std::string buffer)
{
    int id = PackagingSystem::ReadPacketId(buffer);
    Packets::ClientPacket packetId = static_cast<Packets::ClientPacket>(id);

    Async::PrintLn( "ID: " + std::to_string(id) );
    Async::PrintLn( "Message: " + buffer );

    // Add new Player
    if(!isClientRegistered(clientEndpoint)){
        if(packetId != Packets::ClientPacket::clientHandshakeRequest)
            return;
        
        clientHandshakeRequest(clientEndpoint, buffer);
        updateLastResponse(clientEndpoint);
        return;
    }
    

    updateLastResponse(clientEndpoint);
    switch (packetId)
    {
    /*case Packets::ClientPacket::clientHandshakeRequest:
        clientHandshakeRequest(clientEndpoint, buffer);
        break;*/
    case Packets::ClientPacket::clientResponseHeartbeat:
        clientRepondsHeartbeat(clientEndpoint, buffer);
        break;
    case Packets::ClientPacket::clientSharePosition:
        clientSharesPosition(clientEndpoint, buffer);
        break;
    case Packets::ClientPacket::clientShareAnimations:
        clientSharesAnimations(clientEndpoint, buffer);
        break;
    default:
        Async::PrintLn("Unknown Paket...");
        break;
    }
}

bool MessageHandler::isClientRegistered(udp::endpoint &clientEndpoint){
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    auto it = clients->find(clientPortIp);
    if (it)
        return true;
    return false;
}

void MessageHandler::clientHandshakeRequest(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string username = PackagingSystem::ReadItem<std::string>(buffer);

   // ###### ADD NEW CLIENT ######
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    if(clients->existsItem(clientPortIp))
        return;

    CommonStructures::ClientInfo clientInfo;
    clientInfo.endpoint = clientEndpoint;
    clientInfo.lastResponse = std::chrono::high_resolution_clock::now();
    clientInfo.username = username;

    clientInfo.position.posX = PackagingSystem::ReadItem<double>(buffer);
    clientInfo.position.posZ = PackagingSystem::ReadItem<double>(buffer);
    clientInfo.position.posY = PackagingSystem::ReadItem<double>(buffer);
    clientInfo.rotation.yaw = PackagingSystem::ReadItem<double>(buffer);
    clientInfo.rotation.pitch = PackagingSystem::ReadItem<double>(buffer);
    clientInfo.rotation.roll = PackagingSystem::ReadItem<double>(buffer);

    clients->append(clientPortIp, clientInfo);
    Async::PrintLn( "Added new Client: " + clientPortIp );

    updateConsoleTitle();

    // ###################################

    // ###### SEND CLIENT THAT CONNECTION IS ESTABLISHED ######
    Async::PrintLn( clientPortIp + ", " +username+" Handshake Success");

    PackagingSystem handshakePacket(Packets::ServerPacket::serverHandshakeAccept);
    handshakePacket.addString("success");

    std::string serializedPacket = handshakePacket.serializePacket();
    sendMessage(clientEndpoint, serializedPacket);
    // ###################################

    // ###### SEND CLIENT EVERYONE ELSE ######
    // TODO: Continue Here to share the Name of the new Client to the other clients!!
    PackagingSystem helloInfo(Packets::ServerPacket::serverNewClientConnected);
    
    helloInfo.addString(clientPortIp);
    helloInfo.addString(username);
    helloInfo.addFloatPointNumber(clientInfo.position.posX, 2);
    helloInfo.addFloatPointNumber(clientInfo.position.posZ, 2);
    helloInfo.addFloatPointNumber(clientInfo.position.posY, 2);
    helloInfo.addFloatPointNumber(clientInfo.rotation.yaw, 2);
    helloInfo.addFloatPointNumber(clientInfo.rotation.pitch, 2);
    helloInfo.addFloatPointNumber(clientInfo.rotation.roll, 2);

    sendToAllExceptSender(clientEndpoint, helloInfo.serializePacket());

    // ###################################

    // ###### SEND EVERYONE ELSE TO CLIENT ######
    {
        std::lock_guard<std::mutex> lock(clients->getMutex());
        for (auto it = clients->getUnorderedMap()->begin(); it != clients->getUnorderedMap()->end(); ++it)
        {
            if(it->first == clientPortIp)
                continue;

            PackagingSystem playerInfo(Packets::ServerPacket::serverNewClientConnected);

            playerInfo.addString(it->first);
            playerInfo.addString(it->second.username);
            playerInfo.addFloatPointNumber(it->second.position.posX, 2);
            playerInfo.addFloatPointNumber(it->second.position.posZ, 2);
            playerInfo.addFloatPointNumber(it->second.position.posY, 2);
            playerInfo.addFloatPointNumber(it->second.rotation.yaw, 2);
            playerInfo.addFloatPointNumber(it->second.rotation.pitch, 2);
            playerInfo.addFloatPointNumber(it->second.rotation.roll, 2);

            sendMessage(clientEndpoint, playerInfo.serializePacket());
        }
    }
    // ###################################
}

void MessageHandler::clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    Async::PrintLn( clientPortIp + " responded to Heartbeat Request");
}

void MessageHandler::clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto it = clients->find(clientPortIp);
    if (!it)
        return;
    it->get().position.posX = PackagingSystem::ReadItem<double>(buffer);
    it->get().position.posZ = PackagingSystem::ReadItem<double>(buffer);
    it->get().position.posY = PackagingSystem::ReadItem<double>(buffer);
    it->get().rotation.yaw = PackagingSystem::ReadItem<double>(buffer);
    it->get().rotation.pitch = PackagingSystem::ReadItem<double>(buffer);
    it->get().rotation.roll = PackagingSystem::ReadItem<double>(buffer);

    PackagingSystem positionPacket(Packets::ServerPacket::serverDistributePosition);
    positionPacket.addString(clientPortIp);
    positionPacket.addFloatPointNumber(it->get().position.posX, 2);
    positionPacket.addFloatPointNumber(it->get().position.posZ, 2);
    positionPacket.addFloatPointNumber(it->get().position.posY, 2);
    positionPacket.addFloatPointNumber(it->get().rotation.yaw, 2);
    positionPacket.addFloatPointNumber(it->get().rotation.pitch, 2);
    positionPacket.addFloatPointNumber(it->get().rotation.roll, 2);

    std::string serializedPacket = positionPacket.serializePacket();

    sendToAllExceptSender(clientEndpoint, serializedPacket);
}
void MessageHandler::clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    PackagingSystem animationPacket(Packets::ServerPacket::serverDistributeAnimations);

    animationPacket.addString(clientPortIp);
    int animationCount = PackagingSystem::ReadItem<int>(*safeBuffer);
    animationPacket.addInt(animationCount);

    for(int i = 0; i< animationCount; i++) {
        animationPacket.addInt(PackagingSystem::ReadItem<int>(*safeBuffer));
    }

    sendToAllExceptSender(clientEndpoint, animationPacket.serializePacket());
}

void MessageHandler::sendMessage(udp::endpoint &clientEndpoint, std::string buffer)
{
    auto packetPtr = std::make_shared<std::string>(buffer);
    pSocket->async_send_to(
        boost::asio::buffer(*packetPtr),
        clientEndpoint,
        [this, packetPtr, clientEndpoint](boost::system::error_code ec, std::size_t bytes_sent)
        {
            if (ec){
                //std::cerr << "Async send error to " << clientEndpoint << ": " << ec.message() << std::endl;
                Async::Cerr ("Async send error to " + endpointToString(clientEndpoint) + ": " + ec.message());
            } else {
                Async::PrintLn ("Gesendet (" + std::to_string(bytes_sent) + " Bytes) an " + endpointToString(clientEndpoint));
                Async::PrintLn(*packetPtr);
            }
        });
}

/// NEEDS A REWORK
void MessageHandler::sendToAllExceptSender(udp::endpoint &senderEndpoint, std::string buffer)
{
    std::lock_guard<std::mutex> lock(clients->getMutex());
    for (auto it = clients->getUnorderedMap()->begin(); it != clients->getUnorderedMap()->end(); ++it)
    {
        //if (senderEndpoint != it->second.endpoint) // Uncomment for main branch
            sendMessage(it->second.endpoint, buffer);
    }
}

void MessageHandler::removeClient(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    if(clients->existsItem(clientPortIp))
        clients->remove(clientPortIp);

    std::lock_guard<std::mutex> lock(clients->getMutex());
    // Telling the Clients to remove unreachable client
    for (auto &pair : *clients->getUnorderedMap())
    {
        PackagingSystem clientToRemove(Packets::ServerPacket::serverRemoveClient);
        clientToRemove.addString(clientPortIp);
        sendMessage(pair.second.endpoint, clientToRemove.serializePacket());
    }

    updateConsoleTitle();
}

bool MessageHandler::addNewClient(udp::endpoint &clientEndpoint, std::string &username)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    if(clients->existsItem(clientPortIp))
        return false;

    CommonStructures::ClientInfo clientInfo;
    clientInfo.endpoint = clientEndpoint;
    clientInfo.lastResponse = std::chrono::high_resolution_clock::now();
    clientInfo.username = username;

    /*auto [it, inserted] = clients->try_emplace(clientPortIp, clientInfo);
    if (inserted)
        Async::PrintLn( "Added new Client: " + clientPortIp );*/


    clients->append(clientPortIp, clientInfo);
    Async::PrintLn( "Added new Client: " + clientPortIp );

    updateConsoleTitle();
    return true;
}

void MessageHandler::updateLastResponse(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto it = clients->find(clientPortIp);
    if (it)
        it->get().lastResponse = std::chrono::high_resolution_clock::now();
}

std::string MessageHandler::getClientUniqueString(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void MessageHandler::updateConsoleTitle()
{
    std::string title = "Players: " + std::to_string(clients->getUnorderedMap()->size());
    SetConsoleTitle(title.c_str());
}

std::string MessageHandler::endpointToString(const udp::endpoint &clientEndpoint){
    std::string endpointStr = clientEndpoint.address().to_string();
    endpointStr += ":" + std::to_string(clientEndpoint.port());
    return endpointStr;
}