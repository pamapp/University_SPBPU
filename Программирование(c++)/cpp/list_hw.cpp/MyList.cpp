#include <iostream>
#include "MyList.h"

using namespace std;

MyList& MyList:: operator= (const MyList& list)
{
    Node* insert = list.head_;
    while (insert != nullptr)
    {
        this->push_back(insert->data_);
        insert = insert->next_;
    }
    return *this;
}

MyList& MyList::operator+= (int i)
{
    Node* current = head_;
    Node* insert = new Node(i);

    if (current == nullptr)
    {
        this->push_front(i);
        return*this;
    }
    else
    {
        if (insert->data_ < current->data_) //current less head
        {
           this->push_front(i);
           return*this;
        }
        while (current != nullptr) //movement
        {
            if (insert->data_ == current->data_)
            {
                cout << "You already have <" << i << "> in your list" << endl;
                return *this;
            }
            if (current->next_ == nullptr && insert->data_ > current->data_)
            {
                this->push_back(i);
                return *this;
            }
            else if (insert->data_ > current->data_ && insert->data_ < current->next_->data_)
            {
                insert->next_ = current->next_;
                current->next_ = insert;
                return *this;
            }
            
            current = current->next_;
        }
    }
    return *this;
}

ostream& operator<<(ostream &out, const MyList &list)
{
    for (MyList::Node *node = list.head_; node != 0; node = node->next_)
    {
        out << node->data_ << " ";
    }
    return out;
}

bool MyList::operator== (const MyList& list1)
{
    Node* current = head_;
    
    if (list1.head_ == nullptr && current == nullptr)  //bouth empty
    {
        cout << EMPTY_WARNING << endl;
        return 1;
    }
    
    else if ((list1.head_ == nullptr && current != nullptr) ||
        (list1.head_ != nullptr && current == nullptr)) //one of them empty
    {
        return 0;
    }
    
    else
    {
        Node* temp = list1.head_;
        while (temp->data_ == current->data_ && temp->next_ != nullptr && current->next_ != nullptr)
        {
            temp = temp->next_;
            current = current->next_;
        }
        
        if (temp->data_ == current->data_  && (temp->next_ == nullptr && current->next_ == nullptr))
            return 1;
        else
            return 0;
    }
}

MyList operator& (const MyList& list1, const MyList& list2)
{
    MyList list3;
    MyList::Node* current1 = list1.head_;
    MyList::Node* current2 = list2.head_;
    
    if (current1 == nullptr && current2 == nullptr) //both lists are empty
    {
        cout << EMPTY_WARNING;
        return list3;
    }
    else if (current1 == nullptr)
    {
        cout << "Warning: first list is empty!" << endl;
        return list3;
    }
    else if (current2 == nullptr)
    {
        cout << "Warning: seconsd list is empty!" << endl;
        return list3;
    }
    else
    {
        while (current1 != nullptr || current2 != nullptr)
        {
            if (current1 == nullptr || current2 == nullptr)
            {
                if (current1 == nullptr)
                {
                    current2 = nullptr;
                }
                else
                {
                   current2 = list2.head_;
                }
            }
            else
            {
                if (current1->data_ == current2->data_)
                {
                    list3.push_back(current1->data_);
                    current1 = current1->next_;
                }
                else if (current2->next_ == nullptr)
                {
                    current1 = current1->next_;
                    current2 = current2->next_;
                }
                else
                    current2 = current2->next_;
            }
        }
        
        if (list3.head_ != nullptr)
        {
            return list3;
        }
        else
        {
            cout << "Lists don't have same elements";
            return list3;
        }
    }
}

MyList operator| (const MyList& list1, const MyList& list2)
{
    MyList list3;
    MyList::Node* current1 = list1.head_;
    MyList::Node* current2 = list2.head_;

    if (current1 == nullptr && current2 == nullptr) //bouth lists are empty
    {
        cout << EMPTY_WARNING;
        return list3;
    }
    else if (current1 == nullptr)
    {
        cout << "Warning: first list is empty!" << endl;
        return list2;
    }
    else if (current2 == nullptr)
    {
        cout << "Warning: seconsd list is empty!" << endl;
        return list1;
    }
    else
    {
        while (current1 != nullptr || current2 != nullptr)
        {
            if (current1 == nullptr || current2 == nullptr)
            {
                if (current1 == nullptr)
                {
                    list3.push_back(current2->data_);
                    current2 = current2->next_;
                }
                else
                {
                    list3.push_back(current1->data_);
                    current1 = current1->next_;
                }
            }
            else
            {
                if (current1->data_ < current2->data_)
                {
                    list3.push_back(current1->data_);
                    current1 = current1->next_;
                }
                else if (current1->data_ > current2->data_)
                {
                    list3.push_back(current2->data_);
                    current2 = current2->next_;
                }
                else
                {
                    current1 = current1->next_;
                    current2 = current2->next_;
                }
            }
        }
        if (list3.head_ != nullptr)
        {
            return list3;
        }
        else
        {
            cout << "Lists don't have unic elements";
            return list3;
        }
    }
}

MyList MyList::merge (MyList& list)
{
    Node* current = head_;
    Node* insert = list.head_;

    if (insert == nullptr && current == nullptr) //bouth lists are empty
    {
        cout << EMPTY_WARNING;
        return* this;
    }
    else if (insert == nullptr) //empty insert list
    {
        return* this;
    }
    else if (current == nullptr) //empty current list
    {
        while (insert != nullptr)
        {
            this->push_back(insert->data_);
            insert = insert->next_;
        }
        list.head_ = nullptr;
        return* this;
    }
    else
    {
        while (current != nullptr || insert != nullptr)
        {
            if (current == nullptr || insert == nullptr)
            {
                if (current == nullptr)
                {
                    this->push_back(insert->data_);
                    delete insert;
                    insert = list.head_ = insert->next_;
                }
                else
                {
                    return *this;
                }
            }
            else
            {
                if (current->data_ > insert->data_)
                {
                    this->push_front(insert->data_);
                    insert = insert->next_;
                    current = head_;
                }
                else if (current->next_ == nullptr)
                {
                    if (current->data_ == insert->data_)
                    {
                        Node* tempo = insert->next_;
                        delete insert;
                        insert = list.head_ = tempo;
                    }
                    current = current->next_;
                }
                else if (current->data_ < insert->data_ && current->next_->data_ > insert->data_)
                {
                    Node* tempo = insert->next_;
                    insert->next_ = current->next_;
                    current->next_ = insert;
                    insert = list.head_ = tempo;
                    current = head_;
                }
                else if (current->data_ < insert->data_)
                {
                    current = current->next_;
                }
                else
                {
                    Node* tempo = insert->next_;
                    delete insert;
                    insert = list.head_ = tempo;
                    current = head_ ;
                }
            }
            
        }
        return*this;
    }
}










#include <iostream>
#include "MyList.h"
#include <cmath>
void countingSort(int* a, int n)
{
    int k = 0;
    int *b = new int [n]; //массив для отсортированного массива
    int *c = new int [k]; //вспомогательный массив счетчиков

    for (int i = 0; i < n; i++) //определим размер вспомогательного массива
    {
        if (a[i] > k)
            k = a[i];
    }

    for (int i = 0; i <= k; i++) //заполним вспомогательный массив нулями
    {
        c[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        c[a[i]] += 1;
    }

    for (int i = 1; i <= k; i++)
    {
        c[i] += c[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        b[c[a[i]]] = a[i];
        c[a[i]]--;
    }

    for (int x = 1; x <= n; x++)
    {
        std::cout << b[x] << " ";
    }
}

int radixFind(int a, int i)
{
    int result = 0;
    int temp = 0;

    result = pow(10, i);

    if (i == 0)
    {
        return a % 10;
    }
    else
    {
        temp = (a / result);
        return temp % 10;
    }

}

void radixSort(int* a, int n)
{
    int k = 9;
    int maxRadix = 0;
    int temp = 0;
    int count = 0;
    int d = 0;
    int checkRadix = 0;
    int *b = new int [n];
    int *c = new int [k + 1];

    checkRadix = a[0];

    while (checkRadix % 10 != 0)
    {
        maxRadix++;
        checkRadix /= 10;
    }

    for (int i = 0; i < maxRadix; i++)
    {
        for (int j = 0; j <= k; j++) //заполним вспомогательный массив нулями
        {
            c[j] = 0;
        }

        for (int j = 0; j < n; j++)
        {
            d = radixFind(a[j], i);
            c[d] += 1;
        }

        count = 0;

        for (int j = 0; j <= k; j++)
        {
            temp = c[j];
            c[j] = count;
            count += temp;
        }
        for (int j = 0; j < n; j++)
        {
            d = radixFind(a[j], i);
            b[c[d]] = a[j];
            c[d]++;
        }
    }

    for (int x = 0; x < n; x++)
    {
        std::cout << b[x] << " ";
    }
}

void insertSort(MyList *a, int n)
{
    MyList x;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        x = a[i];
        for (j = i - 1; j >= 0 && a[j].getData() > x.getData(); j--)
            a[j+1] = a[j];
        a[j+1] = x;
    }
}
void bucketSort(double *a, int n)
{
    MyList *b = new MyList [n];
   
    for (int i = 0; i < n; i++)
    {
        b[i] = new MyList();
    }

    for (int i = 1; i < n; i++)
    {
        int c = floor(a[i] * n);
        b[c].push_back(a[i]);
    }
    
    insertSort(b, sizeof(b)/sizeof(double));
    
    for (int x = 0; x < n; x++)
    {
        std::cout << x << ") " << b[x] << std::endl;
    }
}
int main()
{
//    0 0 2 2 3 3 3 5
//    13 22 32 34 42 43 51 51 55
    
//    int mass[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
//    int mass1[] = { 52, 22, 43, 34, 42, 51, 55, 13, 32, 36, 33 };
//    int mass2[] = { 329, 457, 657, 839, 436, 720, 355, 435, 345, 357, 720 };
    double massBucket[] = { 0.97, 0.73, 0.21, 0.96, 0.33, 0.97, 0.49, 0.90, 0.23, 0.11, 0.15, 0.78 };
    
//    std::cout << "----------------- COUNTING SORT TESTING -----------------" << std::endl;
//
//    countingSort(mass, sizeof(mass)/sizeof(int));
//
//    std::cout << std::endl;
//
//    countingSort(mass1, sizeof(mass1)/sizeof(int));
//
//    std::cout << std::endl;
//
//    countingSort(mass2, sizeof(mass2)/sizeof(int));
//
//    std::cout << '\n' << std::endl;
//
//    std::cout << "----------------- RADIX SORT TESTING -----------------" << std::endl;
//
//    radixSort(mass, sizeof(mass)/sizeof(int));
//
//    std::cout << std::endl;
//
//    radixSort(mass1, sizeof(mass1)/sizeof(int));
//
//    std::cout << std::endl;
//
//    countingSort(mass2, sizeof(mass2)/sizeof(int));
//
//    std::cout << '\n' << std::endl;
//
//    std::cout << "----------------- BUCKET SORT TESTING -----------------" << std::endl;
//
    bucketSort(massBucket, sizeof(massBucket)/sizeof(double));
    
    for (int i = 0; i < sizeof(massBucket)/sizeof(double); i++)
    {
        std::cout << floor(massBucket[i]) << std::endl;
    }
    std::cout << '\n' << std::endl;

    return 0;
}

// floor(n*(A[i]-a)/(b-a))
