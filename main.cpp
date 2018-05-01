
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <cstring>
#include <list>
#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// include the sql parser
#include "SQLParser.h"

//
#include "catalog.h"
#include "table.h"

// contains printing utilities
#include "sqlhelper.h"

Catalog ctlg;
std::list<std::string> work_q;
pthread_mutex_t work_m;

using hsql::kStmtSelect;
using hsql::kStmtInsert;
using hsql::kStmtDelete;
using hsql::kStmtDrop;
using hsql::kStmtUpdate;
using hsql::kTableSelect;
using hsql::kExprStar;
using hsql::kExprLiteralInt;
using hsql::kExprLiteralString;
using hsql::ColumnDefinition;
using hsql::Expr;

/* Helper functions */
bool icompare_pred(unsigned char a, unsigned char b) {
    return std::tolower(a) == std::tolower(b);
}

bool icompare(std::string const& a, std::string const& b) {
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                           a.begin(), icompare_pred);
    } else {
        return false;
    }
}

// trim from start
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends
static inline void trim(std::string &s) {
	rtrim(s);
    ltrim(s);
}

//find in a vector
static inline bool find(std::vector<std::string> vector, std::string item) {
	for(auto it: vector) {
		if( icompare(it, item) )
			return true;
	}
	return false;
}

/* End helper functions */

bool doOperation(char op, int val1, int val2) {
	bool check=false;
	switch(op) {
		case '=':
			if(val1 == val2)
				check=true;
			break;
		case '<':
			if(val1 < val2)
				check=true;
			break;
		case '>':
			if(val1 > val2)
				check=true;
			break;
		default:
			break;
	}
	return check;
}

bool doOperation(char op, std::string val1, std::string val2) {
	bool check=false;
	switch(op) {
		case '=':
			if(val1 == val2)
				check=true;
			break;
		default:
			break;
	}
	return check;
}

std::vector<std::string> prepareFieldList(std::vector<hsql::Expr *>* values, std::string table="") {
	// prepare select list
	std::vector<std::string> fields;
	for(auto it = values->begin(); it != values->end(); ++it) {
		if ((*it)->type == hsql::kExprStar)
			break;
		if((*it)->table!=NULL) {
			std::string eTable((*it)->table);
			if(table!="")
				if(table != eTable)
					continue;
		}
		fields.push_back((*it)->name);
	}
	return fields;
}

int selectData(const hsql::SelectStatement* stmt, bool print=true) {
	int count=0;
	std::ostringstream hdr;
	std::ostringstream ss;

	if(stmt->fromTable->type == hsql::kTableJoin) {
		// Do Join
		auto join = stmt->fromTable->join;
		auto right = join->right;
		auto left = join->left;
		auto condition = join->condition;
		auto op = condition->opChar;
		auto e1 = condition->expr;
		auto e2 = condition->expr2;

		std::string rName(right->name);
		std::string e2Name(e2->table);
		if (icompare(rName,e2Name)) {
			auto temp = e2;
			e2 = e1;
			e1 = temp;
		}

		Table *rTable = ctlg.findTable(right->name);
		Table *lTable = ctlg.findTable(left->name);
		std::string rtype = rTable->getColumnType(right->name);
		std::string ltype = lTable->getColumnType(left->name);
		//If the columns are not same type, no need to do the join
		if (rtype != ltype)
			return -1;

		std::ifstream *rifs = rTable->getiFile();
		std::ifstream *lifs = lTable->getiFile();

		std::vector<std::string> rFieldList = prepareFieldList(stmt->selectList, right->name);
		std::vector<std::string> lFieldList = prepareFieldList(stmt->selectList, left->name);

		std::list<std::string> headers;

		if (rFieldList.size()==0)
			rFieldList = rTable->getColumnNames();
		if (lFieldList.size()==0)
			lFieldList=lTable->getColumnNames();

		for(const auto it : rFieldList)
			if(find(lFieldList, it)) {
				std::string buf(right->name);
				headers.push_back(buf+"."+it);
			}
			else
				headers.push_back(it);

		for (const auto& it: lFieldList) 
			if(find(rFieldList, it)) {
				std::string buf(left->name);
				headers.push_back(buf+"."+it);
			}
			else
				headers.push_back(it);

		for (const auto& it: headers)
			hdr << it << ' ';
		hdr << "\n";
		
		for(char* rbuf=rTable->getNextRow(rifs); rbuf!=NULL; rbuf=rTable->getNextRow(rifs)) {
			auto val1 = rTable->getRecordColumn(rbuf, e1->name);
			//restart the file
			lifs->clear();
			lifs->seekg (0, lifs->beg);
			for(char* lbuf=lTable->getNextRow(lifs); lbuf!=NULL; lbuf=lTable->getNextRow(lifs)) {
				auto val2 = lTable->getRecordColumn(lbuf, e2->name);
				if(doOperation(op,val1,val2)) {
					ss << rTable->parseRecord(rbuf, rFieldList) << lTable->parseRecord(lbuf, lFieldList) << "\n";
					count++;
				}
			}
		}
		rifs->close();
		lifs->close();
	} else {

		Table *t = ctlg.findTable(stmt->fromTable->name);
		// check if the table exists
		if( t == NULL ) {
			if(print)
				std::cout << "No table found\n";
			return -1;
		}
		
		
		
		std::ifstream* ifs = t->getiFile();
		std::vector<std::string> fieldList = prepareFieldList(stmt->selectList);
		
		if (fieldList.size()==0){
			for (const auto& i: t->getColumnNames())
				hdr << i << ' ';
			hdr << "\n";
		} else {
			for (const auto& i: fieldList)
				hdr << i << ' ';
			hdr << "\n";
		}
			
		for(char* buf=t->getNextRow(ifs); buf!=NULL; buf=t->getNextRow(ifs)) {
			if(stmt->whereClause==NULL) {
				count++;
				ss << t->parseRecord(buf,fieldList) << "\n";
			} else {
				auto where = stmt->whereClause;
				auto field = where->expr->name;
				int pos = t->getColumnBytePosition(field);
				//std::string type = t->getColumnType(field);
				char *b=buf+pos;
				bool doit=false;

				if(where->expr2->type==kExprLiteralString) {
					std::string val1(b);
					std::string val2(where->expr2->name);
					doit = doOperation(where->opChar, val1, val2);
				} else if(where->expr2->type==kExprLiteralInt) {
					int val1;
					memcpy(&val1, b, sizeof(int));
					int val2 = where->expr2->ival;
					doit = doOperation(where->opChar, val1, val2);
				}

				if(doit) {
					count++;
					ss << t->parseRecord(buf,fieldList) << "\n";
				}
			}
		}
		ifs->close();
	}

	if(print && count!=0) {
		std::cout << hdr.str() << ss.str();
	} else if ( print && count == 0 ) {
		std::cout << "No column(s) found.\n";
	}
	return count;
}

void packRecord(std::ofstream *ofs, Table *t, const std::vector<hsql::Expr *>* values) {
	int ind=0;
	int i;
	char* s;
	for(auto it = values->begin(); it != values->end(); ++it, ++ind) {
		size_t size;
		const hsql::Expr* v=*it;
		switch(v->type) {
			case kExprLiteralInt:
				i=v->ival;
				size = t->getColumnByteSizeAt(ind);
				//std::cout << v->ival << "\n";
				ofs->write((char *)&i, size);
				break;
			case kExprLiteralString:
				size = t->getColumnByteSizeAt(ind);
				s = new char[size];
				std::memset(s,0,size);
				std::strcpy(s,v->name);
				//std::cout << s << "\n";
				ofs->write(s, size);
				break;
			default:
				break;
		}
	}
}

int insertData(const hsql::InsertStatement* stmt) {
	std::string fileName = stmt->tableName;
	trim(fileName);
	std::string tName = fileName;
	fileName += ".tbl";
	std::ifstream infile(fileName);
	if (!infile.good()){
		printf("Table doesn't exist to insert into");
		return -1;
	}
	infile.close();

	auto table=ctlg.findTable(stmt->tableName);
	auto values = stmt->values;

	//CHECK BEFORE INSERT
	std::ostringstream query;
	query << "SELECT * FROM ";
	query << stmt->tableName <<" WHERE ";
	query << table->getPrimaryKey() << "=";
	int pos = table->getIndexOfPrimaryKey();
	int i=0;
	for(auto it = values->begin(); it != values->end(); ++it) {
		const hsql::Expr* v=*it;
		if(i==pos) {
			switch(v->type) {
				case kExprLiteralInt:
					query << v->ival;
					break;
				case kExprLiteralString:
					query << "'" << v->name << "';";
					break;
				default:
					break;
			}
			break;
		}
		i++;
	}

	hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(query.str());
	i=selectData((const hsql::SelectStatement*) result->getStatement(0),false);
	if(i!=0) {
		std::cout << "Duplicate Primary Key\n";
		return -1;
	}

	table->lockAppend();
	std::ofstream *ofs = table->getoFile();
	packRecord(ofs, table, values);
	ofs->close();
	table->unlockAppend();
	delete ofs;

	// increment things in catalog
	if (ctlg.incrementRecordsInTable(tName)) printf("Successfully inserted record\n");
	return 1;
}

int deleteData(const hsql::DeleteStatement* stmt) {
	printf("delete\n");
	return 0;
}

int updateData(const hsql::UpdateStatement* stmt, bool specialCase=false) {
	//if (specialCase) printf("Parsed successfully!\n");
	char* buffer;
	int recordsize;
	int count=0;
	int currentValue=0;
    std::string fileName = stmt->table->name;
    trim(fileName);
    fileName += ".tbl";
    std::ifstream ifs(fileName, std::ifstream::binary | std::ifstream::in | std::ifstream::out);
	Table *t = ctlg.findTable(stmt->table->name);
	if( t == NULL ) {
		//table doesnt exist = update should fail = transaction should fail
		return -1;
	}	
	recordsize = t->getRecordSize();	
	buffer = new char[recordsize];

	// prepare update fields/values
	std::string column0 = stmt->updates->at(0)->column;
	std::string whereName = stmt->where->expr->name;
	int targetRowPos = 0;
	
	bool matchFound = false;
	while (!t->lock(stmt->where->expr2->ival)){
		usleep(1000);
	}
	while (true) {
		ifs.read(buffer, recordsize);
		if(ifs.eof())
			break;
		if(stmt->where==NULL) {
			break;
		} else {
			int pos = t->getColumnBytePosition(whereName);
			char *b=buffer+pos;
			bool doit=false;
			if(stmt->where->isSimpleOp('=')) {
				if(stmt->where->expr2->type==kExprLiteralString) {
					std::string val1(b);
					std::string val2(stmt->where->expr2->name);
					if(val1 == val2)
						doit=true;
				} else if(stmt->where->expr2->type==kExprLiteralInt) {
					int val1;
					memcpy(&val1, b, sizeof(int));
					int val2 = stmt->where->expr2->ival;
					if(val1==val2)
						doit=true;
				}
			}
			if(doit) {
				count++;
				matchFound = true;
				targetRowPos = ifs.tellg();
				if (specialCase){
					//save the value
					int poss = t->getColumnBytePosition(column0);
					char* bb = buffer+poss;
					memcpy(&currentValue, bb, sizeof(int));
				}
				break;
			}
		}
	}
	
	ifs.close();
	if (matchFound){
		//pthread_mutex_lock(&out_m);
		
		std::fstream fs(fileName, std::fstream::binary | std::fstream::out | std::ofstream::in);
		fs.seekp(targetRowPos+t->getColumnBytePosition(column0)-recordsize);
		if (stmt->updates->at(0)->value->isType(kExprLiteralInt)){
			fs.write((char *)&stmt->updates->at(0)->value->ival, t->getColumnByteSize(column0));
		} else if (stmt->updates->at(0)->value->isType(kExprLiteralString)){
			if (specialCase){
				//parse this 'balance-1' or 'balance+1' balance+1 WHERE 
				//first find the - or + operator
				std::string fullstring = stmt->updates->at(0)->value->name;
				std::string valueString;
				std::size_t valuepos;
				std::size_t minuspos = fullstring.find('-');
				std::size_t pluspos = fullstring.find('+');
				if (minuspos != std::string::npos){
					//its a decrement function 
					valuepos = minuspos+1;
					valueString = fullstring.substr(valuepos);
					int modiValue = std::stoi(valueString);
					int newValue = currentValue-modiValue;
					fs.write((char *)&newValue, t->getColumnByteSize(column0));
				} else if (pluspos != std::string::npos){
					//its an increment function
					valuepos = pluspos+1;
					valueString = fullstring.substr(valuepos);
					int modiValue = std::stoi(valueString);
					int newValue = currentValue+modiValue;
					fs.write((char *)&newValue, t->getColumnByteSize(column0));
				}
			} else {
				char* s;
				size_t size;
				size = t->getColumnByteSize(column0);
				s = new char[size];
				std::memset(s,0,size);
				std::strcpy(s,stmt->updates->at(0)->value->name);
				fs.write(s, size);
			}
		}
		fs.close();
		//pthread_mutex_unlock(&out_m);
		//printf("Successfully updated record\n");
	} else {
		if(stmt->where->expr2->type==kExprLiteralString) {
			std::string val2(stmt->where->expr2->name);
			std::cout << "Primary key: " << val2 << " does not exist\n";
		} else if(stmt->where->expr2->type==kExprLiteralInt) {
			int val2 = stmt->where->expr2->ival;
			std::cout << "Primary key: " << val2 << " does not exist\n";
		}
	}
	t->unlock(stmt->where->expr2->ival);
	return count;
}

int createTable(const std::string query) {
	std::string tableName, field, lastfield;
	std::string nQuery = query.substr(12);
	std::size_t pos;

	pos = nQuery.find('(');
	tableName = nQuery.substr(0,pos);
	trim(tableName);
	
	//create our table *
	Table* pTable = new Table(tableName);

	nQuery.erase(0, pos+1);
	
	while((pos = nQuery.find(',')) != std::string::npos) {
		field = nQuery.substr(0,pos);
		trim(field);
		std::replace(field.begin(), field.end(), ' ',':');
		// add columns to our table*
		pTable->addColumn(field);
		nQuery.erase(0,pos+1);
	}

	pos = nQuery.rfind(")");
	lastfield = nQuery.substr(0,pos);
	trim(lastfield);
	if(icompare(lastfield.substr(0,11), "PRIMARY KEY")) {
		pos = lastfield.find("(");
		lastfield.erase(0,pos+1);
		pos = lastfield.rfind(")");
		lastfield = lastfield.substr(0,pos);
		trim(lastfield);
	}
	// check if the primary key exists
	
	// now build the table, and insert it into the catalog
	
	pTable->setPrimaryKey(lastfield);
	if (ctlg.addTable(pTable)){
		pTable->createTableFile();
		std::cout << "Created TABLE " << tableName << " Successfully\n";
		return 0;
	} else {
		std::cout << "Duplicate TABLE " << tableName << " exists already\n";
		return -1;
	}
	return 0;
}

int dropTable(const hsql::DropStatement* stmt) {
	//update catalog
	//no need to use drop flag, just delete entry entirely
	std::string tName = stmt->name;
	trim(tName);
	ctlg.dropTable(tName);
	//remove table file
	std::string fName = tName;
	tName += ".tbl";
	if( std::remove( tName.c_str() ) != 0 ){
		perror( "Error deleting file" );
		return -1;
	} else {
		puts( "File successfully deleted" );
		printf("Dropped table successfully\n");
	}
	return 0;
}

int dispatchStatement(const hsql::SQLStatement* stmt, bool updateSpecialCase=false) {
	int result=-1;
	switch (stmt->type()) {
		case kStmtSelect:
		    result=selectData((const hsql::SelectStatement*) stmt);
			break;
		case kStmtInsert:
		    result=insertData((const hsql::InsertStatement*) stmt);
			break;
		case kStmtDelete:
		    result=deleteData((const hsql::DeleteStatement*) stmt);
			break;
		case kStmtDrop:
			result=dropTable((const hsql::DropStatement*) stmt);
			break;
		case kStmtUpdate:
			result=updateData((const hsql::UpdateStatement*) stmt, updateSpecialCase);
			break;
		default:
			break;
	}

	return result;
}

int parseCommand(std::string myStatement) {
	bool updateSpecialCase = false;
	if (icompare(myStatement.substr(0, 6), "UPDATE")){
		int colpos = myStatement.find("SET ");
		int equalpos = myStatement.find('=');
		int length = equalpos-colpos-4;
		//std::cout << myStatement.substr(colpos+4, length) << "\n" << myStatement.substr(equalpos+1, length) << "\n";
		if (icompare(myStatement.substr(colpos+4, length), myStatement.substr(equalpos+1, length))){
			//add the ' ' around the thing.
			int wherepos = myStatement.find("WHERE ");
			myStatement.insert(wherepos-1, "'");
			myStatement.insert(equalpos+1 ,"'");
			updateSpecialCase = true;
		}
	}
	
	if (icompare(myStatement.substr(0,12),"create table")) {
		return createTable(myStatement);
	} else if (icompare(myStatement.substr(0,6),"commit")) {
		return 0;
	} else if (icompare(myStatement.substr(0,10),"show table")) {
		if(icompare(myStatement.substr(0,11),"show tables")) {
			ctlg.showTables();
		} else {
			myStatement.erase(0,10);
			trim(myStatement);
			if (myStatement=="")
				std::cout << "No table name specified.\n";
			else
				ctlg.showTable(myStatement);
		}
		return 0;
	} else {
		int retval=0;
		hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(myStatement);
		if (result->isValid()) {
			//printf("Parsed successfully!\n");

			for (uint i = 0; i < result->size(); ++i) {
				const hsql::SQLStatement* statement = result->getStatement(i);

				retval = dispatchStatement(statement, updateSpecialCase);
			}
		} else {
			fprintf(stderr, "Given string is not a valid SQL query.\n");
			fprintf(stderr, "%s (L%d:%d)\n", 
					result->errorMsg(),
					result->errorLine(),
					result->errorColumn());
			retval=-1;
		}
		delete result;
		return retval;
	}
}

bool processStream(std::istream &ss, bool single = false, bool transaction = false) {
	std::string myStatement;
	while(true) {
		std::getline(ss, myStatement, ';');
		if(ss.eof())
			break;

		size_t pos=myStatement.rfind(';');
		myStatement = myStatement.substr(0,pos-1);
		trim(myStatement);

		if(icompare(myStatement.substr(0,4), "quit")) {
			return false;
		}
		int retval = parseCommand(myStatement);
		if(transaction)
			if(retval < 0)
				return false;
		if (single) return true;
	}
	return true;
}

std::string getWork(int threadNumber) {
	std::string item;
	pthread_mutex_lock(&work_m);
	if(work_q.size() != 0) {
		item = work_q.front();
		work_q.pop_front();
	}
	pthread_mutex_unlock(&work_m);
	return item;
}

int workSize() {
	pthread_mutex_lock(&work_m);
	int size = work_q.size();
	pthread_mutex_unlock(&work_m);
	return size;
}

static void* threadFunc(void *ptr) {
	bool quit=true;
	while(quit) {
		std::string work = getWork(1);
		if(work.size() == 0) {
			quit=false;
			break;
		}
		std::istringstream ifs(work);
		quit=processStream(ifs,false,true);
	}
	return NULL;
}

void processScript(std::string filename, int maxthread) {
	std::ifstream ss(filename);
	std::string line;
	std::string rest;
	pthread_mutex_init(&work_m, NULL);
	while(true) {
		std::getline(ss, line);
		if(ss.eof()) {
			rest+= line;
			break;
		}

		if(icompare(line, "BEGIN TRANSACTION")) {
			std::ostringstream ofs;
			while(true) {
				std::getline(ss, line);
				if(icompare(line, "END TRANSACTION;"))
					break;
				else
					ofs << line << "\n";
			}
			work_q.push_back(ofs.str());
		} else {
			rest+= line;
		}
	}
	ss.close();
	//std::cout << "Work: " << work_q.size() << "\n";

	std::list<pthread_t> threadList;
	for(int i=0; i<maxthread; i++) {
		pthread_t tid;
		int result = pthread_create(&tid, NULL, threadFunc, NULL);
		threadList.push_back(tid);
		if( result!=0 )
			std::cout <<"Ups\n";
	}
	for(auto t : threadList) {
		pthread_join(t, NULL);
	}
	pthread_mutex_destroy(&work_m);
	parseCommand(rest);
}

int main(int argc, char *argv[]) {
	ctlg.loadFromFile("catalog.txt");
	bool quit=true;
	if (argc!=1) {
		std::string arg = argv[1];
		size_t len = arg.size();
		if(icompare(arg.substr(len-4),".sql")) {
			std::ifstream ss(arg);
			quit=processStream(ss);
		} else if (icompare(arg.substr(0,7), "script=")) {
			int pos = arg.find(':');
			int maxthread = 0;
			std::string script = arg.substr(7,pos-7);
			pos+=1;
			if(icompare(arg.substr(pos,11), "numthreads=")) {
				maxthread = std::stoi(arg.substr(pos+11));
			}
			processScript(script, maxthread);
			quit=false;
		} else {
			std::istringstream ss(argv[1]);
			quit=processStream(ss);
		}
	}
	while (quit){
		printf("\nSQL> ");
		quit=processStream(std::cin, true);
    }
	ctlg.writeToFile("catalog.txt");
	return 0;
}
