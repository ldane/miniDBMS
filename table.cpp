//
#include "table.h"
//
#include <sstream>
#include <fstream>
#include <cstring>

#include <pthread.h>

Table::Table(std::string tn, bool temp) : columnTypesMap(){
	tableName = tn;
	primaryKey = "";
	recordSize = 0;
	totalSize = 0;
	numOfRecords = 0;
	temporary = temp;
	dropped = false;
	//columnNames columnTypesMap
	pthread_mutex_init(&m_lock, NULL);
}

Table::~Table() {
	pthread_mutex_destroy(&m_lock);
}

void Table::createTableFile(){
	std::string fileName = tableName;
	fileName += ".tbl";
	std::ofstream ofs(fileName);
	ofs.close();
}

std::ifstream* Table::getiFile() {
	std::ifstream *ifs = new std::ifstream(tableName+".tbl", std::ofstream::binary | std::ofstream::in);
	return ifs;
}

std::ofstream* Table::getoFile(bool append) {
	std::ofstream *ofs;
	if(append==true)
		ofs = new std::ofstream(tableName+".tbl", std::ofstream::binary | std::ofstream::out | std::ofstream::app);
	else
		ofs = new std::ofstream(tableName+".tbl", std::ofstream::binary | std::ofstream::out);
	return ofs;

}
char* Table::getNextRow(std::ifstream* ifs) {
	char *buf = new char[recordSize];
	ifs->read(buf, recordSize);
	if(ifs->eof())
		return NULL;
	return buf;
}

char* Table::getNthRow(std::ifstream* ifs, int n) {
	char *buf;
	ifs->clear();
	ifs->seekg(0, ifs->beg);
	ifs->seekg(getRecordSize()*n-1,ifs->beg);
	buf=getNextRow(ifs);
	return buf;
}

void Table::setPrimaryKey(std::string pk){
	primaryKey = pk;
}

void Table::parseAndSetPrimaryKey(std::string pk){
	primaryKey = pk.substr(8);
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

void Table::addColumn(std::string clmn){
	// passed in value will be of format C1=INT
	// left of = is column name
	// right of = is column type 
	//std::cout << "trying to add column" << std::endl;
	//replace space with : if : not found
	std::size_t pos = clmn.find(":");
	if (pos == std::string::npos){
		//not found 
		pos = clmn.find(" ");
	}
	//std::cout << "trying to add column2" << std::endl;
	std::string nColumnName = clmn.substr(0,pos);
	//std::cout << "trying to add column3" << std::endl;
	std::string nColumnType = clmn.substr(pos+1);
	//std::cout << "trying to add column4" << std::endl;
	columnNames.push_back(nColumnName);
	columnTypesMap.insert(std::make_pair(nColumnName, nColumnType));
	if (nColumnType == "INT"){
		recordSize += 4;
		
	} else if (nColumnType.substr(0, 5) == "CHAR("){
		pos = nColumnType.find(")");
		std::string chB = nColumnType.substr(5, pos-5);
		//std::cout << "chB is " << chB << std::endl;
		recordSize += atoi(chB.c_str());
	}
}

void Table::setColumnTypes(std::string columnName, std::string ctm){
	// need to check if already exists maybe
	columnTypesMap.insert(std::make_pair(columnName, ctm));
}

std::string Table::getTableName(){
	return tableName;
}

std::string Table::getPrimaryKey(){
	return primaryKey;
}

int Table::getRecordSize(){
	return recordSize;
}

int Table::getTotalSize(){
	return totalSize;
}

int Table::getNumOfRecords(){
	return numOfRecords;
}

std::vector<std::string> Table::getColumnNames(){
	return columnNames;
}

std::string Table::getColumnType(std::string column){
	if (columnTypesMap.find(column) != columnTypesMap.end()){
		return columnTypesMap[column];
	} else {
		return "";
	}
}

void Table::setIfDropped(bool dropflag){
	dropped = dropflag;
}
bool Table::isTemporary(){
	return temporary;
}

bool Table::isDropped(){
	return dropped;
}

std::string Table::getFormattedMetaData(){
	std::ostringstream ss;
	ss << "tablename=" << tableName << "\n";
	ss << "columns=";
	bool isFirstTime = true;
	for (std::string clmn : columnNames){
		if (isFirstTime){
			isFirstTime = false;
		} else {
			ss << ",";
		}
		ss << clmn << ":" << columnTypesMap[clmn];
	}
	ss << "\n";
	ss << "primary key=" << primaryKey << "\n";
	ss << "recordsize=" << recordSize << "\n";
	ss << "totalsize=" << totalSize << "\n";
	ss << "records=" << numOfRecords << "\n";
	return ss.str();
	/*std::cout << "does this work\n";
	std::string myReturn = "";
	myReturn += "tablename=";
	std::cout << "does this work\n";
	myReturn += getTableName();
	myReturn += "\n";
	myReturn += "columns=";
	std::cout << "does this work\n";
	bool isFirstTime = true;
	for (std::string clmn : columnNames){
		if (isFirstTime){
			isFirstTime = false;
		} else {
			myReturn += ",";
		}
		myReturn += clmn;
		myReturn += ":";
		myReturn += columnTypesMap[clmn];
	}
	myReturn += "\n";
	myReturn += "primary key=";
	myReturn += primaryKey;
	myReturn += "\n";
	myReturn += "recordsize=";
	myReturn += recordSize;
	myReturn += "\n";
	myReturn += "totalsize=";
	myReturn += totalSize;
	myReturn += "\n";
	std::cout << "does this work\n";
	myReturn += "records=";
	myReturn += numOfRecords;
	return myReturn;*/
}

void Table::incrementRecords(){
	numOfRecords++;
	totalSize+=recordSize;
}

void Table::print(){
	std::cout << getFormattedMetaData();
}

std::string Table::getRecordColumn(char* buffer, std::string col) {
	std::ostringstream ss;
	size_t m = getColumnBytePosition(col);
	char *nbuf= buffer+m;
	std::string focus = getColumnType(col);
	if(focus == "INT") {
		int *i = (int *)nbuf;
		ss << *i;
	} else if (focus.substr(0,4) == "CHAR") {
		size_t pos = focus.length();
		int v = atoi(focus.substr(5,pos-5).c_str());
		std::string s(nbuf,v);
		//ss << c.first << ":" << s << "\n";
		ss << "'" << s << "'";
	}
	return ss.str();
}	

std::string Table::parseRecord(char* buffer, std::vector<std::string> fieldList) {
	std::ostringstream ss;
	for (auto const& value : columnNames){
		std::string focus = getColumnType(value);
		if(fieldList.size() != 0) {
			bool found=false;
			for(auto const& field: fieldList) {
				if (field == value)
					found=true;
			}
			if(found==false) {
				buffer+=getColumnByteSize(value);
				continue;
			}
		}
		if(focus == "INT") {
			int *i = (int *)buffer;
			//ss << c.first << ":" << i << "\n";
			ss << *i;
			buffer+=sizeof(int);
		} else if (focus.substr(0,4) == "CHAR") {
			size_t pos = focus.length();
			int v = atoi(focus.substr(5,pos-5).c_str());
			std::string s(buffer,v);
			//ss << c.first << ":" << s << "\n";
			ss << "'" << s << "'";
			buffer+=v;
		}
		ss << " ";
	}
	return ss.str();
}

bool Table::updateRecord(std::string pk, char* buffer){
	return true;	
}

size_t Table::getColumnByteSizeAt(int columnIndex){
	std::string focus = getColumnType(columnNames.at(columnIndex));
	std::size_t pos;
	
	if (focus == "INT"){
		return 4;
		
	} else if (focus.substr(0, 5) == "CHAR("){
		pos = focus.find(")");
		std::string chB = focus.substr(5, pos-5);
		//std::cout << "chB is " << chB << std::endl;
		return atoi(chB.c_str());
	}
	return 0;
}

size_t Table::getColumnBytePosition(std::string clmn){
	size_t bytePos = 0;
	for (std::size_t i = 0; i < columnNames.size(); i++){
		if (columnNames.at(i) != clmn){
			bytePos += getColumnByteSizeAt(i);
		} else {
			return bytePos;
		}
	}
	// if it doesnt find any matches, return ???
	return -1;
}

size_t Table::getColumnByteSize(std::string clmn){
	std::size_t pos;
	for (auto const& value : columnNames){
		if (value == clmn){
			std::string focus = getColumnType(value);
			if (focus == "INT"){
				return 4;
				
			} else if (focus.substr(0, 5) == "CHAR("){
				pos = focus.find(")");
				std::string chB = focus.substr(5, pos-5);
				//std::cout << "chB is " << chB << std::endl;
				return atoi(chB.c_str());
			}
		}
	}
	
	// none found? 
	return 0;
}

size_t Table::getIndexOfPrimaryKey(){
	for (size_t i = 0; i < columnNames.size(); i++){
		if (columnNames.at(i) == getPrimaryKey()){
			return i;
		}
	}
	return 0;
}

bool Table::isLocked(int pk_target){
	// returns true if locked 
	// returns false if unlocked
	bool result;
	pthread_mutex_lock(&m_lock);
	if (lockedItems.find(pk_target) == lockedItems.end()) {
		result = false;
	} else {
		result = true;
	}
	pthread_mutex_unlock(&m_lock);
	return result;
}
bool Table::lock(int pk_target){
	// returns true if successfully locked row
	// returns false if row is already locked
	bool result;
	pthread_mutex_lock(&m_lock);
	if (isLocked(pk_target)){
		result = false;
	} else {
		lockedItems.insert(pk_target);
		result = true;
	}
	pthread_mutex_unlock(&m_lock);
	return result;
}
bool Table::unlock(int pk_target){
	// returns true if successfully unlocks row
	// returns false if row is already unlocked (shouldn't happen)
	bool result;
	pthread_mutex_lock(&m_lock);
	if (isLocked(pk_target)){
		lockedItems.erase(pk_target);
		result = true;
	} else {
		result = false;
	}
	pthread_mutex_unlock(&m_lock);
	return result;
}
