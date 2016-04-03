#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Node
{
    int value;
    Node* next;

    Node(int v) : value(v), next(nullptr) {}
};

class PriorityQueue
{
public:
    PriorityQueue() : _head(nullptr) {}
    PriorityQueue(std::vector<int> const& values);
    ~PriorityQueue();

    void add(int value);
    void delete_min();
    void print();
    void update_min();

private:
    Node* _head;
    Node** _min;
};

PriorityQueue::PriorityQueue(std::vector<int> const& values) : _head(nullptr) {
    for (int i: values) {
        add(i);
    }
}

PriorityQueue::~PriorityQueue() {
    while (_head) {
        delete_min();
    }

    delete _head;
    delete *_min;
}

void PriorityQueue::add (int value) {
    Node* n = new Node(value);

    // initial node
    if (not _head) {
        _head = n;
        _min = &_head;
        return;
    }

    // add new node at the end
    Node* current = _head;
    while (current->next) {
        current = current->next;
    }
    current->next = n;

    // check min
    if ((*_min)->value > value) {
        _min = &current->next;
    }
}

void PriorityQueue::delete_min() {
    if (not _head) { std::cout << "Nothing to delete, Empty List" << std::endl; return;}

    Node* temp = *_min;
    std::cout << "deleting: " << temp->value << std::endl;

    (*_min) = temp->next;

    delete temp;

    update_min();
}

void PriorityQueue::update_min() {
    if (not _head) { std::cout << "Can't set _min, Empty List" << std::endl; return; }

    _min = &_head;
    Node* current = _head;
    while (current->next) {
        if (current->value > current->next->value) {
            _min = &(current->next);
        }
        current = current->next;
    }
    std::cout << "new min: " << (*_min)->value << std::endl;
}

void PriorityQueue::print() {
    if (not _head) { printf("Empty List\n"); return; }

    Node* current = _head;
    while (current) {
        printf("%d\n", current->value);
        current = current->next;
    }

    if (_min and *_min)
        printf("Minimum is: %d\n", (*_min)->value);
}

int main() {
    // int array[] = {1, 2, 3, 4, 5};
    // std::vector<int> v(array, array + sizeof(array) / sizeof(int));
    // std::vector<int> v {1, 2, 3, 4, 5, 0, 6};
    // PriorityQueue pq(v);

    PriorityQueue pq;
    pq.add(5);
    pq.add(7);
    pq.add(1);
    pq.add(8);
    pq.add(2);
    pq.add(0);
    pq.print();
    pq.delete_min();
    pq.print();

    // std::cin.get();
    return 0;
}










