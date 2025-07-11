# ✅ To-Do List Application (C++ with Qt GUI)

This project is a simple **To-Do List application** implemented in **C++** using **Qt GUI framework**, as part of an Advanced Programming course. It aims to demonstrate practical usage of object-oriented programming (OOP).

---

![Presentation1](https://github.com/user-attachments/assets/7f412b7f-7d86-4e9a-9569-49045e30b6c9)

---

## 💡 Features

### 👤 User Accounts
- Sign up and log in with a unique username and password
- User-specific task assignments

### 📃 Multiple To-Do Lists
- Create multiple lists with unique names and colors

### ✅ Task Management
- Add tasks to any list
- Set a task title
- Add a description to each task
- Set a due date and compare it with the system date on launch
- Star/unstar tasks
- Mark tasks as completed or not completed
- Assign tasks to a specific user

### 👁️‍🗨️ Special Views
- View all starred tasks
- View tasks assigned to a specific user

### 📤 Export
- Export a list of tasks as a **PDF file**

---

## 💾 Data Storage

This application uses **SQLite** database to store **all user data and task information** persistently.

---

## 🛠 Technical Details

- Implemented in **C++**
- Uses **Qt framework** for GUI
- Uses **Linked Lists** to manage tasks in Lists
- **SQLite** for data storage

---

## 📁 Project Structure

```
/ToDoListProject
├── main.cpp
├── ToDoList.db
├── ToDoList.pro
├── AddList.h / .cpp / .ui
├── AddTask.h / .cpp / .ui
├── LinkList.h / .cpp
├── List.h / .cpp
├── Login.h / .cpp / .ui
├── MainPanel.h / .cpp / .ui
├── Signun.h / .cpp / .ui
├── Task.h / .cpp
├── User.h / .cpp
└── README.md
```

---

## 🚀 How to Run

- **Qt Creator IDE** (used to develop the entire project)
- **Qt libraries and dependencies** (to build and run correctly)
- Make sure the compiler is set to support C++17 or later

---

## 👩🏻‍💻 Author

Developed as part of a C++ Advanced Programming course final project
