# Huffman Tree and Restaurant Management System

## Overview
This project is implemented in **C++** and focuses on **Object-Oriented Programming (OOP)** and **Data Structures & Algorithms (DSA)**. It simulates a system using **Huffman Trees**, **Binary Search Trees (BST)**, **Heaps**, and **Hashing** to manage and encode customer names and process various restaurant operations.

## Features
- **Huffman Encoding**: Encodes customer names using Huffman Trees and a Caesar Cipher for character transformation.
- **Binary Search Tree (BST)**: Stores encoded values in a structured format.
- **Min-Heap**: Manages restaurant orders and optimizes order processing.
- **Hashing**: Distributes data efficiently using modular arithmetic.
- **Efficient Data Processing**: Supports quick insertions, deletions, and lookups using advanced data structures.

## Data Structures Used
1. **Huffman Tree**:
   - Implements Huffman encoding to assign binary codes to characters.
   - Uses **AVL tree balancing** techniques.
2. **Binary Search Tree (BST)**:
   - Used in **RESTAURANT_Gojo** for organizing and searching encoded values.
   - Supports **insertion, deletion, and balancing**.
3. **Min-Heap**:
   - Used in **RESTAURANT_Sukuna** for order prioritization.
   - Supports **heap operations (heapify up/down)**.
4. **Hashing**:
   - Used for mapping data efficiently in **RESTAURANT_Gojo**.
   - Provides **O(1) average-case lookup time**.
5. **Queue & List**:
   - Used for **Least Recently Used (LRU) Cache** management.
   - Supports **efficient insertions and deletions**.

## Code Structure
### 1. `HUFFMAN_TREE` Class
- Implements Huffman encoding and decoding.
- Uses **Caesar Cipher** to encode characters before applying Huffman encoding.
- Supports **frequency accumulation and quick sorting**.

### 2. `RESTAURANT_Gojo` Class
- Implements a **BST-based hashing system**.
- Supports **insertions and deletions**.
- Uses a **queue-based deletion strategy** to maintain order records.

### 3. `RESTAURANT_Sukuna` Class
- Implements a **Min-Heap** for managing restaurant orders.
- Uses **Least Recently Used (LRU) Cache** to track the most accessed elements.
- Supports **heap rebalancing and order deletion**.

### 4. `ADMIN` Class
- Acts as a controller for the entire system.
- Manages **customer name encoding**, **order processing**, and **record retrieval**.
- Supports various operations such as **LAPSE, HAND, KOKUSEN, KEITEIKEN, LIMITLESS, and CLEAVE**.

## Usage
### Running the Simulation
```cpp
#include "main.h"
int main() {
    simulate("input.txt");
    return 0;
}
```
### Input File Format (`input.txt`)
```txt
LAPSE Alice
LAPSE Bob
HAND
LIMITLESS 5
KEITEIKEN 3
CLEAVE 2
```

## How It Works
1. **Encoding Customer Names**:
   - Converts names into integer representations using Huffman encoding.
   - Uses a BST and Hashing to organize the encoded values.
2. **Order Management**:
   - Uses a **Min-Heap** to prioritize orders.
   - Implements LRU-based deletion strategy.
3. **Efficient Retrieval**:
   - Uses **BST and Hashing** for quick data retrieval.
   - Uses **Heap-based sorting** for managing order priority.

## Key Algorithms Implemented
- **Huffman Encoding** (Greedy Algorithm)
- **Caesar Cipher** (Basic Cryptography)
- **Quick Sort** (O(n log n) Sorting)
- **BST Operations** (Insert, Delete, Balance)
- **Heap Operations** (Heapify Up/Down)
- **LRU Cache Management**

## Compilation and Execution
To compile the project, use:
```bash
g++ main.cpp -o main
```
To run the executable:
```bash
./main
```

## Conclusion
This project demonstrates advanced **OOP principles** and **DSA techniques** through efficient data processing. It can be extended for **real-world restaurant management** or other **data encoding applications**.

---
**Author:** Pham Nguyen Viet Tri

**Course:** Data Structures & Algorithms (DSA)

**University:** Ho Chi Minh city of Technology (VNU)

