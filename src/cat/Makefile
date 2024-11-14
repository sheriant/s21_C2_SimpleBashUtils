# --------------------------------------------------------------------------Зависимости
.PHONY: s21_cat test_cat clean_cat rebuild_cat clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)

# --------------------------------------------------------------------------Реализация (Simple Bash Utils)
# Сборка cat
s21_cat:
	@$(CC) $(CFLAGS) *.c -o s21_cat
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          cat is ready to work!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Тесты cat
test_cat:
	-diff <(./s21_cat test_case_cat.txt) <(cat test_case_cat.txt)
	-diff <(./s21_cat -e test_case_cat.txt) <(cat -e test_case_cat.txt)
	-diff <(./s21_cat -t test_case_cat.txt) <(cat -t test_case_cat.txt)
	-diff <(./s21_cat -s test_case_cat.txt) <(cat -s test_case_cat.txt)
	-diff <(./s21_cat --squeeze-blank test_case_cat.txt) <(cat -s test_case_cat.txt)
	-diff <(./s21_cat -n test_case_cat.txt) <(cat -n test_case_cat.txt)
	-diff <(./s21_cat --number test_case_cat.txt) <(cat -n test_case_cat.txt)
	-diff <(./s21_cat -b test_case_cat.txt) <(cat -b test_case_cat.txt)
	-diff <(./s21_cat --number-nonblank test_case_cat.txt) <(cat -b test_case_cat.txt)
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             Тесты выполнены!            ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

clean_cat:
	@rm -rf s21_cat
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

rebuild_cat: clean_cat s21_cat

# --------------------------------------------------------------------------Полезные команды
# Форматирование кода
clang:
	@cp ../../materials/linters/.clang-format .clang-format
	@echo "Файл clang-format скопирован в папку cat."
	@clang-format -n *.c
	@echo "Проверка кода по Clang завершена."	
	@clang-format -i *.c
	@echo "Форматирование кода по Clang завершено."		
	@rm -f .clang-format
	@echo "Файл clang-format удален из папки cat."

# Конфиг пользователя
config:
	@git config --global user.name "Sheriant"
	@git config --global user.email "shariant@student.21-school.ru"
	@echo "Привет Sheriant! Рад видеть тебя снова!"

# git add, commit и push
push:
	@read -p "Введите сообщение коммита: " commit_msg; \
	cd ../..; \
	git add .; \
	git commit -m "$$commit_msg"; \
	git push origin develop
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃         Bomb has been planted!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"



# --------------------------------------------------------------------------Проверки памяти
# CPP-check
cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c
	@echo "Проверка CPP выполнена!"

# Утечки leaks
leaks:
	@leaks -atExit -- $(OUTPUT_BUILD)

# Утечки valgrind
valgrind: rebuild
	valgrind --tool=memcheck --leak-check=yes -q $(OUTPUT_BUILD)
	make clean