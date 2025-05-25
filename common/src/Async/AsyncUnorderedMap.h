#pragma once
#include <unordered_map>
#include <mutex>
#include <optional>

template<typename T1, typename T2>
class AsyncUnorderedMap {
    public:
        void append(T1 key, T2 value) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            map.insert({key, value});
        }

        void remove(T1 key) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            map.erase(key);
        }

        bool existsItem(T1 key) {
            std::lock_guard<std::mutex> lock(this->mtxMap);
            auto it = map.find(key);
            if (it != map.end())
                return true;

            return false;
        }

        std::optional<std::reference_wrapper<T2>> find(const T1& key) {
            auto it = map.find(key);
            if(it != map.end()) 
                return it->second;
            else 
                return std::nullopt;
        }

        std::unordered_map<T1, T2> *getUnorderedMap() {
            return &this->map;
        }

        std::mutex &getMutex()  {
            return mtxMap;
        }
        /*T at();
        int size();*/

        /*void lock();
        void unlock();*/

    private:
        std::unordered_map<T1, T2> map;
        std::mutex mtxMap;
};
