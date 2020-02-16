#include "table.hpp"
#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <vector>

using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::string;


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
Table IntersectionOfTables(Table A,Table B ){
	if(!A.isSchemaSame(B))													
	{
		string error="Intersection  Table Error: Table \""+A.getTableName()+"\" and Table \""+B.getTableName()+"\" do not have same schemas";
		throw error;
	}
	Table output;
	output.setTableName("|"+A.getTableName()+" Intersection "+B.getTableName()+"|");	
	std::set<std::vector<Tuple> >::iterator  ite;
	 
 
		for(ite = B.dataInTable.begin(); ite != B.dataInTable.end(); ite++){

		if(A.dataTupleExists(*ite))
		{
			output.addDataTuple(*ite);											
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
 
	set<vector<Tuple>>::iterator it;
	for (it=table.dataInTable.begin(); it!=table.dataInTable.end(); it++)
	{	
		
		vector<Tuple> cell = *it;
		cout << "hello"<<endl;
		std::vector<Tuple> v( attributes.size());
		cout << "hello"<<endl;
		for(int j=0;j<attributes.size();j++)
		{
			 
			int index = table.getAttributeIndexByName(attributes[j]);	
			 	
			cout<<index<<endl;
			v[j]=cell[index];
			
			
		}
		if(!output.dataTupleExists(v))	
			cout << "hello"<<endl;												
			output.addDataTuple(v);														
	}
cout << "hello"<<endl;
	return output;
}

Table SetDifferenceTable(Table A, Table B)
{
	if(!A.isSchemaSame(B))													//Schema should be same for both of them
	{
		string error="SetDifference Table Error: Table \""+A.getTableName()+"\" and Table \""+B.getTableName()+"\" do not have same schemas";
		throw error;
	}

	Table output = A;
	output.setTableName("|"+A.getTableName()+" - "+B.getTableName()+"|");				//New Table Name Set as  | A - B |
	output.dataInTable.clear();
	std::set<std::vector<Tuple> >::iterator it;
	for(it=A.dataInTable.begin(); it!=A.dataInTable.end(); it++)
	{
		if(!B.dataTupleExists(*it))
			output.addDataTuple(*it);											//Add datatuples of A to new table if they does not exist in B
	}

	return output;

}
