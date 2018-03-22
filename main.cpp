
#include <stdlib.h>
#include <string>

// include the sql parser
#include "SQLParser.h"

// contains printing utilities
#include "sqlhelper.h"

using hsql::kStmtSelect;
using hsql::kStmtInsert;
using hsql::kStmtCreate;
using hsql::kStmtUpdate;
using hsql::kStmtDelete;
using hsql::kStmtDrop;


void dispatchStatement(const hsql::SQLStatement* stmt) {
	switch (stmt->type()) {
		case kStmtSelect:
			printf("Select\n");
			break;
		case kStmtInsert:
			printf("Insert\n");
			break;
		case kStmtCreate:
			printf("Create\n");
			break;
		case kStmtUpdate:
			printf("Update\n");
			break;
		case kStmtDelete:
			printf("Delete\n");
			break;
		case kStmtDrop:
			printf("Drop\n");
			break;
		default:
			break;
	}
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./example \"SELECT * FROM test;\"\n");
        return -1;
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
