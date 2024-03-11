#ifndef TICKETSBYEMPLOYEE_H
#define TICKETSBYEMPLOYEE_H
#include <fstream>
#include "Manager.cpp"
#include "Employee.h"
#include "VehicleTicket.h"

class TicketsByEmployee 
{
    private:
        string EmployeeID;
        string TicketID;
        Manager<VehicleTicket> Ticket;
    public:
        TicketsByEmployee(string = "", string = "");
        ~TicketsByEmployee();
        const string getEmployeeID() const;
        const string getTicketID() const;
        void AddTicket(const VehicleTicket&);
        const Manager<VehicleTicket>& getTicket() const;
        friend ostream& operator<<(ostream&, const TicketsByEmployee&);
        bool operator==(const TicketsByEmployee&);          
};

#endif


