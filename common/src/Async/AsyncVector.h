#pragma once

#include <vector>
#include <mutex>


/* NOT FINISHED */
template<typename T>
class AsyncVector {
    public:
        void append(T item);
        /*void remove(T item);
        bool existsItem(T item);

        T at();
        int size();*/

        std::vector<T> *getVector();

        /*void lock();
        void unlock();*/
    private:
        std::vector<T> list;
        std::mutex mtxList;
};