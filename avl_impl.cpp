//
//  avl_impl.cpp
//  Student Management System
//
//  Created by Bronson Bakunga on 19/11/2023.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <chrono>

// Define a structure for your nodes in the AVL tree
struct AVLNode {
    std::string key; // Unique identifier, e.g., student_no or admin_number
    // Other information
    std::string name;
    std::string dateOfBirth;
    std::string telephone;
    std::string email;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(std::string k, std::string n, std::string dob, std::string tel, std::string em)
        : key(k), name(n), dateOfBirth(dob), telephone(tel), email(em), left(NULL), right(NULL), height(1) {}
};

// Define the AVL tree class
class AVLTree {
private:
    AVLNode* root;
    int operationCount;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

    AVLNode* insert(AVLNode* node, const std::string& key, const std::string& name, 
    const std::string& dob, const std::string& tel, const std::string& email);
    AVLNode* deleteNode(AVLNode* node, const std::string& key);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    int getHeight(AVLNode* N);
    int getBalance(AVLNode* N);
    AVLNode* find(AVLNode* node, const std::string& key);

public:
    AVLTree() : root(NULL), operationCount(0) {}
	void printTree() const;
    void insert(const std::string& key, const std::string& name, 
    const std::string& dob, const std::string& tel, const std::string& email);
    void deleteNode(const std::string& key);
    AVLNode* find(const std::string& key);
	void updateValue(const std::string& key, const std::string& name, const std::string& dob, const std::string& tel, const std::string& email);
    int getOperationCount() const { return operationCount; }
    void startTimer() {
        startTime = std::chrono::steady_clock::now();
    }
    void stopTimer() {
        endTime = std::chrono::steady_clock::now();
    }
    double getElapsedTime() const {
        std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
        return elapsedTime.count();
    }
};

// Implementation of AVLTree member functions

// Print Tree
void AVLTree::printTree() const {
    if (root == NULL) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }

    std::queue<AVLNode*> nodesQueue;
    int levelCount = 1;
	std::cout << "\n\n## Printing Tree ##\n";
    nodesQueue.push(root);
    while (!nodesQueue.empty()) {
        int childCount = 0;
        while (levelCount > 0) {
            AVLNode* current = nodesQueue.front();
            nodesQueue.pop();

            std::cout << current->key << " ";
            if (current->left != NULL) {
                nodesQueue.push(current->left);
                ++childCount;
            }
            if (current->right != NULL) {
                nodesQueue.push(current->right);
                ++childCount;
            }

            --levelCount;
        }
        std::cout << std::endl;
        levelCount = childCount;
    }
    std::cout << "\n\n";
}

// Insert function
AVLNode* AVLTree::insert(AVLNode* node, const std::string& key, const std::string& name, 
                         const std::string& dob, const std::string& tel, const std::string& email) {
    operationCount++;
    // Perform standard BST insertion
    if (node == NULL) {
        return new AVLNode(key, name, dob, tel, email);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, name, dob, tel, email);
    } else if (key > node->key) {
        node->right = insert(node->right, key, name, dob, tel, email);
    } else {
        return node; // Duplicate keys not allowed
    }

    // Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Check whether this node became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(const std::string& key, const std::string& name, 
    const std::string& dob, const std::string& tel, const std::string& email) {
    root = insert(root, key, name, dob, tel, email);
    // printTree(); // Print the tree structure after insertion
}

AVLNode* AVLTree::find(AVLNode* node, const std::string& key) {
    operationCount++;
    if (node == NULL) {
        // std::cout << "Node with key '" << key << "' not found." << std::endl;
        return NULL;
    }
    if (node->key == key) {
        // std::cout << "Node found: \n"
        //           << "\tKey: " << node->key << "\n"
        //           << "\tName: " << node->name << "\n"
        //           << "\tDate of Birth: " << node->dateOfBirth << "\n"
        //           << "\tTelephone: " << node->telephone << "\n"
        //           << "\tEmail: " << node->email << "\n";
        return node;
    }

    if (key < node->key) {
        return find(node->left, key);
    } else {
        return find(node->right, key);
    }
}

AVLNode* AVLTree::find(const std::string& key) {
    // std::cout << "Searching for node with key '" << key << "'..." << std::endl;
    return find(root, key);
}

// Delete Node function
AVLNode* AVLTree::deleteNode(AVLNode* node, const std::string& key) {
    operationCount++;
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            AVLNode* temp = node->left ? node->left : node->right;

            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp; // Copy the contents of the non-empty child
            }

            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);

            node->key = temp->key;
            node->name = temp->name;
            node->dateOfBirth = temp->dateOfBirth;
            node->telephone = temp->telephone;
            node->email = temp->email;

            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::deleteNode(const std::string& key) {
    root = deleteNode(root, key);
    // printTree(); // Print the tree structure after deletion
}

// Rotate Right function
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    operationCount++;
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Rotate Left function
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    operationCount++;
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Get Height function
int AVLTree::getHeight(AVLNode* N) {
    operationCount++;
    if (N == NULL) {
        return 0;
    }
    return N->height;
}

void AVLTree::updateValue(const std::string& key, const std::string& name, const std::string& dob, const std::string& tel, const std::string& email) {
    operationCount++;
    AVLNode* node = find(root, key);
    if (node != NULL) {
        node->name = name;
        node->dateOfBirth = dob;
        node->telephone = tel;
        node->email = email;
        // printTree();
    } else {
        std::cout << "Key not found in AVL tree." << std::endl;
    }
}


// Get Balance function
int AVLTree::getBalance(AVLNode* N) {
    operationCount++;
    if (N == NULL) {
        return 0;
    }
    return getHeight(N->left) - getHeight(N->right);
}

// Min Value Node function
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    operationCount++;
    AVLNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Main function for testing
// int main() {
//     AVLTree avl;

//     avl.insert("S123", "John Doe", "1990-01-01", "555-1234", "");
//     avl.insert("S124", "Jane Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S125", "Jack Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S126", "James Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S127", "Sarah Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S128", "Terry Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S129", "Gerald Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S130", "Victoria Smith", "1991-02-01", "555-5678", "");
//     avl.insert("S131", "Henry Smith", "1991-02-01", "555-5678", "");
    
//     avl.updateValue("S123", "John Updated", "1990-01-02", "555-4321", "john@example.com");
//     avl.find("S124");
    
//     // Find and delete operations can be tested here
//     avl.deleteNode("S123");

//     return 0;
// }

