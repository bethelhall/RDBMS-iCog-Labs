#include "type.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <set>


using std::string;
using std::map;
using std::vector;
using std::set;

class Table
{
private:
    //Each private variable declaration for table class
    string tableName;
    int NoOfAttributes;
    int NoOfRecords;
    map<std::string,int> attributeIndexMap;
    vector<Attribute> schema;
public:
    //each dataInTable implemented as a set so that no data need to duplicated
    // dataInTable defined as set of set of class object
    set<Tuple> cell;
    set<vector<Tuple>> dataInTable;
    Table();
    Table(string tableName, int noOfAttributes, vector<string> attributeNames, vector<string> attributeTypes);
    string getTableName();
    void setTableName(string name);
    int getNoOfAttributes();
    void setNoOfAttributes(int number);
    int getNoOfRecords();
    vector<Attribute> getSchema();
    void setSchema(int NoOfAttributes, vector<string> attributeNames, vector<string> attributeTypes);
    void showSchema();
    void showData();
    void InsertIntoTable(vector<string> & values);
    bool attributeExitsinTable(string attribute);
    Attribute getAttributeByName(string name);
    int getAttributeIndexByName(string name);
    void addAttributeToSchema(Attribute newAttribute);
    void addDataTuple(vector<Tuple> dataTuple);
    bool dataTupleExists(vector<Tuple> dataTuple);
    bool isDisjointSchema(std::vector<Attribute> otherSchema);
    bool isSchemaSame(Table A);

};

Table UnionTables(Table A, Table B);
Table ProjectTable(Table table, vector<string> attributes);
Table QueryParser(string query);


