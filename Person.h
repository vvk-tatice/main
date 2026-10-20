#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalGrade;

public:
    // 1. Constructors and Destructor (Rule of Three)
    Person();                                         // Default constructor
    Person(const Person& other);                    // Copy constructor[cite: 2]
    Person& operator=(const Person& other);         // Assignment-copy operator[cite: 2]
    ~Person();                                        // Destructor[cite: 2]

    // Getters
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    
    // 2. Calculation Methods
    double calculateAverageHW() const;
    double calculateMedianHW() const;
    void calculateFinalGrade(bool useMedian);         // Choose between median or average[cite: 2]

    // 3. Overloaded Stream Operators
    friend std::istream& operator>>(std::istream& is, Person& p); // Data input method (cin)[cite: 2]
    friend std::ostream& operator<<(std::ostream& os, const Person& p); // Data output method (cout)[cite: 2]

// 4. Setter method to easily load file data
    void setStudentData(const std::string& n, const std::string& s, const std::vector<int>& hw, int ex) {
        name = n;
        surname = s;
        homeworks = hw;
        exam = ex;
    }
};

#endif // PERSON_H
