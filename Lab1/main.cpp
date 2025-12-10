#include <iostream>
using namespace std;


void swapByRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


// 1. Bubble Sort
void bubbleSort(int* arr, int size) {
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swapByRef(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


// 2. Merge Sort 
void mergeArrays(int* arr, int left, int mid, int right) {
    int size = right - left + 1;
    int temp[size];   

    int leftPointer = left;      
    int rightPointer = mid + 1; 
    int index = 0;          

    while (leftPointer <= mid && rightPointer <= right) {
        if (arr[leftPointer] <= arr[rightPointer])
            temp[index++] = arr[leftPointer++];
        else
            temp[index++] = arr[rightPointer++];
    }

    while (leftPointer <= mid)
        temp[index++] = arr[leftPointer++];

    while (rightPointer <= right)
        temp[index++] = arr[rightPointer++];

    for (int t = 0; t < size; t++)
        arr[left + t] = temp[t];
}


void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeArrays(arr, left, mid, right);
    }
}

// 3. Sequential Search
int seqSearchSorted(int* arr, int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) return i;
        if (arr[i] > key) return -1;
    }
    return -1;
}


// 4. Binary Search - Iterative
int binarySearchIter(int* arr, int size, int key) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] > key) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}


// 4. Binary Search - Recursive
int binarySearchRec(int* arr, int left, int right, int key) {
    if (left > right) return -1;

    int mid = (left + right) / 2;

    if (arr[mid] == key) return mid;
    else if (arr[mid] > key)
        return binarySearchRec(arr, left, mid - 1, key);
    else
        return binarySearchRec(arr, mid + 1, right, key);
}


// 5. Quick Sort
int partitionArr(int* arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swapByRef(arr[i], arr[j]);
        }
    }

    swapByRef(arr[++i], arr[right]);
    return i ;
}

void quickSort(int* arr, int left, int right) {
    if (left < right) {
        int pivotPos = partitionArr(arr, left, right);
        quickSort(arr, left, pivotPos - 1);
        quickSort(arr, pivotPos + 1, right);
    }
}

// 6. Heap Sort
void heapify(int* arr, int size, int i) {
    int largest = i;
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swapByRef(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swapByRef(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[6] = {8, 3, 5, 1, 9, 2};
    int size = 6;

    // bubbleSort(arr, size);
    // mergeSort(arr, 0, size - 1);
    // quickSort(arr, 0, size - 1);
    heapSort(arr, size);
    cout << seqSearchSorted(arr, size, 5) << endl;
    cout << binarySearchIter(arr, size, 5)<< endl;
    cout << binarySearchRec(arr, 0, size - 1, 5) << endl;

    for (int i =0 ; i < size; i++) cout << arr[i] << " ";

    return 0;
}
