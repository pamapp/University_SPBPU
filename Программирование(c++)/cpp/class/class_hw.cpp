
#include <iostream>
#include <math.h>

using namespace std;
class Triangle;
class Point 
{
    private:
        int x_;
        int y_; 
    public:
        Point(int x = 0,int y = 0)
        {
            this->x_ = x;
            this->y_ = y;
        } 
        void setX (int x)
        {
            this->x_ = x; 
        }
        void setY (int y) 
        {
            this->y_ = y; 
        }
        int getX() const
        {
            return this->x_;
        }
        int getY() const
        {
            return this->y_;
        }
        void show()
        {
            int showX;
            int showY;
            showX = this->x_;
            showY = this->y_;
            cout << showX << " " << showY << endl;
        }
        friend bool isEqual(const Point &x_, const Point &y_);
        friend double getDistance(const Point a, const Point b);

//        friend Point operator+(const Point &x_, const Point &y_);
        ~Point(){}
        

};
//Point operator+(const Point &x_, const Point &y_)
//{
//    return (x_.getX() + y_.getY());
//}
bool isEqual(const Point &x_, const Point &y_)
{
    if ((x_.getX() == y_.getX()) && (x_.getY() == y_.getY()))
        return true;
    return false;
}

double getDistance(const Point a, const Point b)
{
    return sqrt(((b.getX()-a.getX())*(b.getX()-a.getX()))+((b.getY()-a.getY())*(b.getY()-a.getY())));
}

int main()
{
    Point a;
    Point b;
    int x1;
    int y1;
    int x2;
    int y2;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    a.setX(x1);
    a.setY(y1);
    b.setX(x2);
    b.setY(y2);
    cout << endl;
    while ((a.getX() != 0 and a.getY() != 0) or (b.getX() != 0 and b.getY() != 0))
    {
        cin >> x1 >> y1;
        a.setX(x1);
        a.setY(y1);
        cout << "The same:" << isEqual(x1, y1) << endl;
        cin >> x2 >> y2;
        b.setX(x2);
        b.setY(y2);
        cout << "The same:" << isEqual(x2, y2) << endl;
        cout << "The distance bitween two points: " << getDistance(a,b) << endl;

    }
//    cout << Point(x1, y1);

    return -1;
}

 
