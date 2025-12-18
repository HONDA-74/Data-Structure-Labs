# 🧪 Data Structure Labs

This repository contains **Data Structure Labs** implemented in **C++** as part of the course.  
Each lab focuses on fundamental data structures and algorithms, including sorting, searching, stacks, queues, linked lists, trees, hash tables, and graphs.

---

## 📌 Labs Overview

### 🔄 Lab 1 – Sorting & Searching
Includes implementations of classic **sorting** and **searching** algorithms, as well as a swap function using references.

**Contents:**
1. **Swap By Reference** – Swap two integers using references  
2. **Bubble Sort** – Compares adjacent elements, stops early if sorted  
3. **Merge Sort** – Divide-and-Conquer recursive sort  
4. **Quick Sort** – Partitioning & recursive sorting  
5. **Heap Sort** – Max heap construction and extraction  
6. **Sequential Search** – For sorted arrays, early stopping  
7. **Binary Search** – Iterative & Recursive versions  

**File Structure:**
```
Lab1/
├── main.cpp # All implementations
```

---

### 🧮 Lab 2 – Doubly Linked List, Stack & Queue
Focuses on **doubly linked list**, **stack**, and **queue** implementations using nodes and pointers.

**Contents:**
1. **Doubly Linked List (DLL)** – Add, Delete, Search, Display, Copy Constructor, Assignment Operator  
2. **Stack (StackDLL)** – Push, Pop, Peek operations  
3. **Queue (QueueDLL)** – Enqueue, Dequeue, Peek operations  
4. **Sorted Doubly Linked List** – Insert nodes in sorted order  

**File Structure:**
```
Lab2/
├── main.cpp
├── main2.cpp
```

---

### 🌳 Lab 3 – Binary Search Tree (BST) & AVL Balancing
Covers **Binary Search Tree (BST)** operations, **AVL balancing**, and recursive tree traversal.

**Contents:**
1. **BST Node Structure** – Employee data, left & right pointers, height  
2. **BST Operations** – Insert, Delete, Search, Traverse, Count nodes & levels  
3. **AVL Tree** – Automatic rebalancing after insertion/deletion  
4. **Demonstration** – Example insertions, deletions, searching, counting, and tree traversal  

**File Structure:**
```
Lab3/
├── main.cpp
```

---

### 📦 Lab 4 – Dynamic Array & Binary Heap
Focuses on building **custom data structures from scratch** using templates, dynamic memory management, and STL containers.

**Contents:**
1. **Dynamic Array (Template Class)**
   - Dynamic resizing (auto-grow & trim)
   - Add and remove elements
   - Copy constructor & assignment operator
   - Operator overloading `[]` with bounds checking
   - Difference between **size** and **capacity**

2. **Binary Min Heap (Template Class)**
   - Implemented using `std::vector`
   - Insert elements with heapify-up
   - Delete minimum element with heapify-down
   - Find minimum element
   - Operator overloading for indexed access

**Concepts Applied:**
- Templates
- Dynamic memory allocation (`new` / `delete`)
- Copy constructor & operator overloading
- Heap property maintenance
- Array-based tree representation

**File Structure:**
```
Lab4/
├── main.cpp # Dynamic Array implementation & testing
├── main2.cpp # Binary Min Heap implementation & testing
```
