# Student Management System 🎓

## Overview
The Student Management System is a console-based application 🖥️ created to manage student and staff information using AVL trees 🌳 for efficient data handling. The system allows administrators and users (students or staff) to interact with the system through various functionalities such as adding, updating, deleting, and searching for user details.

Certainly! Here's an additional section for your README.md that includes the requirements for the `credentials.txt` file and the `avl_impl.cpp` file, along with the structure of credentials for an admin and a regular user:

---

## System Requirements and Setup

### Required Files
For the Student Management System to function correctly, ensure the following files are present in the same directory:

1. **avl_impl.cpp**: This file contains the implementation of the AVL tree used in the system.
2. **credentials.txt**: This file stores the login credentials for users and administrators.

### Setting Up the `credentials.txt` File
The `credentials.txt` file contains the login information for each user. It should be structured as follows:

- Each line represents a different user.
- Each user's information should be formatted as `username password usertype`.
- The `usertype` should be `admin` for administrators and `user` for regular users.

For example:
```
john123 pass123 admin
jane_doe janePass user
```

In this example, `john123` is an administrator with password `pass123`, and `jane_doe` is a regular user with password `janePass`.

### Note
Ensure that the `credentials.txt` file is placed in the same directory as your executable file (generated after compiling `gui.cpp`) for the system to access user credentials correctly.

---

## Users of the System
1. **Administrators** 👩‍💼👨‍💼: They have full access to the system, including adding, deleting, updating, and searching for user details.
2. **Users (Students/Staff)** 👩‍🎓👨‍🎓: Regular users can update their personal information.

---
## Functions
The system offers the following functionalities:

### For Administrators
- **Add User** ➕: Adds a new user to the system.
- **Delete User** 🗑️: Removes an existing user from the system.
- **Update User Details** 📝: Modifies the details of an existing user.
- **Search For User** 🔍: Searches for a user in the system based on a unique identifier.
- **Logout** 🚪: Exit the system.

### For Regular Users
- **Update User Details** 📝: Users can update their own details.
- **Logout** 🚪: Exit the system.

## How to Run Functions

For the "Starting the System" section under "How to Run Functions" in your README.md, you can refer to the following information from an article on Programiz:

---

### Starting the System

To run the Student Management System, you need to have a C++ environment set up on your computer. There are two main ways to run C++ programs:

1. **Using an Online Environment**: The easiest way to run C++ programs is to use an online compiler. This is a good option if you do not wish to install any software on your computer. You can find various online C++ compilers by searching online.

2. **Installing a C++ Environment on Your Computer**: For a more traditional approach, you can install a C++ compiler and development environment on your computer. Common choices include GCC (GNU Compiler Collection) for Linux, Microsoft Visual Studio for Windows, and Xcode for macOS. 

   To set up a C++ environment:
   - For Windows, you can download and install Microsoft Visual Studio, which includes the Visual C++ compiler.
   - For macOS, Xcode provides a comprehensive development environment with a C++ compiler.
   - For Linux, GCC is typically pre-installed, or you can install it via your distribution's package manager.

After setting up the environment, you can compile and run the `gui.cpp` file. The specific commands to compile and run the program depend on the environment you are using. In general, the steps are:
   - Open a terminal or command prompt.
   - Navigate to the directory containing `gui.cpp`.
   - Use a compile command like `g++ gui.cpp -o gui` to compile the program.
   - Run the program using `./gui` on Unix/Linux/macOS or `gui.exe` on Windows.

For detailed instructions, refer to the documentation of the C++ environment you have chosen.

Source: [Programiz - Getting Started With C++](https://www.programiz.com/cpp-programming/online-compiler)


### Navigating Menus
Upon starting the system, you will be greeted with a welcome menu 🎉 with options to log in or seek help. Choose an option by entering the corresponding number.

#### For Administrators
After logging in as an administrator, you will be presented with the admin main menu 📊. Choose an option by entering the number associated with each function:

1. **Add User** ➕: Enter the required details as prompted (key, name, date of birth, telephone, email).
2. **Delete User** 🗑️: Enter the key of the user you wish to delete.
3. **Update User Details** 📝: Enter the key of the user to update, followed by the new details.
4. **Search For User** 🔍: Enter the key of the user to search for.
5. **Logout** 🚪: Exit the system.

#### For Regular Users
After logging in as a regular user, you will be presented with the user main menu 📋:

1. **Update User Details** 📝: Enter your new details as prompted.
2. **Logout** 🚪: Exit the system.

### Exiting the System
Choose the logout option from the main menu to exit the system safely 🏁.