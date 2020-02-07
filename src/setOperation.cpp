#include "./header.hpp"
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <set>
#include <map>
#include <cctype>
#include <vector>
#include <boost/variant.hpp>

using std::vector;
using std::set;


Table ProjectTable(Table table, vector<string> attributes)
{
	if(attributes.size()==0)															// Check for zero projected attributes
	{
		string error="Attribute Match Error: No attributes are provided for Project Function";
		throw error;
	}
	Table output;
	output.setTableName(table.getTableName());											//set the table name of previous table
	output.dataInTable.clear();
	for(int i=0;i<attributes.size();i++)
	{
		output.addAttributeToSchema(table.getAttributeByName(attributes[i]));			//Set schema for projected table
	}
	std::set<std::vector<Tuple> >::iterator it;
	for (it=table.dataInTable.begin(); it!=table.dataInTable.end(); it++)
	{
		vector<Tuple> cell = *it;
		vector<Tuple> v(output.getNoOfAttributes());
		for(int j=0;j<attributes.size();j++)
		{
			int index = table.getAttributeIndexByName(attributes[j]);					//Get projected attribute values in the data Tuple
			v[j]=cell[index];

		}
		if(!output.dataTupleExists(v))													//Check if Projected value is not present, then add it
			output.addDataTuple(v);														// This is a check for Duplicate projected values.
	}

	return output;
}