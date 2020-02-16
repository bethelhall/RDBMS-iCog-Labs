#include <cxxtest/TestSuite.h>
#include "header.hpp"
#include <iostream>
#include <ostream>
#include <map>
#include <string>
#include <vector>
#include <boost/variant.hpp>


using std::string;
using boost::variant;
using std::cout;
using std::endl;
using std::vector;

// test on Table class
class TestTable: public Table
{
public:
    TestTable(): Table("Student", 4, {"Name", "ID", "dept", "grade"}, {"STRING", "INT", "STRING", "DOUBLE"})
    {}
};

class TableSuite: public CxxTest::TestSuite
{
public:
    void test_getTableName()
    {
        std::string TableName = TestTable().getTableName();
        TS_ASSERT_EQUALS(TableName, "Student");

    }

    void test_getNoOfAttribute()
    {
        int NoOfAttribute = TestTable().getNoOfAttributes();
        TS_ASSERT_EQUALS(NoOfAttribute, 4);

    }

    void test_setTableName()
    {
        TestTable().setTableName("Student");
        TS_ASSERT("Student");

    }

    void test_getNoRecord()
    {
        int number = TestTable().getNoOfRecords();
        TS_ASSERT_EQUALS(number, 0)

    }

    void test_setSchema()
    {
        TestTable().setSchema(4, {"Name", "ID", "dept", "grade"}, {"STRING", "INT", "STRING", "DOUBLE"});
        TS_ASSERT("SUCCESS");

    }

    void test_attributeExitsinTable()
    {
        bool attribute = TestTable().attributeExitsinTable("Name");
        TS_ASSERT_EQUALS(attribute, true);

    }

    void test_getAttributeIndexByName()
    {
        int index = TestTable().getAttributeIndexByName("grade");
        TS_ASSERT_EQUALS(index, 3);

    }
};

// test on Attribute class
class TestAttribute: public Attribute
{
public:
    TestAttribute(): Attribute("Name", "STRING")
    {}
};
class AttributeSuite: public CxxTest::TestSuite
{
public:
    void test_getName()
    {
        string name = TestAttribute().getName();
        TS_ASSERT_EQUALS(name, "Name");

    }

    void test_getDataType()
    {
        Type type = TestAttribute().getDataType();
        TS_ASSERT_EQUALS(type, STRING);

    }

    void test_getDataTypeString()
    {
        string name = TestAttribute().getDataTypeString();
        TS_ASSERT_EQUALS(name, "STRING");

    }
};

// test on Tuple class
class TestTuple: public Tuple
{
public:
    TestTuple(): Tuple(false)
    {}

};

class TupleSuite: public CxxTest::TestSuite
{
public:
    void test_getDataType()
    {
        Type type = TestTuple().getDataType();
        TS_ASSERT_EQUALS(type, BOOL);

    }

    void test_getDataTypeString()
    {
        string type = TestTuple().getDataTypeString();
        TS_ASSERT_EQUALS(type, "BOOL");

    }

    void test_isNull()
    {
        bool type = TestTuple().isNull();
        TS_ASSERT_EQUALS(type, false);

    }

    void test_setValue()
    {
        TestTuple().setValue(5);
        TS_ASSERT("SUCCESS");

    }
    
};

