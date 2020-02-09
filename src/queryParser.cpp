#include "header.hpp"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// separates the strings by a space and returns the parsed

vector<string> parseQuery(string str) 
{ 
    vector<string> parsed;
    string word = ""; 
   for (auto x : str + " ") 
   {
       if (x == ' ') 
       { 
           cout << word << endl; 
           parsed.push_back(word);
           word = ""; 
       } 
       else if(x == '('  || x == ')' || x == ','){
           continue;
       }
       else
       { 
           word = word + x; 
       } 
   }  
//    cout << word << endl; 
    return parsed;
} 
