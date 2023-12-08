//
//  gui.cpp
//  Student Management System
//
//  Created by Bronson Bakunga on 19/11/2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include "avl_impl.cpp"

AVLTree avlTree;  

using namespace std;

void handle_input_errors(){
	if (cin.fail()) {
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
        cout << "Invalid input, please enter a number." << endl;
    }
}

int menu(){
    int command = 0;
    cout << "\t\t\t\t\t#### Student Management System ####";
    cout << "\n\t\t\t\t\t\t\tWELCOME\n";
    cout << "\n1. Login";
    cout << "\n2. Help";
    cout << "\n\nEnter the command 1-2:";
    cin >> command;
    handle_input_errors();
    return command;
}

int admin_main_menu(){
	int command = 0;
    cout << "\t\t\t\t\t#### Student Management System ####";
    cout << "\n\t\t\t\t\t\t\tMAIN MENU\n";
    cout << "\n1. Add User";
    cout << "\n2. Delete User";
    cout << "\n3. Update User Details";
    cout << "\n4. Search For User";
    cout << "\n5. Logout";
    cout << "\n\nEnter the command 1-5:";
    cin >> command;
    handle_input_errors();
    return command;
}

int user_main_menu(){
	int command = 0;
    cout << "\t\t\t\t\t#### Student Management System ####";
    cout << "\n\t\t\t\t\t\t\tMAIN MENU\n";
    cout << "\n1. Update User Details";
    cout << "\n2. Logout";
    cout << "\n\nEnter the command 1-2:";
    cin >> command;
    handle_input_errors();
    return command;
}

void addUser() {
    // Implementation for adding a user to the AVL tree
    string key, fullName, dob, tel, email;
    cout << "Enter user details (key, name, date of birth, telephone, email): ";
    cin >> key;
    cin.ignore(); // To safely handle the newline character after reading key
    getline(cin, fullName); // Read the full name
    cin >> dob >> tel >> email;
    avlTree.insert(key, fullName, dob, tel, email);
}

void deleteUser() {
    // Implementation for deleting a user from the AVL tree
    string key;
    cout << "Enter user key to delete: ";
    cin >> key;
    avlTree.deleteNode(key);
}

void updateUser() {
    // Implementation for updating a user in the AVL tree
    string key, fullName, dob, tel, email;
    cout << "Enter user key to update: ";
    cin >> key;
    cout << "Enter user details (name, date of birth, telephone, email): ";
    cin.ignore(); // To safely handle the newline character after reading key
    getline(cin, fullName); // Read the full name
    cin >> dob >> tel >> email;
    avlTree.updateValue(key, fullName, dob, tel, email);
}

void searchUser() {
    // Implementation for searching a user in the AVL tree
    string key;
    cout << "Enter user key to search: ";
    cin >> key;
    AVLNode* node = avlTree.find(key);
    if (node != NULL) {
        cout << "User found: " << node->name << endl;
    } else {
        cout << "User not found." << endl;
    }
}

string login() {
    char user_name[20];
    char password[20];

    cout << "\33[2K\r";
    cout << "\t\t\t\t\t#### Student Management System ####";
    cout << "\n\t\t\t\t\t\t\tLOGIN\n";
    cout << "\nEnter your user name: ";
    cin >> user_name;
    cout << "\nEnter your password: ";
    cin >> password;

    ifstream credentials_file("credentials.txt");

    if (credentials_file.is_open()) {
        string line;
        while (getline(credentials_file, line)) {
            char* char_line = new char[line.length() + 1];
            strcpy(char_line, line.c_str());

            char* word = strtok(char_line, " ");
            int token_counter = 1;
            bool usernameMatch = false, passwordMatch = false, userTypeMatch = false;
            string user_type;

            while (word != NULL) {
                if (token_counter == 1) {
                    usernameMatch = (strcmp(user_name, word) == 0);
                } else if (token_counter == 2) {
                    passwordMatch = (strcmp(password, word) == 0);
                } else if (token_counter == 3) {
                    user_type = word;
                    userTypeMatch = true;
                }
                word = strtok(NULL, " ");
                token_counter++;
            }

            delete[] char_line;

            if (usernameMatch && passwordMatch && userTypeMatch) {
                if (user_type == "admin") {
                    return "admin";
                } else if (user_type == "user") {
                    return "user";
                }
            }
        }
        credentials_file.close();
    } else {
        cout << "Unable to open credentials file.\n";
    }
    return "login failed"; // Return this if login fails
}

int main() {
    int output;
    string login_result;
    
    do {
        output = menu();
    } while (output < 1 || output > 2);

    login_result = login();
    
    while (true) {
        if (login_result.compare("admin") == 0) {
            cout << "\n\n\t\t\t\t\t#### Welcome Administrator ####\n\n";
            output = admin_main_menu();

            switch (output) {
                case 1: {
                    cout << "\n\nAdding a user\n";
                    addUser();
                    break;
                }
                case 2: {
                    cout << "\n\nDeleting a user\n";
                    deleteUser();
                    break;
                }
                case 3: {
                    cout << "\n\nUpdating a user\n";
                    updateUser();
                    break;
                }
                case 4: {
                    cout << "\n\nSearching for a user\n";
                    searchUser();
                    break;
                }
                case 5: {
                    cout << "\n\nLogging out\n";
                    return 0; // Exit the program
                }
                default: {
                    cout << "\n\nWrong Option\n";
                    break;
                }
            }
        } else if (login_result.compare("user") == 0) {
            cout << "\n\n\t\t\t\t\t#### Welcome User ####\n\n";
            output = user_main_menu();

            switch (output) {
                case 1: {
                    cout << "\n\nUpdating user details\n";
                    break;
                }
                case 2: {
                    cout << "\n\nLogging you out\n";
                    return 0; // Exit the program
                }
                default: {
                    cout << "\n\nWrong Option\n";
                    break;
                }
            }
        } else {
            cout << "\n\nSomething went wrong: " << login_result << "\n\n";
            return 1; // Exit the program with an error code
        }
    }

    return 0;
}

