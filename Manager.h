#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
using namespace std;

template<class T>
class Manager {
private:
    T* items;
    int size;
    int capacity;
public:
    Manager();
    ~Manager();
    void Add(const T&);
    void Update(int&, const T&);
    void Remove(const T&);
    void RemoveAt(const int&);
    int IndexOf(const T&) const;
    T& operator[](const int&) const;
    Manager<T>& operator=(const Manager<T>&);
    int Size() const;
    template<typename U>
    friend ostream& operator<<(ostream& ,const Manager<U>&);
};

#endif
