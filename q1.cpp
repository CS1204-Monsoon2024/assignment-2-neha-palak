#include <iostream>
using namespace std;

struct Node {
    int data;
    unsigned long long hash;
    Node* next;
    Node(int x) : data(x), next(nullptr), hash(x) {}
};

class LinkedList {
    Node* head;
    static const int a = 31; // Base for polynomial rolling hash
    static const int m = 1e9 + 9; // Large prime number for modulo
public:
    LinkedList() : head(nullptr) {}

    void insert(int value) {
        if (!head) {
            head = new Node(value);
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new Node(value);
            current->next->hash = (current->hash * a + value) % m;
        }
    }

    bool isEqual(LinkedList& other) {
        Node* node1 = this->head;
        Node* node2 = other.head;
        while (node1 && node2) {
            if (node1->hash != node2->hash) return false;
            node1 = node1->next;
            node2 = node2->next;
        }
        return node1 == nullptr && node2 == nullptr;
    }
};

int main() {
    LinkedList list1, list2;
    list1.insert(1);
    list1.insert(2);
    list2.insert(1);
    list2.insert(2);
    cout << "Lists are equivalent: " << (list1.isEqual(list2) ? "Yes" : "No") << endl;
    return 0;
}