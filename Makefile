include src/main/main.mk
include src/parser/parser.mk
include src/parser/datatypes/datatypes.mk
include src/stdlib/stdlib.mk

include tests/tests.mk

all:
	mkdir -p bin
	g++ --std c++11 -g $(FILES) -o bin/husky

test:
	mkdir -p bin
	mkdir -p tmp
	make
	g++ --std c++11 -g $(TEST_FILES) -o bin/test
	./bin/test

wall:
	mkdir -p bin
	g++ --std c++11 -g -Wall $(FILES) -o bin/husky

valgr:
	mkdir -p bin
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./bin/husky examples/console.husky
	# valgrind ./bin/husky examples/vars.husky

clean:
	rm -rf bin
