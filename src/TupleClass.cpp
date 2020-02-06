#include "./header.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <set>
#include <map>
#include <cctype>
#include <vector>


#include <boost/variant.hpp>

using boost::variant;
using std::cout;
using std::endl;//Function for printing elements on terminal

const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;

template<typename T> 
void printElement(T t, const int& width,int flag)
{
	if(flag==1)
	    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
	else
	    std::cout << std::setw(width) << std::setfill(separator) << t;
}
// Tuple class implementation
string Tuple::enumToString(Type v)
{
    switch(v)
    {
        case 0:
            return "INT";
            break;
        case 1: 
            return "DOUBLE";
            break;
        case 2:
            return "CHAR";
            break;
        case 3:
            return "BOOL";
            break;
        case 4: 
            return "STRING";
            break;
    }
}
Tuple::Tuple(variant<int, std::string, bool, double, char> value): cellValue(value)
{
    null =false;
    this->cellValue = value;
    int index = cellValue.which();
    if(index == 0)
    {
        this->dataType = INT;
        string name = enumToString(dataType); 
    }
    else if(index == 1)
    {
        this->dataType = STRING;
        string name = enumToString(dataType);
    }
    else if(index == 2)
    {
        this->dataType = BOOL;
        string name = enumToString(dataType);
    }
    else if(index == 3)
    {
        this->dataType = DOUBLE;
        string name = enumToString(dataType);
    }
    else if(index == 4)
    {
        this->dataType = CHAR;
        string name = enumToString(dataType);
    }
}
// comparator for sorting them in map
bool Tuple::operator<(const Tuple &x) const
{
    if(x.dataType != dataType)
    {
        return true;
    }
    switch (dataType)
    {
    case INT:
        return cellValue<x.cellValue;
        break;
    case DOUBLE:
        return cellValue<x.cellValue;
        break;
    case CHAR:
        return cellValue<x.cellValue;
        break;
    case BOOL:
        return cellValue<x.cellValue;
        break;
    case STRING:
        return cellValue<x.cellValue;
        break;
    default:
        break;
    }

}
void Tuple::setValue(variant<int, std::string, bool, double, char> v)
{
    null = false;
    cellValue = v;
    int index = cellValue.which();
    if(index == 0)
    {
        this->dataType = INT;
        string name = enumToString(dataType);
    }
    else if(index == 1)
    {
        this->dataType = STRING;
        string name = enumToString(dataType);
    }
    else if(index == 2)
    {
        this->dataType = BOOL;
        string name = enumToString(dataType);
    }
    else if(index == 3)
    {
        this->dataType = DOUBLE;
        string name = enumToString(dataType);
    }
    else if(index == 4)
    {
        this->dataType = CHAR;
        string name = enumToString(dataType);
    }
}
variant<int, std::string, bool, double, char> Tuple::getValue()
{
    return cellValue;
}
// return data type
Type Tuple::getDataType()
{
    return dataType;
}
// retrun datatype in string
string Tuple::getDataTypeString()
{
    return enumToString(getDataType());
}
void Tuple::printTuple()
{
    switch (getDataType())
    {
        case INT:
            printElement(getValue(), numWidth,0);
            break;
        case DOUBLE:
            printElement(getValue(), numWidth,0);
            break;
        case BOOL:
            printElement(getValue(), numWidth,0);
            break;
        case CHAR:
            printElement(getValue(), numWidth,0);
            break;
        case STRING:
            printElement(getValue(), numWidth,0);
            break;    
        default:
            break;
    }
    cout << "";
}
// return true if tuple is null
bool Tuple::isNull()
{
    if(null == true)
    {
        return true;
    }
    return false;
}


int main()
{
    Tuple cell(10);
    cout<<cell.getDataType()<<endl;
    cout<<cell.getDataTypeString()<<endl;
    cout<<cell.isNull()<<endl;
}
