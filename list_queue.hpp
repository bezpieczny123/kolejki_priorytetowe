//
// Created by mikol on 10.05.2025.
//


#ifndef LIST_QUEUE_HPP
#define LIST_QUEUE_HPP

#include "dlinked_list.hpp"

template <typename T, typename C>
class ListPriorityQueue {
public:
    [[nodiscard]] int size() const;
    [[nodiscard]] bool isEmpty() const;
    void add(const T& e);
    const T& peek() const;
    void remove();
    void changePriority(const T& e, const T& newE);
    void removeC(const T& e);
private:
    DLinkedList<T> L;
    C isLess;
};

template<typename T, typename C>
int ListPriorityQueue<T, C>::size() const {
    return L.size();
}

template<typename T, typename C>
bool ListPriorityQueue<T, C>::isEmpty() const {
    return L.isEmpty();
}

template<typename T, typename C>
void ListPriorityQueue<T, C>::add(const T &e) {
    DNode<T>* curr = L.head->next;
    while (curr != L.tail && !isLess(e, curr->elem)) {
        curr = curr->next;
    }
    L.add(curr, e);
}

template<typename T, typename C>
const T& ListPriorityQueue<T,C>::peek() const {
    if (L.isEmpty()) {
        throw std::out_of_range("ListPriorityQueue is empty");
    }
    return L.front();
}

template<typename T, typename C>
void ListPriorityQueue<T,C>::remove() {
    if (L.isEmpty()) {
        throw std::out_of_range("ListPriorityQueue is empty");
    }
    L.removeFront();
}

template<typename T, typename C>
void ListPriorityQueue<T, C>::changePriority(const T &e, const T &newE) {
    int idx = L.findIndexOf(e);
    if (idx < 0) {
        throw std::out_of_range("Element not found");
    }
    L.removeChosen(idx);
    add(newE);
}

template<typename T, typename C>
void ListPriorityQueue<T, C>::removeC(const T &e) {
    int idx = L.findIndexOf(e);
    if (idx < 0) {
        throw std::out_of_range("Element not found");
    }
    L.removeChosen(idx);
}




#endif //LIST_QUEUE_HPP
