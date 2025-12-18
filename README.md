# Fenwick Tree (Binary Indexed Tree) – C++ Implementation

## 📌 Overview

This project presents a **comprehensive C++ implementation of Fenwick Trees (Binary Indexed Trees)** supporting multiple types of prefix queries with efficient point updates.

Fenwick Trees allow:
- **Point updates** in `O(log N)`
- **Prefix queries** in `O(log N)`

This project extends the classic Fenwick Tree to support:
- Prefix **Sum**
- Prefix **Maximum**
- Prefix **Minimum**

The implementation also includes **extensive test cases** and a **performance comparison** with naïve `O(N)` approaches.

---

## 🚀 Features

- ✅ Fenwick Tree for **Prefix Sum**
- ✅ Fenwick Tree for **Prefix Maximum**
- ✅ Fenwick Tree for **Prefix Minimum**
- ✅ Supports point updates
- ✅ Handles negative and mixed values
- ✅ Extensive correctness and edge-case testing
- ✅ Performance benchmarking (`O(N)` vs `O(log N)`)

---
## 📁 Project Structure
    ├── main.cpp
    └── README.md

---
## 🧠 Implemented Data Structures

### 1. FenwickTreeSum
- Point update: add value to index
- Query: prefix sum `[0 … i]`

### 2. FenwickTreeMax
- Point update: propagate maximum
- Query: prefix maximum `[0 … i]`

### 3. FenwickTreeMin
- Point update: propagate minimum
- Query: prefix minimum `[0 … i]`

---

## ⚙️ How Fenwick Tree Works

- Uses **binary indexing**
- Traverses parent/child nodes using the least significant set bit
- Key operation:
  
```
i += i & (-i);  // move forward during update
i -= i & (-i);  // move upward during query
```

🌍 Applications :-
1. Competitive programming
2. Range query optimization
3. Financial analytics
4. Database indexing
5. Real-time cumulative statistics
6. Foundation for 2D Fenwick Trees

## 👨‍💻 Team Members:
- Aryan Sandal
- Moinak Goswami
- Harshit Sahu
- Sarthak Keshaowar
- Bhavya Bansal

Instructor: Prof. Apurva Mudgal
