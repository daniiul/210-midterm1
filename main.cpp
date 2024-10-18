// COMSC-210 | Midterm 1 | Daniil Malakhov
// IDE used: Codeblocks
#include <iostream>
using namespace std;

// creates 4 constant integer variables
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// class of Doubly Linked List
class DoublyLinkedList {
private:
    // declares a private member structure called Node
    // Node contains:
    // an integer to represent the data stored by the node
    // A pointer to a node structure to represent the previous node in the linked list
    // A pointer to a node structure to represent the next node in the linked list
    /* An overloaded declaration of node that allows the node structure to be declared with a specified value integer,
        a pointer to a node structure representing previous node, and a pointer to a node structure representing next node.
        the overloaded Node. Both pointer to node objects have default arguments of nullptr*/
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    // a pointer to node representing the head of the linked list
    Node* head;
    // a pointer to node representing the tail of the linked list
    Node* tail;

public:
    // public default constructor that sets both head and tail pointers in Node to nullptr
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // inserts a node object after specified position and initializes it with given value
    // arguments: integer representing value to insert into new node, integer representing where new node must be placed after given position
    // returns: none
    void insert_after(int value, int position) {
        // if the given position value is less than 0 (which is invalid) will print stating user error and returning/stopping the function
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        //Dynamically allocates memory for new Node object with given value and sets pointer of newNode to that object
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning


    return 0;
}
