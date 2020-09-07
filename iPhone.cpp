// Created by: Zhuoxuan Wang
#include "iPhone.h"
//#include <iostream>
#include <iomanip>
//using namespace std;

/*iPhone::iPhone()
{
    IMEI = "";
    capacity = "";
    serial = "";
    model = "";
    manuLocn = "";
    
}
*/
/*iPhone::iPhone(std::string IMEI_in, std::string capacity_in, std::string serialNum_in, std::string model_in, std::string manuLocn_in)
{
    IMEI = IMEI_in;
    capacity = capacity_in;
    serialNum = serialNum_in;
    model = model_in;
    manuLocn = manuLocn_in;
}*/

ostream &operator <<(ostream & out, const iPhone &obj)
{
    /*cout << left << setw(25) << "IMEI number: " << obj.IMEI
    << setw(10) << "Capacity: " << obj.capacity
    << setw(10) << "Serial num: " << obj.serialNum
    << setw(10) << "Model: " << obj.model
    << setw(10) << "Manufacturing Location: " << obj.manuLocn << endl;*/
    cout << left << setw(20) << obj.IMEI
    << setw(10) << obj.capacity
    << setw(20) << obj.serial
    << setw(20) << obj.model
    << setw(10) << obj.manuLocn << endl;
    return out;
}
/// overload = operator
iPhone & iPhone::operator =(const iPhone & rh)
{
    IMEI = rh.IMEI;
    capacity = rh.capacity;
    serial = rh.serial;
    model = rh.model;
    manuLocn = rh.manuLocn;
    return *this;
}
bool iPhone::operator <(const iPhone & rh)
{
    return ((IMEI < rh.IMEI)); //|| (capacity < rh.capacity));
    
}

bool iPhone::operator >(const iPhone & rh)
{
    return ((IMEI > rh.IMEI)); //|| (capacity > rh.capacity));
}

bool iPhone::operator ==(const iPhone & rh)
{
    return ((IMEI == rh.IMEI)); //|| (capacity == rh.capacity));
}

void iPhone::displayInfo()
{
    cout << left << "IMEI number: " << setw(20) << IMEI
    << "Capacity: " << setw(10) << capacity
    << "Serial num: " << setw(20) << serial
    << "Model: " << setw(20) << model
    << "Manufacturing Location: " << setw(10) << manuLocn << endl;
}

