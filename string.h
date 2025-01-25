#ifndef TEMPLATE_STRING_H
#define TEMPLATE_STRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <exception>

class StringException : public std::exception {
private:
    std::string message;

public:
    explicit StringException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template<typename CharT = char>
class String {
private:
    CharT* str;
    size_t size;

    void allocateMemory(size_t newSize) {
        str = new (std::nothrow) CharT[newSize + 1];
        if (!str) {
            throw StringException("Memory allocation failed.");
        }
        memset(str, '\0', newSize + 1);
    }

public:
    String() : size(80) {
        allocateMemory(size);
    }

    explicit String(size_t customSize) : size(customSize) {
        allocateMemory(size);
    }

    String(const CharT* input) {
        if (!input) {
            throw StringException("Null pointer passed as input.");
        }
        size = strlen(input);
        allocateMemory(size);
        strcpy(str, input);
    }

    String(const String& other) : size(other.size) {
        allocateMemory(size);
        strcpy(str, other.str);
    }

    String(String&& other) noexcept : str(other.str), size(other.size) {
        other.str = nullptr;
        other.size = 0;
    }

    ~String() {
        delete[] str;
    }

    void input() {
        std::cout << "Enter a string: ";
        std::cin.ignore();
        std::cin.getline(str, size + 1);
    }

    void output() const {
        std::cout << "String: " << str << std::endl;
    }

    size_t length() const {
        return size;
    }

    String substr(size_t pos, size_t len) const {
        if (pos >= size) {
            throw StringException("Position out of range.");
        }
        size_t newLen = (pos + len > size) ? size - pos : len;
        CharT* newStr = new (std::nothrow) CharT[newLen + 1];
        if (!newStr) {
            throw StringException("Memory allocation failed for substring.");
        }
        strncpy(newStr, str + pos, newLen);
        newStr[newLen] = '\0';
        String result(newStr);
        delete[] newStr;
        return result;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            allocateMemory(size);
            strcpy(str, other.str);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            size = other.size;
            other.str = nullptr;
            other.size = 0;
        }
        return *this;
    }

    String operator+(const String& other) const {
        size_t newSize = size + other.size;
        CharT* newStr = new (std::nothrow) CharT[newSize + 1];
        if (!newStr) {
            throw StringException("Memory allocation failed for concatenation.");
        }
        strcpy(newStr, str);
        strcat(newStr, other.str);
        String result(newStr);
        delete[] newStr;
        return result;
    }

    String& operator+=(const String& other) {
        size_t newSize = size + other.size;
        CharT* newStr = new (std::nothrow) CharT[newSize + 1];
        if (!newStr) {
            throw StringException("Memory allocation failed for concatenation.");
        }
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        size = newSize;
        return *this;
    }

    CharT& operator[](size_t index) {
        if (index >= size) {
            throw StringException("Index out of range.");
        }
        return str[index];
    }

    const CharT& operator[](size_t index) const {
        if (index >= size) {
            throw StringException("Index out of range.");
        }
        return str[index];
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    bool operator>(const String& other) const {
        return size > other.size;
    }

    bool operator<(const String& other) const {
        return size < other.size;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }
};

#endif
