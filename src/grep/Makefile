# --------------------------------------------------------------------------Зависимости
.PHONY: s21_grep clean_grep rebuild_grep tests_grep clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
S21grep = ./s21_grep
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
	@echo "┃          grep is ready to work!          ┃"
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
tests_grep:
	@echo "Running tests for s21_grep..."

# Стандартный вывод
	@echo -n "Test command [grep] pattern [file_name]: "
	@-diff <($(S21grep) $(FILE)) <(grep $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -b флаг (нумерует непустые строки)
	@echo -n "Test -e flag: "
	@-diff <($(S21grep) -e $(FILE)) <(grep -e $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -e флаг (показывает непечатаемые символы, отображает $ в конце каждой строки)
	@echo -n "Test -i flag: "
	@-diff <($(S21grep) -i $(FILE)) <(grep -i $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -n флаг (нумерует все строки)
	@echo -n "Test -n flag: "
	@-diff <($(S21grep) -n $(FILE)) <(grep -n $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -s флаг (сжимает пустые строки)
	@echo -n "Test -s flag: "
	@-diff <($(S21grep) -s $(FILE)) <(grep -s $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -t флаг (Отображает табуляцию как ^I)
	@echo -n "Test -t flag: "
	@-diff <($(S21grep) -t $(FILE)) <(grep -t $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number флаг (эквивалент -n)
	@echo -n "Test --number flag: "
	@-diff <($(S21grep) --number $(FILE)) <(grep -n $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --squeeze-blank флаг (эквивалент to -s)
	@echo -n "Test --squeeze-blank flag: "
	@-diff <($(S21grep) --squeeze-blank $(FILE)) <(grep -s $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number-nonblank флаг (эквивалент to -b)
	@echo -n "Test --number-nonblank flag: "
	@-diff <($(S21grep) --number-nonblank $(FILE)) <(grep -b $(FILE)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Cppcheck + valgrind
	@echo -n "Test Cppcheck: "
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=201709L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer main.c main.h \
	> /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (empty): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21grep) > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with flag -e): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21grep) -b test_case_grep.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with non-existent flag): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21grep) -o test_case_grep.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"


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
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21grep)