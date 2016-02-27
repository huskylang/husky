all:
	mkdir -p bin
	g++ --std c++11 -g -Wall src/main/main.cpp \
							 src/main/argparser.cpp \
							 src/main/filehandler.cpp \
							 src/main/outputhandler.cpp \
							 src/parser/parser.cpp \
							 src/parser/variable.cpp \
							 src/parser/datatypes/string.cpp \
							 src/parser/file_modifier.cpp \
							 -o bin/husky

run:
	mkdir -p bin
	g++ --std c++11 -g -Wall src/main/main.cpp \
							 src/main/argparser.cpp \
							 src/main/filehandler.cpp \
							 src/main/outputhandler.cpp \
							 src/parser/parser.cpp \
							 src/parser/variable.cpp \
							 src/parser/datatypes/string.cpp \
							 src/parser/file_modifier.cpp \
							 src/parser/function_caller.cpp \
							 -o bin/husky
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./bin/husky examples/console.husky
	# valgrind ./bin/husky examples/vars.husky

clean:
	rm -rf bin
