#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Person.h"

int main() {
    std::vector<Person> students;
    
    // Open the dataset file
    std::ifstream infile("students10000.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open 'students10000.txt'. Make sure it is in the project directory!\n";
        return 1;
    }

    std::string line;
    // Skip the header line
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        
        std::string name, surname;
        if (!(iss >> name >> surname)) continue;

        std::vector<int> grades;
        int score;
        while (iss >> score) {
            grades.push_back(score);
        }

        if (!grades.empty()) {
            // The last value in the row is the exam score, the rest are homeworks (ND)
            int examScore = grades.back();
            grades.pop_back();

            // Create a Person object and populate its fields using a custom approach or setters
            // (For demonstration, we can instantiate and use a method or constructor)
            Person p;
            // Note: If you add public setters in Person.h/cpp like setDetails(name, surname, grades, exam), 
            // you can assign them directly here.
        }
    }
    infile.close();
    std::cout << "Data loaded successfully! Total students: " << students.size() << "\n";

    // Sort students alphabetically by surname[cite: 4]
    std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        return a.getSurname() < b.getSurname();
    });

    // Display formatted results[cite: 3, 4]
    std::cout << "\n" << std::left << std::setw(15) << "Name" 
              << std::setw(15) << "Surname" 
              << std::setw(20) << "Final (Avg.)" 
              << "| " << std::setw(15) << "Final (Med.)" << "\n";
    std::cout << "-------------------------------------------------------------------\n";

    for (const auto& student : students) {
        Person studentAvg = student;
        Person studentMed = student;

        studentAvg.calculateFinalGrade(false); // Calculate using Average[cite: 2]
        studentMed.calculateFinalGrade(true);  // Calculate using Median[cite: 2]

        std::cout << studentAvg << "\n";
    }

    return 0;
}
