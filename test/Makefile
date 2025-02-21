CC = g++
CFLAGS ?= -std=c++17 -pthread
INCLUDE ?= -I../src -I./third_party/googletest/googletest/include
LIBS ?= ../build/lib/norodb.a ./third_party/googletest/build/lib/libgtest.a


all: test_byte_buffer test_db_directory test_index
	@echo "\n>>>> ALL DONE! <<<<\n"

test_byte_buffer:
	@echo "\n>>>> TESTING BYTE BUFFER <<<<\n"
	$(CC) $(CFLAGS) $(INCLUDE) -c test_byte_buffer.cc
	$(CC) $(CFLAGS) -o test_byte_buffer test_byte_buffer.o $(LIBS)
	@./test_byte_buffer


test_db_directory:
	@echo "\n>>>> TESTING DB DIRECTORY <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_db_directory.cc
	@$(CC) $(CFLAGS) -o test_db_directory test_db_directory.o $(LIBS)
	@./test_db_directory

test_row:
	@echo "\n>>>> TESTING ROW <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_row.cc
	@$(CC) $(CFLAGS) -o test_row test_row.o $(LIBS)
	@./test_row

test_index:
	@echo "\n>>>> TESTING INDEX <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_index.cc
	@$(CC) $(CFLAGS) -o test_index test_index.o $(LIBS)
	@./test_index

test_tombstone_entry:
	@echo "\n>>>> TESTING TOMBSTONE ENTRY <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_tombstone_entry.cc
	@$(CC) $(CFLAGS) -o test_tombstone_entry test_tombstone_entry.o $(LIBS)
	@./test_tombstone_entry
