CC=clang++
CFLAGS=-pedantic-errors -gdwarf-4 -std=c++20
LDFLAGS=-lgtest -lgtest_main -lpthread

all: BUtests LogsTests DBtests LAtests

load:
	sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && sudo cp lib/*.a /usr/lib && sudo ln -s /usr/lib/libgtest.a /usr/local/lib/libgtest.a && sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/libgtest_main.a

BUtests: tests/BUtests.cpp code/BankOfUsers.cpp code/sha256.cpp
	$(CC) tests/BUtests.cpp code/BankOfUsers.cpp code/sha256.cpp $(CFLAGS) $(LDFLAGS) -o $@

LogsTests: tests/LogsTests.cpp code/Logs.cpp
	$(CC) tests/LogsTests.cpp code/Logs.cpp $(CFLAGS) $(LDFLAGS) -o $@

DBtests: tests/DBtests.cpp code/Logs.cpp code/DB.cpp
	$(CC) tests/DBtests.cpp code/Logs.cpp code/DB.cpp $(CFLAGS) $(LDFLAGS) -o $@

LAtests: tests/LAtests.cpp code/Logs.cpp code/LexicalAnalysis.cpp
	$(CC) tests/LAtests.cpp code/Logs.cpp code/LexicalAnalysis.cpp $(CFLAGS) $(LDFLAGS) -o $@

testsMemory: BUtests LogsTests DBtests LAtests
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no --error-exitcode=111 ./LogsTests
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no --error-exitcode=111 ./BUtests
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no --error-exitcode=111 ./DBtests
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no --error-exitcode=111 ./LAtests

clean:
	rm -rf *.o BUtests LogsTests DBtests resources/users.txt resources/users_hash resources/data_*.txt resources/del_*.txt
	rm -rf resources/upd_*.txt LAtests