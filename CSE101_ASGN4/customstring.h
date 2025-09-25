#ifndef CUSTOMSTRING_H
#define CUSTOMSTRING_H

#include <cstring>

class CustomString {
public:
    char* str;

    CustomString() : str(nullptr) {}

    CustomString(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    CustomString(const CustomString& other) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    CustomString& operator=(const CustomString& other) {
        if (this == &other) {
            return *this;
        }
        delete[] str;
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
        return *this;
    }

    bool operator==(const CustomString& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const CustomString& other) const {
        return strcmp(str, other.str) != 0;
    }

    bool operator<(const CustomString& other) const {
        return strcmp(str, other.str) < 0;
    }

    bool operator>(const CustomString& other) const {
        return strcmp(str, other.str) > 0;
    }
		bool operator<=(const CustomString& other) const {
        return strcmp(str, other.str) <= 0;
    }

    bool operator>=(const CustomString& other) const {
        return strcmp(str, other.str) >= 0;
    }

    void append(const char* s) {
        char* new_str = new char[strlen(str) + strlen(s) + 1];
        strcpy(new_str, str);
        strcat(new_str, s);
        delete[] str;
        str = new_str;
    }

    ~CustomString() {
        delete[] str;
    }
};

#endif
