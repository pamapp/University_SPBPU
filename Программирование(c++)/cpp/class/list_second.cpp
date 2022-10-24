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
                    if (current->next_ == nullptr and insert->data_ > current->data_)
                    {
                        this->push_back(i);
                        return *this;
                    }
                    if (insert->data_ > current->data_ and insert->data_ < current->next_->data_)
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
    
        bool operator== (const MyList& list1)
        {
            Node* current = head_;
            
            if (list1.head_ == nullptr and current == nullptr)  //bouth empty
            {
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
        friend::ostream& operator<<(ostream &out, const MyList &list)
        {
            for (MyList::Node *node = list.head_; node != 0; node = node->next_)
            {
                out << node->data_ << " ";
            }
            return out;
        }
    
        friend MyList operator& (const MyList& list1, const MyList& list2);

};

MyList operator& (const MyList& list1, const MyList& list2)
{
    MyList result;
    if (list1.head_ == nullptr && list1.tail_ == nullptr && list2.head_ == nullptr && list2.tail_ == nullptr)
    {
        return result;
    }
    else
    {
        MyList::Node* now1 = list1.head_;
        MyList::Node* now2 = list2.head_;
        while (now1 != nullptr && now2 != nullptr)
        {
            if (now1->data_ == now2->data_)
            {
                MyList::Node* newNode = new MyList::Node(now1->data_, nullptr);
                if (result.head_ == nullptr && result.tail_ == nullptr)
                {
                    result.head_ = newNode;
                    result.tail_ = result.head_;
                }
                else
                {
                    result.tail_->next_ = newNode;
                    result.tail_ = result.tail_->next_;
                }
                now1 = now1->next_;
                now2 = now2->next_;
            }
        }
        return result;
    }
}

int main ()
{
    MyList list3;
    MyList list1;
    MyList list2;
    
    list1 += 3;
    cout << list1 << endl;

    list1 += 1;
    cout << list1 << endl;

    list2 += 3;
    cout << list2 << endl;

    list2 += 1;
    cout << list2 << endl;

    cout << "First list: " << list1 << endl;
    cout << "Second list: " << list2 << endl;
    list3 = list1 & list2;
    cout << "Third list: " << list3 << endl;
}
