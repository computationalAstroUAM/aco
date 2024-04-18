//
// Created by weiguang on 18/04/24.
//
/*In C++, you can derive a class from another class. The derived class inherits all members of the base class, except for:
 *
 * - Constructors, destructors, and copy constructors of the base class
 * - Overloaded operators of the base class
 * - The friend functions of the base class
 *
 * The derived class can access the public and protected members of the base class, but not the private members. The access
 * level of the members of the base class is not changed in the derived class.*/

//In this code, DerivedPublic, DerivedProtected, and DerivedPrivate are subclasses of Base with public, protected,
// and private inheritance respectively. Each subclass has a method accessBaseMembers that tries to access the members
// of the base class.

#include <iostream>

class Base {
public:
    int publicMember;
protected:
    int protectedMember;
private:
    int privateMember;
};

class DerivedPublic : public Base {
public:
    void accessBaseMembers() {
        publicMember = 10; // Accessible
        protectedMember = 20; // Accessible
        // privateMember = 30; // Not accessible
    }
};

class DerivedProtected : protected Base {
public:
    void accessBaseMembers() {
        publicMember = 10; // Accessible
        protectedMember = 20; // Accessible
        // privateMember = 30; // Not accessible
    }
};

class DerivedPrivate : private Base {
public:
    void accessBaseMembers() {
        publicMember = 10; // Accessible
        protectedMember = 20; // Accessible
        // privateMember = 30; // Not accessible
    }
};
class Student {
public:
    std::string name;
    int age;
    float gpa;
};

int main() {
    Student s1;
    s1.name = "John Doe";
    s1.age = 20;
    s1.gpa = 3.5;

    std::cout << "Name: " << s1.name << ", Age: " << s1.age << ", GPA: " << s1.gpa << std::endl;


    DerivedPublic dp;
    dp.accessBaseMembers();
    std::cout << "DerivedPublic publicMember: " << dp.publicMember << std::endl;

    DerivedProtected dpro;
    dpro.accessBaseMembers();
    // Can't directly access protected members from an object
    // std::cout << "DerivedProtected publicMember: " << dpro.publicMember << std::endl;

    DerivedPrivate dpri;
    dpri.accessBaseMembers();
    // Can't directly access private members from an object
    // std::cout << "DerivedPrivate publicMember: " << dpri.publicMember << std::endl;

    return 0;
}