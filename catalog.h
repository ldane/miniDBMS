// Header guard
#ifndef CATALOG_H
#define CATALOG_H
//
#include "table.h"
#include <string>
#include <map>

//
class Catalog{
	private:
		unsigned int numOfTables;
		std::map<std::string, Table*> tables;
		pthread_mutex_t m;
	
	public:
		Catalog();
		~Catalog();
		bool addTable(Table *newTable);
		void loadFromFile(std::string fileName);
		void writeToFile(std::string fileName);
		void showTable(std::string t);
		void showTables();
		bool incrementRecordsInTable(std::string tn);
		Table* findTable(std::string t);
		void dropTable(std::string tn);
};

#endif
