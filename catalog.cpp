//
#include "catalog.h"

//

Catalog::Catalog(){
	numOfTables = 0;
}

void Catalog::addTable(Table newTable){
	tables.insert(std::make_pair(newTable.getTableName(), newTable);
	if (numOfTables == tables.size()) {
		// failed to insert because duplicate exists
	} else {
		numOfTables = tables.size();
		// table inserted successfully
	}
}

void Catalog::loadFromFile(std::string fileName){
	// check if file is valid table schemas
	
}

void Catalog::writeToFile(){
	// write the contents of each catalog to file in a specific format
	// format dictated in project specifiction
	// copied below
	// tableName=T
	// columns=C1:INT,C2:CHAR(5),C3:INT
	// primarykey=C1
	// recordsize=13
	// totalsize=65
	// records=5
}