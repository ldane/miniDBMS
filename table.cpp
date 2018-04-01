//
#include "table.h"
//
#include <sstream>

Table::Table(std::string tn, bool temp) : columnTypesMap(){
	tableName = tn;
	primaryKey = "";
	recordSize = 0;
	totalSize = 0;
	numOfRecords = 0;
	temporary = temp;
	dropped = false;
	//columnNames columnTypesMap
}
void Table::setPrimaryKey(std::string pk){
	primaryKey = pk;
}

void Table::parseAndSetPrimaryKey(std::string pk){
	primaryKey = pk.substr(8);
}

void Table::setRecordSize(int size){
	recordSize = size;
}
void Table::setTotalSize(int size){
	totalSize = size;
}
void Table::setNumOfRecords(int num){
	numOfRecords = num;
}
void Table::addColumn(std::string clmn){
	// passed in value will be of format C1=INT
	// left of = is column name
	// right of = is column type 
	//std::cout << "trying to add column" << std::endl;
	//replace space with : if : not found
	std::size_t pos = clmn.find(":");
	if (pos == std::string::npos){
		//not found 
		pos = clmn.find(" ");
	}
	//std::cout << "trying to add column2" << std::endl;
	std::string nColumnName = clmn.substr(0,pos);
	//std::cout << "trying to add column3" << std::endl;
	std::string nColumnType = clmn.substr(pos+1);
	//std::cout << "trying to add column4" << std::endl;
	columnNames.push_back(nColumnName);
	columnTypesMap.insert(std::make_pair(nColumnName, nColumnType));
}

void Table::setColumnTypes(std::string columnName, std::string ctm){
	// need to check if already exists maybe
	columnTypesMap.insert(std::make_pair(columnName, ctm));
}

std::string Table::getTableName(){
	return tableName;
}

std::string Table::getPrimaryKey(){
	return primaryKey;
}

int Table::getRecordSize(){
	return recordSize;
}

int Table::getTotalSize(){
	return totalSize;
}

int Table::getNumOfRecords(){
	return numOfRecords;
}

std::vector<std::string> Table::getColumnNames(){
	return columnNames;
}

std::string Table::getColumnType(std::string column){
	if (columnTypesMap.find(column) != columnTypesMap.end()){
		return columnTypesMap[column];
	} else {
		return "";
	}
}

void Table::setIfDropped(bool dropflag){
	dropped = dropflag;
}
bool Table::isTemporary(){
	return temporary;
}

bool Table::isDropped(){
	return dropped;
}

std::string Table::getFormattedMetaData(){
	std::ostringstream ss;
	ss << "tablename=" << tableName << "\n";
	ss << "columns=";
	bool isFirstTime = true;
	for (std::string clmn : columnNames){
		if (isFirstTime){
			isFirstTime = false;
		} else {
			ss << ",";
		}
		ss << clmn << ":" << columnTypesMap[clmn];
	}
	ss << "\n";
	ss << "primary key=" << primaryKey << "\n";
	ss << "recordsize=" << recordSize << "\n";
	ss << "totalsize=" << totalSize << "\n";
	ss << "records=" << numOfRecords << "\n";
	return ss.str();
	/*std::cout << "does this work\n";
	std::string myReturn = "";
	myReturn += "tablename=";
	std::cout << "does this work\n";
	myReturn += getTableName();
	myReturn += "\n";
	myReturn += "columns=";
	std::cout << "does this work\n";
	bool isFirstTime = true;
	for (std::string clmn : columnNames){
		if (isFirstTime){
			isFirstTime = false;
		} else {
			myReturn += ",";
		}
		myReturn += clmn;
		myReturn += ":";
		myReturn += columnTypesMap[clmn];
	}
	myReturn += "\n";
	myReturn += "primary key=";
	myReturn += primaryKey;
	myReturn += "\n";
	myReturn += "recordsize=";
	myReturn += recordSize;
	myReturn += "\n";
	myReturn += "totalsize=";
	myReturn += totalSize;
	myReturn += "\n";
	std::cout << "does this work\n";
	myReturn += "records=";
	myReturn += numOfRecords;
	return myReturn;*/
}

void Table::print(){
	//std::cout << "Printing a table..." << std::endl;
	std::cout << "tablename=" << tableName << std::endl;
	// build the string for columns.
	std::cout << "columns=";
	bool isFirstTime = true;
	for (std::string clmn : columnNames){
		if (isFirstTime){
			isFirstTime = false;
		} else {
			std::cout << ",";
		}
		std::cout << clmn << ":" << columnTypesMap[clmn];
	}
	std::cout << std::endl;
	std::cout << "primary key=" << primaryKey << std::endl;
	std::cout << "recordsize=" << recordSize << std::endl;
	std::cout << "totalsize=" << totalSize << std::endl;
	std::cout << "records=" << numOfRecords << std::endl;
}