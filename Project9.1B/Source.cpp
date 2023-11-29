#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

const int MAX_NAME_LENGTH = 20;

// Об'єднання для курсів
union Course {
    int value;
};

// Об'єднання для спеціальностей
union Specialty {
    int value;
};

const int NUM_COURSES = 5;
const int NUM_SPECIALTIES = 8;

// Функція для конвертації значення спеціальності в назву
const char* specialtyToString(Specialty specialty) {
    switch (specialty.value) {
    case 0:
        return "Mathematics";
    case 1:
        return "Physics";
    case 2:
        return "Crafting";
    case 3:
        return "Computer Science";
    case 4:
        return "Mathematics and Economics";
    case 5:
        return "Physics and Computer Science";
    case 6:
        return "Labour Training";
    case 7:
        return "Informatics";
    default:
        return "Unknown";
    }
}

// Структура, що представляє інформацію про студента
struct Student {
    int studentNumber;
    char lastName[MAX_NAME_LENGTH];
    Course course;
    Specialty specialty;
    double physics;
    double math;
    union {
        double it;  // для "Комп'ютерних наук"
        double pedagogy;  // для інших спеціальностей
        double numericalMethods;  // для "Інформатики"
    };
};

// Функція для введення даних про студентів
void inputStudents(Student* students, int numberOfStudents) {
    const char* lastNames[] = { "Vovk", "Mazurok", "Ushakov", "Kojushko", "Zarubich", "Simonenko", "Barchuk", "Osadchyi", "Kalyna" };

    for (int i = 0; i < numberOfStudents; ++i) {
        strncpy(students[i].lastName, lastNames[i % (sizeof(lastNames) / sizeof(lastNames[0]))], MAX_NAME_LENGTH - 1);
        students[i].lastName[MAX_NAME_LENGTH - 1] = '\0';

        students[i].specialty.value = i % NUM_SPECIALTIES;

        students[i].course.value = rand() % NUM_COURSES + 1;
        students[i].physics = rand() % 3 + 3;
        students[i].math = rand() % 3 + 3;

        if (students[i].specialty.value == 3) {
            students[i].it = rand() % 3 + 3;
        }
        else if (students[i].specialty.value == 7) {
            students[i].numericalMethods = rand() % 3 + 3;
        }
        else {
            students[i].pedagogy = rand() % 3 + 3;
        }

        students[i].studentNumber = i + 1;
    }
}

// Функція для виведення таблиці студентів та розрахунку кількості та відсотка студентів
void displayTable(const Student* students, int numberOfStudents) {
    int countWithoutThrees = 0;
    int countBelowFour = 0;

    std::cout << "----------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| No |  Surname   |Course|            Speciality        |  Physics |    Math   |  Programming  |   Pedagogy   | Numerical methods|" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < numberOfStudents; ++i) {
        std::cout << "| " << std::setw(2) << students[i].studentNumber << " | " << std::setw(10) << students[i].lastName << " | "
            << std::setw(4) << students[i].course.value << " | " << std::setw(28) << specialtyToString(students[i].specialty) << " | "
            << std::setw(8) << students[i].physics << " | " << std::setw(9) << students[i].math << " | ";

        if (students[i].specialty.value == 3) {
            std::cout << std::setw(13) << students[i].it << " |              |              |";
        }
        else if (students[i].specialty.value == 4 || students[i].specialty.value == 5 || students[i].specialty.value == 6) {
            std::cout << "              |" << std::setw(13) << students[i].pedagogy << " |              |";
        }
        else if (students[i].specialty.value == 7) {
            std::cout << "              |              |" << std::setw(13) << students[i].numericalMethods << " |";
        }
        else {
            std::cout << "              |              |              |";
        }

        std::cout << std::endl;

        if (students[i].physics >= 4 && students[i].math >= 4 && ((students[i].specialty.value == 3 && students[i].it >= 4) || (students[i].specialty.value == 7 && students[i].numericalMethods >= 4) || (students[i].specialty.value != 3 && students[i].specialty.value != 7 && students[i].pedagogy >= 4))) {
            countWithoutThrees++;
        }

        double averageGrade = (students[i].physics + students[i].math + ((students[i].specialty.value == 3) ? students[i].it : ((students[i].specialty.value == 7) ? students[i].numericalMethods : students[i].pedagogy))) / 3.0;

        if (averageGrade < 4.0) {
            countBelowFour++;
        }
    }

    std::cout << "----------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "1. Number of students without threes: " << countWithoutThrees << std::endl;
    std::cout << "2. Percentage of students with an average grade below 4: " << std::fixed << std::setprecision(2)
        << (static_cast<double>(countBelowFour) / numberOfStudents) * 100 << "%" << std::endl;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    int numberOfStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numberOfStudents;

    Student* students = new Student[numberOfStudents];

    inputStudents(students, numberOfStudents);

    displayTable(students, numberOfStudents);

    delete[] students;

    return 0;
}
