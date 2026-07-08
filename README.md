<div align="center">

# 📚 Shelf-Control

**A Lightweight, Console-Based Library & Inventory Management System in Pure C++**

[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

<!-- ================================================================= -->
<!-- 📸 TOP PICTURE PLACEHOLDER: Insert your console banner or logo here -->
<!-- Upload an image to your repo root and put its name in src="", e.g., src="banner.png" -->
<!-- ================================================================= -->
<p align="center">
  <img src="https://via.placeholder.com/900x400/1e1e2e/ffffff?text=Drop+Your+Console+Banner+or+Screenshot+Here" alt="Shelf-Control Preview Banner" width="90%">
</p>

</div>

---

## 💡 Overview

**Shelf-Control** is a fast, lightweight, and interactive console application built from the ground up in **pure C++**. Designed as a foundational software engineering project, it demonstrates efficient memory handling, Object-Oriented Programming (OOP) principles, and robust local data persistence without relying on external database engines or heavy frameworks.

To save and retrieve inventory data across sessions, the application implements custom file handling using the native C++ **`<fstream>`** library. All records are dynamically parsed and stored in local `.txt` files, ensuring seamless CRUD (Create, Read, Update, Delete) functionality right from your terminal.

---

## ✨ Key Features

- **⚡ Pure C++ Architecture:** Built using standard C++ practices, focusing on speed, clean logic, and minimal overhead.
- **💾 Persistent File Storage (`<fstream>`):** Utterly database-free! Uses standard `ifstream` and `ofstream` file streams to serialize and deserialize data directly to and from local `.txt` files.
- **📖 Full CRUD Functionality:** Easily add new books/items, view current inventory, update existing records, and delete items from your shelf.
- **🖥️ Interactive Console UI:** A clean, easy-to-navigate command-line interface with intuitive menu prompts and error handling.
- **0️⃣ Zero External Dependencies:** Runs anywhere with a standard C++ compiler—no third-party libraries, packages, or servers required!

---

## 🛠️ Tech Stack

* **Language:** C++ (Standard Template Library)
* **File I/O:** C++ `<fstream>` (`ifstream`, `ofstream`)
* **Interface:** Command Line / Terminal Console
* **Compiler Support:** GCC (`g++`), Clang (`clang++`), or MSVC (Visual Studio)

---

## 📁 Typical Project Structure

```text
Shelf-control/
├── src/
│   ├── main.cpp             # Entry point and main application loop
│   ├── Book.cpp             # Item/Book class implementation (Adjust if named differently)
│   └── Book.h               # Header file for data structures
├── data/
│   └── inventory.txt        # Local text file where <fstream> saves persistent data
├── README.md
└── LICENSE
