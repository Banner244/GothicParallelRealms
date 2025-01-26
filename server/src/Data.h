#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Data {
public:
    int id;
    std::vector<std::string> names;

    Data() : id(0) {}
    Data(int id, const std::vector<std::string>& names) : id(id), names(names) {}

    // Serializes the object into a string buffer
    std::string serialize() const {
        std::ostringstream oss;
        oss << id << "|";
        for (const auto& name : names) {
            oss << name << ",";
        }
        std::string serialized = oss.str();
        if (!names.empty()) {
            serialized.pop_back(); // Remove the trailing comma
        }
        return serialized;
    }

    // Deserializes a string buffer into the object
    void deserialize(const std::string& buffer) {
        std::istringstream iss(buffer);
        std::string idStr;
        getline(iss, idStr, '|');
        id = std::stoi(idStr);

        names.clear();
        std::string name;
        while (getline(iss, name, ',')) {
            names.push_back(name);
        }
    }
};