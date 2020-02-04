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


using std::left;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::set;
using boost::variant;

// restriction for numeration values
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};
//Constants For Displaying in Tabular Form In Terminal
const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;
//Checks whether a string contains only alphabets or not
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

//Generic function used to throw error from anywhere in the code
void throwError(string error)
{
	throw error;
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
class Tuple{
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

class Table
{

    private:
        string tableName;
        int NoOfAttributes;
        int NoOfRecords;
        map<std::string,int> attributeIndexMap;
        vector<Attribute> schema;
    public:
        //each dataInTable implemented as a set so that no data need to duplicated
        // dataInTable defined as set of set of class object
        set<Tuple> cell;
        set<set<Tuple>> dataInTable;
        //empty table
        Table()
        {
            NoOfAttributes = 0;
            NoOfRecords = 0;
        }
        Table(string tableName, int noOfAttributes, vector<string> attributeNames, vector<string> attributeTypes)
        {
            if(!isAlphaNumeric(tableName))
            {
                string error = "Table Name should be alphanumeric only";
                throw error;
            }
            if(tableName == "")
            {
                string error = "Table Name should not be empty";
                throw error;
            }
            this->tableName = tableName;
            setSchema(noOfAttributes, attributeNames, attributeTypes);
        }
        // return table name
        string getTableName()
        {
            return tableName;
        }
        // set table name
        void setTableName(string name)
        {
            if(!isAlphaNumeric(name))
            {
                string error = "Table Name should be alphanumeric only";
                throw error;
            }
            this->tableName = name;
        }
        //return no of attributes in table
        int getNoOfAttributes()
        {
            return NoOfAttributes;
        }
        //Sets the no of attributes of the table
        void setNoOfAttributes(int number)
        {
            this->NoOfAttributes = number;
        }
        //Returns no of data Tuples stored in the table presently.
        int getNoOfRecords()
        {
            return NoOfRecords;
        }
        // Returns The schema of the table. Methos to access Private Data
        vector<Attribute> getSchema()
        {
            return schema;
        }
        // set the schema of the table
        void setSchema(int NoOfAttributes, vector<string> attributeNames, vector<string> attributeTypes)
        {
            if(NoOfAttributes == 0)
            {
                string error = "NULL Schema Cannot be Allowed In "+getTableName();
                throw error;
            }

            this->NoOfAttributes = NoOfAttributes;
            attributeIndexMap.clear();
            dataInTable.clear();
            NoOfRecords=0;
            schema = vector<Attribute>(NoOfAttributes);
            std::vector<Attribute> newSchema(NoOfAttributes);
            for(int i = 0; i < NoOfAttributes; i++)
            {
                if(attributeExitsinTable(attributeNames[i]))
                {
                    string error= "Corrupt Data Exception: Duplicate Attributes Are Not Allowed In "+getTableName();
				    throw error;
                }
                schema[i].setValues(attributeNames[i],attributeTypes[i]);				
			    attributeIndexMap[schema[i].getName()]=i;	
            }
            schema = newSchema;
        }

        void showSchema()
        {
            cout<<"Table: "<<tableName<<endl;
            for(int i=0;i<schema.size();i++)
                cout<<i+1<<". "<<schema[i].getName()<<" "<<schema[i].getDataTypeString()<<std::endl;
        }

        // void showData()
        // {
        //     cout<<"Table: "<<tableName<<endl;
        //     showSchema();
        //     set<set<Tuple>>::iterator it;
        //     for(auto const & it : dataInTable)
        //     {
        //         for(auto const & i : cell)
        //         {
        //             std::cout << i << ' ';
        //         }
        //         std::cout << std::endl;
        //     }
                
        // }
        // void InsertIntoTable(set<variant<int, string, char, double, bool>> & values)
        // {
        //     if(values.size() != NoOfAttributes)
        //     {
        //         string error = "the number of values should be equal to the number of attributes";
        //         throw error;
        //     }
        //     set<Tuple> v(NoOfAttributes);
        //     for(int i = 0; i < NoOfAttributes; i++)
        //     {
        //         switch (schema[i].getDataType())
        //         {
        //             case INT:
        //                 v[i].setValueInt(stringToInt(values[i]));
        //                 break;
        //             case DOUBLE:
        //                 v[i].setValueDouble(stringToDouble(values[i]));
        //             default:
        //                 break;
        //         }
        //     }
        //     if(!dataTupleExists(v))
        //     {
        //         addDataTuple(v);
        //     }
        // }
        bool attributeExitsinTable(string attribute)
        {
            if(attributeIndexMap.count(attribute)>0)
                return true;
            return false;
        }
        // return attribute by name
        Attribute getAttributeByName(string name)
        {
            if(!attributeExitsinTable(name))
            {
                string error="Attribute Match Error: No attribute \""+name+"\" found in Table "+getTableName();
                throw error;
            }

            int index = attributeIndexMap[name];
            return schema[index];
        }
        // return atrribute index by name
        int getAttributeIndexByName(string name)
        {
            if(!attributeExitsinTable(name))
            {
                string error="Attribute Match Error: No attribute \""+name+"\" found in Table "+getTableName();
                throw error;
            }

            return attributeIndexMap[name];
        }
        // Adds Attribute to schema if it does not exists already
        void addAttributeToSchema(Attribute newAttribute)
        {
            if(attributeExitsinTable(newAttribute.getName()))
            {
                string error= "Corrupt Data Exception: Duplicate Attributes Are Not Allowed In "+getTableName();
                throw error;
            }
            schema.push_back(newAttribute);
            attributeIndexMap[newAttribute.getName()]=NoOfAttributes;
            NoOfAttributes++;

        }
        // Adds a datatuple in dataInTable
        void addDataTuple(set<Tuple> dataTuple)
        {
            dataInTable.insert(dataTuple);
            NoOfRecords++;
        }
        // Check if Tuple exists in the table or not
        bool dataTupleExists(set<Tuple> dataTuple)
        {
            if(dataInTable.find(dataTuple) != dataInTable.end())
                return true;
            return false;
        }
        // check two schema are disjoint
        // bool isDisjointSchema(std::vector<Attribute> otherSchema)
        // {
        //     for(int i=0;i<otherSchema.size();i++)
        //     {
        //         for(int j=0;j<schema.size();j++)
        //         {
        //             if(otherSchema[i]==schema[j])
        //                 return false;
        //         }
        //     }
        //     return true;
        // }
        //Checks if schema of two tables is exactly same 
        bool isSchemaSame(Table A)
        {
            int flag;
            std::vector<Attribute> schemaA = A.getSchema();
            for(int i=0;i<schema.size();i++)
            {
                flag=0;
                for(int j=0;j<schemaA.size();j++)
                {
                    if(schema[i].getName()==schemaA[j].getName() && schema[i].getDataType()==schemaA[j].getDataType())
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                        return false;
            }
            for(int j=0;j<schemaA.size();j++)
            {
                flag=0;
                for(int i=0;i<schema.size();i++)
                {
                    if(schema[i].getName()==schemaA[j].getName() && schema[i].getDataType()==schemaA[j].getDataType())
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                        return false;
            }
            return true;
        }
};


int main()
{
    Attribute attr;
    Tuple cell;
    Table table;
    attr.setValues("Age", "INT");
    string name = attr.getName();
    Type a = attr.getDataType();
    string b = attr.getDataTypeString();
    attr.printAttribute();
    cout <<" ";
    attr.printDatatype();
    cout <<endl;
    cell.setValue(true);
    cout << cell.getDataTypeString() <<endl;
    Table("Student", 3, {"Name", "Age", "dept"}, {"STRING", "INT", "STRING"});
    string c = table.getTableName();
    table.showSchema();


}