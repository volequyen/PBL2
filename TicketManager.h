#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H
#include "TicketsByEmployee.h"
#include "Employee.h"
#include "Convert.h"

class TicketManager
{
    private:
        Manager<Employee> employee;
        Manager<TicketsByEmployee> ticketsbyemployee; 
        Manager<VehicleTicket> Ticket;
        Manager<VehicleTicket> HistoryTicket;
    public:
        TicketManager();
        ~TicketManager();
        void CalculateFee(VehicleTicket&);
        void CheckIn(const VehicleTicket&);
        void CheckOut(const string&, const string&);
        void AddtoHistory(const VehicleTicket&);
        const VehicleTicket GetTicketByTicketID(const string&) const; 
        Employee getEmployeeByName(const string&);
        const Manager<VehicleTicket>& getHistoryTicket() const;
        const Manager<VehicleTicket>& getTicket() const;
        bool IsTicketContains(const VehicleTicket&) const;
        void InputTickets(const string&);
        void UpdateHistoryTicketFile(const string&);
        void UpdateTicketFile(const string&);
        void Swap(VehicleTicket&, VehicleTicket&);
        void TicketsSort();

        void AddEmployee(const Employee&);
        bool IsEmployeeContains(const Employee&) const;
        const Manager<Employee>& getEmployee() const;
        const Employee GetEmployeeByEmployeeID(const string&) const;
        void Insert(const Employee&, const int&);
        int IndexOf(const string&) const;
        void SearchEm(const string&, int&);
        void RemoveEm(const Employee&);
        void RemoveAt(const string&);
        void UpdateEm(const string&);
        void UpdateEmployeeFile(const string&);
        void InputEmployee(const string&);

        void TicketsByEm(const string&);
        void LoadData(const string&, const string&, const string&);
        void AddTicketsByEm(const TicketsByEmployee&);
        void RemoveTicketsByEm(const TicketsByEmployee&);
        int TicketsIndexOf(const string&) const;
        void UpdateTicketByEmployeeFile(const string&);
        const Manager<TicketsByEmployee>& getTicketsByEmployee() const;

        void ProfitInDay(const string& );
        void ProfitByEmployeeInDay(const string&, const string&); 
        void ProfitInMonth(const string&);
        void ProfitByEmployeeInMonth(const string&, const string&);
        void Profit();
        void ProfitByEmployee();
        void PrintEmployees();

};

#endif
