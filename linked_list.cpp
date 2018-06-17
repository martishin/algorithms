#include <iostream>

using namespace std;


struct Node {
    int data;
    Node *next;

    Node(int data, Node *next = nullptr)
        : data(data), next(next) {}
};


class SinglyLinkedList {
private:
    Node *head, *tail;
    size_t size_;

public:
    SinglyLinkedList(Node *head = nullptr, Node *tail = nullptr, size_t size_ = 0)
        : head(head), tail(tail), size_(size_) {}

    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node *current = head;
            head = head->next ;
            delete current;
        }
        tail = nullptr;
    }

    int front() {
        if (head == nullptr)
            throw runtime_error("List is empty");
        return head->data;
    }

    int back() {
        if (tail == nullptr)
            throw runtime_error("List is empty");
        return tail->data;
    }

    size_t size() {
        return size_;
    }

    void push_front(int data) {
        head = new Node(data, head);

        if (head == nullptr)
            tail = head;

        ++size_;
    }

    void pop_front() {
        if (head == nullptr)
            throw runtime_error("List is empty");

        Node *current = head;
        head = head->next;

        if (head == nullptr)
            tail = nullptr;

        delete current;
    }

    void push_back(int data) {
        Node *current = new Node(data);

        if (tail == nullptr) {
            head = tail = current;
        } else {
            tail->next = current;
            tail = current;
        }

        ++size_;
    }

    void pop_back() {
        if (tail == nullptr)
            throw runtime_error("List is empty");

        Node *current = head;
        Node *previous = nullptr;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        tail = previous;
        tail->next = nullptr;

        delete current;
    }

    void insert(int data, int position) {
        if (position > size_ - 1)
            throw out_of_range("Bad index");

        if (position == 0)
            this->push_front(data);
        else if (position == size_ - 1)
            this->push_back(data);
        else {
            Node *next = head;
            Node *previous = nullptr;

            for (size_t i = 0; i < position; ++i) {
                previous = next;
                next = next->next;
            }

            Node *current = new Node(data, next);
            previous->next = current;
        }

        ++size_;
    }

    void erase(int position) {
        if (position > size_ - 1)
            throw out_of_range("Bad index");

        if (position == 0)
            this->pop_front();
        else if (position == size_ - 1)
            this->pop_back();
        else {
            Node *current = head;
            Node *previous = nullptr;

            for (size_t i = 0; i < position; ++i) {
                previous = current;
                current = current->next;
            }

            previous->next = current->next;
            delete current;
        }

        --size_;
    }

    void reverse() {
        Node *previous = nullptr;
        Node *current = head;
        Node *next = nullptr;

        tail = head;

        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    void print() {
        Node *current = head;

        while (current != nullptr) {
            cout << current->data << ' ';
            current = current->next;
        }

        cout << endl;
    }
};


int main() {
    SinglyLinkedList linked_list;

    linked_list.push_back(1);
    linked_list.push_back(2);
    linked_list.insert(3, 1);
    linked_list.push_front(4);
    linked_list.erase(2);
    linked_list.print();

    linked_list.reverse();
    linked_list.print();

    return 0;
}
