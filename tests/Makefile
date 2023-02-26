CC = g++
CFLAGS = -g -Werror -Wpedantic -Wall -O3
STD = -std=c++2b

clean:
	rm -f genTest*
optional:
	echo "creating tests for optional"
	$(CC) $(STD) $(CFLAGS) optional_tests.cpp -o genTestOptional

tuple:
	echo "creating tests for tuple"
	$(CC) $(STD) $(CFLAGS) tuple_tests.cpp -o genTestTuple

vector:
	echo "creating tests for vector"
	$(CC) $(STD) $(CFLAGS) vector_tests.cpp -o genTestVector

array:
	echo "creating tests for array"
	$(CC) $(STD) $(CFLAGS) array_tests.cpp -o genTestArray
