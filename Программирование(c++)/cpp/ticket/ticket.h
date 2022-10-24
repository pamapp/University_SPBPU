
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#ifndef TICKET_H
#define TICKET_H

using namespace std;

class Ticket
{   
    private:
        string _name;
        string _surname;
        string _distanation;
        string _date;
        string _flightNumber;
    public:
        // Ticket(): _name(NULL), _surname(NULL), _distanation(NULL), _date(NULL), _flightNumber(NULL){}

        Ticket(string name, string surname, string distanation, string date, string flightNumber)
        {
            this ->_name = name;
            this ->_surname = surname;
            this ->_distanation = distanation;
            this ->_date = date;
            this ->_flightNumber = flightNumber;
        }
        // Ticket(const Ticket& ob): _name(ob._name), _surname(ob._surname), _distanation(ob._distanation),
        //  _date(ob._date), _flightNumber(ob._flightNumber){}
        void setName(string &name)
        {
            this ->_name = name;
        }
        void setSurname(string &surname)
        {
            this ->_surname = surname;
        }
        // void setDistanation(const Ticket &distanation)
        // {
        //     this ->_distanation = distanation;
        // }
        // void setDate(const Ticket &date)
        // {
        //     this ->_date = date;
        // }
        // void setFlightNumber(const Ticket &flightNumber)
        // {
        //     this ->_flightNumber = flightNumber;
        // }
        string getName() const
        {
            return this-> _name;
        }
        string getSurname() const
        {
            return this-> _surname;
        }
        string getDistanation() const
        {
            return this-> _distanation;
        }
        string getDate() const
        {
            return this-> _date;
        }
        string getFlightNumber() const
        {
            return this-> _flightNumber;
        }
        void show_ticket()
        {
            string showName;
            string showSurname;
            string showDistanation;
            string showDate;
            string showFlightNumber;
            showName = this-> _name;
            showSurname = this-> _surname;
            showDistanation = this-> _distanation;
            showDate = this-> _date;
            showFlightNumber = this-> _flightNumber;
            cout << showName << endl << showSurname << endl << showDistanation << endl << showDate << endl << showFlightNumber << endl;

        }
        // ~Ticket(); 
        friend ostream & operator << (ostream & out, Ticket & object);
        friend istream & operator >> (istream & in, Ticket & object);
        ~Ticket()
        {
            delete [] &_name;
        }
};



#endif //TICKET_H










// class String 
// {
//     private:
//         char *str_;
//         int size_;
//     public:
//         String(): str_(0), size_(0) {} //конструктор без параметров 
//         String(const char *str)  //конструктор принимает строку текста
//         {
//             size_ = strlen(str);
//             str_ = new char[size_+ 1]; //массив размера char
//             strcpy(str_, str); //копирует содержимое str в pStr
//         }
//         int size()  
//         {
//             return size_;
//         }
//         ~String()  //диструктор
//         {
//             delete []str_;
//         }
//         friend ostream &operator << (ostream &os, String &obj); //перегрузка оператора вывода
//         friend istream &operator >> (istream &os, String &obj);
//         // friend bool isLetter (const String &obj, unsigned int& item);
//         // friend bool isCapital (const String &obj, unsigned int& item);
//         // friend bool isDash (const String &obj, unsigned int& item);
//         // friend bool isNameOrSurname (const String &obj, unsigned int& item);
//         // friend bool nsCheck (String &obj);
        
// };
// ostream &operator << (ostream &out, String &obj) //перегрузка оператора вывода
// {
//     for(int i = 0; i < obj.size(); i++)
//         out << obj.str_[i];
//     return out;
// }
// istream &operator >> (istream &in, String &obj) //перегрузка оператора ввода
// {
//     in >> obj.str_;
//     return in;
// }
