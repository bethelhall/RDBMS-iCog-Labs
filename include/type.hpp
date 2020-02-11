#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <boost/variant.hpp>
#include <set>

using std::string;
using std::map;
using std::vector;
using boost::variant;
using std::set;
using std::string;

// declaration of Enum
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};

class Attribute
{
    private:
        string attributeNames;
        Type dataType;
    public:
        string enumToString(Type v);
        Type stringToEnum(string v);
        Attribute();
        Attribute(string attributeName, Type dataType);
        Attribute(string attributeName,string dataType);
        bool operator ==(const Attribute &x) const;
        void setValues(string attributeName, string dataType);
        string getName();
        Type getDataType();
        string getDataTypeString();
        void printAttribute();
        void printDatatype();

};

class Tuple
{
    private:
        bool null;
        variant<int, std::string, bool, double, char> cellValue;
        Type dataType;
        string enumToString(Type v);
    public:
        Tuple();
        Tuple(variant<int, std::string, bool, double, char> value);
        bool operator<(const Tuple &x) const;
        void setValue(variant<int, std::string, bool, double, char> value);
        variant<int, std::string, bool, double, char> getValue();
        Type getDataType();
        string getDataTypeString();
        void printTuple();
        bool isNull();


};