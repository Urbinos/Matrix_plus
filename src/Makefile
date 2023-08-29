CC = gcc -std=c11 -Wall -Werror -Wextra -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
    F_LIB_CHECK = -lcheck -pthread -lrt -lm
else
    F_LIB_CHECK = -lcheck 
endif

all: clean s21_matrix.a 

s21_matrix.a: clean
	$(CC) -c *.c
	ar rc libs21_matrix.a *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

test: s21_matrix.a
	$(CC) s21_matrix.a tests/s21_test_matrix.c  $(F_LIB_CHECK) -o s21_test -L. -ls21_matrix
	./s21_test
 
clang: test s21_matrix.a
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -n tests/*.c
	clang-format -i *.c *.h
	clang-format -i tests/*.c
	rm -fr .clang-format

gcov_report: clean s21_matrix.a
	$(CC) $(GCOVFLAGS) tests/*.c *.c $(F_LIB_CHECK) -o s21_test -L. -ls21_matrix
	./s21_test
	gcov tests/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda 
	open ./report/index.html


leaks: test
	CK_FORK=no leaks --atExit -- ./s21_test

valgrind:
	$(CC) s21_matrix.a tests/*.c  $(F_LIB_CHECK) -o s21_test -L. -ls21_matrix -ggdb
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_test
	
valgrind_full:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_test

clean:
	rm -rf *.o s21_test *.info *.a .clang-format *.dSYM *.out report *.txt *.gcda *.gcno run

test_val:
	$(CC) *.c tests/*.c -o run $(F_LIB_CHECK) -lgcov --coverage
	sh valgrind.sh ./run