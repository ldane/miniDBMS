// Header guard
#ifndef CATALOG_H
#define CATALOG_H
//
#include "table.h"

//
class Catalog{
	private:
		int numOfTables;
		std::map<std::string, Table*> tables;
	
	public:
		Catalog();
		void addTable(Table* newTable);
		void loadFromFile(std::string fileName);
		void writeToFile();
}

#endif