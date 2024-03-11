#include "TicketManager.h"

TicketManager::TicketManager()
{
}
TicketManager::~TicketManager()
{   
}

void TicketManager::CalculateFee(VehicleTicket& ticket) {
    int fee = 0;
    if (ticket.getVehicleType() == "B") {
        fee = 1000;
    } else if (ticket.getVehicleType() == "M") {
        fee = 2000;
    }
    ticket.setFee(fee);
}

void TicketManager::CheckIn(const VehicleTicket& v)  {
    if (IsTicketContains(v))
        throw invalid_argument("Check In unseccessfully. Ticket already exists.");
    Ticket.Add(v);
}

void TicketManager::CheckOut(const string& vehicleID, const string& TimeOut) {
    bool found = false;
    int index = -1;

    for (int i = 0; i < this->Ticket.Size(); i++) {
        if ((this->Ticket[i]).getVehicleID() == vehicleID) {
            found = true;
            index = i;
            break;
        }
    }

    if (found) {
        CalculateFee(this->Ticket[index]);
        (Ticket[index]).setTimeOut(TimeOut);
        (Ticket[index]).setIsPaid(true);
        AddtoHistory(Ticket[index]);
        Ticket.Remove(Ticket[index]);
    } else {
        throw invalid_argument("Ticket with VehicleID " + vehicleID + " not found");
    }
}

void TicketManager::AddtoHistory(const VehicleTicket& t) {
    HistoryTicket.Add(t);
}

const VehicleTicket TicketManager::GetTicketByTicketID(const string& ticketID) const {
    for (int i = 0; i < HistoryTicket.Size(); i++) {
        if (HistoryTicket[i].getTicketID() == ticketID) {
            return HistoryTicket[i];
        }
    }
    throw invalid_argument("Ticket with ID " + ticketID + " not found.");
}

Employee TicketManager::getEmployeeByName(const string& Name) {
    for (int i = 0; i < employee.Size(); i++) {
        if (employee[i].getName() == Name) {
            return employee[i]; 
        }
    }
    throw invalid_argument("Employee with name " + Name + " not found.");
}

bool TicketManager::IsTicketContains(const VehicleTicket& v) const {
    for (int i = 0; i < HistoryTicket.Size(); i++) {
        if (((HistoryTicket[i]).getVehicleID() == v.getVehicleID() && HistoryTicket[i].getDayIn() == v.getDayIn()) || (HistoryTicket[i]).getTicketID() == v.getTicketID() ) {
            return true;
        }
    }
    return false;
}

const Manager<Employee>& TicketManager::getEmployee() const {
    return this->employee;
}

const Manager<VehicleTicket>& TicketManager::getHistoryTicket() const {
    return this->HistoryTicket;
}

const Manager<VehicleTicket>& TicketManager::getTicket() const {
    return this->Ticket;
}

void TicketManager::InputTickets(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    string ticketID, vehicleType, timeIn, vehicleID, timeOut, dayIn;

    while (getline(file, ticketID, ',')) {
        getline(file, vehicleID, ',');
        getline(file, vehicleType, ',');
        getline(file, timeIn, ',');
        getline(file, dayIn, ',');
        getline(file, timeOut);

        VehicleTicket newTicket(ticketID, vehicleID, vehicleType, timeIn, dayIn);
        CheckIn(newTicket);
        CheckOut(vehicleID, timeOut);
    }
    file.close();
}

void TicketManager::UpdateHistoryTicketFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    for (int i = 0; i < HistoryTicket.Size(); i++) {
        outputFile << HistoryTicket[i].getTicketID() << "," << HistoryTicket[i].getVehicleID() << ","
                   << HistoryTicket[i].getVehicleType() << "," << HistoryTicket[i].getTimeIn() << ","
                   << HistoryTicket[i].getDayIn() << "," << HistoryTicket[i].getTimeOut() << endl;
    }

    outputFile.close();
}

void TicketManager::UpdateTicketFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    for (int i = 0; i < Ticket.Size(); i++) {
        outputFile << Ticket[i].getTicketID() << "," << Ticket[i].getVehicleID() << ","
                   << Ticket[i].getVehicleType() << "," << Ticket[i].getTimeIn() << ","
                   << Ticket[i].getDayIn() << "," << Ticket[i].getTimeOut() << endl;
    }
    outputFile.close();
}

int TicketManager::IndexOf(const string& employeeID) const {
    for (int i = 0; i < employee.Size(); i++) {
        if (employee[i].getEmployeeID() == employeeID) {
            return i;
        }
    }
    return -1;
}

void TicketManager::UpdateEmployeeFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    for (int i = 0; i < employee.Size(); i++) {
        outputFile << employee[i].getName() << "," << employee[i].getEmployeeID() << ","
                   << (employee[i].getGender() ? "1" : "0") << ","
                   << employee[i].getPhoneNum() << "," << employee[i].getAddress() << endl;
    }

    outputFile.close();
}

void TicketManager::AddEmployee(const Employee& s) {
    if (IsEmployeeContains(s))
        throw invalid_argument("Add Employee unseccessfully. EmployeeID already exists.");
    employee.Add(s);
}

void TicketManager::SearchEm(const string& e, int& n) {
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << setw(48) << "THONG TIN NHAN VIEN" << setw(35) << "|" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << "STT" << " |" << setw(15) << "Ten nhan vien"
         << "  | " << setw(12) << "ID nhan vien" << " | " << setw(10) << "Gioi tinh" << setw(3)
         << "| " << setw(8) << "SDT" << setw(8)
         << " | " << setw(10) << "Dia chi" << setw(6) << "| " << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    switch (n)
    {
    case 1: 
    {
        for (int i = 0; i < employee.Size(); i++) {
            if (employee[i].getEmployeeID() == e) {
                string genderStr = (employee[i].getGender() == 0) ? "Nu" : "Nam";
                cout << "|  " << i + 1 << setw(3)
                    << "  | " << left << setw(15) << employee[i].getName()
                    << " |  " << setw(11) << employee[i].getEmployeeID()
                    << " |    " << setw(7) << genderStr << setw(5)
                    << " |" << setw(10) << employee[i].getPhoneNum() 
                    << "  |   " << left << setw(11) << employee[i].getAddress() << " |" << endl;
                }
        }
        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
        break;
    }
    case 2:
    {
        for (int i = 0; i < employee.Size(); i++) {
            if (employee[i].getName() == e) {
                string genderStr = (employee[i].getGender() == 0) ? "Nu" : "Nam";
                cout << "|  " << i + 1 << setw(3)
                    << "  | " << left << setw(15) << employee[i].getName()
                    << " |  " << setw(11) << employee[i].getEmployeeID()
                    << " |    " << setw(7) << genderStr << setw(5)
                    << " |" << setw(10) << employee[i].getPhoneNum() 
                    << "  |   " << left << setw(11) << employee[i].getAddress() << " |" << endl;
                }
        }
        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
        break;
    }
    case 3:
    {
        bool gender;
        (e == "0")?gender = 0:gender = 1;
        for (int i = 0; i < employee.Size(); i++) {
            if (employee[i].getGender() == gender) {
                string genderStr = (employee[i].getGender() == 0) ? "Nu" : "Nam";
                cout << "|  " << i + 1 << setw(3)
                    << "  | " << left << setw(15) << employee[i].getName()
                    << " |  " << setw(11) << employee[i].getEmployeeID()
                    << " |    " << setw(7) << genderStr << setw(5)
                    << " |" << setw(10) << employee[i].getPhoneNum() 
                    << "  |   " << left << setw(11) << employee[i].getAddress() << " |" << endl;
                }
        }
        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
        break;
    }
    case 4:
    {
        for (int i = 0; i < employee.Size(); i++) {
            if (employee[i].getAddress() == e) {
                string genderStr = (employee[i].getGender() == 0) ? "Nu" : "Nam";
                cout << "|  " << i + 1 << setw(3)
                    << "  | " << left << setw(15) << employee[i].getName()
                    << " |  " << setw(11) << employee[i].getEmployeeID()
                    << " |    " << setw(7) << genderStr << setw(5)
                    << " |" << setw(10) << employee[i].getPhoneNum() 
                    << "  |   " << left << setw(11) << employee[i].getAddress() << " |" << endl;
                }
        }
        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
        break;
    }
    default:
    {   cout << "Lua chon khong hop le!";
        break;
    }
    }
    
}

void TicketManager::RemoveEm(const Employee& s) {
    employee.Remove(s);
}

void TicketManager::RemoveAt(const string& employeeID) {
    const Employee emp = GetEmployeeByEmployeeID(employeeID);
    employee.Remove(emp);
    UpdateEmployeeFile("Employees.txt");
    int index = TicketsIndexOf(employeeID);
    if (index != -1) {
        RemoveTicketsByEm(ticketsbyemployee[index]);
        UpdateTicketByEmployeeFile("TicketsByEmployee.txt");
    }
}

void TicketManager::UpdateEm(const string& employeeID) {
    for (int i = 0; i < employee.Size(); i++) {
        if (employee[i].getEmployeeID() == employeeID) {
            employee[i] >> cin;
        }
    }
    UpdateEmployeeFile("Employees.txt");
}

bool TicketManager::IsEmployeeContains(const Employee& e) const {
    for (int i = 0; i < employee.Size(); i++) {
        if ((employee[i]).getEmployeeID() == e.getEmployeeID()) {
            return true;
        }
    }
    return false;
}

void TicketManager::InputEmployee(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    string employeeName, employeeID, gender, phoneNum, address;

    while (getline(file, employeeName, ',')) {
        getline(file, employeeID, ',');
        getline(file, gender, ',');
        getline(file, phoneNum, ',');
        getline(file, address);

        bool isMale = (gender == "1");
        Employee newEmployee(employeeName, employeeID, isMale, phoneNum, address);
        AddEmployee(newEmployee);
    }

    file.close();
}

void TicketManager::TicketsByEm(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    string employeeID, ticketID;

    while (file >> ticketID >> employeeID) {
        int index = IndexOf(employeeID);
        if (index != -1) {
            int ticketindex = TicketsIndexOf(employeeID);
            if (ticketindex != -1) {
                    VehicleTicket vt = GetTicketByTicketID(ticketID);
                    ticketsbyemployee[ticketindex].AddTicket(vt);
            }
            else {
                TicketsByEmployee newEmployee(employeeID, ticketID);
                AddTicketsByEm(newEmployee);
                int IndexEm = TicketsIndexOf(employeeID);
                VehicleTicket vt = GetTicketByTicketID(ticketID);
                ticketsbyemployee[IndexEm].AddTicket(vt);
            }
        } else {
            cerr << "Employee with ID " << employeeID << " not found." << endl;
        }
    }
    file.close();
}

void TicketManager::UpdateTicketByEmployeeFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    for (int i = 0; i < ticketsbyemployee.Size(); i++) {
        const Manager<VehicleTicket>& tickets = ticketsbyemployee[i].getTicket();
        for (int j = 0; j < tickets.Size(); j++) {
            outputFile << tickets[j].getTicketID() << " " << ticketsbyemployee[i].getEmployeeID() << endl;
        }
    }

    outputFile.close();
}

void TicketManager::LoadData(const string& tickets, const string& employeesFile, const string& ticketsFile) {
    InputTickets(tickets);
    InputEmployee(employeesFile);
    TicketsByEm(ticketsFile);
}

const Employee TicketManager::GetEmployeeByEmployeeID(const string& employeeID) const {
    for (int i = 0; i < employee.Size(); i++) {
        if (employee[i].getEmployeeID() == employeeID) {
            return employee[i];
        }
    }
    throw invalid_argument("Employee with ID " + employeeID + " not found.");
}

const Manager<TicketsByEmployee>& TicketManager::getTicketsByEmployee() const {
    return ticketsbyemployee;
}

void TicketManager::AddTicketsByEm(const TicketsByEmployee& t) {
    ticketsbyemployee.Add(t);
}

int TicketManager::TicketsIndexOf(const string& employeeID) const {
    for (int i = 0; i < ticketsbyemployee.Size(); i++) {
        if (ticketsbyemployee[i].getEmployeeID() == employeeID) {
            return i;
        }
    }
    return -1;
}

void TicketManager::RemoveTicketsByEm(const TicketsByEmployee& tk) {
    ticketsbyemployee.Remove(tk);
}

void TicketManager::ProfitInDay(const string& day) {
    int totalProfit = 0;
    int count = 0;
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "| " << setw(35) << "BAO CAO NGAY " << day << " CUA BAI DO XE" << setw(20) << "|"<< endl;
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "| " << setw(10) << "Ticket ID" << " | " << setw(11) << "Vehicle ID"
         << " | " << setw(13) << "Vehicle Type" << " | " << setw(10) << "Time In"
         << " | " << setw(10) << "Time Out" << " | " << setw(7) << "Fee" << "  |" << endl;
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    for (int i = 0; i < HistoryTicket.Size(); i++) {
        string VT = (HistoryTicket[i].getVehicleType() == "B") ? "Bicycle" : "Motobike";
        if (HistoryTicket[i].getIsPaid() && HistoryTicket[i].getDayIn().substr(0, 10) == day) {

            cout << "| " << setw(10) << this->HistoryTicket[i].getTicketID()
                 << " | " << setw(11) << this->HistoryTicket[i].getVehicleID()
                 << " | " << setw(13) << VT
                 << " | " << setw(10) << this->HistoryTicket[i].getTimeIn()
                 << " | " << setw(10) << this->HistoryTicket[i].getTimeOut()
                 << " | " << setw(7) << to_string(this->HistoryTicket[i].getFee()) + " VND" << " |" << endl;

            totalProfit += this->HistoryTicket[i].getFee();
            count++;
        }
    }
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "Tong xe quan ly trong ngay " << day << " :" << count << endl;
    cout << "Tong doanh thu trong ngay " << day << " :" << totalProfit << " VND" << endl;
}

void TicketManager::ProfitByEmployeeInDay(const string& Name, const string& day) {

    int totalProfit = 0;
    int count = 0;
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "| " << setw(37) << "BAO CAO DOANH THU CUA NHAN VIEN " << Name << " TRONG NGAY " << day << setw(8) << "|"<< endl;
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "| " << setw(10) << "Ticket ID" << " | " << setw(11) << "Vehicle ID"
         << " | " << setw(13) << "Vehicle Type" << " | " << setw(10) << "Time In"
         << " | " << setw(10) << "Time Out"
         << " | " << setw(7) << "Fee" << "  |" << endl;
     cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;    
    
    for(int i = 0; i < ticketsbyemployee.Size(); i++) {
        
        const TicketsByEmployee& currentTicketsByEmployee = ticketsbyemployee[i];
        Employee e = getEmployeeByName(Name);
        if (e.getEmployeeID() == ticketsbyemployee[i].getEmployeeID()) {
            const Manager<VehicleTicket> Tickets = ticketsbyemployee[i].getTicket();
            string VT = (Tickets[i].getVehicleType() == "B") ? "Bicycle" : "Motobike";
            for (int j = 0; j < Tickets.Size(); j++) {
                if (Tickets[j].getDayIn().substr(0, 10) == day ) {
                    cout << "| " << setw(10) << Tickets[j].getTicketID()
                        << " | " << setw(11) << Tickets[j].getVehicleID()
                        << " | " << setw(13) << VT
                        << " | " << setw(10) << Tickets[j].getTimeIn()
                        << " | " << setw(10) << Tickets[j].getTimeOut()
                        << " | " << setw(7) << to_string(Tickets[j].getFee()) + " VND" << " |" << endl;
                    if (Tickets[j].getIsPaid()) {
                        totalProfit += Tickets[j].getFee();
                        count++;
                    }
                }

            }
        }
    }
    cout << setfill('-') << setw(81) << "" << setfill(' ') << endl;
    cout << "Tong xe nhan vien " << Name << " quan ly trong ngay " << day << ": " << count << endl;
    cout << "Tong doanh thu cua nhan vien " << Name << " trong ngay " << day << ": " << totalProfit << " VND" << endl;
}

void TicketManager::ProfitInMonth(const string& day)
{
    int totalProfit = 0;
    int count = 0;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(40) << "BAO CAO THANG "<< day <<" CUA BAI DO XE:" << setw(30) << "|" << endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(10) << "Ticket ID" << " | " << setw(11) << "Vehicle ID"
         << " | " << setw(13) << "Vehicle Type" << " | " << setw(10) << "Time In"
         << " | " << setw(10) << "Time Out"
         << " | " << setw(10) << "Day In" << " | " << setw(7) << "Fee" << "  |" << endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;

    for (int i = 0; i < HistoryTicket.Size(); i++) {
        string VT = (HistoryTicket[i].getVehicleType() == "B") ? "Bicycle" : "Motobike";
        if (HistoryTicket[i].getDayIn().substr(0, 7) == day ) {
            cout << "| " << setw(10) << this->HistoryTicket[i].getTicketID()
                 << " | " << setw(11) << this->HistoryTicket[i].getVehicleID()
                 << " | " << setw(13) << VT
                 << " | " << setw(10) << this->HistoryTicket[i].getTimeIn()
                 << " | " << setw(10) << this->HistoryTicket[i].getTimeOut()
                 << " | " << setw(8) << this->HistoryTicket[i].getDayIn()
                 << " | " << setw(7) << to_string(this->HistoryTicket[i].getFee()) + " VND" << " |" << endl;

            if (HistoryTicket[i].getIsPaid()) {
                totalProfit += HistoryTicket[i].getFee();
                count++;
            }
        }
    }
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "Tong xe quan ly trong thang " << day << ": " << count << endl;
    cout << "Tong doanh thu cua bai do xe trong thang " << day << ": " << totalProfit << " VND" << endl;
 }

void TicketManager::ProfitByEmployeeInMonth(const string& Name, const string& day) {

    int totalProfit = 0;
    int count = 0;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(45) << "BAO CAO DOANH THU CUA NHAN VIEN " << Name << " TRONG THANG " << day << setw(16) << "|"<< endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(10) << "Ticket ID" << " | " << setw(11) << "Vehicle ID"
         << " | " << setw(13) << "Vehicle Type" << " | " << setw(10) << "Time In"
         << " | " << setw(10) << "Time Out"
         << " | " << setw(10) << "Day In" << " | " << setw(7) << "Fee" << "  |" << endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;    
    
    Employee e = getEmployeeByName(Name);
    for(int i = 0; i < ticketsbyemployee.Size(); i++) {
        const TicketsByEmployee& currentTicketsByEmployee = ticketsbyemployee[i];
        if (e.getEmployeeID() == ticketsbyemployee[i].getEmployeeID()) {
            const Manager<VehicleTicket> Tickets = ticketsbyemployee[i].getTicket();
            for (int j = 0; j < Tickets.Size(); j++) {
                string VT = (Tickets[j].getVehicleType() == "B") ? "Bicycle" : "Motobike";
                if (Tickets[j].getDayIn().substr(0, 7) == day ) {
                    cout << "| " << setw(10) << Tickets[j].getTicketID()
                        << " | " << setw(11) << Tickets[j].getVehicleID()
                        << " | " << setw(13) << VT
                        << " | " << setw(10) << Tickets[j].getTimeIn()
                        << " | " << setw(10) << Tickets[j].getTimeOut()
                        << " | " << setw(8) << Tickets[j].getDayIn()
                        << " | " << setw(7) << to_string(Tickets[j].getFee()) + " VND" << " |" << endl;
                    if (Tickets[j].getIsPaid()) {
                        totalProfit += Tickets[j].getFee();
                        count++;
                    }
               }

            }
        }
    }
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "Tong xe nhan vien " << Name << " quan ly trong thang " << day << ": " << count << endl;
    cout << "Tong doanh thu cua nhan vien " << Name << " trong thang " << day << ": " << totalProfit << " VND" << endl;
}

void TicketManager::ProfitByEmployee() {
    int totalProfit = 0;
    int totalMotorbike = 0;
    int totalBicycle = 0;

    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << setw(43) << "THONG KE" << setw(40) << "|" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;   
    cout << "| " << "STT" << " |" << setw(15) << "Ten nhan vien"
         << "  | " << setw(10) << "ID nhan vien" << " | " << setw(10) << "Motorbike" << setw(5)
         << " | " << setw(10) << "Bicycle" << setw(5) 
         << " | " << setw(10) << "Tong tien" << setw(5) << " | " << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;

    for(int i = 0; i < ticketsbyemployee.Size(); i++) {

        int motorbikeCount = 0;
        int bicycleCount = 0;
        int profitByEmployee = 0;

        const Employee& currentEmployee = GetEmployeeByEmployeeID(ticketsbyemployee[i].getEmployeeID());
        const Manager<VehicleTicket>& employeeTickets = ticketsbyemployee[i].getTicket();

        for (int j = 0; j < employeeTickets.Size(); j++) {
            const VehicleTicket& currentTicket = employeeTickets[j];

            if (currentTicket.getIsPaid()) {
                    profitByEmployee += currentTicket.getFee();
                if (currentTicket.getVehicleType() == "M") {
                    motorbikeCount++;
                } else if (currentTicket.getVehicleType() == "B") {
                    bicycleCount++;
                }
            }
        }

      cout << "|  " << i + 1 << setw(3)
            << "  | " << left << setw(15) << currentEmployee.getName()
            << " |  " << setw(11) << currentEmployee.getEmployeeID() 
            << " |      " << setw(7) << motorbikeCount << setw(5)
            << " |      " << setw(7) << bicycleCount << setw(5)
            << " | " << setw(5) << profitByEmployee << "VND" << "   |" << endl;


        totalMotorbike += motorbikeCount;
        totalBicycle += bicycleCount;
        totalProfit += profitByEmployee;
    }
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << setw(20) <<  right << "Tong" << setw(18) << "          |" 
         << setw(7) << totalMotorbike << setw(8) << "|"
         << setw(7) << totalBicycle << setw(8) << "|"
         << setw(8) << totalProfit << " VND" << setw(3) << "|" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
}

void TicketManager::Profit()
{
    TicketsSort();
    int totalProfit = 0;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(48) << "THONG KE VE" << setw(44) << "|" << endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "| " << setw(10) << "Ticket ID" << " | " << setw(11) << "Vehicle ID"
         << " | " << setw(13) << "Vehicle Type" << " | " << setw(10) << "Time In"
         << " | " << setw(10) << "Time Out"
         << " | " << setw(10) << "Day In" << " | " << setw(7) << "Fee" << "  |" << endl;
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;

    for (int i = 0; i < HistoryTicket.Size(); i++) {
        string VT = (HistoryTicket[i].getVehicleType() == "B") ? "Bicycle" : "Motobike";
        if (HistoryTicket[i].getIsPaid() ) {
            cout << "| " << setw(10) << HistoryTicket[i].getTicketID()
                 << " | " << setw(11) << HistoryTicket[i].getVehicleID()
                 << " | " << setw(13) <<VT
                 << " | " << setw(10) << HistoryTicket[i].getTimeIn()
                 << " | " << setw(10) << HistoryTicket[i].getTimeOut()
                 << " | " << setw(8) << HistoryTicket[i].getDayIn()
                 << " | " << setw(7) << to_string(HistoryTicket[i].getFee()) + " VND" << " |" << endl;

            if (HistoryTicket[i].getIsPaid()) {
                totalProfit += HistoryTicket[i].getFee();
            }
        }
    }
    cout << setfill('-') << setw(94) << "" << setfill(' ') << endl;
    cout << "Tong doanh thu cua bai do xe : " << totalProfit << " VND" << endl;
}

void TicketManager::PrintEmployees()
{
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << setw(48) << "THONG TIN NHAN VIEN" << setw(35) << "|" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    cout << "| " << "STT" << " |" << setw(15) << "Ten nhan vien"
         << "  | " << setw(12) << "ID nhan vien" << " | " << setw(10) << "Gioi tinh" << setw(3)
         << "| " << setw(8) << "SDT" << setw(8)
         << " | " << setw(10) << "Dia chi" << setw(6) << "| " << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
for (int i = 0; i < employee.Size(); i++) {
    string genderStr = (employee[i].getGender() == 0) ? "Nu" : "Nam";

    cout << "|  " << i + 1 << setw(3)
         << "  | " << left << setw(15) << employee[i].getName()
         << " |  " << setw(11) << employee[i].getEmployeeID()
         << " |    " << setw(7) << genderStr << setw(5)
         << " |" << setw(10) << employee[i].getPhoneNum() 
         << "  |   " << left << setw(11) << employee[i].getAddress() << " |" << endl;
}

cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
}

void TicketManager::Swap(VehicleTicket& a, VehicleTicket& b) {
    VehicleTicket t = a;
    a = b;
    b = t;
}

void TicketManager::TicketsSort() {
    int n = HistoryTicket.Size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
                if (Convert::Compare(HistoryTicket[j].getDayIn(), HistoryTicket[j + 1].getDayIn()) == 1) {
                Swap(HistoryTicket[j], HistoryTicket[j + 1]);
            }
        }
    }
}