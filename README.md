# miniDBMS
miniDBMS written in C++

# before grading/testing
we will try to remove any leftover .tbl files and clear the catalog prior to the deadline.
however, you may have to remove .tbl files and "catalog.txt" before executing anything to "clear" the database

# to compile 
should not be necessary to compile if running on server
if compilation is needed, call "make" in folder

# execution
./main file.sql //USE THIS FOR EXECUTING CREATE/INSERT sqls such as "create.sql"
./main
./main "SQL STATEMENT"
./main script=script.sql:numthreads=10 //USE THIS FOR TRANSACTIONS sqls such as "script.sql"

# Limitations
single PK in tables
a stored CHAR can not contain ';' ( example: 'ab;c' will cause complications )
Syntax for executing sql scripts in the database are limited. See the execution subsection for examples.
for transactions:
	when attempting to process a transaction sql file, the execution command must use ':' not ';'
		valid example: ./main script=script.sql:numthreads=10
		invalid example: ./main script=script.sql;numthreads=10
	when a query is invalid, it will not execute. any other queries in the same transaction as the failed query are still executed however.
	we did not set a hard check on if a column named 'balance' cannot go negative. so negative balances will not throw an error.
	MUST USE "./main script=x.sql:numthreads=y" to process as a transaction. cannot use "./main script=x.sql" if the script contains transactions

# Links/references
https://stackoverflow.com/questions/5455802/how-to-read-a-complete-line-from-the-user-using-cin
http://thispointer.com/stdmap-tutorial-part-1-usage-detail-with-examples/
http://www.cplusplus.com/reference/string/string/substr/
https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character
https://stackoverflow.com/questions/12702561/iterate-through-a-c-vector-using-a-for-loop
https://stackoverflow.com/questions/2850312/use-of-for-each-on-map-elements
https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder
http://www.cplusplus.com/forum/general/13135/
https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
http://www.cplusplus.com/reference/cstdio/remove/
https://stackoverflow.com/questions/544928/reading-integer-size-bytes-from-a-char-array
https://stackoverflow.com/questions/21647/reading-from-text-file-until-eof-repeats-last-line
https://vichargrave.github.io/multithreaded-work-queue-in-cpp/