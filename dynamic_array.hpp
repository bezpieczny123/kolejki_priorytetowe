#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>



template <typename T>
class DynamicArray {

private:
	T* data;
	size_t capacity;
	size_t size;


public:
	explicit DynamicArray() : capacity(1), size(0) {
		data = new T[capacity];
	}

	~DynamicArray() {
		delete[] data;
	}

	void display() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

	size_t getSize() const {
		return size;
	}

	void resize() {
		capacity *= 2;
		T* new_data = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			new_data[i] = data[i];        // kopiuje stare elementy do nowej tablicy o rozmiarze *2
		}
		delete[] data;
		data = new_data;
	}

	void addFront(T element) {
		if (size == capacity) {
			resize();
		}
		for (size_t i = size; i > 0; --i) {
			data[i] = data[i - 1];			// przesuwa elementy i wstawia nowy na pocz�tek
		}
		data[0] = element;
		++size;
	}

	void addBack(T element) {
		if (size == capacity) {
			resize();
		}
		data[size] = element;		// dodaje element na ko�cu kiedy jest miejsce
		++size;
	}

	void addChosen(T element, size_t index) {
		
		if (size == capacity) {
			resize();
		}
		for (size_t i = size; i > index; --i) {
			data[i] = data[i - 1];		// przesuwa elementy w prawo od indeksu i wstawia element w indeksie 
		}
		data[index] = element;
		++size;
	}

	void removeFront() {
		
		for (size_t i = 0; i < size - 1; ++i) {
			data[i] = data[i + 1];		// przesuwa elementy w lewo i zmniejsza rozmiar
		}
		--size;
	}

	void removeBack() {
		
		--size;						// zmniejsza rozmiar
	}

	void removeChosen(size_t index) {
		
		for (size_t i = index; i < size - 1; ++i) {
			data[i] = data[i + 1];		// przesuwa elementy w lewo od indeksu i zmniejsza rozmiar
		}
		--size;
	}

	size_t findIndexOf(T element) const {
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == element) {
				return i;				// zwraca indeks elementu
			}
		}
		return -1;
	}

	// dostep do elementu
	T& operator[](size_t index) {
		
		return data[index];
	}

	const T& operator[](size_t index) const {

		return data[index];
	}


};

#endif // DYNAMIC_ARRAY_HPP