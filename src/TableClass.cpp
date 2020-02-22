#include "table.hpp"
#include "helper.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <set>
#include <map>
#include <cctype>
#include <vector>



using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::set;

const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;

// table constractor
Table::Table(){}
Table::Table(string tableName, int NoOfAttributes, vector<string> attributeNames, vector<string> attributeTypes):
    tableName(tableName), NoOfAttributes(NoOfAttributes)
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
    setSchema(NoOfAttributes, attributeNames, attributeTypes);
}
// return table name
string Table::getTableName()
{
    return tableName;
}
// // set table name
void Table::setTableName(string name)
{
    if(!isAlphaNumeric(name))
    {
        string error = "Table Name should be alphanumeric only";
        throw error;
    }
    this->tableName = name;
}
// //return no of attributes in table
int Table::getNoOfAttributes()
{
    return NoOfAttributes;
}
// //Sets the no of attributes of the table
void Table::setNoOfAttributes(int number)
{
    this->NoOfAttributes = number;
}
// //Returns no of data Tuples stored in the table presently.
int Table::getNoOfRecords()
{
    return NoOfRecords;
}
// // Returns The schema of the table. Methos to access Private Data
vector<Attribute> Table::getSchema()
{
    return schema;
}
// set the schema of the table
void Table::setSchema(int NoOfAttributes, vector<string> attributeNames, vector<string> attributeTypes)
{
    if(NoOfAttributes == 0)
    {
        string error = "NULL Schema Cannot be Allowed In ";
        throw error;
    }
    this->NoOfAttributes = NoOfAttributes;
    attributeIndexMap.clear();
    dataInTable.clear();
    NoOfRecords=0;
    schema = vector<Attribute>(NoOfAttributes);
    for(int i = 0; i < NoOfAttributes; i++)
    {
        if(attributeExitsinTable(attributeNames[i]))
        {
            string error= "Duplicate Attributes Are Not Allowed In ";
            throw error;
        }
        schema[i].setValues(attributeNames[i], attributeTypes[i]);				
        attributeIndexMap[schema[i].getName()]=i;	
    }
}

void Table::showSchema()
{
    for(int i=0;i<NoOfAttributes;i++){

        schema[i].printAttribute();
    }
    cout <<endl;
}

void Table::showData()
{
    cout<<"Table: "<<tableName<<endl;
    showSchema();
    std::set<std::vector<Tuple> >::iterator it;
    for(it=dataInTable.begin(); it!=dataInTable.end(); it++)
    {
        vector<Tuple> Tuple = *it;
        for(int j=0;j<NoOfAttributes;j++)
            Tuple[j].printTuple();

        std::cout<<std::endl;
    }
        std::cout<<std::endl;
}
void Table::InsertIntoTable(vector<string> & values)
{
    if(values.size() != NoOfAttributes)
    {
        string error = "the number of values should be equal to the number of attributes";
        throw error;
    }
    vector<Tuple> v(NoOfAttributes);
    for(int i = 0; i < NoOfAttributes; i++)
    {
        switch (schema[i].getDataType())
        {
            case INT:
                v[i].setValue(values[i]);
                break;
            case DOUBLE:
                v[i].setValue(values[i]);
            case BOOL:
                v[i].setValue(values[i]);
            case CHAR:
                v[i].setValue(values[i]);
            case STRING:
                v[i].setValue(values[i]);
            default:
                break;
        }
    }
    if(!dataTupleExists(v))
    {
        addDataTuple(v);
    }
}
bool Table::attributeExitsinTable(string attribute)
{
    if(attributeIndexMap.count(attribute)>0)
        return true;
    return false;
}
// return attribute by name
Attribute Table::getAttributeByName(string name)
{
    if(!attributeExitsinTable(name))
    {
        string error="No attribute \""+name+"\" found in Table "+getTableName();
        throw error;
    }

    int index = attributeIndexMap[name];
    return schema[index];
}
// return atrribute index by name
int Table::getAttributeIndexByName(string name)
{
    if(!attributeExitsinTable(name))
    {
        string error="No attribute \""+name+"\" found in Table "+getTableName();
        throw error;
    }

    return attributeIndexMap[name];
}
// Adds Attribute to schema if it does not exists already
void Table::addAttributeToSchema(Attribute newAttribute)
{
    if(attributeExitsinTable(newAttribute.getName()))
    {
        string error= "Duplicate Attributes Are Not Allowed In "+getTableName();
        throw error;
    }
    schema.push_back(newAttribute);
    attributeIndexMap[newAttribute.getName()]=NoOfAttributes;
    NoOfAttributes++;

}
// Adds a datatuple in dataInTable
void Table::addDataTuple(vector<Tuple> dataTuple)
{
    dataInTable.insert(dataTuple);
    NoOfRecords++;
}

// Check if Tuple exists in the table or not

bool Table::dataTupleExists(vector<Tuple> dataTuple)
{
    if(dataInTable.find(dataTuple) != dataInTable.end())
        return true;
    return false;
}

//check two schema are disjoint
bool Table::isDisjointSchema(std::vector<Attribute> otherSchema)
{
    for(int i=0;i<otherSchema.size();i++)
    {
        for(int j=0;j<schema.size();j++)
        {
            if(otherSchema[i] == schema[j])
                return false;
        }
    }
    return true;
}
//Checks if schema of two tables is exactly same 
bool Table::isSchemaSame(Table A)
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
