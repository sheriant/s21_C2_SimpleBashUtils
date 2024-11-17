# --------------------------------------------------------------------------Зависимости
.PHONY: s21_grep clean_grep rebuild_grep tests_grep clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
S21GREP = ./s21_grep
FILE = test_case_grep.txt

# Цвета
GREEN = \033[0;32m
RED= \033[0;31m
NC = \033[0m



# --------------------------------------------------------------------------Реализация (Simple Bash Utils / grep)
# Сборка
s21_grep:
	@$(CC) $(CFLAGS) *.c -o s21_grep
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          grep is ready to work!         ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Удаление исполняемого файла
clean_grep:
	@rm -rf s21_grep
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Пересборка исполняемого файла
rebuild_grep: clean_grep s21_grep



# --------------------------------------------------------------------------Тесты 
tests_grep: rebuild_grep
	@echo "Running tests for s21_grep..."

# Стандартный вывод
	@echo -n "Test basic grep command: "
	@-diff <($(S21GREP) $(FILE)) <(grep $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -b флаг (нумерует непустые строки)
	@echo -n "Test -b flag: "
	@-diff <($(S21GREP) -b $(FILE)) <(grep -b $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -e флаг (показывает непечатаемые символы, отображает $ в конце каждой строки)
	@echo -n "Test -e flag: "
	@-diff <($(S21GREP) -e $(FILE)) <(grep -e $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -n флаг (нумерует все строки)
	@echo -n "Test -n flag: "
	@-diff <($(S21GREP) -n $(FILE)) <(grep -n $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -s флаг (сжимает пустые строки)
	@echo -n "Test -s flag: "
	@-diff <($(S21GREP) -s $(FILE)) <(grep -s $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -t флаг (Отображает табуляцию как ^I)
	@echo -n "Test -t flag: "
	@-diff <($(S21GREP) -t $(FILE)) <(grep -t $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number флаг (эквивалент -n)
	@echo -n "Test --number flag: "
	@-diff <($(S21GREP) --number $(FILE)) <(grep -n $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --squeeze-blank флаг (эквивалент to -s)
	@echo -n "Test --squeeze-blank flag: "
	@-diff <($(S21GREP) --squeeze-blank $(FILE)) <(grep -s $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number-nonblank флаг (эквивалент to -b)
	@echo -n "Test --number-nonblank flag: "
	@-diff <($(S21GREP) --number-nonblank $(FILE)) <(grep -b $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -etsnb флаг (Все флаги)
	@echo -n "Test all flags: "
	@-diff <($(S21GREP) -etsnb $(FILE)) <(grep -etsnb $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Cppcheck + valgrind + style test
	@echo -n "Test Cppcheck: "
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=201709L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer main.c main.h \
	> /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	
	@echo -n "Test Valgrind (empty): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with flag -e): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) -b test_case_grep.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with non-existent flag): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) -o test_case_grep.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test style: "
	@cp ../../materials/linters/.clang-format .clang-format
	@clang-format --Werror -n *.c > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@rm -f .clang-format



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
	@echo "Файл .clang-format удален из папки grep."

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
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=201709L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer main.c main.h
	@echo "Проверка CPP выполнена!"

# Утечки leaks
leaks:
	@leaks -atExit -- s21_grep

# Утечки valgrind
valgrind:
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP)