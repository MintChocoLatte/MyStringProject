#include <iostream>
#include <string.h>

class MyString {
private:
    char* string_content; // 문자열 데이터를 가리키는 포인터
    int string_length; // 문자열 길이
public:
    MyString(char c);
    MyString(const char* str);
    MyString(const MyString& str);
    ~MyString();
    int length() const;
    void print() const;
    void println() const;  
};

MyString::MyString(char c) 
{
    string_content = new char[1];
    string_content[0] = c;
}

MyString::MyString(const char* str)
{
    string_length = strlen(str);
    string_content = new char[string_length];
    for(int i = 0; i != string_length; i++)
        string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
    string_length = str.string_length;
    string_content = new char[string_length];
    for(int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}

MyString::~MyString() 
{
    delete[] string_content;
}

int MyString::length() const
{
    return string_length;
}

void MyString::print() const
{
    for(int i = 0; i != string_length; i++)
        std::cout << string_content[i];
}

void MyString::println() const
{
    for(int i = 0; i != string_length; i++)
        std::cout << string_content[i];
    std::cout << std::endl;
}

int main()
{
    MyString str1("Hello world!");
    MyString str2(str1);
    str1.println();
    str2.println();
    return 0;
}





