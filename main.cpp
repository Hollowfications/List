#include "list.h"
#include <exception>
#include <iostream>
#include <cstdlib>

using namespace std;
typedef int T;

int main() {
    List<T>* list = new List<T>();
    cout << "list constructor enabled, so isEmpty(): " << list->isEmpty() << endl;
    list->push_back(8);
    list->push_back(2);
    list->push_back(5);
    list->print();
    cout << endl << "3 elements were pushed (8 2 5), so isEmpty(): " << list->isEmpty() << endl;
    list->clear();
    list->print();
    cout << "after clearing, isEmpty(): " << " "<< list->isEmpty() << endl;
    int a, b, c, d, pos;
    cout << "enter four integer numbers: ";
    cin >> a >> b >> c >> d;
    list->push_back(a);
    list->push_back(b);
    list->push_back(c);
    list->push_back(d);
    system("cls");
    cout << "list is: ";
    list->print();
    cout << endl << "let's try delete element by it's position, enter position: " << endl;
    cin >> pos;
    while (pos > list->count || pos <= 0) {
        cout << "wrong number, try again: ";
        cin >> pos;
    }
    if (pos <= list->count) {
        list->eraseByPos(pos);
        list->print();
    }
    cout << endl << "let's try enter element by it's position, enter position: " << endl;
    cin >> pos;
    while ((pos > list->count + 1) || pos <= 0) {
        cout << "wrong number, try again: ";
        cin >> pos;
    }
    int val;
    cout << "enter value: ";
    cin >> val;
    if (pos <= list->count+1) {
        list->insertByPos(val, pos);
        list->print();
    }
    return 0;
}
