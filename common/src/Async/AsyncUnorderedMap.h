#pragma once
#include <unordered_map>
#include <mutex>
#include <optional>
#include <functional>

/**
 * @brief A thread-safe wrapper around std::unordered_map.
 * 
 * This class provides synchronized access to an unordered_map using a mutex,
 * allowing safe concurrent usage in multithreaded environments.
 * 
 * @tparam T1 Key type
 * @tparam T2 Value type
 */
template<typename T1, typename T2>
class AsyncUnorderedMap {
    public:

        /**
         * @brief Inserts a key-value pair into the map.
         * If the key already exists, the value is not updated.
         * 
         * @param key The key to insert
         * @param value The value to associate with the key
         */
        void append(T1 key, T2 value) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            map.insert({key, value});
        }

        /**
         * @brief Removes an entry by key.
         * 
         * @param key The key to remove
         */
        void remove(T1 key) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            map.erase(key);
        }

        /**
         * @brief Checks whether the map contains the specified key.
         * 
         * @param key The key to look for
         * @return true if key exists, false otherwise
         */
        bool existsItem(T1 key) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            auto it = map.find(key);
            if (it != map.end())
                return true;

            return false;
        }

        /**
         * @brief Grants access to the internal map via a user-defined function.
         * The map is locked during this operation.
         * 
         * @param userFunction A function that takes a reference to the map
         */
        void accessMap (std::function<void(std::unordered_map<T1, T2>&)> userFunction) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            userFunction(map);
        }

        /**
         * @brief Finds a value by key and returns it as a reference.
         * 
         * @param key The key to look for
         * @return std::optional containing a reference to the value if found, or std::nullopt otherwise
         */
        std::optional<std::reference_wrapper<T2>> find(const T1& key) {
            auto it = map.find(key);
            if(it != map.end()) 
                return it->second;
            else 
                return std::nullopt;
        }

        /**
         * @brief Returns a raw pointer to the internal unordered_map.
         * Use with caution. No synchronization is applied.
         * 
         * @return Pointer to the internal map
         */
        std::unordered_map<T1, T2> *getUnorderedMap() {
            return &this->map;
        }
/*
        std::mutex &getMutex()  {
            return mtxMap;
        }*/
        /*T at();
        int size();*/

        /*void lock();
        void unlock();*/

    private:
        std::unordered_map<T1, T2> map; ///< The internal key-value map
        std::mutex mtxMap;              ///< Mutex for thread-safe access
};
