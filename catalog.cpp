//
#include "catalog.h"
#include <iostream>
#include <fstream>
//

Catalog::Catalog(){
	numOfTables = 0;
}

void Catalog::addTable(Table* newTable){
	tables.insert(std::make_pair(newTable->getTableName(), newTable));
	if (numOfTables == tables.size()) {
		// failed to insert because duplicate exists
	} else {
		numOfTables = tables.size();
		// table inserted successfully
	}
}

void Catalog::loadFromFile(std::string fileName){
	// check if file is valid table schemas
	printf("Loading catalog from file");
	std::string line;
	std::ifstream file (fileName);
	if (file.is_open()){
		while (getline(file, line)){
			// process >> 6 << lines at a time
			// if a line fails to be parsed correctly, the catalog is formatted wrong or contains wrong syntax (watch out for empty lines)
			// a correctly formatted file has 6 lines in the following order.
			// tablename=?
			// columns=C1:INT,C2,CHAR(10)
			// primary key=C1
			// recordsize=?
			// totalsize=?
			// records=?
			
			// case-sensitive
			std::cout << line.substr(0, 0);
			if (line.substr(0, 9) == "tablename="){
				std::string nTableName = line.substr(10);
				printf("test1");
				if (getline(file, line)){
					if (line.substr(0, 7) == "columns="){
						printf("test2");
						if (getline(file, line)){
							if (line.substr(0, 11) == "primary key="){
								printf("test3");
								std::string nPrimaryKey = line.substr(12);
								if (getline(file, line)){
									if (line.substr(0, 10) == "recordsize="){
										printf("test4");
										std::string nRecordSize = line.substr(11);
										if (getline(file, line)){
											if (line.substr(0, 9) == "totalsize="){
												printf("test5");
												std::string nTotalSize = line.substr(10);
												if (getline(file, line)){
													if (line.substr(0, 7) == "records="){
														printf("test6");
														std::string nRecords = line.substr(8);
														// now build the table, and insert it into the catalog
														Table* pTable = new Table(nTableName);
														pTable->setPrimaryKey(nPrimaryKey);
														//pTable->setColumnNames
														//pTable->setColumnTypes
														pTable->setRecordSize(std::stoi(nRecordSize));
														pTable->setTotalSize(std::stoi(nTotalSize));
														pTable->setNumOfRecords(std::stoi(nRecords));
														addTable(pTable);
														pTable->print();
														delete pTable;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		file.close();
	}
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