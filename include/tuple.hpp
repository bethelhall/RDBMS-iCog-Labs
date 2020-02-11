#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <boost/variant.hpp>


using std::string;
using std::vector;
using boost::variant;

// declaration of Enum
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};
class Tuple
{
private:
    // each private variable declaration for the tuple class
    bool null;
    variant<int, std::string, bool, double, char> cellValue;
    Type dataType;
    string enumToString(Type v);
public:
    // each public methods declaration for the tuple class
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