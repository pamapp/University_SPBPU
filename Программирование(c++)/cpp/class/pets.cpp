#include <iostream>
#include <string>
#include <vector>
using namespace std;
//class Pet
//{
//    public:
//
//    virtual string name() = 0;
//    virtual string voice() = 0;
//};
//
//class Cat : public Pet
//{
//    private:
//        string catName;
//        string catVoice;
//
//    public:
//        Cat(string cN, string cV): catName(cN), catVoice(cV){}
//
//        string name()
//        {
//            return catName;
//        }
//        string voice()
//        {
//            return catVoice;
//        }
//};
//
//class Dog : public Pet
//{
//    private:
//        string dogName;
//        string dogVoice;
//    public:
//        Dog(string dN, string dV) : dogName(dN), dogVoice(dV){}
//        string name()
//            {
//                return dogName;
//            }
//            string voice()
//            {
//                return dogVoice;
//            }
//};
//
//class FamillyPets : public Pet
//{
//    private:
//        int maxNumberOfPets = 0;
//        int realNumberOfPets = 0;
//        Pet** pPets = new Pet*[maxNumberOfPets];
//
//    public:
//        FamillyPets( int maxNum, int realNum) : maxNumberOfPets(maxNum), realNumberOfPets(realNum){}
//
//        string name()
//        {
//            for (int i = 0; i < realNumberOfPets; i++)
//            {
//                cout << pPets[i] -> name() << endl;
//            }
//        }
//
//        string voice()
//        {
//            for (int i = 0; i < realNumberOfPets; i++)
//            {
//                cout << pPets[i] -> voice() << endl;
//            }
//        }
//        unsigned int size() const
//        {
//            return realNumberOfPets;
//        }
//        friend ostream& operator<<(ostream& out,FamillyPets& pPets);
//        //friend istream& operator>>(istream& in, FamillyPets& anim);
//};
////friend istream& operator>>(istream& in, FamillyPets& anim)
////{
////
////}
//ostream& operator<<(ostream& out, FamillyPets& pets)
//{
////
////    for (int i = 0; i < pets.size(); i++)
//    out << "Кличка питомца: " << pets.name() << endl << "Голос питомца" << endl;
//}
//// << pets.voice()
//
//int main()
//{
//    //для объектов cat и dog
//    cout << "==================================" << endl;
//    cout << "JUST CAT!" << endl;
//    Cat cat("musya", "myau");
//    cout << "Cat name: " << cat.name() << endl;
//    cout << "Cat voice: " << cat.voice() << endl;
//
//    cout << endl;
//
//    cout << "JUST DOG!" << endl;
//    Dog dog("charly", "gav");
//    cout << "Dog name: " << dog.name() << endl;
//    cout << "Dog voice: " << dog.voice() << endl;
//
//    cout << endl;
//
//    //через указатели pCat и pDog
//    cout << "==================================" << endl;
//    cout << "POINTER CAT!" << endl;
//    Cat *pCat = &cat;
//    cout << "Cat name: " << pCat-> name() << endl;
//    cout << "Cat voice: " << pCat-> voice() << endl;
//
//    cout << endl;
//
//    cout << "POINTER DOG!" << endl;
//    Dog *pDog = &dog;
//    cout << "Dog name: " << pDog-> name() << endl;
//    cout << "Dog voice: " << pDog-> voice() << endl;
//
//    cout << endl;
//
//    //через указатель pPet, загружая cat и dog
//    cout << "==================================" << endl;
//    cout << "POINTER PET CAT!" << endl;
//    Pet* pPet;
//    pPet = &cat;
//    cout << "Cat name: " << pPet -> name() << endl;
//    cout << "Cat voice: " << pPet -> voice() << endl;
//
//    cout << endl;
//
//    cout << "POINTER PET DOG!" << endl;
//    pPet = &dog;
//    cout << "Dog name: " << pPet-> name() << endl;
//    cout << "Dog voice: " << pPet-> voice() << endl;
//
//    cout << "==================================" << endl;
//
//
////    pPet = &dog, &cat;
////    cout << pPet-> name() << endl;
//
//    int maxN = 0;
//    cout << "Enter max number of family pets" <<  endl;
//    cin >> maxN;
//    FamillyPets fam(maxN, 3);
//    cout << fam.name() << endl;
//
//
////    Pet *pPet = &pet;
////    string cName1;
////    string cVoice1;
////    cin >> cName1 >> cVoice1;
////    Cat yourCat(cName1, cVoice1);
////    cout << "Your cat name: " << endl;
////    yourCat.getName();
////    cout << "Your cat voice: " << endl;
////    yourCat.getVoice();
////
//
//
//    return 0;
//}
//
//
class Human
{
public:
    virtual string name() = 0;
    virtual string surname() = 0;
    virtual int age() = 0;
};

class Child : public Human
{
private:
    string childName;
    string childSurname;
    int childAge;
public:
    Child(string childName, string childSurname, int childAge): childName(childName), childSurname(childSurname), childAge(childAge){}
    
    string name()
    {
        return childName;
    }
    
    string surname()
    {
        return childSurname;
    }
    
    int age()
    {
        return childAge;
    }
    
    void setName(string name_)
    {
        childName = name_;
    }
    
    void setSurname(string surname_)
    {
        childSurname = surname_;
    }
    
    void setAge(int age_)
    {
        childAge = age_;
    }
    
    void printChild()
    {
        cout << "Name: " << name() << endl << "Surname: " << surname() << endl << "Age: " << age() << endl;
    }
    friend ostream& operator<<(ostream &out, Child &child);
};

int main()
{
    int age1;
    string surname1;
    string name1;
    
    int age2;
    string surname2;
    string name2;
    
    Child firstChild(name1, surname1, age1);
    
    Child secondChild(name2, surname2, age2);
    
    cout << "Enter first child name: ";
    cin >> name1;
    firstChild.setName(name1);
    cout << "Enter first child surname: ";
    cin >> surname1;
    firstChild.setSurname(surname1);
    cout << "Enter first child age: ";
    cin >> age1;
    firstChild.setAge(age1);
    
    cout << "Enter second child name: ";
    cin >> name2;
    secondChild.setName(name2);
    cout << "Enter second child surname: ";
    cin >> surname2;
    secondChild.setSurname(surname2);
    cout << "Enter second child age: ";
    cin >> age2;
    secondChild.setAge(age2);
    
    firstChild.printChild();
    cout << endl;
    secondChild.printChild();

}
