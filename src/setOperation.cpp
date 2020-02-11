#include "table.hpp"
#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <vector>

using std::vector;
using std::set;


// UNION
Table UnionTables(Table A, Table B)
{
	if(!A.isSchemaSame(B))													
	{
		string error="Union Table Error: Table \""+A.getTableName()+"\" and Table \""+B.getTableName()+"\" do not have same schemas";
		throw error;
	}

	Table output = A;
	output.setTableName("|"+A.getTableName()+" Union "+B.getTableName()+"|");				
	std::set<std::vector<Tuple> >::iterator it;
	for(it = B.dataInTable.begin(); it != B.dataInTable.end(); it++)
	{
		if(!A.dataTupleExists(*it))
		{
			output.addDataTuple(*it);											
		}
	}

	return output;
}
// Projection
Table ProjectTable(Table table, vector<string> attributes)
{
	if(attributes.size()==0)															
	{
		string error="Attribute Match Error: No attributes are provided for Project Function";
		throw error;
	}
	Table output;
	output.setTableName(table.getTableName());											
	output.dataInTable.clear();
	for(int i=0;i<attributes.size();i++)
	{
		output.addAttributeToSchema(table.getAttributeByName(attributes[i]));			
	}
	std::set<std::vector<Tuple> >::iterator it;
	for (it=table.dataInTable.begin(); it!=table.dataInTable.end(); it++)
	{
		vector<Tuple> cell = *it;
		vector<Tuple> v(output.getNoOfAttributes());
		for(int j=0;j<attributes.size();j++)
		{
			int index = table.getAttributeIndexByName(attributes[j]);					
			v[j]=cell[index];

		}
		if(!output.dataTupleExists(v))													
			output.addDataTuple(v);														
	}

	return output;
}