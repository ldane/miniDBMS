//
#include "catalog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
	printf("Loading catalog from file\n");
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
			//std::cout << line.substr(10) << "111\n";
			if (line.substr(0, 10) == "tablename="){
				std::string nTableName = line.substr(10);
				if (getline(file, line)){
					if (line.substr(0, 8) == "columns="){
						// columns=C1:INT,C2,CHAR(10)
						// first take everything after the =
						// split this string by ','
						// into a vector 
						std::stringstream allColumns(line.substr(8));
						
						if (getline(file, line)){
							if (line.substr(0, 12) == "primary key="){
								std::string nPrimaryKey = line.substr(12);
								if (getline(file, line)){
									if (line.substr(0, 11) == "recordsize="){
										std::string nRecordSize = line.substr(11);
										if (getline(file, line)){
											if (line.substr(0, 10) == "totalsize="){
												std::string nTotalSize = line.substr(10);
												if (getline(file, line)){
													if (line.substr(0, 8) == "records="){
														std::string nRecords = line.substr(8);
														// now build the table, and insert it into the catalog
														Table* pTable = new Table(nTableName);
														pTable->setPrimaryKey(nPrimaryKey);
														//pTable->setColumnNames
														//pTable->setColumnTypes
														pTable->setRecordSize(std::stoi(nRecordSize));
														pTable->setTotalSize(std::stoi(nTotalSize));
														pTable->setNumOfRecords(std::stoi(nRecords));
														
														// add columns
														std::string segment;
														while(std::getline(allColumns, segment, ',')){
															pTable->addColumn(segment);
														}
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

void Catalog::writeToFile(std::string fileName){
	// write the contents of each table in catalog to file in a specific format
	// ignore tables that have the temporary and dropped flags 
	// format dictated in project specifiction
	// copied below
	// tableName=T
	// columns=C1:INT,C2:CHAR(5),C3:INT
	// primarykey=C1
	// recordsize=13
	// totalsize=65
	// records=5
	std::ofstream ofs(fileName);
	if (ofs.is_open()){
		// for each table in the map 
		// print the schema of the table if the temporary and dropped flags are both false
		for (const auto& kv : tables){
			if (!kv.second->isTemporary() && !kv.second->isDropped()){
				ofs << kv.second->getFormattedMetaData();
			}
		}
	}
	
	ofs.close();
	
}