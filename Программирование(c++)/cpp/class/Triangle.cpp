#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
class Point
{
private:
	int x_;
	int y_;
public:
	Point() : x_(0), y_(0) {}
	Point(int x, int y) : x_(x), y_(y) {}
	Point(const Point& ob) : x_(ob.x_), y_(ob.y_) {}
	~Point() {}

	void setXY(int x, int y)
	{
		x_ = x;
		y_ = y;
	}

	void setX(int x)
	{
		x_ = x;
	}

	void setY(int y)
	{
		y_ = y;
	}

	int getX() 
	{
		return x_;
	}

	int getY() 
	{
		return y_;
	}

	void show()
	{
		cout << x_ << "  " << y_ << endl;
	}

	friend bool isEqual(const Point &a, const Point &b);
	friend float getDistance(const Point &a, const Point &b);
};

bool isEqual(const Point& a, const Point& b) 
{
	return ((a.x_ == b.x_) && (a.y_ == b.y_));
}

float getDistance(const Point& a, const Point& b)
{
	return sqrt((float)((a.x_ - b.x_)* (a.x_ - b.x_)) + (float)((a.y_ - b.y_)*(a.y_ - b.y_)));
}

class Triangle
{
private:
	Point a_;
	Point b_;
	Point c_;
public:
	Triangle() : a_(0, 0), b_(0, 0), c_(0, 0) {}
	Triangle(Point a, Point b, Point c) : a_(a), b_(b), c_(c) {}
	Triangle(const Triangle& ob) : a_(ob.a_), b_(ob.b_), c_(ob.c_) {}
	~Triangle() {}

	void setA(Point a)
	{
		a_ = a;
	}
	void setB(Point b)
	{
		b_ = b;
	}
	void setC(Point c)
	{
		c_ = c;
	}

	Point getA()
	{
		return a_;
	}
	Point getB()
	{
		return b_;
	}
	Point getC()
	{
		return c_;
	}

	void show()
	{
		a_.show();
		b_.show();
		c_.show();
	}

	bool isTriangle()
	{
		return ((getDistance(a_, b_) + getDistance(b_, c_) > getDistance(a_, c_)) and
			(getDistance(a_, c_)) + getDistance(b_, c_) > getDistance(a_, b_) and
			(getDistance(a_, c_) + getDistance(a_, b_) > getDistance(c_, b_)));
	}
	float getPerimeter() const
	{
		return (getDistance(a_, b_) + getDistance(b_, c_) + getDistance(c_, a_));
	}

	friend bool isEqualSquare(const Triangle& figure1, const Triangle& figure2);
	friend void move(Triangle& figure, Point& K);
};

bool isEqualSquare(const Triangle& figure1, const Triangle& figure2)
{
	float p1 = figure1.getPerimeter() / 2;
	float p2 = figure2.getPerimeter() / 2;
	return (sqrt(p1 * (p1 - getDistance(figure1.a_, figure1.b_)) * (p1 - getDistance(figure1.b_, figure1.c_)) * (p1 - getDistance(figure1.c_, figure1.a_))) ==
		sqrt(p2 * (p2 - getDistance(figure1.a_, figure1.b_)) * (p2 - getDistance(figure1.b_, figure1.c_)) * (p2 - getDistance(figure1.c_, figure1.a_))));
}

void move(Triangle& figure, Point& K)
{
	Point a, b, c;
	a.setXY(figure.a_.getX() + K.getX(), figure.a_.getY() + K.getY());
	b.setXY(figure.b_.getX() + K.getX(), figure.b_.getY() + K.getY());
	c.setXY(figure.c_.getX() + K.getX(), figure.c_.getY() + K.getY());
	figure.setA(a);
	figure.setB(b);
	figure.setC(c);
}

int main()
{
	setlocale(LC_ALL, "rus");

	cout << "������� ���������� ����� - ";
	int x, y;
	cin >> x >> y;
	Point resultPoint(x, y);
	float minDistance = getDistance(Point(x, y), Point(0, 0));
	while (x != 0 && y != 0) 
	{
		if (getDistance(Point(x, y), Point()) < minDistance)
		{
			minDistance = getDistance(Point(x, y), Point());
			resultPoint = Point(x, y);
		}
		cin >> x >> y;
	}
	cout << "����� �� ���������� ���������� �� ������ ";
	resultPoint.show();

	x = 0;
	y = 0;
	cout << "������� ������ ����� ";
	cin >> x >> y;
	Point a(x, y);
	cout << "������� ������ ����� ";
	cin >> x >> y;
	Point b(x, y);

	cout << "������� ������ ����� ";
	cin >> x >> y;
	Point c(x, y);
	Triangle figure (a, b, c);
	figure.show();
	cout << figure.isTriangle() << endl;
	cout << figure.getPerimeter() << endl;
	Point q(2, 2);
	Point w(0, 0);
	Point z(2, 0);
	Triangle figureHelp(q, w, z);
	cout << isEqualSquare(figure, figureHelp) << endl;
	
	cout << "������� K ";
	cin >> x >> y;

	Point k(x, y);
	figure.show();
	move(figure, k);
	figure.show();
}