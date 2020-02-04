#include "./header.hpp"
#include "AttributeClass.cpp"
#include "TupleClass.cpp"
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

//Constants For Displaying in Tabular Form In Terminal
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

//Generic function used to throw error from anywhere in the code
void throwError(string error)
{
	throw error;
}

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