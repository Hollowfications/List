#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <cstdlib>
#include <iterator>
#include <iostream>

template <class T>
class List {
public:
    List() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    List (T val) {
        head = nullptr;
        tail = nullptr;
        push(val);
    }

    ~List(){
        clear();
    }

    class Node{
    public:
        Node *next;
        Node *prev;
        T value;
        Node() {}
        Node(T val, Node* prior) : value(val) {
            this->prev = prior;
            this->prev = prior;
        }
        ~Node() {}
    };

    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
    public:
        friend class List;

        Iterator() {
            current_node = nullptr;
        }
        Iterator(List::Node* p) : current_node(p) {}

        ~Iterator() {}

        Node* getCurrent() {
            return current_node;
        }

        T operator*() {
            if (current_node == nullptr) {
                throw "Invalid pointer";
            }
            else {
                return current_node->value;
            }
        }

        Iterator operator++() {
            current_node = current_node->next;
            return (current_node == nullptr ? nullptr : *this);
        }

        Iterator operator--() {
            current_node = current_node->prev;
            return (current_node == nullptr ? nullptr : *this);
        }

        bool operator== (const Iterator &other) {
            return (current_node == other.current_node);
        }

        bool operator!= (const Iterator &other) {
            return (current_node != other.current_node);
        }

    private:
        Node *current_node;
    };

    bool isEmpty(){
        if (head == nullptr)
            return true;
        else
            return false;
    }

    void push_back(T val) {
        Node *new_node = new Node(val, tail);
        if (isEmpty()) {
            head = tail = new_node;
            count++;
        }
        else {
            new_node->next = tail->next;
            tail->next = new_node;
            tail->prev = tail;
            tail = new_node;
            count++;
        }
    }

    void push_begin(T val) {
        Node *new_node = new Node(val, nullptr);
        if (isEmpty()) {
            head = tail = new_node;
            count++;
        }
        else {
            new_node->prev = head->prev;
            new_node->next = head;
            head = new_node;
            head->prev = new_node->prev;
            count++;
        }
    }

    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(tail);
    }

    void print() {
        Iterator It = begin();
        if (head == tail && head != nullptr){
            std::cout << *It;
        }
        else if (head == nullptr)
            std::cout << "empty list\n";
        else if (head != tail) {
            while (It != end()) {
                std::cout << *It << " ";
                ++It;
            }
            std::cout << *end();
        }
    }
    void clear(){
        Node* ptr;
        while (head != tail) {
            ptr = head->next;
            delete head;
            head = ptr;
            count--;
        }
        if (head == tail) {
            head = tail = nullptr;
            count--;
        }
    }

    void eraseByPos(int pos) {
        int index = 1;
        Iterator It, PrevIt;
        It = begin();
        while (It != end() && index != pos) {
            PrevIt = It;
            ++It;
            index++;
        }
        if (It.getCurrent() == head) {
            Node* ptr = head;
            head = head->next;
            head->prev = nullptr;
            delete ptr;
            count--;
        }
        else if ((It.getCurrent() == head) && (It.getCurrent() == tail)) {
            clear();
        }
        else if (It.getCurrent() == tail) {
            Node* ptr = tail;
            tail = tail->prev;
            tail->next = ptr->next;
            delete ptr;
            count--;
        }
        else {
            Node* ptr = It.getCurrent();
            PrevIt.getCurrent()->next = ptr->next;
            delete ptr;
            count--;
        }
    }

    void insertByPos(T val, int pos) {
        int index = 1;
        Iterator It, PrevIt;
        It = begin();
        while (It != end() && index != pos) {
            PrevIt = It;
            ++It;
            index++;
        }
        if (It.getCurrent() == head) {
           push_begin(val);
        }
        else if ((It.getCurrent() == head) && (It.getCurrent() == tail)) {
            push_begin(val);
        }
        else if (It.getCurrent() == tail && pos == index) {
            Node* new_node = new Node(val, PrevIt.getCurrent());
            new_node->next = tail;
            tail->prev = new_node;
            PrevIt.getCurrent()->next = new_node;
            count++;
        }
        else if (pos != index && It.getCurrent() == tail) {
            push_back(val);
        }
        else if (pos == index && It.getCurrent() != tail && It.getCurrent() != head){
            Node* new_node = new Node(val, PrevIt.getCurrent());
            new_node->next = It.getCurrent();
            It.getCurrent()->prev = new_node;
            PrevIt.getCurrent()->next = new_node;
            count++;
        }
    }

    bool eraseByVal(T val) {
        Iterator It, PrevIt;
        It = begin();
        bool isIn = false;
        while (It != end() && *It != val) {
            PrevIt = It;
            ++It;
        }
        if (*It == val) {
            isIn = true;
            if (It.getCurrent() == head && It.getCurrent() != tail) {
                Node* ptr = head;
                head = head->next;
                //head->prev = nullptr;
                delete ptr;
                count--;
            }
            else if ((It.getCurrent() == head) && (It.getCurrent() == tail)) {
                clear();
            }
            else if (It.getCurrent() == tail && It.getCurrent() != head) {
                Node* ptr = tail;
                tail = tail->prev;
                tail->next = ptr->next;
                delete ptr;
                count--;
            }
            else {
                Node* ptr = It.getCurrent();
                PrevIt.getCurrent()->next = ptr->next;
                delete ptr;
                count--;
            }
        }

        if (isIn == false) {
            std::cout << "no such value in list\n";
        }
        return isIn;
    }

  Node *head;
  Node *tail;
  int count;
};
#endif // LIST_H_INCLUDED
