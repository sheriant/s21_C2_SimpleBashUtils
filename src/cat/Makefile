# --------------------------------------------------------------------------Зависимости
.PHONY: s21_cat clean_cat rebuild_cat tests_cat clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
S21CAT = ./s21_cat
TEST = test_case_cat.txt

# Цвета
GREEN = \033[0;32m
RED= \033[0;31m
NC = \033[0m



# --------------------------------------------------------------------------Реализация (Simple Bash Utils / cat)
# Сборка
s21_cat:
	@$(CC) $(CFLAGS) *.c -o s21_cat
	@echo -n "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo -n "┃          cat is ready to work!          ┃"
	@echo -n "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Удаление исполняемого файла
clean_cat:
	@rm -rf s21_cat
	@echo -n "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo -n "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo -n "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Пересборка исполняемого файла
rebuild_cat: clean_cat s21_cat



# --------------------------------------------------------------------------Тесты 
tests_cat:
	@echo "Running tests for s21_cat..."

# Стандартный вывод
	@echo -n "Test basic cat command: "
	@-diff <($(S21CAT) $(TEST)) <(cat $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -b флаг (нумерует непустые строки)
	@echo -n "Test -b flag: "
	@-diff <($(S21CAT) -b $(TEST)) <(cat -b $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -e флаг (показывает непечатаемые символы, отображает $ в конце каждой строки)
	@echo -n "Test -e flag: "
	@-diff <($(S21CAT) -e $(TEST)) <(cat -e $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -n флаг (нумерует все строки)
	@echo -n "Test -n flag: "
	@-diff <($(S21CAT) -n $(TEST)) <(cat -n $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -s флаг (сжимает пустые строки)
	@echo -n "Test -s flag: "
	@-diff <($(S21CAT) -s $(TEST)) <(cat -s $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# -t флаг (Отображает табуляцию как ^I)
	@echo -n "Test -t flag: "
	@-diff <($(S21CAT) -t $(TEST)) <(cat -t $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number флаг (эквивалент -n)
	@echo -n "Test --number flag: "
	@-diff <($(S21CAT) --number $(TEST)) <(cat -n $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --squeeze-blank флаг (эквивалент to -s)
	@echo -n "Test --squeeze-blank flag: "
	@-diff <($(S21CAT) --squeeze-blank $(TEST)) <(cat -s $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# --number-nonblank флаг (эквивалент to -b)
	@echo -n "Test --number-nonblank flag: "
	@-diff <($(S21CAT) --number-nonblank $(TEST)) <(cat -b $(TEST)) && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Cppcheck + valgrind
	@echo -n "Test Cppcheck: "
	@cppcheck $(S21CAT) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo -n "Test Valgrind: "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT) > /dev/null 2>&1 \
	&& echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"



# --------------------------------------------------------------------------Полезные команды
# Форматирование кода
clang:
	@cp ../../materials/linters/.clang-format .clang-format
	@echo -n "Файл clang-format скопирован в папку cat."
	@clang-format -n *.c
	@echo -n "Проверка кода по Clang завершена."	
	@clang-format -i *.c
	@echo -n "Форматирование кода по Clang завершено."		
	@rm -f .clang-format
	@echo -n "Файл .clang-format удален из папки cat."

# Конфиг пользователя
config:
	@git config --global user.name "Sheriant"
	@git config --global user.email "shariant@student.21-school.ru"
	@echo -n "Привет Sheriant! Рад видеть тебя снова!"

# git add, commit и push
push:
	@read -p "Введите сообщение коммита: " commit_msg; \
	cd ../..; \
	git add .; \
	git commit -m "$$commit_msg"; \
	git push origin develop
	@echo -n "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo -n "┃         Bomb has been planted!          ┃"
	@echo -n "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"



# --------------------------------------------------------------------------Проверки памяти
# CPP-check
cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(S21CAT)
	@echo -n "Проверка CPP выполнена!"

# Утечки leaks
leaks:
	@leaks -atExit -- s21_cat

# Утечки valgrind
valgrind:
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21CAT)