# miniDBMS
miniDBMS written in C++

#
./main file.sql 
./main
./main "SQL STATEMENT"

# Limitations
single PK in tables
a stored CHAR can not contain ';' ( example: 'ab;c' will cause complications )
JOIN, functionality not implemented
SELECT x,y INTO t FROM t2, functionality not implemented

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