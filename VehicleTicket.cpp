#include "VehicleTicket.h"

VehicleTicket::VehicleTicket(string tk, string v, string vt, string t, string di, string to) 
: TicketID(tk), Vehicle(v, vt), TimeIn(t), DayIn(di), isPaid(false), TimeOut("N/A")
{
}  

VehicleTicket::~VehicleTicket() {

}

const string VehicleTicket::getDayIn() const {
    return this->DayIn;
}

void VehicleTicket::setDayIn(const string& d) {
    this->DayIn = d;
}

void VehicleTicket::setFee(int fee) {
    this->Fee = fee;
}

void VehicleTicket::setFee() {
    this->Fee = 0;
    if (this->VehicleType == "B")
        this->Fee = 1000;
    else if (this->VehicleType == "M")
        this->Fee = 2000;
}

void VehicleTicket::setTimeOut(const string& timeOut) {
    this->TimeOut = timeOut;
}

const string VehicleTicket::getTimeOut() const {
    return this->TimeOut;
}

const string VehicleTicket::getVehicleType() const {
    return this->VehicleType;
}

const string VehicleTicket::getTicketID() const {
    return this->TicketID;
}

const string VehicleTicket::getVehicleID() const {
    return this->VehicleID;
}

const int VehicleTicket::getFee() const {
    return this->Fee;
}

const string VehicleTicket::getTimeIn() const {
    return this->TimeIn;
}

void VehicleTicket::setIsPaid(bool paid) {
    this->isPaid = paid;
}

const bool VehicleTicket::getIsPaid() const {
    return this->isPaid;
}

const string VehicleTicket::getDate() const {
    string dayin;
    time_t currentTime = time(nullptr);
    tm* currentDateTime = localtime(&currentTime);
    stringstream dayStream;
    dayStream << setw(4) << (currentDateTime->tm_year + 1900) << '/'
              << setw(2) << setfill('0') << (currentDateTime->tm_mon + 1) << '/'
              << setw(2) << setfill('0') << currentDateTime->tm_mday;
    dayin = dayStream.str();
    return dayin;
}

const string VehicleTicket::getTime() const {
    string timein;
    time_t currentTime = time(nullptr);
    tm* currentDateTime = localtime(&currentTime);
    stringstream timeStream;
    timeStream << setw(2) << setfill('0') << currentDateTime->tm_hour << 'h'
               << setw(2) << setfill('0') << currentDateTime->tm_min;
    timein = timeStream.str();
    return timein;
}

ostream& operator<<(ostream& o,const VehicleTicket& v) {
    o << v.TicketID << ", " << v.VehicleID << ", " << v.VehicleType << ", " << v.TimeIn << ", " << v.TimeOut << ", " << v.DayIn << ", " << v.Fee << endl;
    return o;
}

istream& operator>>(istream& i, VehicleTicket& v) {
    cout << "Enter TicketID: ";
    i >> v.TicketID;
    cout << "Enter VehicleID: ";
    i >> v.VehicleID;
    cout << "Enter Vehicle Type (B/M): ";
    i >> v.VehicleType;
    v.TimeIn = v.getTime();
    v.DayIn = v.getDate();
    return i;
}

bool VehicleTicket::operator==(const VehicleTicket& other) {
    return this->TicketID == other.TicketID &&
           this->VehicleID == other.VehicleID &&
           this->VehicleType == other.VehicleType &&
           this->TimeIn == other.TimeIn &&
           this->TimeOut == other.TimeOut &&
           this->Fee == other.Fee &&
           this->isPaid == other.isPaid;
}
