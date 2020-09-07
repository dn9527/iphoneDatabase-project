/// iPhone class
/// Dat Nguyen

#ifndef IPHONE_H
#define IPHONE_H

#include <iostream>
using namespace std; //std::string;


class iPhone
{
private:
     string IMEI;
     string capacity;
     string serial;
     string model;
     string manuLocn;
public:
    /// constructors
    iPhone() {} /// default constructor
    iPhone(const string& IMEIIn, const string& capacityIn, const string& serialIn, const string& modelIn, const string& locnIn)
    {
        IMEI = IMEIIn;
        serial = serialIn;
        capacity = capacityIn;
        model = modelIn;
        manuLocn = locnIn;
    }

    /// getters
     string getIMEI() const {return IMEI;}
     string getSerial() const {return serial;}
     string getModel() const {return model;}
     string getCapacity() const {return capacity;}
     string getCountry() const {return manuLocn;}
     void displayInfo();
    /// setters
    void setIMEI(const string& IMEI_in){ IMEI = IMEI_in;}
    void setSerial(const string& data) {serial = data;}
    void setModel(const string& data) {model = data;}
    void setCapacity(const string& data) {capacity = data;}
    void setCountry(const string& data) {manuLocn = data;}
    void setInfo(string IMEI_in, string capacity_in, string serialNum_in, string model_in, string manuLocn_in)
    {
        IMEI = IMEI_in;
        capacity = capacity_in;
        serial = serialNum_in;
        model = model_in;
        manuLocn = manuLocn_in;
    
    }
    
    // operator overloads(Vera added)
    friend std::ostream &operator <<(std::ostream & out, const iPhone &obj);
    iPhone &operator =(const iPhone & rh);
    bool operator <(const iPhone & rh);
    bool operator >(const iPhone & rh);
    bool operator ==(const iPhone & rh);
    
    /*/// overloaded
    bool  operator==(const iPhone& item) const
    {
        return IMEI == item.getIMEI();
    }
    bool  operator<(const iPhone& item) const
    {
        return IMEI < item.getIMEI();
    }*/
};

#endif
