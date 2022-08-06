#include <iostream>
#include <string.h>

class MyString {
private:
    char* string_content; // 문자열 데이터를 가리키는 포인터
    int string_length; // 문자열 길이 
    int memory_capacity; //현재 할당된 용량
public:
    MyString(char c);
    MyString(const char* str);
    MyString(const MyString& str);
    ~MyString();
    int length() const;
    int capacity() const;
    void reserve(int size);
    
    void print() const;
    void println() const;  
    MyString& assign(const MyString& str);
    MyString& assign(const char* str);
    
    MyString& insert(int loc, const MyString& str);
    MyString& insert(int loc, const char* str);
    MyString& insert(int loc, char c);
    
    MyString& erase(int loc, int num);
    
    int find(int find_from, MyString& Str) const;
    int find(int find_from, const char* str) const;
    int find(int find_from, char c) const;
};

MyString::MyString(char c) 
{
    string_content = new char[1];
    string_content[0] = c;
    memory_capacity = 1;
    string_length = 1;
}

MyString::MyString(const char* str)
{
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];
    for(int i = 0; i != string_length; i++)
        string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
    string_length = str.string_length;
    memory_capacity = str.string_length;
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

MyString& MyString::assign(const MyString& str)
{
    if(str.string_length > memory_capacity) //기존보다 용량크면
    {
        delete[] string_content;    //재할당
        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    for(int i = 0; i != str.string_length; i++)
        string_content[i] = str.string_content[i];
    string_length = str.string_length;
    return *this; 
}

MyString& MyString::assign(const char* str)
{
    int str_length = strlen(str);
    if(str_length > memory_capacity)
    {
        delete[] string_content;
        string_content = new char[str_length];
        memory_capacity = str_length;
    }
    for(int i = 0; i != str_length; i++)
        string_content[i] = str[i];
    string_length = str_length;
    
    return *this;  
}

int MyString::capacity() const
{
    return memory_capacity;
}

void MyString::reserve(int size)
{
    if(size > memory_capacity)
    {
        char* prev_string_content = string_content;
        string_content = new char[size];
        memory_capacity = size;
        for(int i = 0; i != string_length; i++)
            string_content[i] = prev_string_content[i];
        delete[] prev_string_content;
    }
    //예약하려는 size가 현재 capacity보다 작으면 아무것도 안함
}    


MyString& MyString::insert(int loc, const MyString& str)
{
    //이는 i의 위치 바로 앞에 문자를 삽입하게 된다. 예를 들어서 
    // abc 라는 문자열에 insert(1, "d")를 하게 된다면 adbc가 된다.
    
    // 범위를 벗어나는 입력에 대해서는 삽입을 수행하지 않는다. 
    if(loc < 0 || loc > string_length)
        return *this;

    if(string_length + str.string_length > memory_capacity)
    {
        //이제 새롭게 동적으로 할당을 해야 한다.
        memory_capacity = string_length + str.string_length;
        char* prev_string_content = string_content;
        string_content = new char[memory_capacity];
        //일단 insert 되는 부분 직전까지의 내용을 복사한다.
        int i;
        for (i = 0; i < loc; i++)
            string_content[i] = prev_string_content[i];
        //그리고 새롭게 insert 되는 문자열을 넣는다.
        for (int j = 0; j != str.string_length; j++)
            string_content[i+j] = str.string_content[j];
        //이제 다시 원 문자열의 나머지 뒷부분을 복사한다.
        for (; i < string_length; i ++)
            string_content[str.string_length + i] = prev_string_content[i];
        delete[] prev_string_content;
        string_length = string_length + str.string_length;
        return *this;
    }
    
    //만일 초과하지 않는 경우 굳이 동적 할당을 할 필요가 없게 된다.
    //효율적으로 insert 하기 위해, 밀리는 부분을 먼저 뒤로 밀어버린다.
    for (int i = string_length - 1; i >= loc; i--)  //뒷부분 문자열 길이가 얼마나되든간 loc에서 넣을 문자 길이까지 밀어 
        string_content[i + str.string_length] = string_content[i];    
    for(int i = 0; i < str.string_length; i++)  //그리고 insert 되는 문자 다시 집어넣기
        string_content[i+loc] = str.string_content[i];
    string_length = string_length + str.string_length;
    return *this;
}

MyString& MyString::insert(int loc, const char* str)
{
    MyString temp(str);
    return insert(loc, temp);
}

MyString& MyString::insert(int loc, char c)
{
    MyString temp(c);
    return insert(loc, temp);
} 

MyString& MyString::erase(int loc, int num)
{
    if(num < 0 || loc < 0 < loc > string_length) // 지역이 잘못되거나 지울 문자 수가 잘못된 경우
        return *this;

    for(int i = loc + num; i < string_length; i++)
        string_content[i - num] = string_content[i];
    string_length -= num;
    return *this;
} 

int MyString::find(int find_from, MyString& str) const {
    int i, j;
    if (str.string_length == 0)
        return -1;
    for(i = find_from; i <= string_length - str.string_length; i++)
    {
        for(j = 0; j < str.string_length; j++)
        {
            if(string_content[i + j] != str.string_content[j])
                break;
        }
        if (j == str.string_length) //= 찾으려는 문자열의 끝까지 반복문이 진행되었다면
            return i;
    } 
    return -1;  //찾지 못했을 경우
}
    
int MyString::find(int find_from, const char* str) const
{
    MyString temp(str);
    return find(find_from, temp);
}

int MyString::find(int find_from, const char* str) const
{
    MyString temp(c);
    return find(find_from, temp);
}   
  

    

int main()
{
    MyString str1("this is a very very long string");
    std::cout << "Location of first <very> in the string : " << str.find(0, "very") << std::endl;
    std::cout << "Location of second <very> in the string : " 
        << str1.find(str1.find(0, "very") + 1, "very") << std::endl; 
    return 0;
}






