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
using std::cin;
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};
//Constants For Displaying in Tabular Form In Terminal
const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;

bool isAlpha(string name)
{
	for(int i=0;i<name.size();i++)
		if(!( (name[i]>='a' && name[i]<='z')|| (name[i]>='A' && name[i]<='Z') ) )
			return false;
	return true;
}
bool isAlphaNumeric(string name)
{
    for(int i=0;i<name.size();i++)
		if(!( (name[i]>='a' && name[i]<='z')|| (name[i]>='A' && name[i]<='Z') || (name[i]>='0' && name[i]<='9') || name[i]=='_' || name[i]==' ' ||name[i]=='-'|| name[i]=='|') )
			return false;
	return true;
}

//Function for printing elements on terminal
template<typename T> 
void printElement(T t, const int& width,int flag)
{
	if(flag==1)
	    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
	else
	    std::cout << std::setw(width) << std::setfill(separator) << t;
}
class Attribute{
    private:
        string attributeName;
        Type dataType;
        // Converting ENUM to String
	    string enumToString(Type v)
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
   	    Type stringToEnum(string v)
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
    public:
        // empty attribute
        Attribute()
        {

        }
        Attribute(string attributeName, Type dataType)
        {
            if(!isAlpha(attributeName))
            {											
                string error = "Attribute Name should have alphabets only";
                throw error;
            }
            this->attributeName = attributeName;
	        this->dataType = dataType;
        }
        Attribute(string attributeName,string dataType)
        {
            setValues(attributeName,dataType);
        }
        //Comparator for attribute object
        bool operator <(const Attribute &x) const
        {							
            if(attributeName==x.attributeName)
            {
                return true;
            }
            return false;
        }

        //Set values of a attribute after declaring it
	    void setValues(string attributeName, string dataType)				
        {
            if(!isAlpha(attributeName))
            {
                string error = "Attribute Name should have alphabets only";
                throw error;
            }
            this -> attributeName = attributeName;
            this -> dataType = stringToEnum(dataType);
            
        }
        //returns the name of the attribute
        string getName()													
        {
            return attributeName;
        }
        // returns the datatype of attribute 
        Type getDataType()
        {
            return dataType;
        }
        //returns the datatype in string
        string getDataTypeString()
        {
            return enumToString(getDataType());
        }

        //Used for printing the attribute name on the screen
        void printAttribute()
        {
            if(getDataType()==STRING)
                printElement(getName(),nameWidth,1);
            else
                printElement(getName(),numWidth,0);
            std::cout<<" ";
        }
        //Used for printing the attribute type on the screen
        void printDatatype()
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
};

int main()
{
    
}