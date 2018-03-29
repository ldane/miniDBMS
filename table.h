// Header guard
#ifndef TABLE_H
#define TABLE_H

//
class Table{
	private:
		std::string tableName;
		std::string primaryKey;
		int recordSize;
		int totalSize;
		int numOfRecords;
		std::vector<std::string>;
		std::map<std::string, std::string>;
	
	public :
		Table(std::string);
		void setPrimaryKey(std::string);
		void setRecordSize(int size);
		void setTotalSize(int size);
		void setNumOfRecords(int num);
		void setColumnNames(std::vector<std::string> columnNames);
		void setColumnTypes(std::string columnName, std::string columnType);
		std::string getTableName();
		std::string getPrimaryKey();
		int getRecordSize();
		int getTotalSize();
		int getNumOfRecords();
		std::vector<std::string> getColumnNames();
		std::string getColumnType(std::string column);
}

#endif