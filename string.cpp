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

};
