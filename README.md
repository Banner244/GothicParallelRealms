# GothicParallelRealms

Play Gothic 1 together with friends — see each other's progress in real time!
## About

>[!WARNING]
>This is early in development -- A LOT of bugs

GothicParallelRealms allows multiple players to experience the classic RPG Gothic 1 side by side.
While each player runs their own instance of the game, the tool synchronizes key gameplay elements, so you can see your friends' progress live inside your game.

    Real-time synchronization.

    Minimal impact on the original game experience.

## Features

    Live Progress Sharing: Watch your friends explore the world.

    Multiple Player Support: Play with 2 or more players simultaneously.

    Non-Invasive: No need to modify the core Gothic 1 files directly (except dxd11 mod).

    Modern C++ Networking: Powered by Boost.Asio.

## Requirements

    A working installation of Gothic 1.

    DirectX 11 Mod for Gothic 1 (required for graphical overlays and rendering hooks).

    C++20 compatible compiler.

    Boost libraries installed.

## How It Works

Each player runs a lightweight client that:

    Sends their gameplay data (e.g., position, actions) to a shared server.

    Receives updates from other players.

    Displays friends' characters in their own game world.

The server acts as a relay to synchronize all connected clients.


## Build Instructions
----

## Running

    Install the DirectX 11 mod for Gothic 1.

    Start the GothicParallelRealms server (just the host).

    Launch Gothic 1.

    Run the GothicParallelRealms client application.

    Play together!

## Contributing

Contributions, suggestions, and bug reports are very welcome!
Feel free to open an issue or submit a pull request.
