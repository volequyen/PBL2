#include "Manager.h"

template<class T>
Manager<T>::Manager() : size(0), capacity(1000) {
    this->items = new T[this->capacity];
}
template<class T>
Manager<T>::~Manager() {
    delete[] this->items;
}
template<class T>
void Manager<T>::Add(const T& item) {
     if (this->size < this->capacity) {
        this->items[this->size] = item;
        this->size++;
    } else {
        cout << "Array is full!";
    }
}
template<typename T>
void Manager<T>::Update(int& index, const T& item) {
    if(index >= 0 && index < size) {
        items[index] = item;
    } else {
        cout << "Index out of range. Update failed." << endl;
    }
}
template<class T>
void Manager<T>::Remove(const T& item) {
    int indexToRemove = -1;
    for (int i = 0; i < this->size; i++) {
        if (this->items[i] == item) {
            indexToRemove = i;
            break;
        }
    }
    if (indexToRemove >= 0) {
        for (int i = indexToRemove; i < this->size - 1; i++) {
            this->items[i] = this->items[i + 1];
        }
        this->size--;
    } else {
        cout << "Item not found." << endl;
    }
}
template<class T>
int Manager<T>::Size() const {
    return this->size;
}

template<typename T>
ostream& operator<<(ostream& o,const Manager<T>& m) {
    for (int i = 0; i < m.size; i++) {
        o << m[i] << endl;
    }
    return o;
}

template<class T>
Manager<T>& Manager<T>::operator=(const Manager<T>& m) {
    if (this != &m) {
        delete[] items;
        size = m.size;
        capacity = m.capacity;
        items = new T[capacity];
        
        for (int i = 0; i < size; ++i) {
            items[i] = m.items[i];
        }
    }

    return *this;
}


template<typename T>
T& Manager<T>::operator[](const int& index) const {
    if(index >= 0 && index < size) {
        return *(this->items + index);
    }
    throw out_of_range("Index out of range.");
}

// template<typename T>
// void Manager<T>::RemoveAt(int index) {
//     if (index >= 0 && index < this->size) {
//         for (int i = index; i < this->size - 1; i++) {
//             this->items[i] = this->items[i + 1];
//         }
//         this->size--;
//     } else {
//         cout << "Index out of range. RemoveAt failed." << endl;
//     }
// }
