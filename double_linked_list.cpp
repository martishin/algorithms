#include <iostream>

using namespace std;


template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node() {
            next = nullptr;
            prev = nullptr;
        }

        Node(T data, Node *next = nullptr, Node *prev = nullptr)
            : data(data), next(next), prev(prev) {}
    };
    Node *front, *back;

public:
    int size;

    DoubleLinkedList() {
        front = nullptr;
        back = nullptr;
        size = 0;
    }

    ~DoubleLinkedList() {
        while (front != nullptr) {
            Node *ptr = front;
            front = front->next;
            delete ptr;
        }
        back = nullptr;
    }

    void push_front(T data) {
        if (size == 0) {
            front = new Node(data);
            back = front;
        } else {
            Node *ptr = new Node(data, front);
            front->prev = ptr;
            front = ptr;
        }
        ++size;
    }

    void push_back(T data) {
        if (size == 0) {
            front = back = new Node(data);
        } else {
            back = new Node(data, nullptr, back);
            back->prev->next = back;
        }
        ++size;
    }

    T pop_front() {
        if (size == 0) {
            throw runtime_error("List is empty");
        }

        Node *ptr = front;
        T data = front->data;

        if (front == back) {
            front = back = nullptr;
        } else {
            front = front->next;
            front->prev = nullptr;
        }

        --size;
        delete ptr;
        return data;
    }

    T pop_back() {
        if (size == 0) {
            throw runtime_error("List is empty");
        }

        Node *ptr = back;
        T data = back->data;

        if (front == back) {
            front = back = nullptr;
        } else {
            back = back->prev;
            back->next = nullptr;
        }

        --size;
        delete ptr;
        return data;
    }

    void insert(T data, int pos) {
        if (pos > size - 1) {
            throw runtime_error("Bad index");
        }

        if (pos == 0) {
            this->push_front(data);
        } else {
            Node *iptr = front;

            for (int i = 0; i < pos; ++i) {
                iptr = iptr->next;
            }

            Node *ptr = new Node(data, iptr, iptr->prev);

            iptr->prev->next = ptr;
            iptr->prev = ptr;
        }
        ++size;
    }

    void erase(int pos) {
        if (pos > size - 1) {
           throw runtime_error("Bad index");
        }

        if (pos == 0) {
            this->pop_front();
        } else if (pos == size - 1) {
            this->pop_back();
        } else {
            Node *ptr = front;

            for (int i = 0; i < pos; ++i) {
                ptr = ptr->next;
            }

            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;

            delete ptr;
        }

        --size;
    }

    void print() {
        Node *ptr = front;

        while (ptr) {
            cout << ptr->data << ' ';
            ptr = ptr->next;
        }
        cout << endl;
    }
};


int main() {
    int n;
    double d;

    DoubleLinkedList<double> dll;

    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        cin >> d;
        dll.push_back(d);
    }

    dll.insert(3, 2);
    dll.erase(0);

    dll.print();
}
