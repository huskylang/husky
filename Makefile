include src/main/main.mk
include src/parser/parser.mk
include src/parser/datatypes/datatypes.mk
include src/stdlib/stdlib.mk

all:
	mkdir -p bin
	g++ --std c++11 -g $(FILES) -o bin/husky

wall:
	g++ --std c++11 -g -Wall $(FILES) -o bin/husky

valgr:
	mkdir -p bin
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./bin/husky examples/console.husky
	# valgrind ./bin/husky examples/vars.husky

clean:
	rm -rf bin
