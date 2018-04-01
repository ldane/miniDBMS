
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>

// include the sql parser
#include "SQLParser.h"

//
#include "catalog.h"
#include "table.h"

// contains printing utilities
#include "sqlhelper.h"

Catalog ctlg;


#define STRSIZE 100

using hsql::kStmtSelect;
using hsql::kStmtInsert;
using hsql::kStmtDelete;
using hsql::kStmtDrop;
using hsql::kTableSelect;
using hsql::ColumnDefinition;

/* Helper functions */
bool icompare_pred(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

bool icompare(std::string const& a, std::string const& b)
{
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                           a.begin(), icompare_pred);
    }
    else {
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

/* End helper functions */

void selectData(const hsql::SelectStatement* stmt) {
	printf("select\n");
}

void insertData(const hsql::InsertStatement* stmt) {
	printf("Insert\n");
	std::cout <<"Ups\n";
	for(auto it = stmt->values->begin(); it != stmt->values->end(); ++it) {
		std::cout <<"Ups\n";
	}
	//read catalog
}

void deleteData(const hsql::DeleteStatement* stmt) {
	printf("delete\n");
	//read catalog
}

void createTableFile(std::string tableName){
	std::string fileName = tableName;
	trim(&fileName);
	fileName += ".tbl";
	std::ofstream ofs(fileName);
	ofs.close();
}

void createTable(const std::string query) {
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
	ctlg.addTable(pTable);
	createTableFile(tableName);
	//pTable->print();
}
void dropTable(const hsql::DropStatement* stmt) {
	//update catalog
	//remove table file
	printf("drop\n");
}

void dispatchStatement(const hsql::SQLStatement* stmt) {
	switch (stmt->type()) {
		case kStmtSelect:
		    selectData((const hsql::SelectStatement*) stmt);
			break;
		case kStmtInsert:
		    insertData((const hsql::InsertStatement*) stmt);
			break;
		case kStmtDelete:
		    deleteData((const hsql::DeleteStatement*) stmt);
			break;
		case kStmtDrop:
			dropTable((const hsql::DropStatement*) stmt);
			break;
		default:
			break;
	}
}

void parseCommand(std::string myStatement) {
	if (icompare(myStatement.substr(0,12),"create table")) {
		createTable(myStatement);
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
	} else {
		hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(myStatement);
		if (result->isValid()) {
			printf("Parsed successfully!\n");
			printf("Number of statements: %lu\n", result->size());

			for (uint i = 0; i < result->size(); ++i) {
				const hsql::SQLStatement* statement = result->getStatement(i);

				dispatchStatement(statement);

				hsql::printStatementInfo(statement);
			}

			delete result;
		} else {
			fprintf(stderr, "Given string is not a valid SQL query.\n");
			fprintf(stderr, "%s (L%d:%d)\n", 
					result->errorMsg(),
					result->errorLine(),
					result->errorColumn());
			delete result;
		}
	}
}



int main(int argc, char *argv[]) {
	
	ctlg.loadFromFile("catalog.txt");
	std::string myStatement;
	bool quit=true;
	if (argc!=1) {
		std::istringstream ss(argv[1]);
		while(std::getline(ss, myStatement, ';')) {
			size_t pos=myStatement.rfind(';');
			myStatement = myStatement.substr(0,pos-1);
			trim(myStatement);
			
			if(icompare(myStatement.substr(0,4), "quit")) {
				quit=false;
				break;
			}
			parseCommand(myStatement);
		}
		ctlg.writeToFile("catalogWRITETEST.txt");
	}
	while (quit){
		size_t pos;
		printf("\nSQL> ");
		std::getline(std::cin, myStatement, ';');
		pos=myStatement.rfind(';');
		myStatement = myStatement.substr(0,pos-1);
		trim(myStatement);

		if(icompare(myStatement.substr(0,4), "quit")) {
			quit=false;
			break;
		}
		parseCommand(myStatement);
		//ctlg.writeToFile("catalogWRITETEST.txt");
    }
	return 0;
}
