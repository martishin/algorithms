#include <iostream>

using namespace std;


template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node *next;
    };
    Node *front, *back;

public:
    Queue() {front = nullptr; back = nullptr;}

    void push(T data) {
        Node *ptr = new Node;
        ptr->data = data;
        ptr->next = nullptr;

        if (front == nullptr) {
            front = ptr;
            back = ptr;
        } else {
            back->next = ptr;
            back = ptr;
        }
    }

    T pop() {
        if (front == nullptr) {
            throw runtime_error("Queue is empty");
        }

        Node *ptr = front;
        T data = ptr->data;

        if (front == back) {
            front = nullptr;
            back = nullptr;
        } else {
            front = front->next;
        }

        delete ptr;
        return data;
    }

    void print() {
        Node *ptr = front;

        while (ptr) {
            cout << ptr->data << ' ';
            ptr = ptr->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (front != nullptr) {
            Node *ptr = front;
            front = front->next;
            delete ptr;
        }
        back = nullptr;
    }
};


int main() {
    int n;
    double d;

    Queue<double> q;

    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        cin >> d;
        q.push(d);
    }

    for (size_t i = 0; i < n; ++i) {
        cout << q.pop() << endl;
    }
}
