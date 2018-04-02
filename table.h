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
		bool temporary;
		bool dropped;
	
	public :
		Table(std::string tn, bool temp = false);
		void setPrimaryKey(std::string pk);
		void setRecordSize(int size);
		void incrementRecords();
		void setTotalSize(int size);
		void setNumOfRecords(int num);
		void addColumn(std::string clmn);
		void setColumnTypes(std::string columnName, std::string ctm);
		void parseAndSetPrimaryKey(std::string pk);
		std::string getTableName();
		std::string getPrimaryKey();
		int getRecordSize();
		int getTotalSize();
		int getNumOfRecords();
		std::vector<std::string> getColumnNames();
		std::string getColumnType(std::string column);
		void print();
		void setIfDropped(bool dropflag);
		bool isTemporary();
		bool isDropped();
		std::string getFormattedMetaData();
		std::string parseRecord(char* buffer);
		int getColumnByteSizeAt(int columnIndex);
		int getColumnBytePosition(std::string clmn);
		int getColumnByteSize(std::string);
		int getIndexOfPrimaryKey();
};

#endif
