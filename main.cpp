
#include <stdlib.h>
#include <string>
#include <iostream>

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
using hsql::kStmtCreate;
using hsql::kStmtDelete;
using hsql::kStmtDrop;
using hsql::kTableSelect;

std::string getString(std::FILE *f) {
	char buf[STRSIZE];
	fread(buf, sizeof(char)*STRSIZE, 1, f);
	std::string result(buf);
	return result;
}

int getInt(std::FILE *f) {
	int buf;
	fread(&buf, sizeof(int), 1, f);
	return buf;
}

void writeString(std::FILE *f, std::string input) {
//	fwrite();
}

void writeInt(std::FILE *f, int input) {
//	fwrite();
}

std::FILE* openTable(const char* table, const char* mode) {
	std::string fname(table);
	fname = fname+".tbl";
	std::FILE* f = fopen(fname.c_str(), mode);
	return f
}

void readCatalog() {
	return;
}

void writeCatalog() {
	return;
}

void log(std::string logbuf) {
	printf("LOG: %s\n", logbuf.c_str());
}

void selectData(const hsql::SelectStatement* stmt) {
	printf("select\n");
	std::FILE* f = openTable(stmt->tableName, "rb");
	//read catalog
	fclose(f);
	delete f;
}
void insertData(const hsql::InsertStatement* stmt) {
	printf("Insert\n");
	//read catalog
}
void deleteData(const hsql::DeleteStatement* stmt) {
	printf("delete\n");
	//read catalog
}
void createTable(const hsql::CreateStatement* stmt) {
	printf("create %s\n", stmt->tableName);
	std::FILE* f = openTable(stmt->tableName, "wb");
	//update catalog
	fclose(f);
	delete f;
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
		case kStmtCreate:
		    createTable((const hsql::CreateStatement*) stmt);
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

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./example \"SELECT * FROM test;\"\n");
		Catalog ctlg;
		ctlg.loadFromFile("catalog.txt");
		while (true){
			printf("\nSQL> ");
			std::string myStatement;
			getline(std::cin, myStatement);
			if (myStatement == "quit"){
				return 0;
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
    }
    std::string query = argv[1];

    // parse a given query
    hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(query);
	
    // check whether the parsing was successful
    if (result->isValid()) {
        printf("Parsed successfully!\n");
        printf("Number of statements: %lu\n", result->size());

        for (uint i = 0; i < result->size(); ++i) {
			const hsql::SQLStatement* statement = result->getStatement(i);

			dispatchStatement(statement);

            hsql::printStatementInfo(statement);
        }

        delete result;
        return 0;
    } else {
        fprintf(stderr, "Given string is not a valid SQL query.\n");
        fprintf(stderr, "%s (L%d:%d)\n", 
                result->errorMsg(),
                result->errorLine(),
                result->errorColumn());
        delete result;
        return -1;
    }
}
