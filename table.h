// Header guard
#ifndef TABLE_H
#define TABLE_H

//
#include <string>
#include <vector>
#include <map>
#include <iostream>


class Table{
	private:
		std::string tableName;
		std::string primaryKey;
		int recordSize;
		int totalSize;
		int numOfRecords;
		std::vector<std::string> columnNames;
		std::map<std::string, std::string> columnTypesMap;
	
	public :
		Table(std::string tn);
		void setPrimaryKey(std::string pk);
		void setRecordSize(int size);
		void setTotalSize(int size);
		void setNumOfRecords(int num);
		void addColumn(std::string clmn);
		void setColumnTypes(std::string columnName, std::string ctm);
		std::string getTableName();
		std::string getPrimaryKey();
		int getRecordSize();
		int getTotalSize();
		int getNumOfRecords();
		std::vector<std::string> getColumnNames();
		std::string getColumnType(std::string column);
		void print();
};

#endif