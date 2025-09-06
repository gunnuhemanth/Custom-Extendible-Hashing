# Extendible Hashing Simulation in C++

This project is an implementation of a **dynamic hashing technique** using a custom category-based bucket splitting mechanism, inspired by **Extendible Hashing**.  
It demonstrates how collisions in hash buckets can be resolved dynamically by splitting categories into finer partitions.

---

## 🚀 Features
- Implements a **bucket-based hashing system** with configurable bucket size (`BUCKET_SIZE` = 3).
- **Collision handling**: when a bucket is full, it is split into finer modular categories.
- Uses **modulus-based categories** `(mod k + rem)` to organize numbers.
- Tracks and reports:
  - Total number of collisions
  - Collision rate (% of insertions causing collisions)
- Prints the **final bucket organization** after all insertions.

---

## 📂 Code Overview
- `belongTo(...)`: checks if a number belongs to an existing category set.
- `getSplitPairs(...)`: generates finer categories when a bucket splits.
- `allbelong(...)`: verifies if all values fit into the same category.
- `cat_buck`: global structure mapping categories to their bucket values.
- Tracks **bucket splits and collisions** as data grows.

---

## 🛠️ Usage
### 1. Compile
```bash
g++ -std=c++17 -O2 hashing.cpp -o hashing
./hashing
8
5 8 12 15 20 25 30 35
(4k) (2k+1)  ->  5 25 
(4k+3)  ->  15 35 
(4k+0)  ->  8 12 20 30 
Total collisions: 3
Collision rate: 37.50%
