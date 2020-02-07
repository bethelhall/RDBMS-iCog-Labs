#include <iostream>
#include "header.hpp"


using std::cout;
using std::endl;
using std::cin;


int main ()
{
    try
    {
        loadData();
        cout << "Data loaded.." <<endl;
        while(1)
        {
            try
            {
                cout <<">>";
                string query;
                getline(cin, query);
                string queryCheck = trim(query);
                transform(queryCheck.begin(), queryCheck.end(), queryCheck.begin(), ::toupper);
                if(queryCheck == "EXIT")
                {
                    cout << "Bye Exiting...."<<endl;
                    return 0;
                }
                else if(starts_with(queryCheck, "PROJECT"))
                {
                    cout<<"hello"<<endl;
                    QueryParser(query).showData();
                }
                else
                {
                    throwError("Invalid Query");
                }
                

            }
            catch(string msg)
            {
                msg = "Error";
                cout <<msg<<endl;
            }
        }
    }
    catch(string msg)
    {
        msg = "Error";
        cout << msg << endl;

    }
    return 0;
};