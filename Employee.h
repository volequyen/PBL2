#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include <iostream>

using namespace std;
class Employee {
    private:
        string Name;
        string EmployeeID;
        bool Gender;
        string PhoneNum;
        string Address;
    public:
        Employee(string = "", string = "", bool = 0, string = "", string = "");
        ~Employee();
        const string getName() const;
        const string getEmployeeID() const;
        const bool getGender() const;
        const string getPhoneNum() const;
        const string getAddress() const;
        bool operator==(const Employee&);
        friend ostream& operator<<(ostream&, const Employee&);
        friend istream& operator>>(istream&, Employee&);
        friend istream& operator>>(Employee&, istream&);
};

#endif