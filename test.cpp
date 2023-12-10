#include "avl_impl.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

struct StudentData {
    std::string id;
    std::string name;
    std::string phoneNumber;
};

void shuffle(std::vector<StudentData>& students) {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generator
    for (size_t i = students.size() - 1; i > 0; --i) {
        size_t j = std::rand() % (i + 1); // Random index from 0 to i
        std::swap(students[i], students[j]); // Swap elements
    }
}

int main() {
    std::string SDataset = "SourceDataset.txt";
    std::vector<StudentData> students;
    std::string line, id, name, phoneNumber;
    int iterations = 10;

    std::ifstream file(SDataset);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << SDataset << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, id, ',');
        std::getline(iss, name, ',');
        std::getline(iss, phoneNumber, ',');

        StudentData student;
        student.id = id;
        student.name = name;
        student.phoneNumber = phoneNumber;
        students.push_back(student);
    }
    file.close();

    for (int i = 0; i < iterations; ++i) {
        shuffle(students); // Shuffle the students vector

        AVLTree avlTree;
        avlTree.startTimer();
        for (size_t j = 0; j < students.size(); ++j) {
            avlTree.insert(students[j].id, students[j].name, "DateOfBirth", students[j].phoneNumber, "Email");
        }
        avlTree.stopTimer();
        int operationCount = avlTree.getOperationCount();

        std::cout << "Iteration " << (i + 1) << " completed.\n";
        std::cout << "Operation Count: " << operationCount << "\n\n";
        std::cout << "Total time taken for insertions: " << avlTree.getElapsedTime() << "ms" << std::endl;
    }

    return 0;
}
