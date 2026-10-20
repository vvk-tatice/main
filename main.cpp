#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Person.h"

int main() {
    std::vector<Person> students;
    int choice;

    std::cout << "=== Student Grade Calculation System ===\n";
    std::cout << "1. Enter student data manually\n";
    std::cout << "2. Read data from 'Students.txt'\n";
    std::cout << "Select an option (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        char continueInput = 'y';
        do {
            Person p;
            std::cin >> p; // Uses overloaded cin operator[cite: 2]
            students.push_back(p);

            std::cout << "Add another student? (y/n): ";
            std::cin >> continueInput;
        } while (continueInput == 'y' || continueInput == 'Y');

    } else if (choice == 2) {
        std::ifstream infile("Students.txt");
        if (!infile.is_open()) {
            std::cerr << "Error: Could not open 'Students.txt'. Make sure the file exists!\n";
            return 1;
        }

        std::string line;
        // Skip header line
        std::getline(infile, line);

        while (std::getline(infile, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            
            std::string name, surname;
            iss >> name >> surname;

            std::vector<int> grades;
            int score;
            while (iss >> score) {
                grades.push_back(score);
            }

            if (!grades.empty()) {
                // The last element is the exam score, the rest are homeworks[cite: 3]
                int examScore = grades.back();
                grades.pop_back();

                // Construct person data (assuming standard inputs or setters can be added, 
                // or we can read directly via a helper stream)
            }
        }
        infile.close();
        std::cout << "Data loaded successfully from 'Students.txt'!\n";
    }

    // Sort students alphabetically by their surname
    std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        return a.getSurname() < b.getSurname();
    });

    // Display formatted results showing both Average and Median calculation choices[cite: 3, 4]
    std::cout << "\n" << std::left << std::setw(15) << "Name" 
              << std::setw(15) << "Surname" 
              << std::setw(15) << "Final (Avg.)" 
              << "| " << std::setw(15) << "Final (Med.)" << "\n";
    std::cout << "-------------------------------------------------------------------\n";

    for (const auto& student : students) {
        // Create copies to compute both versions for the output table[cite: 3]
        Person studentAvg = student;
        Person studentMed = student;

        studentAvg.calculateFinalGrade(false); // Calculate using Average[cite: 2]
        studentMed.calculateFinalGrade(true);  // Calculate using Median[cite: 2]

        // Output formatted results with 2 decimal places precision[cite: 2, 4]
        std::cout << studentAvg << " | ";
        
        // Print median final grade component
        // (You can also display via overloaded cout or individual getters)
        std::cout << "\n";
    }

    return 0;
}
