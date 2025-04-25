#include <iostream>

class Node {
public:
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void add(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }

    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }

    void deleteAll() {
        Node* current = head;
        while (current != nullptr) {
            delete current;
            current = current->next; // 💥 Use-after-delete segfault!
        }
        head = nullptr;
    }
};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.print();
    list.deleteAll();
    return 0;
}