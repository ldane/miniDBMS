
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


void log(std::string logbuf) {
	printf("LOG: %s\n", logbuf.c_str());
}

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
	std::string tableName, fields;
	std::string nQuery = query.substr(6);
	std::cout << nQuery;
	std::stringstream ss(nQuery);
	if(std::getline(ss, tableName, '(')) {
		std::cout << "Ups";
	}
	if(std::getline(ss, fields, ')')) {
		std::cout << "Ups";
	}
	std::cout << tableName << " " << fields;
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

hsql::SQLParserResult* parse(std::string query){
	hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(query);
	return result;
}

void parseCommand(std::string myStatement) {
	if (myStatement == "quit"){
		return 0;
	} else if (icompare(myStatement.substr(0,6),"create")) {
		std::cout << "Create";
		createTable(myStatement);
	} else if (icompare(myStatement.substr(0,10),"show table")) {
		std::cout << "Show";
	} else {
		hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(myStatement);
		if (result->isValid()) {
			printf("Parsed successfully!\n");
			printf("Number of statements: %lu\n", result->size());

			for (uint i = 0; i < result->size(); ++i) {
				;const hsql::SQLStatement* statement = result->getStatement(i);

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
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./example \"SELECT * FROM test;\"\n");
		Catalog ctlg;
		ctlg.loadFromFile("catalog.txt");
		while (true){
			printf("\nSQL> ");
			std::string myStatement;
			getline(std::cin, myStatement);
			parseCommand(myStatement);
		}
    }
	return 0;
}
