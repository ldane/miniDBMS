
CFLAGS = -Wl,-R -Wl,$(shell pwd)/sql-parser/ -std=c++0x -lstdc++ -Wall -Werror -I./sql-parser/src/ -L./sql-parser/

all:
	$(CXX) $(CFLAGS) main.cpp -o main -lsqlparser

