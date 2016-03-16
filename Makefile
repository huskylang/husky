include src/main/main.mk
include src/parser/parser.mk
include src/parser/datatypes/datatypes.mk
include src/stdlib/stdlib.mk

include tests/tests.mk

MINIMAL_FILES = $(FILES) src/main/main.cpp

all:
	mkdir -p bin
	g++ --std c++11 -g $(MINIMAL_FILES) -o bin/husky

test:
	mkdir -p bin_dev
	touch /tmp/huskylang_test_asdfasdf_31221
	touch /tmp/huskylang_test_asdfasdf_31221_1
	touch /tmp/huskylang_test_asdfasdf_31221_2
	g++ --std c++11 -g $(TEST_FILES) -o bin_dev/test
	./bin_dev/test

install:
	sudo ln -s $(CURDIR)/bin/husky /usr/bin/husky

wall:
	mkdir -p bin
	g++ --std c++11 -g -Wall $(MINIMAL_FILES) -o bin/husky

valgr:
	mkdir -p bin
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./bin/husky examples/console.husky
	# valgrind ./bin/husky examples/vars.husky

clean:
	rm -rf bin bin_dev
