CC=gcc -std=c++17
CFLAGS=-Wall -Werror -Wextra -lstdc++
SOURCES=s21_matrix_oop.cc
TEST_SOURSE = s21_matrix_oop_test.cc
LIBO=s21_matrix_oop.o
LIBA=s21_matrix_oop.a
OUT=tests.out

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs -lgtest -lgtest_main`
endif

all: s21_matrix_oop.a

rebuild: clean all

s21_matrix_oop.a: clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o ./$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) $(TEST_SOURSE) $(LIBA) $(LIBFLAGS) -o ./tests.out
	./tests.out

gcov_report: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) --coverage $(TEST_SOURSE) $(SOURCES) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o ./$(OUT)
	./$(OUT)
	lcov --ignore-errors mismatch -t  "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory ./report/
	open ./report/index.html

leaks:
	# CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt 	$(BUILD_PATH)$(OUT)
	leaks -atExit -- ./$(OUT) 

clang: 
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc *.h
	rm .clang-format

clean:
	@rm -rf s21_matrix \
	*.a \
	*.o \
	*.out \
	*.info \
	*.gcda \
	*.gcno \
	*.gcov \
	*.gch  \
	report
