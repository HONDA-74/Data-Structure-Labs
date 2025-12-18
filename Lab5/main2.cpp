#include <iostream>
#include <vector>
#include <limits>
using namespace std;

template<typename T>
class BinaryHeap {
private:
    vector<T> arr;
    int size;

public:
    BinaryHeap(int capacity = 4) : arr(capacity+1) {
        size = 0;
        arr[0] = numeric_limits<T>::min() ;
    }

    bool isEmpty() const {
        return size == 0;
    }

    T* findMin() {
        if (isEmpty()) {
            return nullptr;
        }
        return &arr[1];
    }

    ~BinaryHeap() {
        arr.clear();
    }

    void insert(const T& value) {
        if (size == arr.size() - 1) {
            arr.resize(arr.size() * 2);
        }
            int nodeIndex = ++size;
            arr[nodeIndex] = value;
            heapfyUp(nodeIndex);    
    }

    T deleteMin() {
        if (isEmpty()) return T();
        T min = arr[1];
        arr[1] = arr[size--];
        heapfyDown(1);
        return min;
    }

    void heapfyDown(int index) {
    while (2 * index <= size) {
        int left = 2 * index;
        int right = 2 * index + 1;
        int minIndex = left;

        if (right <= size && arr[right] < arr[left])
            minIndex = right;

        if (arr[index] <= arr[minIndex])
            break;

        swap(arr[index], arr[minIndex]);
        index = minIndex;
    }
    }

    void heapfyUp(int index) {
        while (index > 1 && arr[index] < arr[index / 2]) {
            swap(arr[index], arr[index / 2]);
            index /= 2;
        }
    }

    void view() {
        for (int i = 1; i <= size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    T& operator[](int index) {
        if (index < 1 || index > size) {
            cout << "Index out of range" << endl;
            return arr[0];
        }
        return arr[index];
    }
};

int main(){
    BinaryHeap<int> heap;
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(15);
    heap.view();

    int deletedElement = heap.deleteMin();
    cout << "Deleted Element: " << deletedElement << endl;

    heap.view();

    int* minElement = heap.findMin();
    cout << "Minimum Element: " << *minElement << endl;

    cout << "first element: " << heap[1] << endl;

    return 0;
}