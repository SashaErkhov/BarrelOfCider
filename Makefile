CC=clang++
CFLAGS=-pedantic-errors -gdwarf-4 -std=c++20
LDFLAGS=-lgtest -lgtest_main -lpthread

all: BUtests

load:
	sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && sudo cp lib/*.a /usr/lib && sudo ln -s /usr/lib/libgtest.a /usr/local/lib/libgtest.a && sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/libgtest_main.a

BUtests: tests/BUtests.cpp code/BankOfUsers.cpp code/sha256.cpp
	$(CC) tests/BUtests.cpp code/BankOfUsers.cpp code/sha256.cpp $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o BUtests resources/users.txt resources/users_hash