#include "Vehicle.h"

class VehicleTicket : public Vehicle {
    private:
        string TicketID;
        string TimeIn;
        string TimeOut;
        string DayIn;
        int Fee;
        bool isPaid;
    public:
        VehicleTicket(string = "", string = "", string = "", string = "", string = "", string = "");
        ~VehicleTicket();
        void setFee(int);
        void setFee();
        void setTimeOut(const string&);
        void setIsPaid(bool);
        void setDayIn(const string&);
        const int getFee() const;
        const bool getIsPaid() const;
        const string getDayIn() const;
        const string getTimeIn() const;
        const string getTimeOut() const;
        const string getVehicleType() const;
        const string getTicketID() const;
        const string getVehicleID() const;
        const string getDate() const;
        const string getTime() const;

        bool operator==(const VehicleTicket&);
        friend ostream& operator<<(ostream&, const VehicleTicket&);
        friend istream& operator>>(istream&, VehicleTicket&);
};

