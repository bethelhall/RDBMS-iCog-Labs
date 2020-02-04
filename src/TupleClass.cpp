#include <iostream>
#include "./header.hpp"
#include <boost/variant.hpp>

using boost::variant;
using std::cout;
using std::endl;
class Tuple
{
    private:
        bool null;
        variant<int, std::string, bool, double, char> cellValue;
        Type dataType;
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
    public:
        Tuple()
        {
            null = true;
        }
        Tuple(variant<int, std::string, bool, double, char> value)
        {
            null =false;
            this->cellValue = value;
            int index = cellValue.which();
            if(index == 0)
            {
                this->dataType = INT;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 1)
            {
                this->dataType = STRING;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 2)
            {
                this->dataType = BOOL;
                string name = enumToString(dataType);
                // cout << name << endl; 
            }
            else if(index == 3)
            {
                this->dataType = DOUBLE;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 4)
            {
                this->dataType = CHAR;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            cout << cellValue <<endl;
        }
        // comparator for sorting them in map
        bool operator<(const Tuple &x) const
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
        void setValue(variant<int, std::string, bool, double, char> v)
        {
            null = false;
            cellValue = v;
            int index = cellValue.which();
            cout <<index <<endl;
            if(index == 0)
            {
                this->dataType = INT;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 1)
            {
                this->dataType = STRING;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 2)
            {
                this->dataType = BOOL;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 3)
            {
                this->dataType = DOUBLE;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            else if(index == 4)
            {
                this->dataType = CHAR;
                string name = enumToString(dataType);
                cout << name << endl; 
            }
            cout << v <<endl;
        }
        // return data type
        Type getDataType()
        {
            return dataType;
        }
        // retrun datatype in string
        string getDataTypeString()
        {
            return enumToString(getDataType());
        }
        // return true if tuple is null
        bool isNull()
        {
            if(null == true)
            {
                return true;
            }
            return false;
        }      
};