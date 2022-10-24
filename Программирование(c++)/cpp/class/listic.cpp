#include <iostream>

using namespace std;

class MyList
{
    private:
        struct Node
        {
            int data_;
            Node* next_;
            Node(const int& data, Node* next = nullptr) : data_(data), next_(next) {}
        };

        Node* head_ = nullptr;
        Node* tail_ = nullptr;
    
        void insertHead(Node* x)
        {
            x->next_ = head_;
            if (head_ == nullptr)
                tail_ = x;
            head_ = x;
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
    
    public:
        MyList() : head_(nullptr), tail_(nullptr) {}

        ~MyList()
        {
            while (head_ != nullptr)
            {
                Node* temp = head_->next_;
                delete head_;
                head_ = temp;
            }
        }
    
        void push_front(const int& data) //add element in the beginning
        {
            head_ = new Node(data, head_);
        }
    
        void push_back(const int& data) //add element in the end
        {
            if (head_ == nullptr)
            {
                head_ = new Node(data);
            }
            else
            {
                Node* current = head_;
                while(current->next_ != nullptr) //move pointer to end of list
                {
                    current = current->next_;
                }
                current->next_ = new Node(data);
            }
        }
        MyList& operator+= (int i)
        {
            Node* insert = new Node(i, head_);
            head_ = insert;
            return *this;
        }

        friend bool operator ==(const MyList& list1, const MyList& list2);
        friend void operator& (MyList& list1, MyList& list2);
        friend ostream& operator<<(ostream &out, MyList &list);

};

bool operator== (const MyList& list1, const MyList& list2)
{
    if (list1.head_ == nullptr && list2.head_ == nullptr)  //bouth empty
    {
        return 1;
    }
    
    else if ((list1.head_ == nullptr && list2.head_ != nullptr) ||
        (list1.head_ != nullptr && list2.head_ == nullptr)) //one of them empty
    {
        return 0;
    }
    
    else
    {
        MyList::Node* temp1 = list1.head_;
        MyList::Node* temp2 = list2.head_;
        while (temp1->data_ == temp2->data_ && temp1->next_ != nullptr && temp2->next_ != nullptr)
        {
            temp1 = temp1->next_;
            temp2 = temp2->next_;
        }
        if (temp1->data_ == temp2->data_)
            return 1;
        else
            return 0;
    }
}
//void operator& (MyList& list1, MyList& list2)
//{
//
//    MyList::Node*
//    while ()
//    list1.merge(list2);
//}
ostream& operator<<(ostream &out, MyList &list)
{
    for (MyList::Node *node = list.head_; node != 0; node = node->next_)
    {
        out << node->data_ << " ";
    }
    return out;
}

int main ()
{
    ПРОВЕРКА СРАВНЕНИЯ

    MyList list1;
    MyList list2;
    
    list1 += 2;
    list2 += 5;
    
    list1 += 1;
    list2 += 1;
    
    list1+=5;
    list2+=6;
    
    list1+=6;
    list2+=6;
    
    cout << list1 << endl;
    cout << list2 << endl;
    
    if (list1 == list2)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    
    return 0;
}

//        void merge(const int& data)
//        {
//            Node* current = head_;
//            Node* insert = new Node(data);
//
//            if (current == nullptr) //empty list
//            {
//                this->push_front(data);
//                return;
//            }
//
//            if (data < current->data_) //current less head
//            {
//                this->push_front(data);
//                return;
//            }
//
//            if (data == current->data_) //current is equal to the head
//            {
//                cout << "You already have <" << data << "> in your list" << endl;
//                return;
//            }
//
//            if (current->next_ == nullptr) //there is no element after the head
//            {
//                this->push_back(data);
//                return;
//            }
//
//            while (current->next_->data_ <= data) //movement
//            {
//                current = current->next_;
//                if (current->data_ == data)
//                {
//                    cout << "You already have <" << data << "> in your list" << endl;
//                    return;
//                }
//                if (current->next_ == nullptr)
//                {
//                    current->next_ = insert;
//                    this->insertTail(insert);
//                    return;
//                }
//            }
//
//            insert->next_ = current->next_;
//            current->next_ = insert;
//            return;
//        }
//

//ПРОВЕРКА ДОБАВЛЕНИЯ И СОРТИРОВКИ

//    MyList list;
//
//    list += 5;
//    cout << list << endl;
//
//    list += 3;
//    cout << list << endl;
//
//    list += 1;
//    cout << list << endl;
//
//    list.merge(2);
//    cout << list << endl;
//
//    list.merge(4);
//    cout << list << endl;
//
//    list.merge(3);
//    cout << list << endl;



//ПРОВЕРКА СРАВНЕНИЯ

//MyList list1;
//MyList list2;
//
//list1 += 2;
//list2 += 5;
//
//list1 += 1;
//list2 += 1;
//
//list1+=5;
//list2+=6;
//
//list1+=6;
//list2+=6;
//
//cout << list1 << endl;
//cout << list2 << endl;
//
//if (list1 == list2)
//{
//    cout << "true" << endl;
//}
//else
//{
//    cout << "false" << endl;
//}
