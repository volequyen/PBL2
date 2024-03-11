#include "TicketManager.h"

void PrintMenu() {
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
    cout << "|" << setw(38) << "QUAN LI NHA GIU XE SINH VIEN" << setw(11) << "|" <<endl;
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
        cout << "                ===== MENU =====        " << endl;
        cout << "1. Check In" << endl;
        cout << "2. Check Out" << endl;
        cout << "3. Bao cao doanh thu trong ngay " << endl;
        cout << "4. Bao cao doanh thu cua nhan vien trong ngay" << endl;
        cout << "5. Bao cao doanh thu trong thang" << endl;
        cout << "6. Bao cao doanh thu cua nhan vien trong thang" << endl;
        cout << "7. Bao cao doanh thu theo tung nhan vien" << endl;
        cout << "8. Thong ke ve" << endl;
        cout << "9. Them nhan vien" << endl;
        cout << "10. Sua thong tin nhan vien" << endl;
        cout << "11. Tim kiem thong tin nhan vien" << endl;
        cout << "12. Xoa nhan vien" << endl;
        cout << "13. In thong tin nhan vien" << endl;
        cout << "14. Thoat" << endl;
        cout << "Nhap lua chon: ";
}

int main() {
    TicketManager t;
    t.LoadData("Tickets.txt", "Employees.txt", "TicketsByEmployee.txt");
    int n;
    do {
        PrintMenu();
        cin >> n;
          switch (n) {
            case 1: 
            {
                VehicleTicket v;
                cin >> v;
                string employeeID;
                cout << "Enter EmployeeID manage: ";
                cin >> employeeID;
                t.CheckIn(v);
                int index = t.TicketsIndexOf(employeeID);
                if (index != -1)         
                    t.getTicketsByEmployee()[index].AddTicket(v);
                else {
                    TicketsByEmployee tb(employeeID, v.getTicketID());
                    tb.AddTicket(v);
                    t.AddTicketsByEm(tb);
                }
                t.UpdateTicketFile("TicketsNow.txt");
                t.UpdateTicketByEmployeeFile("TicketsByEmployee.txt");
                cout << "Check In sucessfully!" << endl;
                cout << "Time In: " << v.getDayIn() << " " << v.getTimeIn() << endl;
                system("pause");
                break;
            }
            case 2:
                {
                    VehicleTicket v;
                    string vehicleID, timeOut;
                    cout << "Enter VehicleID: ";
                    cin >> vehicleID;
                    timeOut = v.getTime();

                    const Manager<TicketsByEmployee>& ticketsbyem = t.getTicketsByEmployee();
                    for (int i = 0; i < ticketsbyem.Size(); i++) {
                        const Manager<VehicleTicket>& employeeTickets = ticketsbyem[i].getTicket();
                        for (int j = 0; j < employeeTickets.Size(); j++) {
                            if (employeeTickets[j].getVehicleID() == vehicleID) {
                                employeeTickets[j].setTimeOut(timeOut);
                                employeeTickets[j].setIsPaid(true);
                                employeeTickets[j].setFee();
                                break;
                            }
                        }
                    }

                    t.CheckOut(vehicleID, timeOut);
                    t.UpdateHistoryTicketFile("Tickets.txt"); 
                    t.UpdateTicketFile("TicketsNow.txt");
                    cout << "Check Out successfully!" << endl;
                    cout << "Time Out: " << timeOut << endl;
                    system("pause");
                    break;
                }
            case 3:
            {
                string day;
                cout << "Enter DayIn: ";
                cin >> day;
                t.ProfitInDay(day);
                system("pause");
                break;
            }
            case 4:
            {
                string Name, day;
                cin.ignore();
                cout <<"Enter EmployeeName: " ;
                getline(cin,Name);
                cout <<"Enter Day: ";
                cin >> day;
                t.ProfitByEmployeeInDay(Name, day);
                system("pause");
                break;
            }
            case 5:
            {
                string day;
                cout << "Enter Month: " ;
                cin >> day;
                t.ProfitInMonth(day);
                system("pause");
                break;
            }
            case 6: 
            {
        
                string Name, month;
                cin.ignore();
                cout << "Enter EmployeeName: ";
                getline(cin,Name);
                cout << "Enter Month: ";
                cin >> month;
                t.ProfitByEmployeeInMonth(Name, month);
                system("pause");
                break;
            }

            case 7:
            {
                t.ProfitByEmployee();
                system("pause");
                break;
            }
            case 8:
            {
                t.Profit();
                system("pause");
                break;
            }
            case 9:
            {
                Employee e;
                cin >> e;
                t.AddEmployee(e);
                t.UpdateEmployeeFile("Employees.txt");
                cout << "Add Employee successfully!" << endl;
                system("pause");
                break;
            }
            case 10:
            {
                string employeeID;
                cout << "Enter EmployeeID: ";
                cin >> employeeID;
                t.UpdateEm(employeeID);
                cout << "Update sucessfully!" << endl;
                system("pause");
                break;
            }
            case 11:
            {
                int n;
                string e;
                cout << "Tim kiem thong tin nhan vien dua tren: " << endl;
                cout << "1. EmployeeID" << endl;
                cout << "2. EmployeeName" << endl;
                cout << "3. Gender" << endl;
                cout << "4. Address" << endl;
                cout << "Nhap lua chon: ";
                cin >> n;
                cout << "Nhap thong tin can tim: ";
                getline(cin.ignore(), e);
                t.SearchEm(e, n);
                system("pause");
                break;
            }
            case 12:
            {
                string id, yn;
                cout << "Enter EmployeeID: ";
                cin >> id;
                cout << "Do you want to remove Employee with ID " << id << " (Y/N)?" << endl;
                cin >> yn;
                if (yn == "Y") {
                    t.RemoveAt(id);
                    cout << "Remove Employee successfully!" << endl;
                }
                else cout << "Exit" << endl;
                system("pause");
                break;
            }
            case 13:
            {
                t.PrintEmployees();
                system("pause");
                break;
            }
            case 14:
            {
                cout << "Ban da thoat khoi chuong trinh!" << endl;
                break;
            }
            default:
            {
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                break;
            }
          }
    } while (n != 14);

    return 0;
}


