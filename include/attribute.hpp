#include <iostream>
#include <string>
#include <cctype>
#include <map>


using std::string;
using std::map;
using std::string;


// declaration of Enum
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};
//declaration of Table, Database, Tuple and Attribute class
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