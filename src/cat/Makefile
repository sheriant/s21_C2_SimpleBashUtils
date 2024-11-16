# --------------------------------------------------------------------------Зависимости
.PHONY: s21_cat clean_cat rebuild_cat tests_cat clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
S21CAT = ./s21_cat
FILE = test_case_cat.txt

# Цвета
GREEN = \033[0;32m
RED= \033[0;31m
NC = \033[0m



# --------------------------------------------------------------------------Реализация (Simple Bash Utils / cat)
# Сборка
s21_cat:
	@$(CC) $(CFLAGS) *.c -o s21_cat
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          cat is ready to work!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Удаление исполняемого файла
clean_cat:
	@rm -rf s21_cat
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Пересборка исполняемого файла
rebuild_cat: clean_cat s21_cat



# --------------------------------------------------------------------------Тесты 
tests_cat: rebuild_cat
	@echo "Running tests for s21_cat..."

# Стандартный вывод
	@echo -n "Test basic cat command: "
	@-diff <($(S21CAT) $(FILE)) <(cat $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -b флаг (нумерует непустые строки)
	@echo -n "Test -b flag: "
	@-diff <($(S21CAT) -b $(FILE)) <(cat -b $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -e флаг (показывает непечатаемые символы, отображает $ в конце каждой строки)
	@echo -n "Test -e flag: "
	@-diff <($(S21CAT) -e $(FILE)) <(cat -e $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -n флаг (нумерует все строки)
	@echo -n "Test -n flag: "
	@-diff <($(S21CAT) -n $(FILE)) <(cat -n $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -s флаг (сжимает пустые строки)
	@echo -n "Test -s flag: "
	@-diff <($(S21CAT) -s $(FILE)) <(cat -s $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -t флаг (Отображает табуляцию как ^I)
	@echo -n "Test -t flag: "
	@-diff <($(S21CAT) -t $(FILE)) <(cat -t $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number флаг (эквивалент -n)
	@echo -n "Test --number flag: "
	@-diff <($(S21CAT) --number $(FILE)) <(cat -n $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --squeeze-blank флаг (эквивалент to -s)
	@echo -n "Test --squeeze-blank flag: "
	@-diff <($(S21CAT) --squeeze-blank $(FILE)) <(cat -s $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number-nonblank флаг (эквивалент to -b)
	@echo -n "Test --number-nonblank flag: "
	@-diff <($(S21CAT) --number-nonblank $(FILE)) <(cat -b $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -etsnb флаг (Все флаги)
	@echo -n "Test all flags: "
	@-diff <($(S21CAT) -etsnb $(FILE)) <(cat -etsnb $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Cppcheck + valgrind + style test
	@echo -n "Test Cppcheck: "
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=201709L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer main.c main.h \
	> /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	
	@echo -n "Test Valgrind (empty): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT) > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with flag -e): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT) -b test_case_cat.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind (with non-existent flag): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT) -o test_case_cat.txt > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test style: "
	@cp ../../materials/linters/.clang-format .clang-format
	@clang-format --Werror -n *.c > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@rm -f .clang-format



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
	@echo "Файл .clang-format удален из папки cat."

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
	@leaks -atExit -- s21_cat

# Утечки valgrind
valgrind:
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT)