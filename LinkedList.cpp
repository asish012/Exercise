#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Node
{
    unsigned int value;
    Node* next;

    Node(unsigned int v) : value(v), next(nullptr) {}
};

class LinkedList
{
public:
    LinkedList() : _head(nullptr), _tail(nullptr) {}
    LinkedList(std::vector<unsigned int> const& values);
    ~LinkedList() { /* CLEAN UP */ }

    void push_back(unsigned int value);
    void print();

private:
    Node* _head;
    Node* _tail;
};

LinkedList::LinkedList(std::vector<unsigned int> const& values) : _head(nullptr), _tail(nullptr) {
    for (unsigned int i: values) {
        push_back(i);
    }
}

void LinkedList::push_back (unsigned int value) {
    Node* temp = new Node(value);
    if (not _head) {
        _head = temp;
        _tail = _head;
        return;
    }
    _tail->next = temp;
    _tail = _tail->next;
}

void LinkedList::print() {
    if (not _head) { std::cout << "Empty List" << std::endl; return; }

    Node* current = _head;
    while (current) {
        std::cout << current->value << std::endl;
        current = current->next;
    }
}

int main() {
    // int array[] = {1, 2, 3, 4, 5};
    // std::vector<unsigned int> v(array, array + sizeof(array) / sizeof(unsigned int));
    std::vector<unsigned int> v {1, 2, 3, 4, 5};

    LinkedList list(v);
    list.print();

    // std::cin.get();
    return 0;
}