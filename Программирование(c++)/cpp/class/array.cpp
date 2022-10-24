#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Array
{
private:
    char* str_;
    size_t size_;
public:
    //конструкторы
    Array() : size_(0), str_(nullptr) {}

    Array(size_t size): size_(size), str_(new char[size]) {}

    Array(Array& temp)
    {
        str_ = new char[temp.size_];
        for (size_t i = 0; i < temp.size_; ++i)
        {
            str_[i] = temp.str_[i];
        }
        size_ = temp.size_;
    }
    
    //диструктор
    ~Array()
    {
        delete[] str_;
    }
    
    //перегрузка опертора индексации
    char& operator[] (size_t i) const
    {
        if (i >= size_)
            throw out_of_range("индекс за границами");
        return str_[i];
    }
    //метод возвращающий размер массива
    size_t GetSize() const
    {
        return size_;
    }

};
