//
// Created by weiguang on 18/04/24.
//

#include <string>
#include <iostream>

struct Student {
    std::string name;
    int age;
    float gpa;
};  // can you put (multiple) variable names here?

struct Person
{
   int age;      // 4 bytes
   float weight; // 4 bytes
};

struct Rectangle {
    int length;
    int width;

    int area() {
        return length * width;
    }
};

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    std::string name;
    Date dateOfJoining;
};


int main() {
    Student s1; // define Student Variable; can you define an array/dynamically allocated memory array? here?
    s1.name = "John Doe";
    s1.age = 20;
    s1.gpa = 3.5;
    std::cout << "Name: " << s1.name << ", Age: " << s1.age << ", GPA: " << s1.gpa << std::endl;
    // can struct being removed?? If so, how?

    // sturcture and pointer
    Person *personPtr, person1;
    std::cout << "Size of my structure = " << sizeof(Person) << std::endl;  //Person or person1? Does it have the same size??

    int n = 1000;
    personPtr = new Person[n];  // try to do sizeof personPtr before and after the dynamical allocation

    delete[] personPtr; // Don't forget to delete the allocated memory

    // structure and function
    Rectangle rect;
    rect.length = 5;
    rect.width = 10;

    std::cout << "Area of rectangle: " << rect.area() << std::endl;

    // nested structure
    Employee emp;
    emp.name = "John Doe";
    emp.dateOfJoining.day = 1;
    emp.dateOfJoining.month = 1;
    emp.dateOfJoining.year = 2020;

    std::cout << "Name: " << emp.name << ", Date of Joining: " << emp.dateOfJoining.day << "/" << emp.dateOfJoining.month << "/" << emp.dateOfJoining.year << std::endl;



    return 0;
}
