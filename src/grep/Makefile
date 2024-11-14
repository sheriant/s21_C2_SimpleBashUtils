# --------------------------------------------------------------------------Зависимости
.PHONY: s21_grep test_grep clean_grep rebuild_grep clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)

# --------------------------------------------------------------------------Реализация (Simple Bash Utils / grep)
# Сборка
s21_grep:
#	@$(CC) $(CFLAGS) *.c -o s21_grep
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃         grep is ready to work!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Тесты
test_grep:
#	-diff <(./s21_grep test_case_grep.txt) <(grep test_case_grep.txt)
#	-diff <(./s21_grep -e test_case_grep.txt) <(grep -e test_case_grep.txt)
#	-diff <(./s21_grep -t test_case_grep.txt) <(grep -t test_case_grep.txt)
#	-diff <(./s21_grep -s test_case_grep.txt) <(grep -s test_case_grep.txt)
#	-diff <(./s21_grep --squeeze-blank test_case_grep.txt) <(grep -s test_case_grep.txt)
#	-diff <(./s21_grep -n test_case_grep.txt) <(grep -n test_case_grep.txt)
#	-diff <(./s21_grep --number test_case_grep.txt) <(grep -n test_case_grep.txt)
#	-diff <(./s21_grep -b test_case_grep.txt) <(grep -b test_case_grep.txt)
#	-diff <(./s21_grep --number-nonblank test_case_grep.txt) <(grep -b test_case_grep.txt)
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             Тесты выполнены!            ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Удаление исполняемого файла
clean_grep:
#	@rm -rf s21_grep
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Пересборка исполняемого файла
rebuild_grep: clean_grep s21_grep

# --------------------------------------------------------------------------Полезные команды
# Форматирование кода
clang:
	@cp ../../materials/linters/.clang-format .clang-format
	@echo "Файл clang-format скопирован в папку grep."
	@clang-format -n *.c
	@echo "Проверка кода по Clang завершена."	
	@clang-format -i *.c
	@echo "Форматирование кода по Clang завершено."		
	@rm -f .clang-format
	@echo "Файл clang-format удален из папки grep."

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
	@leaks -atExit -- s21_grep

# Утечки valgrind
valgrind: rebuild_grep
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q ./s21_grep
	make clean_grep