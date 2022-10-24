#include <iostream>
#include <string>
using namespace std;
class Ticket
{
	friend string dogType (const Dogs&, int weight);
	private:
		string name;
        string name;
		int weight;
	public:
		Dogs(string n = "", int w = 0)
		{
			name = n;
			weight = w;
		}
		void setWeight (int w)
		{
			if (w > 1 and w < 30)
				weight = w;
		}
		void setName (string n)
		{
			name = n;
		}
		int getWeight ()
		{
			return weight;
		}
		string getName ()
		{
			return name;
		}
};

string dogType (const Dogs&, int weight)
{
	if (weight > 10)
		return "Oh, shit. You're big boy!";
	return "Uti-Puti";
}
int main ()
{
	int weight1, weight2;
	string name1, name2;
	Dogs doggyFirst;
	Dogs doggySecond;
	doggyFirst.setName(name1);
	doggyFirst.setWeight(weight1);
	doggySecond.setName(name2);
	doggySecond.setWeight(weight2);
	cout << "Enter the doggy's names!" << endl;
	cin >> name1 >> name2;
	cout << "Enter the doggy's weights!" << endl;
	cin >> weight1 >> weight2;
	cout << name1 << " " << dogType(doggyFirst, weight1) << endl;
	cout << name2 << " " <<dogType(doggySecond, weight2) << endl;
	return 0;

}
