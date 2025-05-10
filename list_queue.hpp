#ifndef LIST_QUEUE_HPP
#define LIST_QUEUE_HPP

#include "dlinked_list.hpp"

template <typename T, typename C>
class ListPriorityQueue {
public:
    [[nodiscard]] int size() const;
    [[nodiscard]] bool isEmpty() const;
    void add(const T& e, int priority);
    const T& peek() const;
    void remove();
    void changePriority(T& e, int oldPriority, int newPriority);
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
void ListPriorityQueue<T, C>::add(const T &e, int priority) {
    DNode<T>* curr = L.head->next;
    while (curr != L.tail && curr->entry.priority <= priority) {
        if (curr->entry.priority == priority && isLess(e, curr->entry.elem)) {
            break;
        }
        curr = curr->next;
    }
    L.add(curr, e, priority);
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
void ListPriorityQueue<T, C>::changePriority(T& e, int oldPriority, int newPriority) {
    int idx = L.findIndexOf(oldPriority);
    if (idx < 0) {
        throw std::out_of_range("Element not found");
    }
    L.removeChosen(idx);
    add(e, newPriority);
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