#include "AsyncVector.h"

template<typename T>
void AsyncVector<T>::append(T item) {
    std::lock_guard<std::mutex> lock(this->mtxList);
}

template<typename T>
std::vector<T> *AsyncVector<T>::getVector() {
    return &this->list;
}