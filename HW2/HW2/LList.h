#ifndef _LList_H_
#define _LList_H_
#include <iostream>


template <typename T> struct ListItem
{
    T item;
    ListItem<T>* next = nullptr;
};

template<typename T> class LList {
public:
    LList();
    ~LList();
    bool IsEmpty();
    void AddFront(T item);
    T PeekFront();
    void RemoveFront();
    void Print();

private:
    ListItem<T> *head = nullptr;
};

template<typename T>
LList<T>::LList() {
}

template<typename T>
LList<T>::~LList() {
    while (!IsEmpty()) {
        RemoveFront();
    }
    head = nullptr;
}

template<typename T>
bool LList<T>::IsEmpty() {
    return head == nullptr;
}

template<typename T>
void LList<T>::AddFront(T item) {
    ListItem<T> *temp = new ListItem<T>;
    temp->item = item;
    temp->next = head;
    head = temp;
}

template<typename T>
T LList<T>::PeekFront() {
    return head->item;
}

template<typename T>
void LList<T>::RemoveFront() {
    if (IsEmpty())
        return;
    ListItem<T> *temp = head->next;
    delete head;
    head = temp;
}

template<typename T>
void LList<T>::Print() {
    for (ListItem<T> *i = head; i != nullptr; i = i->next) {
        std::cout << i->item << " ";
    }
    std::cout << std::endl;
}

#endif /* _LList_H_ */
