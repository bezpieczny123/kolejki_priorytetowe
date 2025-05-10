#ifndef DLINKED_LIST_HPP
#define DLINKED_LIST_HPP
#include <stdexcept>

template <typename T_elem, typename T_comp>
class ListPriorityQueue;

template <typename T>
class DLinkedList;

template <typename T>
class DNode {
private:
    T elem;
    DNode *prev;
    DNode *next;

    template <typename U, typename V>
    friend class ListPriorityQueue;

    friend class DLinkedList<T>;
};

template <typename T>
class DLinkedList {
public:
    DLinkedList() : n(0) {
        head = new DNode<T>;
        tail = new DNode<T>;
        head->next = tail;
        tail->prev = head;
    };
    ~DLinkedList() {
        while (!isEmpty())
            removeFront();
        delete head;
        delete tail;
    }
    [[nodiscard]] bool isEmpty() const {
        return head->next == tail;
    };
    [[nodiscard]] int size() const {
        return n;
    }
    const T& front() const {
        if (isEmpty()) throw std::out_of_range("List is empty");
        return head->next->elem;
    }
    const T& back() const {
        if (isEmpty()) throw std::out_of_range("List is empty");
        return tail->prev->elem;
    }
    const T& chosen(int i) const{
        if (isEmpty()) throw std::out_of_range("List is empty");
        if (i < 0) throw std::out_of_range("Invalid index");
        DNode<T> *temp = head->next;
        for (int j = 0; j < i; j++) {
            if (temp == tail) {
                throw std::out_of_range("Out of bounds");
            }
            temp = temp->next;
        }
        if (temp == tail) {
            throw std::out_of_range("Out of bounds");
        }
        return temp->elem;
    }
    void addFront(const T& elem) {
        add(head->next, elem);
    }
    void addBack(const T& elem) {
        add(tail, elem);
    }
    void addChosen(const T& elem, const int index) {
        if (index < 0) throw std::out_of_range("Invalid index");
        if (isEmpty()) addFront(elem);
        DNode<T> *temp = head->next;
        for (int j = 0; j < index; j++) {
            if (temp == tail) {
                break;
            }
            temp = temp->next;
        }
        add(temp, elem);
    }
    void removeFront() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        remove(head->next);
    }
    void removeBack() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        remove(tail->prev);
    }
    void removeChosen(const int index) {
        if (index < 0) throw std::out_of_range("Invalid index");
        if (isEmpty()) throw std::out_of_range("List is empty");
        DNode<T> *temp = head->next;
        for (int j = 0; j < index; j++) {
            if (temp == tail) {
                throw std::out_of_range("Out of bounds");
            }
            temp = temp->next;
        }
        if (temp == tail) throw std::out_of_range("Out of range");
        remove(temp);
    }
    int findIndexOf(const T& elem) {
        DNode<T>* temp = head->next;
        int index = 0;

        while (temp != tail) {
            if (temp->elem == elem) {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }
    private:
    DNode<T> *head;
    DNode<T> *tail;
    int n;
    template <typename U, typename V>
    friend class ListPriorityQueue;
protected:
    void add(DNode<T>* v, const T& e) {
        auto* u = new DNode<T>;
        u->elem = e;
        u->next = v;
        u->prev = v->prev;
        v->prev->next = u;
        v->prev = u;
        n++;
    }
    void remove(DNode<T>* v) {
        DNode<T>* u = v->prev;
        DNode<T>* w = v->next;
        u->next = w;
        w->prev = u;
        delete v;
        n--;
    }
};


#endif //DLINKED_LIST_HPP