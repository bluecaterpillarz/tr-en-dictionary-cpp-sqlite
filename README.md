# 📚 TR-EN Dictionary (C++ & SQLite)

Console-based Turkish ↔ English dictionary application built in **C++** using an embedded **SQLite** database.

Designed as a learning-focused project with interactive suggestions, deletion logic, and a fun "Word of the Day" feature.

---

## 🎯 Project Purpose

This project was originally developed as a university assignment.  
It demonstrates:

- Working with embedded SQLite in C++
- SQL query handling (SELECT / DELETE)
- Prefix-based search logic
- Random selection algorithms
- File I/O (CSV history tracking)
- Modular project structure

The internal structure follows assignment constraints (including pointer-based handling).

---

## ✨ Features

### 🔎 Smart Prefix Search
Type the first 2 letters of a word and get suggestions:
"TR: ki
kitap 0 -> Bunu mu demek istedin?"

### 📖 Detailed Output
Displays:
- Translation
- Turkish example sentence
- English example sentence

Fallback messages are shown if sentences are missing.

---

### 🧠 Learning Mode
After viewing a word:
"Bu kelimeyi öğrendiniz mi? Silmek için 1, devam için 0:"

If learned, the word is removed from the database.

---

### 🌟 Word of the Day
- Random word selection from database
- Avoids repetition using CSV history
- Stores shown words in `oncekiler.csv`

---

## 🗂 Project Structure
├── src/ → Core application logic
├── external/ → Embedded SQLite source
├── data/ → Database & CSV history
├── README.md
└── .gitignore

---

## ⚙️ How to Compile (g++ Example)
g++ src/main.cpp src/mydictionary.cpp external/sqlite3.c -o dictionary./dictionary


---

## 🗄 Database

The application uses:

- `data/veritabani.db`
- Table: `kelimeler`
- Stores: Turkish word, English word, example sentences

---

## 🧩 Technologies Used

- C++
- SQLite (embedded)
- SQL queries
- File I/O
- Random number generation
- Modular design

---

## 📌 Why This Project?

This is not just a simple dictionary.

It simulates a small learning tool:
- Suggestion system
- Word retention logic
- Data persistence
- Randomized daily content

A compact example of combining **C++ + database logic + user interaction** in a structured project.

---

## 🚀 Future Improvements

- Parameterized SQL queries
- Modern C++ random engine
- GUI version
