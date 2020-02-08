#include <iostream>
#include "header.hpp"


using std::cout;
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
                else if(starts_with(queryCheck, "PROJECT")||starts_with(queryCheck, "UNION"))
                {
                    QueryParser(query).showData();
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