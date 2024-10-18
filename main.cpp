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

        // creates a pointer to Node and sets it to the head node. Represents a sort of iterator
        Node* temp = head;
        // traverses linked list until either the given position is reached or the end of the list is reached
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        // If the given position exceeds the size of the list then prints to console that the position exceeds list size.
        // Also doesn't insert the new node created earlier and returns function
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // assigns the next node pointer of newNode to that of the node after the found node at given position represented by temp
        newNode->next = temp->next;
        // assigns the previous node pointer of newNode to that of the node at given position represented by temp
        newNode->prev = temp;
        /* if the node stored at temp isn't the last node in the linked list, then the next node's previous pointer will be assigned to newNode
            otherwise if at end of the list newNode will be assigned as the tail of the linked list*/
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        // sets the next of the node before newNode to that of newNode
        temp->next = newNode;
    }

    // deletes the first node with the found given value
    // arguments: integer representing the value of node with value to delete
    void delete_val(int value) {
        // if list is empty return
        if (!head) return;
        // creates temp node to traverse list
        Node* temp = head;

        // traverses list until it finds the node with the value to be deleted
        while (temp && temp->data != value)
            temp = temp->next;
        // if value not found return
        if (!temp) return;

        // if temp is not head then derefrence next of the previous pointer and make it point to the next node of current temp node
        // if temp is head then derefrence head and set it to that of the pointer next of temp node
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        // if temp is not tail then rewire the nodes , if temp is tail the set tail to the node before temp
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;
        // deletes the temp node
        delete temp;
    }
    // deletes the node at given position
    // arguments: integer representing the value of node with value to delete
    void delete_pos(int pos) {
        // if list is empty print list is empty and return
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // if the given position is 1 or first node in linked list, call pop_front and return
        if (pos == 1) {
            pop_front();
            return;
        }

        // creates a temporary node pointer and sets it that of head
        Node* temp = head;

        // iterates through linked list, if position not found print not found and return
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }

        // checks again if temp doesn't exist in case it reaches end of linked list
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        // if the node was found and is tail of list then calls pop_back method and returns
        if (!temp->next) {
            pop_back();
            return;
        }

        // derefrence previous and nexts of nodes surrounding found node and rewires the list
        // then deletes the found node stored in temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // pushes a new node to the end of the linked list with given value
    // arguments: integer representing given value
    void push_back(int v) {
        //Dynamically allocates memory for new Node object with given value and sets pointer of newNode to that object
        Node* newNode = new Node(v);
        // if the list is empty sets the new node as head and tail of new list
        // otherwise sets the newNode to the right of tail and makes the previous node of newNode the former tail node
        // sets tail to newNode
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // pushes a new node to the beginning of the linked list with given value
    // arguments: integer representing given value
    void push_front(int v) {
        //Dynamically allocates memory for new Node object with given value and sets pointer of newNode to that object
        Node* newNode = new Node(v);
        // if the list is empty sets the new node as head and tail of new list
        // otherwise sets the newNode to the left of tail and makes the previous node of newNode the former head node
        // sets head to newNode
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // deletes the node at the front of linked list
    void pop_front() {
        // list is empty return and print to screen
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        // if list not empty create a pointer to head
        Node * temp = head;

        // if list doesn't contain only one element, change head to next node in list and derefrence previous pointer of new head node
        // if list is only one element derefrence head and tail
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        // delete old head node stored in temp
        delete temp;
    }

    void pop_back() {
         // list is empty return and print to screen
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        // if list not empty create a pointer to tail
        Node * temp = tail;
        // if list doesn't contain only one element, change previous node of tail to nullptr and derefrence old tail node
        // if list is only one element derefrence head and tail
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        // delete old tail node stored in temp
        delete temp;
    }

    //destructor deletes whole list
    ~DoublyLinkedList() {
        // goes through list deletes all nodes
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // prints linked list to screen
    void print() {
        // iterator node starting at head
        Node* current = head;
        // if list is empty print to screen and return
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        // itterates through list and prints the data stored in each node
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    // prints linked list to screen in reverse order from tail end
    void print_reverse() {
        // iterator node starting at tail
        Node* current = tail;

        // if list is empty print to screen and return
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        // iterates through list and prints data stored in each node
        // iterates by calling previous of each node until reaches head
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // prints every other node in the linked list
    void every_other_element()
    {
        // iterator node starting at head
        Node* current = head;

        // if list is empty print to screen and return
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        // iterates through list and prints data stored in each node
        // prints every other node, if the if first statement reaches too far which can cause overflow error, falls back on safety net and prints next element instead
        while (current) {
            cout << current->data << " ";
            if (current->next != nullptr)
                current = current->next->next;
            else
                current = current->next;
        }

        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList list;

    for (int i = 1; i <= 5; i++)
    {
        list.push_back(i);
    }

    list.every_other_element();

    return 0;
}
