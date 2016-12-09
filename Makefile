CFLAGS=-Wall -O2 -std=c++11 -g -L/usr/lib/x86_64-linux-gnu/

SRCFOLDER=src
BINFOLDER=bin
TESTFLAG=-I $(SRCFOLDER)/
LINKS=-lboost_serialization

CPP_FILES = $(filter-out $(SRCFOLDER)/shell.cpp, $(wildcard $(SRCFOLDER)/*.cpp))
OBJ_FILES = $(addprefix $(BINFOLDER)/, $(notdir $(CPP_FILES:.cpp=.o)))

all: bin/shell


# Creates the executable
bin/shell: $(OBJ_FILES) src/shell.cpp
	g++ $(CFLAGS) $^ -o $@ $(LINKS)

# Compiling all classes into object files
bin/%.o: src/%.cpp
	@mkdir -p bin
	g++ $(CFLAGS) -c $< -o $@

# ---- Test ---------------------------
bin/blockTest: bin/block.o test/blockTest.cpp
	g++ $(CFLAGS) $(TESTFLAG) $^ -o $@

bin/memBlockTest: bin/memblockdevice.o test/memBlockTest.cpp bin/blockdevice.o bin/block.o
	g++ $(CFLAGS) $(TESTFLAG) $^ -o $@

clean:
	rm -rf bin
