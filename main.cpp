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
        std::cerr << "Error: Could not open 'students10000.txt'. Make sure it's in the project folder!\n";
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
            // The last value is the exam score, the rest are homeworks (ND)
            int examScore = grades.back();
            grades.pop_back();

            // Populate the Person object using our setter method
            Person p;
            p.setStudentData(name, surname, grades, examScore);
            students.push_back(p);
        }
    }
    infile.close();
    std::cout << "Successfully loaded " << students.size() << " students from file.\n\n";

    // Sort students alphabetically by surname
    std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        return a.getSurname() < b.getSurname();
    });

 // Display formatted results showing both Average and Median calculation choices
    std::cout << std::left << std::setw(15) << "Name" 
              << std::setw(15) << "Surname" 
              << std::setw(15) << "Final (Avg.)" 
              << " | " << std::setw(15) << "Final (Med.)" << "\n";
    std::cout << "-------------------------------------------------------------------\n";

    for (const auto& student : students) {
        Person studentAvg = student;
        Person studentMed = student;

        studentAvg.calculateFinalGrade(false); // Calculate using Average[cite: 2]
        studentMed.calculateFinalGrade(true);  // Calculate using Median[cite: 2]

        // Print Name, Surname, and Average Final Grade using the overloaded operator
        std::cout << studentAvg; 

        // Print the Separator and the Median Final Grade with 2 decimal places
        std::cout << " | " << std::fixed << std::setprecision(2) << studentMed.getFinalGrade() << "\n";
    }

    return 0;
}
