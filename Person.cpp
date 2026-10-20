#include "Person.h"
#include <numeric>
#include <algorithm>
#include <iomanip>

// Default Constructor
Person::Person() : name(""), surname(""), exam(0), finalGrade(0.0) {}

// Copy Constructor (Rule of Three)[cite: 2]
Person::Person(const Person& other) 
    : name(other.name), surname(other.surname), 
      homeworks(other.homeworks), exam(other.exam), 
      finalGrade(other.finalGrade) {}

// Copy Assignment Operator (Rule of Three)[cite: 2]
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homeworks = other.homeworks;
        exam = other.exam;
        finalGrade = other.finalGrade;
    }
    return *this;
}

// Destructor (Rule of Three)[cite: 2]
Person::~Person() {
    homeworks.clear();
}

// Calculate Average of Homeworks
double Person::calculateAverageHW() const {
    if (homeworks.empty()) return 0.0;
    double sum = std::accumulate(homeworks.begin(), homeworks.end(), 0.0);
    return sum / homeworks.size();
}

// Calculate Median of Homeworks
double Person::calculateMedianHW() const {
    if (homeworks.empty()) return 0.0;
    std::vector<int> sortedHW = homeworks;
    std::sort(sortedHW.begin(), sortedHW.end());
    size_t size = sortedHW.size();
    if (size % 2 == 0) {
        return (sortedHW[size / 2 - 1] + sortedHW[size / 2]) / 2.0;
    } else {
        return sortedHW[size / 2];
    }
}

// Calculation Method for Final Grade (Formula: 0.4 * HW + 0.6 * Exam)
void Person::calculateFinalGrade(bool useMedian) {
    double hwScore = useMedian ? calculateMedianHW() : calculateAverageHW();
    finalGrade = 0.4 * hwScore + 0.6 * exam;
}

// Overloaded cin operator for data input[cite: 2]
std::istream& operator>>(std::istream& is, Person& p) {
    std::cout << "Enter Name: ";
    is >> p.name;
    std::cout << "Enter Surname: ";
    is >> p.surname;

    p.homeworks.clear();
    std::cout << "Enter homework scores (enter -1 to finish): ";
    int score;
    while (is >> score && score != -1) {
        p.homeworks.push_back(score);
    }

    std::cout << "Enter Exam score: ";
    is >> p.exam;
    return is;
}

// Overloaded cout operator for data output[cite: 2]
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << std::left << std::setw(15) << p.name 
       << std::setw(15) << p.surname 
       << std::fixed << std::setprecision(2) << std::setw(15) << p.finalGrade;
    return os;
}
