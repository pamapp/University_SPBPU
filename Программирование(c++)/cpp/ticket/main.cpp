#include <iostream>

using namespace std;

class String
{
    private:
        char* str;

    public:
        String();
        String(const char* str);
        ~String();
        String& operator=(const String& other);
        String(const String& other);
        friend istream& operator >> (istream& in, String& string);
        friend ostream& operator << (ostream& out, const String& string);

};


String::String()
{
    str = nullptr;
}
String::String(const char* str)
{
    int length = strlen(str);
    this->str = new char[length + 1];
    for (int i = 0; i < length+1; i++)
    {
        this->str[i] = str[i];
    }
}
String::String(const String& other)
{
    int length = strlen(other.str);
    this->str = new char[length + 1];
    for (int i = 0; i < length+1; i++)
    {
        this->str[i] = other.str[i];
    }
}
String& String::operator=(const String& other)
{
    if (this == &other) return *this;
    if (this->str != nullptr)
    {
        delete[] str;
    }
    int length = strlen(other.str);
    this->str = new char[length + 1];
    for (int i = 0; i < length+1; i++)
    {
        this->str[i] = other.str[i];
    }
    return *this;
}
String::~String()
{
    delete[] this->str;
}

istream& operator >> (istream& in, String& string)
{
    const int length = 100;
    char baffer[length];
    in.get(baffer[0]);
    int i;
    for (i = 0; baffer[i] != '\0'; i++);
    string.str = new char[i + 1];

    for (int j = 0; j < i+1; j++)
    {
        string.str[i] = baffer[i];
    }
    return in;
}


ostream& operator << (ostream& out, const String& string)
{
    out << string.str;
    return out;
}

int main()
{

    String str;
    String str2;
    cin >> str >> str2;


    cout << "+++++++++++++++++++++++" << endl;
    cout << str << str2;

//    result.Print();
    return 0;
}


//
//class MyString
//{
//    private:
//    // Указатель на массив char, хранит символы, которые мы передали в наш объект.
//        char *str;
//        int length;
//
//    public:
//    //конструктор без параметров
//    MyString()
//    {
//        str = nullptr;
//        length = 0;
//    }
//
//    //конструктор с параметрами, при создании объекта класса необходимо перелать строку которую он будет хранить
//    MyString(char *str)
//    {
//        length = strlen(str);
//        this->str = new char[length + 1];
//        for (int i = 0; i < length; i++)
//        {
//            this->str[i] = str[i];
//        }
//        this->str[length] = '\0';
//
//    }
//
//    // деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
//    ~MyString()
//    {
//        delete[] this->str;
//    }
//
//    // конструктор копировании, необходим для создании точной копи объекта класса но в другой области памяти
//    MyString(const MyString &other)
//    {
//        length = strlen(other.str);
//        this->str = new char[length + 1];
//        for (int i = 0; i < length; i++)
//        {
//            this->str[i] = other.str[i];
//        }
//        this->str[length] = '\0';
//    }
//
//    // перегруженый оператор присваивания, вызывается когда необходимо присвоить значение одного объекта другому
//    MyString& operator =(const MyString &other)
//    {
//        if (this->str != nullptr)
//        {
//            delete[] str;
//        }
//        length = strlen(other.str);
//        this->str = new char[length + 1];
//        for (int i = 0; i < length; i++)
//        {
//            this->str[i] = other.str[i];
//        }
//        this->str[length] = '\0';
//        return *this;
//    }
//
//    MyString operator+(const MyString &other)
//    {
//        MyString newStr;
//
//        int thisLength = strlen(this->str);
//        int otherLength = strlen(other.str);
//        newStr.length = thisLength + otherLength;
//        newStr.str = new char[thisLength + otherLength + 1];
//
//        int i = 0;
//        for (; i < thisLength; i++)
//        {
//            newStr.str[i] = this->str[i];
//        }
//
//        for (int j = 0; j < otherLength; j++, i++)
//        {
//            newStr.str[i] = other.str[j];
//        }
//
//        newStr.str[thisLength + otherLength] = '\0';
//        return newStr;
//    }
//
//    void Print()
//    {
//        cout << str;
//    }
//
//    int Length()
//    {
//        return length;
//    }
//
//    bool operator ==(const MyString & other)
//    {
//        if (this->length != other.length)
//        {
//            return false;
//        }
//
//        for (int i = 0; i < this->length; i++)
//        {
//            if (this->str[i] != other.str[i])
//            {
//                return false;
//            }
//        }
//        return true;
//    }
//
//    bool operator !=(const MyString & other)
//    {
//        return !(this->operator==(other));
//    }
//
//    char& operator [](int index)
//    {
//        return this->str[index];
//    }
//
//
//    MyString(MyString &&other)
//    {
//        this->length = other.length;
//        this->str = other.str;
//        other.str = nullptr;
//    }
//};
//
//
//int main()
//{
//
//    MyString str("Hello");
//    MyString str2("World");
//
//    MyString result;
//    result = str + str2;
//
//    result.Print();
//    cout << endl << endl;
//
//    system("pause");
//    return 0;
//}


