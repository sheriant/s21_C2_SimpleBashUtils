# --------------------------------------------------------------------------Зависимости
.PHONY: s21_grep clean_grep rebuild_grep tests_grep clang config push cpp leaks valgrind

# --------------------------------------------------------------------------Переменные
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L
LIBS = -lm -lncurses
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
S21GREP = ./s21_grep
FILE = test_ptrn_grep.txt

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
	@echo "Running tests for s21_grep with $(FILE)..."
	@echo "=========================================="

# Базовые тесты с разными паттернами
	@echo -n "Test basic grep (pattern 'test'): "
	@-diff <($(S21GREP) "test" $(FILE)) <(grep "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test basic grep (pattern 'clean'): "
	@-diff <($(S21GREP) "clean" $(FILE)) <(grep "clean" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test basic grep (pattern 'CLEAN'): "
	@-diff <($(S21GREP) "CLEAN" $(FILE)) <(grep "CLEAN" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -i (игнорирование регистра)
	@echo -n "Test -i flag (case insensitive): "
	@-diff <($(S21GREP) -i "clean" $(FILE)) <(grep -i "clean" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -v (инвертирование поиска)
	@echo -n "Test -v flag (invert match): "
	@-diff <($(S21GREP) -v "test" $(FILE)) <(grep -v "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -c (количество совпадений)
	@echo -n "Test -c flag (count matches): "
	@-diff <($(S21GREP) -c "test" $(FILE)) <(grep -c "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -l (имена файлов)
	@echo -n "Test -l flag (file names only): "
	@-diff <($(S21GREP) -l "test" $(FILE)) <(grep -l "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -n (номера строк)
	@echo -n "Test -n flag (line numbers): "
	@-diff <($(S21GREP) -n "test" $(FILE)) <(grep -n "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -h (без имен файлов)
	@echo -n "Test -h flag (no file names): "
	@-diff <($(S21GREP) -h "test" $(FILE)) <(grep -h "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -s (подавление ошибок)
	@echo -n "Test -s flag (suppress errors): "
	@-diff <($(S21GREP) -s "test" nonexistent_file.txt $(FILE)) <(grep -s "test" nonexistent_file.txt $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -o (только совпадения)
	@echo -n "Test -o flag (only matching parts): "
	@-diff <($(S21GREP) -o "clean" $(FILE)) <(grep -o "clean" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -e (явное указание паттерна)
	@echo -n "Test -e flag (explicit pattern): "
	@-diff <($(S21GREP) -e "test" $(FILE)) <(grep -e "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Флаг -f (паттерны из файла)
	@echo -n "Test -f flag (patterns from file): "
	@echo "test" > patterns.txt
	@-diff <($(S21GREP) -f patterns.txt $(FILE)) <(grep -f patterns.txt $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@rm -f patterns.txt

# Регулярные выражения (строка начинающаяся с #include)
	@echo -n "Test regex pattern (^#include): "
	@-diff <($(S21GREP) "^#include" $(FILE)) <(grep "^#include" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Комбинации флагов
	@echo -n "Test combined flags (-in): "
	@-diff <($(S21GREP) -in "clean" $(FILE)) <(grep -in "clean" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test combined flags (-cv): "
	@-diff <($(S21GREP) -cv "test" $(FILE)) <(grep -cv "test" $(FILE)) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Тесты с Valgrind (проверка утечек памяти)
	@echo "=========================================="
	@echo -n "Test Valgrind (basic pattern): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) "test" $(FILE) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test Valgrind (with flags -i -n): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) -i -n "clean" $(FILE) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test Valgrind (regex pattern): "
	@valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) "^#include" $(FILE) > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

# Статический анализ и стиль
	@echo "=========================================="
	@echo -n "Test Cppcheck: "
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=200809L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer s21_grep.c s21_grep.h \
	> /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"

	@echo -n "Test code style: "
	@clang-format -style=file:../../materials/linters/.clang-format -n --Werror *.[ch] > /dev/null 2>&1 && echo -e "$(GREEN)PASS$(NC)" || echo -e "$(RED)FAIL$(NC)"
	@echo "=========================================="
	@echo "All tests completed!"



# --------------------------------------------------------------------------Полезные команды
# Форматирование кода
clang:
	@echo "🔍 Format check..."
	@clang-format -style=file:../../materials/linters/.clang-format -n --Werror *.[ch] >/dev/null 2>&1 && \
		echo "✅ OK" || (echo "❌ Fixing..." && clang-format -style=file:../../materials/linters/.clang-format -i *.[ch] && echo "🎉 Done")

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
	@cppcheck --enable=all --std=c11 -D_POSIX_C_SOURCE=200809L \
	--suppress=missingIncludeSystem --suppress=checkersReport --suppress=constParameter --suppress=constParameterPointer s21_grep.c s21_grep.h
	@echo "Проверка CPP выполнена!"

# Утечки leaks
leaks:
	@leaks -atExit -- s21_grep

# Утечки valgrind
valgrind:
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -q $(S21GREP) -i test test_ptrn_grep.txt