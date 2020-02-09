#include "header.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>
#include <cctype>
#include <iomanip>
#include <string.h>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <bits/stdc++.h> 


using std::cout;
using std::vector;
using std::endl;
using std::cin;

static inline std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
static inline std::string rtrim(std::string s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

static inline std::string trim(std::string s) 
{
    return ltrim(rtrim(s));
}

int main ()
{
    Database db;
    Attribute atr;
    Table table;
    try
    {
        loadData();
        cout << "Data loaded.." <<endl;
        //string keyboard;
        while(1)
        {
            try
            {
                Type v;
                string a;
                vector<string> attr_type;
                vector<string>parseData;
                cout <<">>";
                string query;
                getline(cin, query);
                vector<string>parsedQuery = parseQuery(query);
                string queryCheck = trim(query);
                transform(queryCheck.begin(), queryCheck.end(), queryCheck.begin(), ::toupper);
                string mainQuery = parsedQuery[0];  
                for (int i = 0; i < parsedQuery.size(); i++)
                {
                    if(parsedQuery[i] == "INT" || parsedQuery[i] == "STRING")
                    {
                        
                        v = atr.stringToEnum(parsedQuery[i]);
                        a = atr.enumToString(v);
                        attr_type.push_back(a); 
                    }

                    if((parsedQuery[i] != "INT" && parsedQuery[i] != "STRING") && (parsedQuery[i] != "CREATE" && parsedQuery[i] != "TABLE" && parsedQuery[i] != parsedQuery[2]))

                    {
                        parseData.push_back(parsedQuery[i]);

                    }
                }
    
                if(queryCheck == "EXIT")
                {
                    cout << "Bye Exiting...."<<endl;
                    return 0;
                }

                else if(queryCheck == "SHOW TABLE")
                {
                    db.showTables();
                }
                else if(mainQuery == "CREATE")
                {
                    if(parsedQuery[1] == "DATABASE")
                    {
                        db.CreateDatabase(parsedQuery[2]);
                        cout << parsedQuery[2] + "Database Has Created" ;
                    }
                    else if(parsedQuery[1] == "TABLE")
                    {
                        db.CreateTable(parsedQuery[2], parseData, attr_type);
                        db.NameTable(parsedQuery[2]);
                        cout <<parsedQuery[2] + " " << "table has created"<<endl;
                    }
                }               
                else if(mainQuery == "PROJECT")
                {
                    if(db.tableExists(parsedQuery[parsedQuery.size() - 1]))
                    {
                        
                        table = db.getTableByName(parsedQuery[parsedQuery.size() - 1]);
                    }

                    vector<string>attr_projects;
                    string tablename = parsedQuery[parsedQuery.size() - 1];
                    for(int i = 2; i < parsedQuery.size(); i++)
                    {
                        attr_projects.push_back(parsedQuery[i - 1]);
                    }

                    ProjectTable(table,  attr_projects);
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