CC = g++
CFLAGS := -std=c++17 -Wall -Werror -Wextra
GTEST_LIB := /usr/local/lib
GTEST_INCLUDE := /usr/local/include

all: test


test: clean test_stack test_queue test_array test_vector test_list test_tree_map_set_multiset

test_stack:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/stack_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_stack && ./test_stack

test_queue:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/queue_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_queue && ./test_queue

test_array:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/array_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_array && ./test_array

test_vector:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/vector_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_vector && ./test_vector
	
test_list:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/list_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_list && ./test_list

test_tree_map_set_multiset:
	@$(CC) $(CFLAGS) -I$(GTEST_INCLUDE) ./tests/tree_map_set_multiset_tests.cpp -L$(GTEST_LIB) -lgtest_main -lgtest -o test_tree_map_set_multiset && ./test_tree_map_set_multiset

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h containers/*.h containers/*/*.h containers/*/*.tpp tests/*.cpp
	@rm -f .clang-format

rebuild:
	make clean
	make test

clean:
	rm -rf test_stack test_queue test_array test_vector test_list test_tree_map_set_multiset


.PHONY: all test test_stack test_queue test_array test_vector test_list test_tree_map_set_multiset style rebuild clean
