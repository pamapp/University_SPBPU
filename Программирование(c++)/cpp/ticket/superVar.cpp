#include <iostream>
#include <string> // подключаем строки
#include <fstream> // подключаем файлы
using namespace std;

const string fileName = "C:\\Users\\alinapotapova\\Documents\\cpp\\ticket\\output.txt";

class MyString
{
private:
    char* a_;
    int size_;
public:
    MyString()
    {
        a_ = nullptr;
        size_ = 0;
    }

    MyString(const char a[])
    {
        int n = 0;
        for (int n; a[n] != 0; ++n);
        a_ = new char[n];
        for (int i = 0; i < n; ++i)
        {
            a_[i] = a[i];
        }
        size_ = n;
    }

    MyString(int size)
    {
        if (size <= 0)
            throw "Ошибка, неверно задан размер массива";
        a_ = new char[size]{};
        if (a_ == nullptr)
            throw "Ошибка выделения памяти";
        size_ = size;
    }

    MyString(const MyString& temp)
    {
        a_ = new char[temp.size_];
        for (int i = 0; i < temp.size_; ++i)
        {
            a_[i] = temp.a_[i];
        }
        size_ = temp.size_;
    }

    char& operator[] (int i) const
    {
        if (i < 0 or i >= size_)
            throw "Ошибка, нарушены границы массива";
        return a_[i];
    }

    ~MyString()
    {
        delete[] a_;
    }

    unsigned int getSize() const
    {
        return size_;
    }

    MyString substr(const unsigned int first, const unsigned int last);
    /*MyString substr(const unsigned first);*/

    friend ostream& operator<<(ostream& out, const MyString& str);
    friend istream& operator>>(istream& in, MyString& str);

    bool operator== (const MyString& str) const;
    bool operator== (const char* str) const;

    MyString& operator= (const MyString& str);
    MyString& operator+ (const MyString& str) const;
    MyString& operator+ (const char& tempChar) const;
};

ostream& operator<<(ostream& out, const MyString& str)
{
    for (int i = 0; i < str.size_; ++i)
    {
        out << str.a_[i];
    }
    return out;
}



istream& operator>>(istream& in, MyString& str)
{
    char t;
    int size = 0;
    char* buf = new char[256];
    in >> noskipws;

    while (in >> t)
    {
        if (t == '\n')
            break;
        buf[size] = t;
        ++size;
    }
    buf[size] = '\0';

    str.a_ = buf;
    str.size_ = size;
    return in;
}
bool MyString::operator==(const MyString& str) const
{
    if (size_ != str.size_)
        return false;
    bool result = true;
    for (int i = 0; i < str.size_; ++i)
    {
        result *= (a_[i] == str.a_[i]);
    }
    return result;
}

bool MyString::operator==(const char* str) const
{
    unsigned int size;
    for (size = 0; str[size]; ++size);
    if (size_ != size)
        return false;
    bool result = true;
    for (int i = 0; i < size; ++i)
    {
        result &= (a_[i] == str[i]);
    }
    return result;
}

MyString& MyString::operator=(const MyString& str)
{
    if (&str == this)
        return *this; // проверка на самоприсваивание
    if (str.size_ == 0)
    {
        delete[] a_;
        a_ = nullptr;
        size_ = 0;
    }
    else
    {
        delete[] a_;
        a_ = new char[str.size_];
        if (a_ == nullptr)
            throw "IntArray: Ошибка выделения памяти";
        size_ = str.size_;
        for (int i = 0; i < str.size_; i++)
            a_[i] = str.a_[i];
    }
    return *this;
}

MyString& MyString::operator+(const MyString& str) const
{
    MyString temp(size_ + str.size_);
    for (int i = 0; i < size_; ++i)
    {
        temp.a_[i] = a_[i];
    }
    for (int i = 0; i < str.size_; ++i)
    {
        temp.a_[size_ + i] = str.a_[i];
    }
    return temp;
}

MyString& MyString::operator+(const char& tempChar) const
{
    MyString temp(size_ + 1);
    for (int i = 0; i < size_; ++i)
    {
        temp.a_[i] = a_[i];
    }
    temp.a_[size_] = tempChar;
    return temp;
}

MyString MyString::substr(const unsigned int first, const unsigned int last)
{
    if ((first > last) or (last > size_))
    {
        return "";
    }

    MyString res;
    res.a_ = new char[last - first + 1];
    for (size_t i = first; i < last+1; i++)
    {
        res.a_[i - first] = a_[i];
    }
    res.size_ = last - first+1;
    return res;

}


class MusicAlbum
{
private:
    MyString title_;    //название
    MyString performer_;    //исполнитель
    MyString genre_;    //жанр
    unsigned int yearOfIssue_;    //год выпуска
    unsigned int time_;    //время звучания
public:
    MusicAlbum()
    {
        title_ = "";
        performer_ = "";
        genre_ = "";
        yearOfIssue_ = 0;
        time_ = 0;
    }

    MusicAlbum(const MyString& title, const MyString& perfomer, const MyString& genre, const unsigned int& yearOfIssue, const unsigned int& time)
    {
        title_ = title;
        performer_ = perfomer;
        genre_ = genre;
        yearOfIssue_ = yearOfIssue;
        time_ = time;
    }

    MusicAlbum(const MusicAlbum& album)
    {
        title_ = album.title_;
        performer_ = album.performer_;
        genre_ = album.genre_;
        yearOfIssue_ = album.yearOfIssue_;
        time_ = album.time_;
    }

    ~MusicAlbum() {}

    void setTitle(MyString title)
    {
        title_ = title;
    }

    void setPerformer(MyString performer)
    {
        performer_ = performer;
    }

    void setGenre(MyString genre)
    {
        genre_ = genre;
    }

    void setYearOfIssue(unsigned int yearOfIssue)
    {
        yearOfIssue_ = yearOfIssue;
    }

    void setTime(unsigned int time)
    {
        time_ = time;
    }

    MyString getTitle()
    {
        return title_;
    }

    MyString getPerformer()
    {
        return performer_;
    }

    MyString getGenre()
    {
        return genre_;
    }

    unsigned int getYearOfIssue()
    {
        return yearOfIssue_;
    }

    unsigned int getTime()
    {
        return time_;
    }



    MusicAlbum& operator= (const MusicAlbum& album);
    bool operator>(const MusicAlbum& album) const;
    bool operator<(const MusicAlbum& album) const;
    bool operator==(const MusicAlbum& album) const;

    friend ostream& operator<<(ostream& out, const MusicAlbum& album);
    friend istream& operator>>(istream& in, MusicAlbum& album);
    //friend unsigned int timeInInt(const MyString& time);
};

bool MusicAlbum::operator==(const MusicAlbum& album) const
{
    return (album.title_ == title_ and
        album.performer_ == performer_ and
        album.genre_ == genre_ and
        album.yearOfIssue_ == yearOfIssue_ and
        album.time_ == time_);
}

MusicAlbum& MusicAlbum::operator=(const MusicAlbum& album)
{
    if (&album == this)
        return *this;
    title_ = album.title_;
    performer_ = album.performer_;
    genre_ = album.genre_;
    yearOfIssue_ = album.yearOfIssue_;
    time_ = album.time_;
    return *this;
}


bool MusicAlbum::operator>(const MusicAlbum& album) const
{
    return (time_ > album.time_);
}

bool MusicAlbum::operator<(const MusicAlbum& album) const
{
    return (time_ < album.time_);
}
ostream& operator<<(ostream& out, const MusicAlbum& album)
{
    out << album.title_ << " " << album.performer_ << " " << album.genre_ << " " << album.yearOfIssue_ << " " << album.time_ / 60 << ':' << album.time_ % 60;
    return out;
}


istream& operator>>(istream& in, MusicAlbum& album)
{
    in >> album.title_ >> album.performer_ >> album.genre_ >> album.yearOfIssue_ >> album.time_;
    return in;
}
template <class T>
class MyList
{
private:
    struct Node
    {
        T item_;
        Node* next_;
        Node(const T& item, Node* next = nullptr) : item_(item), next_(next) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;

    unsigned int count_ = 0;

    Node* head() const { return head_; }

    Node* tail() const { return tail_; }

    void insertHead(Node* x)
    {
        x->next_ = head_;
        if (head_ == nullptr)
            tail_ = x;
        head_ = x;
        count_++;
    }

    void insertTail(Node* x)
    {
        if (tail_ != nullptr)
        {
            tail_->next_ = x;
            tail_ = x;
        }
        else
        {
            head_ = x;
            tail_ = x;
        }
    }

    Node* searchNode(const T& item)
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            if (item == temp->item_)
            {
                return temp;
            }
            temp = temp->next_;
        }
    }

    void replaceNode(Node* x, const T& item)
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            if (item == temp->item_)
            {
                temp = x;
                return;
            }
            temp = temp->next_;
        }
    }

public:
    MyList() : count_(0), head_(nullptr), tail_(nullptr) {}

    MyList(const MyList& src)
    {
        Node* temp = src.head_;
        while (temp != nullptr)
        {
            this->insertTail(temp);
            temp = temp->next_;
        }
    }

    ~MyList() {}

    int getSize() const { return count_; }

    T headItem() const
    {
        return head_->item_;
    }

    T& headItem()
    {
        return head_->item_;
    }

    T tailItem() const
    {
        return tail_->item_;
    }

    T& tailItem()
    {
        return tail_->item_;
    }

    void loadElementsInArray(T* tempoArray)
    {
        Node* tempo = head_;
        for (unsigned int i = 0; i < count_; i++)
        {
            tempoArray[i] = tempo->item_;
            tempo = tempo->next_;
        }
    }

    void insertHead(const T& item)
    {
        insertHead(new Node(item));
    }

    void insertTail(const T& item)
    {
        insertTail(new Node(item));
    }

    void sortedInsertItem(const T& item)
    {
        Node* temp = head_;
        Node* insert = new Node(item);
        if (temp == nullptr)
        {
            this->insertHead(item);
            return;
        }

        if (item < temp->item_)
        {
            this->insertHead(item);
            return;
        }

        if (temp->next_ == nullptr)
        {
            this->insertTail(item);
            return;
        }

        while (temp->next_->item_ < item)
        {
            temp = temp->next_;
            if (temp->next_ == nullptr)
            {
                temp->next_ = insert;
                this->insertTail(insert);
                return;
            }
        }

        insert->next_ = temp->next_;
        temp->next_ = insert;
        count_++;
        return;
    }

    bool deleteHead()
    {
        if (head_ != nullptr)
        {
            head_ = head_->next_;
            return true;
        }
        return false;
    }

    bool searchItem(const T& item)
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            if (item == temp->item_)
                return true;
            temp = temp->next_;
        }
        return false;
    }

    bool replaceItem(const T& itemOld, const T& itemNew)
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            if (itemOld == temp->item_)
            {
                temp->item_ = itemNew;
                return true;
            }
            temp = temp->next_;
        }
        return false;
    }

    void outAll()
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            cout << temp->item_ << endl;
            temp = temp->next_;
        }
    }

    void outAll(ofstream& out)
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            out << temp->item_ << endl;
            temp = temp->next_;
        }
    }
};

template <typename T>
class Array
{
private:
    T* a_;
    size_t size_;
public:
    Array() : size_(0), a_(nullptr) {}

    Array(size_t size): size_(size), a_(new T[size]) {}

    Array(Array& temp)
    {
        a_ = new T[temp.size_]{};
        for (size_t i = 0; i < temp.size_; ++i)
        {
            a_[i] = temp.a_[i];
        }
        size_ = temp.size_;
    }

    ~Array()
    {
        delete[] a_;
    }

    T& operator[] (size_t i) const
    {
        if (i >= size_)
            throw out_of_range("индекс за границами");
        return a_[i];
    }

    size_t GetSize() const
    {
        return size_;
    }

};

//struct maxMinAlbum getMaxMinObjInArray(const Array<MusicAlbum>& arrayOfAlbum, int size)
//{
//    MusicAlbum maxAlbum = arrayOfAlbum[0];
//    MusicAlbum minAlbum = arrayOfAlbum[0];
//
//    for (int i = 1; i < size; ++i)
//    {
//        if (arrayOfAlbum[i] > maxAlbum)
//        {
//            maxAlbum = arrayOfAlbum[i];
//        }
//        if (arrayOfAlbum[i] < minAlbum)
//        {
//            minAlbum = arrayOfAlbum[i];
//        }
//    }
//
//    struct maxMinAlbum result = { maxAlbum, minAlbum };
//    return result;
//}
//struct maxMinAlbum
//{
//    MusicAlbum max;
//    MusicAlbum min;
//};
template <class T>
void selectionSort(Array<T> &sortableArray)
{
    unsigned n = sortableArray.GetSize();
    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned id = i;
        for (unsigned int j = i + 1; j < n; ++j)
        {
            id = (sortableArray[j] < sortableArray[id] ? j : id);
        }
        T temp = sortableArray[i];
        sortableArray[i] = sortableArray[id];
        sortableArray[id] = temp;
    }
}
MusicAlbum split(MyString& str)
{
    MusicAlbum tempMusicAlbum;
    unsigned int pointTitle = 0;
    unsigned int pointPerformer = 0;
    unsigned int pointGenre = 0;
    unsigned int pointYearOfIssue = 0;
    for (unsigned int i = 0; i < str.getSize(); ++i)
    {
        if (str[i] == ' ' and pointTitle == 0)
        {
            pointTitle = i;
            MyString title = str.substr(1, pointTitle - 2);
            tempMusicAlbum.setTitle(title);
        }
        if (str[i] == ' ' and pointTitle != 0 and pointTitle != i and pointPerformer == 0)
        {
            pointPerformer = i;
            MyString perfomer = str.substr(pointTitle + 2, pointPerformer - 2);
            tempMusicAlbum.setPerformer(perfomer);
        }
        if (str[i] == ' ' and pointPerformer != 0 and pointPerformer != i and pointGenre == 0)
        {
            pointGenre = i;
            MyString genre = str.substr(pointPerformer + 1, pointGenre - 1);
            tempMusicAlbum.setGenre(genre);
        }
        if (str[i] == ' ' and pointGenre != 0 and pointGenre != i and pointYearOfIssue == 0)
        {

            pointYearOfIssue = i;
            unsigned int tempYear = 0;
            MyString yearOfIssue = str.substr(pointGenre + 1, pointYearOfIssue - 1);
            for (unsigned int j = 0; j < yearOfIssue.getSize(); ++j)
            {
                tempYear *= 10;
                tempYear += (unsigned int)(yearOfIssue[j] - '0');
            }
            /*if (tempYear < 1 and tempYear>2019)
            {
                return tempMusicAlbum();
            }*/
            tempMusicAlbum.setYearOfIssue(tempYear);

            MyString tempTime;
            unsigned int tempPoint = 0;
            for (tempPoint = pointYearOfIssue + 1; str[tempPoint] != ':'; ++tempPoint) {}
            MyString tempMinutes = str.substr(pointYearOfIssue + 1, tempPoint - 1);
            MyString tempSeconds = str.substr(tempPoint + 1, str.getSize()-1);
            unsigned int tempTimeMinutes = 0;
            unsigned int tempTimeSeconds = 0;
            for (unsigned int j = 0; j < tempMinutes.getSize(); ++j)
            {
                tempTimeMinutes *= 10;
                tempTimeMinutes += (unsigned int)(tempMinutes[j] - '0');
            }
            for (unsigned int j = 0; j < tempSeconds.getSize(); ++j)
            {
                tempTimeSeconds *= 10;
                tempTimeSeconds += (unsigned int)(tempSeconds[j] - '0');
            }

            tempMusicAlbum.setTime(tempTimeMinutes * 60 + tempTimeSeconds);
            break;
        }
    }
    return tempMusicAlbum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    try
    {
        ifstream fileIn;
        fileIn.open("albums.txt");
        int nOfAlbums;
        fileIn >> nOfAlbums;
        Array <MusicAlbum> arrayOfAlbums(nOfAlbums);
        MyString strOfAlbom;
        fileIn.get();

        for (int i = 0; i < nOfAlbums; ++i)
        {
            fileIn >> strOfAlbom;
            arrayOfAlbums[i] = split(strOfAlbom);
        }

        for (int i = 0; i < nOfAlbums; ++i)
        {
            cout << arrayOfAlbums[i] << endl;
        }
        cout << endl;
        fileIn.close();
        ofstream fileOutSortedArray;
        fileOutSortedArray.open("outSortedArray.txt");

//        fileOutSortedArray << "Максимальный элемент в массиве: " << getMaxMinObjInArray(arrayOfAlbums, arrayOfAlbums.GetSize()).max << endl
//            << "Минимальный элемент в массиве: " << getMaxMinObjInArray(arrayOfAlbums, arrayOfAlbums.GetSize()).min << endl;
//        fileOutSortedArray << endl;

        MyList <MusicAlbum> listOfAlbums;
        for (int i = 0; i < nOfAlbums; ++i)
        {
            listOfAlbums.sortedInsertItem(arrayOfAlbums[i]);
        }
        ofstream outList;
        outList.open("outList.txt");
        listOfAlbums.outAll(outList);
        outList.close();

        selectionSort (arrayOfAlbums);
        for (int i = 0; i < nOfAlbums; ++i)
        {
            fileOutSortedArray << arrayOfAlbums[i] << endl;
        }
        fileOutSortedArray << endl;
        fileOutSortedArray.close();
    }
    catch (const char* message)
    {
        cerr << message << endl;
    }
}
        

6
dog
cat
ball
good
frog
hello
        
6
пес/собака
кот/кошка
мяч
хорошо
лягушка
привет

7
–ø–µ—Å/—Å–æ–±–∞–∫–∞
–∫–æ—Ç/–∫–æ—à–∫–∞
–º—è—á
—Ö–æ—Ä–æ—à–æ
–ª—è–≥—É—à–∫–∞
–ø—Ä–∏–≤–µ—Ç/–ø—Ä–∏–≤–µ—Ç—Å—Ç–≤–∏–µ
–∞—Ä–±—É–∑
