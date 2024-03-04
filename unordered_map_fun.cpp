#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <initializer_list>

struct Point {
  int x;
  int y;
  int z;
};
int main() {
    Point p{1, 2, 3};
    std::cout << "p: " << p.x << ", " << p.y << ", " << p.z << std::endl;
    std::initializer_list<Point> points{(1, 2, 3)};
    int a = (1, 2, 3);
    std::cout << a << std::endl;
    int i=1;
    for(auto p : points) {
        std::cout << "Point #" << i++ << ": " << p.x << ", " << p.y << ", " << p.z << std::endl;
    }
    std::pair<std::string, int> p1("hello", 1);
    std::unordered_map<std::string, int> um{
        {"hello", 1},
        {"world", 2},
    };
}

