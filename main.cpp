
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

// include the sql parser
#include "SQLParser.h"

//
#include "catalog.h"
#include "table.h"

// contains printing utilities
#include "sqlhelper.h"


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

void trim(std::string* s) {
	size_t pos;
	pos = s->find_first_not_of(" \t");
	s->erase(0,pos);
}

void log(std::string logbuf) {
	printf("LOG: %s\n", logbuf.c_str());
}
/* End helper functions */

void selectData(const hsql::SelectStatement* stmt) {
	printf("select\n");
}

void insertData(const hsql::InsertStatement* stmt) {
	printf("Insert\n");
	//read catalog
}

void deleteData(const hsql::DeleteStatement* stmt) {
	printf("delete\n");
	//read catalog
}

void createTable(const std::string query) {
	std::string tableName, field;
	std::string nQuery = query.substr(12);
	std::size_t pos;

	pos = nQuery.find('(');
	tableName = nQuery.substr(0,pos);
	trim(&tableName);

	std::cout << tableName << "\n";

	nQuery.erase(0, pos+1);
	
	while((pos = nQuery.find(',')) != std::string::npos) {
		field = nQuery.substr(0,pos);
		trim(&field);
		std::cout << field << "\n";
		nQuery.erase(0,pos+1);
	}

	pos = nQuery.find(");");
	std::cout << nQuery << "\n";
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
			log("undefined sql operation");
			break;
	}
}

void parseCommand(std::string myStatement) {
	if (icompare(myStatement.substr(0,12),"create table")) {
		std::cout << "create table\n";
		createTable(myStatement);
	} else if (icompare(myStatement.substr(0,10),"show table")) {
		std::cout << "show table";
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
	Catalog ctlg;
	ctlg.loadFromFile("catalog.txt");
	std::string myStatement;

	if (argc >=1) {
		std::istringstream ss(argv[1]);
		while(std::getline(ss, myStatement, ';')) {
			trim(&myStatement);
			parseCommand(myStatement);
		}
	}
	while (true){
		printf("\nSQL> ");
		while(std::getline(std::cin, myStatement, ';')) {
			trim(&myStatement);
			parseCommand(myStatement);
		}
		ctlg.writeToFile("catalogWRITETEST.txt");
    }
	return 0;
}
