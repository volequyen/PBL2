#include "Employee.h"

Employee::Employee(string n, string id, bool g, string pn, string add) 
: Name(n), EmployeeID(id), Gender(g), PhoneNum(pn), Address(add) {

}

Employee::~Employee() {

}

const string Employee::getName() const {
    return this->Name;
}

const string Employee::getEmployeeID() const {
    return this->EmployeeID;
}

const bool Employee::getGender() const {
    return this->Gender;
}

const string Employee::getPhoneNum() const {
    return this->PhoneNum;
}

const string Employee::getAddress() const {
    return this->Address;
}

bool Employee::operator==(const Employee& e) {
    return Name == e.Name &&
           EmployeeID == e.EmployeeID &&
           Gender == e.Gender &&
           PhoneNum == e.PhoneNum &&
           Address == e.Address;
}

ostream& operator<<(ostream& o, const Employee& e)
{
    o << "Name: " << e.Name << endl
      << "EmployeeID: " << e.EmployeeID << endl
      << "Gender: " << e.Gender << endl
      << "Phone Number: " << e.PhoneNum << endl
      << "Address: " << e.Address << endl;
    return o;
}

istream& operator>>(istream& i, Employee& e) {
    cout << "Enter EmployeeName: ";
    i.ignore();
    getline(i, e.Name);
    cout << "Enter EmployeeID: ";
    i >> e.EmployeeID;
    cout << "Gender (0/1): ";
    i >> e.Gender;
    cout << "Enter Phone Number: ";
    i >> e.PhoneNum;
    cout << "Enter Address: ";
    i.ignore();
    getline(i, e.Address);
    return i;
}

istream& operator>>(Employee& e, istream& i) {
    cout << "Enter New Phone Number: ";
    i >> e.PhoneNum;
    cout << "Enter New Address: ";
    i.ignore();
    getline(i, e.Address);
    return i;
}