#include "TicketsByEmployee.h"

TicketsByEmployee::TicketsByEmployee(string i, string ti)
: EmployeeID(i), TicketID(ti)
{
    
}

TicketsByEmployee::~TicketsByEmployee()
{}

const string TicketsByEmployee::getEmployeeID() const {
    return this->EmployeeID;
}

const string TicketsByEmployee::getTicketID() const {
    return this->TicketID;
}

void TicketsByEmployee::AddTicket(const VehicleTicket& v) {
    Ticket.Add(v);
}

const Manager<VehicleTicket>& TicketsByEmployee::getTicket() const {
    return this->Ticket;
}

bool TicketsByEmployee::operator==(const TicketsByEmployee& e) {
    return EmployeeID == e.EmployeeID &&
           TicketID == e.TicketID;
}
