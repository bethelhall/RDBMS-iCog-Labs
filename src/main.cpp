#include "header.hpp"
#include <iostream>
#include <cctype>
#include <iomanip>
#include <string.h>
#include <vector>


using std::cout;
using std::vector;
using std::endl;
using std::cin;
using std::string;

void display_query_syntax()
{
  cout << "=====================================================================================================\n";
  cout << "\t\t sample query syntax example\n";
  cout << "\t0) CREATE DATABASE \n";
  cout << "\t1) CREATE TABLE student id INT name STRING age INT gender STRING \n";
  cout << "\t2) INSERT INTO student 1 danny 21 male\n";
  cout << "\t4) UNIOTN TableA TableB\n";
  cout << "\t5) DIFF TableA TableB\n";
  cout << "\t6) PROJECT attributeA TableA\n";
  cout << "\t7) SHOW TABLE \n";
  cout << "\t8) SHOW DATA TableA\n";
  cout << "\t\t Enter exit.\n";
  cout << "=====================================================================================================\n\n";
}


int main ()
{
    Database db;
    Attribute atr;
    display_query_syntax();
    try
    {
        while(1)
        {
            try
            {
                Type v;
                string a;
                vector<string> values;
                vector<string> attr_type;
                vector<string>parseData;
                vector <string> projectedData;
                cout <<">>";
                string query;
                getline(cin, query);
                string queryCheck = query;
                transform(queryCheck.begin(), queryCheck.end(), queryCheck.begin(), ::toupper);
                vector<string>parsedQuery = parseQuery(query);
                string mainQuery = parsedQuery[0];
                // creating vector of datatype from parsing  
                for (int i = 0; i < parsedQuery.size(); i++)
                {
                    if(parsedQuery[i] == "INT" || parsedQuery[i] == "STRING" || parsedQuery[i] == "DOUBLE" || parsedQuery[i] == "CHAR" || parsedQuery[i] == "BOOL")
                    {
                        
                        v = atr.stringToEnum(parsedQuery[i]);
                        a = atr.enumToString(v);
                        attr_type.push_back(a); 
                    }

                    if((parsedQuery[i] != "INT" && parsedQuery[i] != "STRING" && parsedQuery[i] != "DOUBLE" && parsedQuery[i] != "CHAR" && parsedQuery[i] != "BOOL") && (parsedQuery[i] != "CREATE" && parsedQuery[i] != "TABLE" && parsedQuery[i] != parsedQuery[2]))

                    {
                        parseData.push_back(parsedQuery[i]);

                    }
                }
                // getting vector of values from parssing
                for(int i = 3; i < parsedQuery.size(); i++)
                {
                    values.push_back(parsedQuery[i]);
                }
                // getting values for projecting function
                for(int i= 1; i < (parsedQuery.size() -1); i++)
                {
                     projectedData.push_back(parsedQuery[i]);
                }
                if(queryCheck == "EXIT")
                {
                    cout << "Bye Exiting...."<<endl;
                    return 0;
                }
                else if(mainQuery == "SHOW")
                {
                    cout << "\t\t ==========created" + parsedQuery[1] + "=========" <<endl;
                    if(parsedQuery[1] == "TABLE")
                    {
                        db.showTables();
                    }
                    else if(parsedQuery[1] == "DATA")
                    {
                        cout <<"\t\t ==========inserted element into " + parsedQuery[2] + "=========" <<endl;
                        db.getTableByName(parsedQuery[2]).showData();
                    }
                }
                else if(mainQuery == "CREATE")
                {
                    if(parsedQuery[1] == "DATABASE")
                    {
                        db.CreateDatabase(parsedQuery[2]);
                        cout << parsedQuery[2] + " " << "database has created" << endl;
                    }
                    else if(parsedQuery[1] == "TABLE")
                    {
                        db.CreateTable(parsedQuery[2], parseData, attr_type);
                        cout <<parsedQuery[2] + " " << "table has created"<<endl;
                    }
                }
                else if(mainQuery == "INSERT")
                {
                    for (int i = 0; i < values.size(); i++)
                    {
                        db.getTableByName(parsedQuery[2]).InsertIntoTable(values);
                    }
                }
                else if(mainQuery == "PROJECT")
                {
                    Table table = db.getTableByName(parsedQuery[parsedQuery.size() - 1]);
                     
                    Table C = ProjectTable(table, projectedData);
                    C.showData();
                }
                else if(mainQuery == "UNION")
                {
                    Table A = db.getTableByName(parsedQuery[parsedQuery.size() - 1]);
                    Table B = db.getTableByName(parsedQuery[parsedQuery.size() - 2]);
                    Table C = UnionTables(A, B);
                    C.showData();

                }
                else if(mainQuery == "INTERSECTION"){
                    Table A = db.getTableByName(parsedQuery[parsedQuery.size()-1]);
                    Table B = db.getTableByName(parsedQuery[parsedQuery.size()-2]);
                    Table C = IntersectionOfTables(A,B);
                    C.showData();

                }
                else if(mainQuery == "DIFF")
                {
                    Table A = db.getTableByName(parsedQuery[parsedQuery.size() - 2]);
                    Table B = db.getTableByName(parsedQuery[parsedQuery.size() - 1]);
                    Table C = SetDifferenceTable(A, B);
                    C.showData();
                }
                else
                {
                    throwError("Invalid Query");
                }
                

            }
            catch(const string msg)
            {
                cout <<msg<<endl;
            }
        }
    }
    catch(const string msg)
    {
        cout << msg << endl;

    }
    return 0;
    
};