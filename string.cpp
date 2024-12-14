#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    size_t size;

public:
    String() : size(80) {
        str = new char[size + 1];
        memset(str, '\0', size + 1);
    }

    String(size_t customSize) : size(customSize) {
        str = new char[size + 1];
        memset(str, '\0', size + 1);
    }

    String(const char* input) {
        size = strlen(input);
        str = new char[size + 1];
        strcpy(str, input);
    }

    String(const String& other) : size(other.size) {
        str = new char[size + 1];
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
        cout << "Введіть рядок: ";
        cin.ignore();
        cin.getline(str, size + 1);
    }

    void output() const {
        cout << "Рядок: " << str << endl;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
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
        char* newStr = new char[size + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        return *this;
    }

    char& operator[](size_t index) {
        if (index >= size) throw out_of_range("Index out of range");
        return str[index];
    }

    const char& operator[](size_t index) const {
        if (index >= size) throw out_of_range("Index out of range");
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

    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.str;
        return os;
    }
};