#include <cxxtest/TestSuite.h>
#include "../include/header.hpp"
#include <iostream>
#include <string>


using std::string;
using std::vector;

class Test: public Table
{
class TableSuite: public CxxTest::TestSuite
{
public:
    void test_getTableName()
    {
        Table table("Student", 4, {"Name", "ID", "dept", "grade"}, {"STRING", "INT", "STRING", "DOUBLE"});
        string name = table.getTableName();
        TS_ASSERT_EQUALS(name, "Student");
    }

};
};

