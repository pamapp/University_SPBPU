
#include <iostream>
#include <math.h>
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
        void setX (int x)
        {
            x_ = x;
        }
        void setY (int y)
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
            cout << x_ << " " << y_ << endl;
        }
        friend bool isEqual(const Point &a, const Point &b);
        friend double getDistance(const Point &a, const Point &b);
};

bool isEqual(const Point &a, const Point &b)
{
        if ((a.x_ == b.x_) && (a.y_ == b.y_))
            return true;
        return false;
}

double getDistance(const Point& a, const Point& b)
{
    return sqrt((double)((a.x_ - b.x_)* (a.x_ - b.x_)) + (double)((a.y_ - b.y_)*(a.y_ - b.y_)));
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
    
        void setA (Point a)
        {
            a_ = a;
        }
        void setB (Point b)
        {
            b_ = b;
        }
        void setC (Point c)
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
        bool isTriangle ()
        {
            if ((getDistance(a_, c_) + getDistance(b_, c_) > getDistance(a_, b_)) and
            (getDistance(a_, b_) + getDistance(b_, c_) > getDistance(a_, c_)) and
            (getDistance(a_, c_) + getDistance(a_, b_) > getDistance(c_, b_)))
            {
                return true;
            }
            return false;
        }
        double getPerimeter () const
        {
            return (getDistance(a_, b_) + getDistance(b_, c_) + getDistance(c_, a_));
        }
        friend bool isEqualSquare(const Triangle& firstFigure, const Triangle& secondFigure);
        friend void move(Triangle& figure, Point& k);
};

bool isEqualSquare(const Triangle& firstFigure, const Triangle& secondFigure)
{
    double p1 = firstFigure.getPerimeter() / 2;
    double p2 = secondFigure.getPerimeter() / 2;
    return (sqrt(p1 * (p1 - getDistance(firstFigure.a_, firstFigure.b_)) *
                 (p1 - getDistance(firstFigure.b_, firstFigure.c_)) *
                 (p1 - getDistance(firstFigure.c_, firstFigure.a_))) ==
            sqrt(p2 * (p2 - getDistance(firstFigure.a_, firstFigure.b_)) *
                 (p2 - getDistance(firstFigure.b_, firstFigure.c_)) *
                 (p2 - getDistance(firstFigure.c_, firstFigure.a_))));
}

void move(Triangle& figure, Point& k)
{
    Point a;
    Point b;
    Point c;
    a.setXY(figure.a_.getX() + k.getX(), figure.a_.getY() + k.getY());
    b.setXY(figure.b_.getX() + k.getX(), figure.b_.getY() + k.getY());
    c.setXY(figure.c_.getX() + k.getX(), figure.c_.getY() + k.getY());
    figure.setA(a);
    figure.setB(b);
    figure.setC(c);
}
int main()
{
    int x = 0;
    int y = 0;
    cout << "Enter the coordinates of the vertex A:" << endl;
    cin >> x >> y;
    Point a(x, y);
    cout << "Enter the coordinates of the vertex B" << endl;
    cin >> x >> y;
    Point b(x, y);
    cout << "Enter the coordinates of the vertex A" << endl;
    cin >> x >> y;
    Point c(x, y);
    cout << endl;
    
    Triangle figure (a, b, c);
    cout << "Figure coordinates:" << endl;
    figure.show();
    cout << endl;
    
    cout << "Is it a triangle?" << endl;
    cout << figure.isTriangle() << endl;
    cout << endl;
    cout << "Figure perimeter: " << endl;
    cout << figure.getPerimeter() << endl;
    cout << endl;
    
    Point q(5, 5);
    Point w(1, 1);
    Point z(3, 0);
    Triangle constFigure(q, w, z);
    cout << "Are the areas equal?" << endl;
    cout << isEqualSquare(figure, constFigure) << endl;
    cout << endl;
    
    cout << "How many K do you want to move the figure?" << endl;
    cin >> x >> y;
    cout << endl;
    Point k(x, y);
    move(figure, k);
    cout << "The resulting figure:" << endl;
    figure.show();
    return -1;
}

 
