//
#include "table.h"
//

Table::Table(std::string tn){
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

void setColumnTypes(std::string columnName, std::string ctm){
	// need to check if already exists maybe
	columnTypesMap.insert(std::make_pair(columnName, ctm));
}
		/*std::string getTableName();
		std::string getPrimaryKey();
		int getRecordSize();
		int getTotalSize();
		int getNumOfRecords();
		std::vector<std::string> getColumnNames();
		std::string getColumnType(std::string column);*/