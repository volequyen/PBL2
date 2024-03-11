#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Vehicle
{
    protected:
        string VehicleID;
        string VehicleType;
    public:
        Vehicle(string = "", string = "");
        ~Vehicle();

};

#endif

