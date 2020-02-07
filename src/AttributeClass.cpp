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
using std::endl;
using std::cin;
using std::vector;

const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;

//Function for printing elements on terminal
template<typename T> 
void printElement(T t, const int& width,int flag)
{
	if(flag==1)
	    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
	else
	    std::cout << std::setw(width) << std::setfill(separator) << t;
}

// Converting ENUM to String
string Attribute::enumToString(Type v)
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
//Converting String To Enum
Type Attribute::stringToEnum(string v)
{
    std::transform(v.begin(), v.end(), v.begin(), ::toupper);
    if(v=="INT")
        return INT;
    else if(v=="DOUBLE") 
        return DOUBLE;
    else if(v=="CHAR")
        return CHAR;
    else if(v=="STRING")
        return STRING;
    else if(v=="BOOL")
        return BOOL;
    else

    {
        string error = "DataType Should Be Only Among INT,DOUBLE, CHAR, STRING, BOOL";
        throw error;
    }
}
// empty attribute
Attribute::Attribute(){}
Attribute::Attribute(string attributeNames, Type dataType):attributeNames(attributeNames), dataType(dataType)
{
    if(!isAlpha(attributeNames))
    {											
        string error = "Attribute Name should have alphabets only";
        throw error;
    }
    this->attributeNames = attributeNames;
    this->dataType = dataType;
}
Attribute::Attribute(string attributeNames,string dataType)
{
    setValues(attributeNames,dataType);
}
//Comparator for attribute object
bool Attribute::operator <(const Attribute &x) const
{							
    if(attributeNames==x.attributeNames)
    {
        return true;
    }
    return false;
}

//Set values of a attribute after declaring it
void Attribute::setValues(string attributeNames, string dataType)				
{
    if(!isAlpha(attributeNames))
    {
        string error = "Attribute Name should have alphabets only";
        throw error;
    }
    this -> attributeNames = attributeNames;
    this -> dataType = stringToEnum(dataType);


}
//returns the name of the attribute
string Attribute::getName()													
{
    return attributeNames;
}
// returns the datatype of attribute 
Type Attribute::getDataType()
{
    return dataType;
}
//returns the datatype in string
string Attribute::getDataTypeString()
{
    return enumToString(getDataType());
}

//Used for printing the attribute name on the screen
void Attribute::printAttribute()
{
    if(getDataType()==STRING)
        printElement(getName(),nameWidth,1);
    else
        printElement(getName(),numWidth,0);
    std::cout<<" ";
}
//Used for printing the attribute type on the screen
void Attribute::printDatatype()
{
    switch(getDataType())
    {
        case INT:
            printElement(getDataTypeString(),numWidth,0);
            break;
        case DOUBLE:
            printElement(getDataTypeString(),numWidth,0);
            break;
        case CHAR:
            printElement(getDataTypeString(),numWidth,0);
            break;
        case STRING:
            printElement(getDataTypeString(),numWidth,1);
            break;
        case BOOL:
            printElement(getDataTypeString(),numWidth,0);
            break;
    }
    std::cout<<" ";
}
