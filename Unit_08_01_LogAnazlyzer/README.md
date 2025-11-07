# 🧩 Unit 08_01 — Multithreaded Log Analyzer   
**Student:** Sudin Koirala  

---

## 📖 Overview
This project implements a **Multithreaded Log Analyzer** in modern **C++17**.  
It scans multiple `.log` files concurrently, searches for specific log-level keywords,  
and reports the total number of occurrences across all files.

The program demonstrates:
- **Multithreading** using `std::thread`
- **Thread safety** via `std::mutex` and `std::lock_guard`
- **Lambda expressions** with `std::for_each`
- **File iteration** using `std::filesystem`

---

## ⚙️ Features
- Reads all `.log` files inside a given directory.
- Each file is processed in its **own thread**.
- Counts the following keywords:
  - `[WARN]`
  - `[ERROR]`
  - `[FATAL]`
  - `[INFO]`
  - `[DEBUG]`
  - `[TRACE]`
- Aggregates results safely using a shared `std::map`.
- Prints a clean keyword summary after all threads complete.

---

## 🧰 Technologies Used
- **C++17**
- **Threads (`<thread>`)**
- **Mutexes (`<mutex>`)**
- **Lambdas (`<algorithm>`)**
- **Filesystem (`<filesystem>`)**
- Developed and tested in **Xcode on macOS**

---

## 🧾 Example Output
