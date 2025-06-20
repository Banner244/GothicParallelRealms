#pragma once
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cstdio>

class basic_string {
public:
    void* unusedAllocator;
    char* data;
    uint32_t length;
    uint32_t capacity;

    basic_string() {
        initEmpty();
    }

    basic_string(const char* str) {
        assign(str);
    }

    basic_string(const basic_string& other) {
        copyFrom(other);
    }

    ~basic_string() {
        tidy();
    }

    basic_string& operator=(const basic_string& other) {
        if (this != &other)
            copyFrom(other);
        return *this;
    }

    basic_string& operator=(const char* str) {
        assign(str);
        return *this;
    }

    const char* c_str() const {
        return data ? data : "";
    }

    size_t size() const {
        return length;
    }

    void verifyInternal(const basic_string& str) const {
        printf("Data:        %p\n", str.data);
        printf("Length:      %u\n", str.length);
        printf("Capacity:    %u\n", str.capacity);
        if (str.data) {
            printf("Data[-1]:    0x%02X\n", (unsigned char)str.data[-1]);
            printf("String:      \"%s\"\n", str.data);
        }
    }

private:
    void initEmpty() {
        char* raw = new char[2];
        raw[0] = (char)0xFE;
        raw[1] = '\0';

        data = raw + 1;
        length = 0;
        capacity = 0;
    }

    void assign(const char* str) {
        tidy();

        if (!str || str[0] == '\0') {
            initEmpty();
            return;
        }

        length = static_cast<uint32_t>(std::strlen(str));
        capacity = length;

        data = allocate(capacity);
        std::memcpy(data, str, length + 1);
    }

    void copyFrom(const basic_string& other) {
        tidy();

        if (other.data && getRefCount(other.data) < 0xFE) {
            data = other.data;
            length = other.length;
            capacity = other.capacity;
            incrementRefCount(data);
        } else if (other.length > 0) {
            length = other.length;
            capacity = other.capacity;
            data = allocate(capacity);
            std::memcpy(data, other.data, length + 1);
        } else {
            initEmpty();
        }
    }

    void tidy() {
        if (data) {
            if (getRefCount(data) < 0xFE) {
                decrementRefCount(data);
            } else {
                delete[] (data - 1);
            }
        }
        data = nullptr;
        length = 0;
        capacity = 0;
    }

    char* allocate(size_t size) {
        char* raw = new char[size + 2];
        raw[0] = (char)0xFE;
        raw[size + 1] = '\0';
        return raw + 1;
    }

    uint8_t getRefCount(const char* str) const {
        assert(str);
        return *(reinterpret_cast<const uint8_t*>(str) - 1);
    }

    void setRefCount(char* str, uint8_t count) {
        *(reinterpret_cast<uint8_t*>(str) - 1) = count;
    }

    void incrementRefCount(char* str) {
        uint8_t& ref = *(reinterpret_cast<uint8_t*>(str) - 1);
        if (ref < 0xFE) ref++;
    }

    void decrementRefCount(char* str) {
        uint8_t& ref = *(reinterpret_cast<uint8_t*>(str) - 1);
        if (--ref == 0) {
            delete[] (str - 1);
        }
    }
};