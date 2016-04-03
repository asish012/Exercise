#include <iostream>

struct Node
{
    explicit Node(int v) : _value(v), _next(nullptr) {}
    ~Node() { }

    int _value;
    Node* _next;
};

class Stack
{
public:
    Stack() : _size(0), _head(nullptr) {}
    ~Stack() {
        std::cout << "~Stack" << std::endl;
        while (_head)
            pop();
    }

    void push(int value);
    int pop();

    Node* _head;
    int _size;
};

void Stack::push(int value) {
    Node* node = new Node(value);
    node->_next = _head;

    _head = node;
    ++_size;

    std::cout << "push: " << value << std::endl;
    std::cout << "current size: " << _size << std::endl;
}

int Stack::pop() {
    if (not _head) { std::cout << "Empty Stack" << std::endl; return 0; }

    Node* temp = _head;
    _head = _head->_next;

    int value = temp->_value;
    delete temp;

    --_size;
    std::cout << "pop: " << value << std::endl;
    std::cout << "current size: " << _size << std::endl;

    return value;
}

int main()
{
    Stack stack;
    stack.push(5);
    stack.push(6);
    stack.push(7);
    stack.push(8);

    return 0;
}