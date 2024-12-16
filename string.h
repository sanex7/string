#ifndef TEMPLATE_STRING_H
#define TEMPLATE_STRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>

template<typename CharT = char>
class String {
private:
    CharT* str;
    size_t size;

public:
    // Конструктори
    String() : size(80) {
        str = new CharT[size + 1];
        memset(str, '\0', size + 1);
    }

    String(size_t customSize) : size(customSize) {
        str = new CharT[size + 1];
        memset(str, '\0', size + 1);
    }

    String(const CharT* input) {
        size = strlen(input);
        str = new CharT[size + 1];
        strcpy(str, input);
    }

    String(const String& other) : size(other.size) {
        str = new CharT[size + 1];
        strcpy(str, other.str);
    }

    String(String&& other) noexcept : str(other.str), size(other.size) {
        other.str = nullptr;
        other.size = 0;
    }

    ~String() {
        delete[] str;
    }

    // Методи
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
            throw std::out_of_range("Position out of range");
        }
        size_t newLen = (pos + len > size) ? size - pos : len;
        CharT* newStr = new CharT[newLen + 1];
        strncpy(newStr, str + pos, newLen);
        newStr[newLen] = '\0';
        return String(newStr);
    }

    // Оператори
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new CharT[size + 1];
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
        String result(size + other.size);
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        size += other.size;
        CharT* newStr = new CharT[size + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        return *this;
    }

    CharT& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return str[index];
    }

    const CharT& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
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