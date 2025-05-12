#ifndef HEAP_QUEUE_HPP
#define HEAP_QUEUE_HPP

#include <stdexcept>
#include <functional>
#include "dynamic_array.hpp"

template <typename T, typename C = std::less<>>
class HeapPriorityQueue {
private:
    struct Node {
        T value;
        T priority;
    };

    DynamicArray<Node> heap;
    C comp;

    size_t parent(size_t i)    const { return (i - 1) / 2; }
    size_t leftChild(size_t i) const { return 2 * i + 1; }
    size_t rightChild(size_t i)const { return 2 * i + 2; }

    void swapNodes(size_t i, size_t j) {
        Node tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    void siftUp(size_t i) {
        while (i > 0) {
            size_t p = parent(i);
                                                                 // if heap[p].priority < heap[i].priority, swap
            if (comp(heap[p].priority, heap[i].priority)) {
                swapNodes(p, i);
                i = p;
            }
            else {
                break;
            }
        }
    }

    void siftDown(size_t i) {
        size_t n = heap.getSize();
        while (true) {
            size_t l = leftChild(i), r = rightChild(i), largest = i;
            if (l < n && comp(heap[largest].priority, heap[l].priority))
                largest = l;
            if (r < n && comp(heap[largest].priority, heap[r].priority))
                largest = r;
            if (largest != i) {
                swapNodes(i, largest);
                i = largest;
            }
            else {
                break;
            }
        }
    }

public:
    HeapPriorityQueue() = default;

    void add(const T& value, const T& priority) {
        heap.addBack({ value, priority });
        siftUp(heap.getSize() - 1);
    }

    void remove() {
		if (heap.getSize() == 0)
			throw std::out_of_range("Heap is empty");
        heap[0] = heap[heap.getSize() - 1];
        heap.removeBack();
        if (heap.getSize() > 0)
            siftDown(0);
    }

    const T& peek() const {
		if (heap.getSize() == 0)
			throw std::out_of_range("Heap is empty");

        return heap[0].value;
    }

    size_t size() const {
        return heap.getSize();
    }

    void changePriority(const T& value, const T& oldPriority, const T& newPriority) {
        size_t n = heap.getSize();
        for (size_t i = 0; i < n; ++i) {
            if (heap[i].value == value && heap[i].priority == oldPriority) {
                heap[i].priority = newPriority;
                if (comp(oldPriority, newPriority))
                    siftUp(i);
                else
                    siftDown(i);
                return;
            }
        }
    }
};

#endif // HEAP_QUEUE_HPP
