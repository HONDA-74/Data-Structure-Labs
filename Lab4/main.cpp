#include <iostream>

using namespace std;

template<typename T>
class DynamicArray 
{
    T* arr;
    int size;
    int capacity;
    static const int INITIAL_CAPACITY = 4;
public:
    DynamicArray() : size(0), capacity(INITIAL_CAPACITY) {
        arr = new T[capacity];
    }

    DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
        arr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    ~DynamicArray() {
        delete[] arr;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    void add(const T& value) {
        if(size == capacity){ 
            resize(capacity * 2); 
        }
        arr[size++] = value;
    }

    void remove_at(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return;
        }
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    void remove(const T& value) { 
        for (int i = 0; i < size; ++i) {
            if (arr[i] == value) {
                remove_at(i);
                --i;
            }
        }
    }

    void resize(int newSize) {
        if (newSize <= capacity) return;
        T* newArr = new T[newSize];
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newSize;
    }

    const T& operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

    void trim() {
    if (size == capacity) return;

    T* newArr = new T[size];
    for (int i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = size;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};


int main(){
    DynamicArray<int> arr ;
    arr.add(10);
    arr.add(20);
    cout << "size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << endl;
    arr.add(30);
    arr.add(40);
    cout << "size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << endl;
    arr.add(50);
    cout << "size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << endl;
    DynamicArray<int> arr2 = arr;
    DynamicArray<int> arr3;
    arr3 = arr;
    arr2.print();
    arr3.print();
    arr.trim();
    cout << "size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << endl;
    return 0;
}
