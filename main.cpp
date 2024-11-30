#include <iostream>
#include <cstring>

using namespace std;

char* CopyString(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    char* new_str = new char[length + 1];
    memcpy(new_str, str, length + 1);
    return new_str;
}

char* ConcatinateStrings(const char* a, const char* b) {
    size_t len_a = 0;
    while (a[len_a] != '\0') {
        ++len_a;
    }

    size_t len_b = 0;
    while (b[len_b] != '\0') {
        ++len_b;
    }

    char* new_str = new char[len_a + len_b + 1];

    memcpy(new_str, a, len_a);

    memcpy(new_str + len_a, b, len_b + 1);

    return new_str;
}

int main() {
    const char* original = "Привет, мир!";
    char* copy = CopyString(original);
    cout << "Оригинальная строка: " << original << endl;
    cout << "Копия строки: " << copy << endl;

    const char* str1 = "Hello, ";
    const char* str2 = "World!";
    char* concatenated = ConcatinateStrings(str1, str2);
    cout << "Строка 1: " << str1 << endl;
    cout << "Строка 2: " << str2 << endl;
    cout << "Объединённая строка: " << concatenated << endl;


    return 0;
}