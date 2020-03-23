//---------------------------------------------------------------------
// Name: Saikiran Nuthakki
// Email: sqn5261@psu.edu
//
// Description: Reverse Polish Notation Calculator
//---------------------------------------------------------------------
#include <iostream>

using namespace std;

class ListNode// listnode class
{
private: // private member functions
    int data;
    ListNode* prev;
    ListNode* next;
    
public: // public memeber functions
    ListNode() { prev = next = NULL; } // ListNode default constructor
    ListNode(int d, ListNode* p, ListNode* n) { data = d; prev = p; next = n; }
    
    friend class List;
};

class List // list class
{
private: // private member functions
    ListNode* list_head;
    ListNode* list_tail;
    
public: // public member functions
    List() { list_head = list_tail = NULL; } //List constructor
    ~List() { clear(); } // List destructor
    
    bool isEmpty() { return list_head == NULL; } // isEmpty function
    bool contains(int value); // contains function
    
    void addToHead(int value); // addToHead Function
    void addToTail(int value);
    
    int head() { return list_head->data; }
    int tail() { return list_tail->data; }
    
    int removeHead();
    int removeTail();
    void clear();
};

bool List::contains(int value)
{
    ListNode *temp = list_head;
    while (temp != NULL && temp->data != value)
        temp = temp->next;
    
    return temp != NULL;
}

void List::addToHead(int value)
{
    if (isEmpty())
    {
        list_head = list_tail = new ListNode(value, NULL, NULL);
    }
    else
    {
        list_head = new ListNode(value, NULL, list_head);
        list_head->next->prev = list_head;
    }
}

void List::addToTail(int value)
{
    if (isEmpty())
    {
        list_head = list_tail = new ListNode(value, NULL, NULL);
    }
    else
    {
        list_tail = new ListNode(value, list_tail, NULL);
        list_tail->prev->next = list_tail;
    }
}

int List::removeHead()// function that removes the head
{
    int value = list_head->data;
    if (list_head == list_tail)
    {
        delete list_tail;
        list_head = list_tail = NULL;
    }
    else
    {
        list_head = list_head->next;
        delete list_head->prev;
        list_head->prev = NULL;
    }
    
    return value;
}

int List::removeTail()// function that removes the tail
{
    int value = list_head->data;
    if (list_head == list_tail)
    {
        delete list_tail;
        list_head = list_tail = NULL;
    }
    else
    {
        list_tail = list_tail->prev;
        delete list_tail->next;
        list_tail->next = NULL;
    }
    
    return value;
}

void List::clear() // clear function
{
    while (!isEmpty())
        removeTail();
}

class Stack // stack class
{
private: // private member functions
    List* list;
public: // public member functions
    Stack() { list = new List(); }
    ~Stack() { delete list;    }
    
    bool isEmpty() { return list->isEmpty(); } // isEmpty function
    void clear() { list->clear(); } // clear function
    void push(int data) { list->addToHead(data); } // push function
    int pop() { return list->removeHead(); } // pop function
    int top() { return list->head(); } // top function
};

