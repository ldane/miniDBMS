//
#include "table.h"
//

Table::Table(std::string tn) : columnTypesMap(){
	tableName = tn;
	primaryKey = "";
	recordSize = 0;
	totalSize = 0;
	numOfRecords = 0;
	//columnNames columnTypesMap
}
void Table::setPrimaryKey(std::string pk){
	primaryKey = pk;
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
void Table::setColumnNames(std::vector<std::string> cn){
	columnNames = cn;
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

void Table::print(){
	// printf("tablename=%s\n", tableName);
	std::cout << "tablename=" << tableName << std::endl;
	// printf("primary key=%s\n", primaryKey);
	std::cout << "primary key=" << primaryKey << std::endl;
	// printf("recordsize=%d\n", recordSize);
	std::cout << "recordsize=" << recordSize << std::endl;
	// printf("totalsize=%d\n", totalSize);
	std::cout << "totalsize=" << totalSize << std::endl;
	// printf("records=%d\n", numOfRecords);
	std::cout << "records=" << numOfRecords << std::endl;
}