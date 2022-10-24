#include <iostream>
#ifndef MyList_h
#define MyList_h

using namespace std;

const string EMPTY_WARNING = "Both lists are empty!";

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
    
    public:
        MyList() : head_(nullptr), tail_(nullptr) {}
    
        MyList(const MyList &list): head_(0), tail_(0)
        {
            Node *temp = list.head_;
            while(temp != 0)
            {
                this->push_back(temp->data_);
                temp = temp->next_;
            }
        }

        ~MyList()
        {
            while (head_ != nullptr)
            {
                Node* temp = head_->next_;
                delete head_;
                head_ = temp;
            }
        }

        void push_front(const int& data)
        {
            head_ = new Node(data, head_);
        }
        void push_back(const int& data)
        {
            if (head_ == nullptr)
            {
                head_ = new Node(data);
            }
            else
            {
                Node* current = head_;
                while(current->next_ != nullptr)
                {
                    current = current->next_;
                }
                current->next_ = new Node(data);
            }
        }
    
        MyList merge (MyList& list);
    
        friend ostream& operator<<(ostream &out, const MyList &list);

        MyList& operator+= (int i);
        MyList& operator= (const MyList& list);
    
        bool operator== (const MyList& list1);
    
        friend MyList operator& (const MyList& list1, const MyList& list2);
        friend MyList operator| (const MyList& list1, const MyList& list2);
};

#endif /* MyList_h */
