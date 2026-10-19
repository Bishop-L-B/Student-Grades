
/*
Bishop Brandstetter
CSC222
Student Grades
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
    string lastName;
    int studentID;
    double* scores;
    double average;
    char letterGrade;
};

bool readGradeData(const string& filename, Student*& students,
    int& numStudents, int& numTests);

void calculateAverages(Student* students, int numStudents, int numTests);

void assignLetterGrades(Student* students, int numStudents);

void displayReport(const Student* students, int numStudents, int numTests);

void releaseMemory(Student*& students, int numStudents);

int main()
{
    Student* students = nullptr;
    int numStudents = 0;
    int numTests = 0;

    cout << "Student grades program" << endl;

    if (!readGradeData("grades.txt", students,
        numStudents, numTests))
    {
        return 1;
    }

    calculateAverages(students, numStudents, numTests);

    assignLetterGrades(students, numStudents);

    displayReport(students, numStudents, numTests);

    releaseMemory(students, numStudents);

    return 0;
}

bool readGradeData(const string& filename, Student*& students,
    int& numStudents, int& numTests)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    if (!(inputFile >> numStudents >> numTests)
        || numStudents <= 0 || numTests <= 0)
    {
        cout << "Error: Invalid file header." << endl;
        return false;
    }

    students = new Student[numStudents]{};

    for (int i = 0; i < numStudents; i++)
    {
        students[i].scores = new double[numTests] {};
    }

    for (int i = 0; i < numStudents; i++)
    {
        if (!(inputFile >> students[i].lastName
            >> students[i].studentID))
        {
            cout << "Error: Invalid student data." << endl;
            releaseMemory(students, numStudents);
            return false;
        }

        for (int j = 0; j < numTests; j++)
        {
            if (!(inputFile >> students[i].scores[j]))
            {
                cout << "Error: Invalid test score." << endl;
                releaseMemory(students, numStudents);
                return false;
            }

            if (students[i].scores[j] < 0
                || students[i].scores[j] > 100)
            {
                cout << "Error: Score must be between 0 and 100."
                    << endl;
                releaseMemory(students, numStudents);
                return false;
            }
        }
    }

    return true;
}

void calculateAverages(Student* students, int numStudents, int numTests)
{
    for (int i = 0; i < numStudents; i++)
    {
        double total = 0.0;

        for (int j = 0; j < numTests; j++)
        {
            total += students[i].scores[j];
        }

        students[i].average = total / numTests;
    }
}

void assignLetterGrades(Student* students, int numStudents)
{
    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].average >= 90)
        {
            students[i].letterGrade = 'A';
        }
        else if (students[i].average >= 80)
        {
            students[i].letterGrade = 'B';
        }
        else if (students[i].average >= 70)
        {
            students[i].letterGrade = 'C';
        }
        else if (students[i].average >= 60)
        {
            students[i].letterGrade = 'D';
        }
        else
        {
            students[i].letterGrade = 'F';
        }
    }
}

void displayReport(const Student* students, int numStudents, int numTests)
{
    cout << endl;
    cout << "STUDENT GRADE REPORT" << endl;

    cout << left << setw(12) << "Name"
        << setw(10) << "ID";

    for (int j = 0; j < numTests; j++)
    {
        cout << right << setw(10)
            << ("Test " + to_string(j + 1));
    }

    cout << setw(12) << "Average"
        << setw(8) << "Grade" << endl;

    for (int i = 0; i < numStudents; i++)
    {
        cout << left << setw(12) << students[i].lastName
            << setw(10) << students[i].studentID;

        for (int j = 0; j < numTests; j++)
        {
            cout << right << setw(10)
                << fixed << setprecision(2)
                << students[i].scores[j];
        }

        cout << setw(12) << fixed << setprecision(2)
            << students[i].average
            << setw(8) << students[i].letterGrade
            << endl;
    }
}

void releaseMemory(Student*& students, int numStudents)
{
    if (students == nullptr)
    {
        return;
    }

    for (int i = 0; i < numStudents; i++)
    {
        delete[] students[i].scores;
        students[i].scores = nullptr;
    }

    delete[] students;
    students = nullptr;
}
