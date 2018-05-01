// Header guard
#ifndef TABLE_H
#define TABLE_H

//
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>
#include <set>
#include <fstream>


class Table{
	private:
		std::string tableName;
		std::string primaryKey;
		int recordSize;
		int totalSize;
		int numOfRecords;
		std::vector<std::string> columnNames;
		std::map<std::string, std::string> columnTypesMap;
		pthread_mutex_t m_lock;
		pthread_mutex_t m_out;
		std::set<int> lockedItems;
		std::set<std::string> lockedItemsStr;
		bool temporary;
		bool dropped;
	
	public :
		Table(std::string tn, bool temp = false);
		~Table();
		void setPrimaryKey(std::string pk);
		void setRecordSize(int size);
		void incrementRecords();
		void setTotalSize(int size);
		void setNumOfRecords(int num);
		void addColumn(std::string clmn);
		void setColumnTypes(std::string columnName, std::string ctm);
		void parseAndSetPrimaryKey(std::string pk);
		void createTableFile();
		std::ifstream* getiFile();
		std::ofstream* getoFile(bool append=true);
		void lockAppend();
		void unlockAppend();
		char* getNextRow(std::ifstream* ifs);
		char* getNthRow(std::ifstream* ifs, int n);
		std::string getRecordColumn(char* buffer, std::string col);
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
		std::string parseRecord(char* buffer, std::vector<std::string> fieldList);
		bool updateRecord(std::string pk, char* buffer);
		size_t getColumnByteSizeAt(int columnIndex);
		size_t getColumnBytePosition(std::string clmn);
		size_t getColumnByteSize(std::string);
		size_t getIndexOfPrimaryKey();
		bool isLocked(int rowpos_target, bool inside = false);
		bool lock(int rowpos_target);
		bool unlock(int rowpos_target);
		bool isLocked(std::string rowpos_target, bool inside = false);
		bool lock(std::string rowpos_target);
		bool unlock(std::string rowpos_target);
};

#endif
