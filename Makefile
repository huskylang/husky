FILES := \
	src/main/main.cpp \
	src/main/argparser.cpp \
	src/main/filehandler.cpp \
	src/main/outputhandler.cpp \
	src/main/inputhandler.cpp \
	src/parser/parser.cpp \
	src/parser/variable.cpp \
	src/parser/datatypes/string.cpp \
	src/parser/file_modifier.cpp \
	src/parser/function_caller.cpp \
	src/parser/variable_utils.cpp

include stdlib/stdlib.conf

all:
	mkdir -p bin
	g++ --std c++11 -g $(FILES) -o bin/husky

wall:
	g++ --std c++11 -g -Wall $(FILES) -o bin/husky

valgr:
	mkdir -p bin
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./bin/husky examples/strings.husky
	# valgrind ./bin/husky examples/vars.husky

clean:
	rm -rf bin
