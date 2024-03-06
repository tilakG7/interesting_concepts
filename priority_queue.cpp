#include <iostream>
#include <queue>

using namespace std;


struct Human {
    double weight;
    double height_inches;
    char sex;
    int age;
};

struct BP {
    bool operator()(const Human &h1, const Human &h2) {
        return h1.age > h2.age;
    }
};

void printHuman(const Human& h) {
    cout << "-" << endl;
    cout << "Weight = " << h.weight << endl;
    cout << "Height (inches) = " << h.height_inches << endl;
    cout << "Sex = " << h.sex << endl;
    cout << "Age = " << h.age << endl;
}

int main() {
    cout << "Priority Queue" << endl;
    
    priority_queue<int> max_heap;
    max_heap.push(7);
    max_heap.push(6);
    max_heap.push(8);
    max_heap.push(9);
    max_heap.push(2);
    max_heap.push(3);
    max_heap.push(4);
    max_heap.push(5);
    max_heap.push(10);
    max_heap.push(1);

    int counter = 0;
    while(max_heap.size()) {
        cout << counter++ << ": " << max_heap.top() << endl;
        max_heap.pop();
    }

    priority_queue<Human, vector<Human>, BP> human_heap;
    human_heap.push({20.0, 24, 'M', 2});
    human_heap.push({50.0, 43, 'F', 6});
    human_heap.push({123.0, 65, 'F', 101});
    human_heap.push({156.0, 70, 'M', 24});
    human_heap.push({113.0, 64, 'F', 34});

    while(human_heap.size()) {
        printHuman(human_heap.top());
        human_heap.pop();
    }

    return 0;
}