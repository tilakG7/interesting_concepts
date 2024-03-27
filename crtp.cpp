#include <iostream>
#include <cmath>

using namespace std;

template<typename Derived>
class Shape {
public:
    double area() const {
        return static_cast<const Derived*>(this)->area();
    }
private:
};

class Circle : public Shape<Circle> {
private:
    double radius;
public:
    explicit Circle(double r) : radius(r) {}
    double area() const {
        return M_PI * radius * radius; 
    }

};

class Square : public Shape<Square> {
private:
    double side_len;
public:
    explicit Square(double len) : side_len(len) {}
    double area() const {
        return side_len * 4;
    }
};

int main() {
    Circle c(10.0);
    Square s(100.0);
    cout << "Circle area = " << c.area() << endl;
    cout << "Square area = " << s.area() << endl;
}