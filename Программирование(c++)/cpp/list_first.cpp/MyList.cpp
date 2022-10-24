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

