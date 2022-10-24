//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//class String
//{
//private:
//    char* str_;
//    int size_;
//public:
//    String()
//    {
//        str_ = nullptr;
//        size_ = 0;
//    }
//
//    String(const char str[])
//    {
//        int n = 0;
//        for (int n; str[n] != 0; ++n);
//        str_ = new char[n];
//        for (int i = 0; i < n; ++i)
//        {
//            str_[i] = str[i];
//        }
//        size_ = n;
//    }
//
//    String(int size)
//    {
//        if (size <= 0)
//            throw "Invalid size!";
//        str_ = new char[size];
//        if (str_ == nullptr)
//            throw "Memory allocation error!";
//        size_ = size;
//    }
//
//
//    //перегрузка опертора индексации
//    char& operator[] (int i) const
//    {
//        // if (i < 0 or i >= size_)
//        //     throw "Ошибка, нарушены границы массива";
//        return str_[i];
//    }
//
//    //диструктор
//    ~String()
//    {
//        delete[] str_;
//    }
//
//    //метод, который возвращает размер строки
//    unsigned int getSize() const
//    {
//        return size_;
//    }
//    String deleteBeginning(const unsigned int last, int n)
//    {
//        const int first = 0;
////        if ((first > last) or (last > size_))
////        {
////            return "";
////        }
//        String res;
//        res.str_ = new char[last - first + 1];
//
//        for (size_t i = first; i <= last; i++)
//        {
//            if (i > n - 1)
//            {
//                res.str_[i] = str_[i];
//            }
//        }
//        res.size_ = last - first + 1;
//        return res;
//
//    }
//    //метод для подстрок
//    String substr(const unsigned int first, const unsigned int last);
//
//
//    friend ostream& operator<<(ostream& out, const String& str);
//    friend istream& operator>>(istream& in, String& str);
//
//
//    bool operator== (const String& str) const;
//    bool operator== (const char* str) const;
//    bool operator!= (const String& str) const;
//
//    String& operator= (const String& str);
//    String& operator+ (const String& str) const;
//    String& operator+ (const char& tempChar) const;
//
//};
////перегрузка оператора вывода
//ostream& operator<<(ostream& out, const String& str)
//{
//    for (int i = 0; i < str.size_; ++i)
//    {
//        out << str.str_[i];
//    }
//    return out;
//}
////перегрузка оператора ввода
//istream& operator>>(istream& in, String& str)
//{
//    char t;
//    int size = 0;
//    char* buffer = new char[256];
//    in >> noskipws;
//
//    while (in >> t)
//    {
//        if (t == '\n')
//            break;
//        buffer[size] = t;
//        ++size;
//    }
//    buffer[size] = '\0';
//
//    str.str_ = buffer;
//    str.size_ = size;
//    return in;
//}
//
//int main()
//{
//    int n1 = 0;
//    String str1;
//    cout << "Введите строку: " << endl;
//    cin >> str1;
//    cout << "Введите число символов, которое хотите удалить: " << endl;
//    cin >> n1;
//    cout << str1.deleteBeginning(str1.getSize(), n1);
//}
