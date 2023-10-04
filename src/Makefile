OS := $(shell uname -s)
SRC = s21_structs.c
TEST = s21_testest.c
CC = gcc -std=c11

CFLAGS	= -Wall -Wextra -Werror
FLAGS_PLATFORM = -lcheck

GCOVFLAGS = -fprofile-arcs -ftest-coverage
REPORT = GcovReport

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM = -lcheck
else
	FLAGS_PLATFORM = -lcheck -lsubunit -lrt -lm -lpthread -g
endif

all: install

dvi:
	open dvi.txt

gcov_report:
	gcc $(GCOVFLAGS) $(TEST) $(SRC) $(FLAGS_PLATFORM) -o $(REPORT)
	chmod +x *
	./GcovReport
	lcov -t "$(REPORT)" -o $(REPORT).info -c -d .
	genhtml -o report $(REPORT).info
	rm -rf ./*.gcno ./*.gcda ./$(REPORT).*
	open ./report/index.html
	rm $(REPORT)
	rm -rf *.dSYM

install:
	make clean
	mkdir build
	cd qt && qmake && make && make clean && rm Makefile && cd ../ && mv qt/opengl.app build/

uninstall:	
	@rm -rf build

dist:
	cd .. && tar -czf Viewer_v1.0.tgz src

test:
	@$(CC) $(CFLAGS) $(TEST) $(SRC) $(FLAGS_PLATFORM) -g -o tests.out
	@./tests.out

check_i:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	cp ../materials/linters/.clang-format qt/.clang-format
	clang-format -i qt/*.cpp qt/*.h
	rm .clang-format
	rm qt/.clang-format

check_n:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	cp ../materials/linters/.clang-format qt/.clang-format
	clang-format -n qt/*.cpp qt/*.h
	rm .clang-format
	rm qt/.clang-format

leaks:
	make test
	CK_FORK=no leaks --atExit -- ./tests.out
	make clean

leaks_lin:
	make test
	CK_FORK=no valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full ./tests.out

clean:
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_Viewer_v1.0
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test
	@rm -rf .clang-format
	@rm -rf tests.out
	@rm -rf s21_test