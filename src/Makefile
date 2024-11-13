# --------------------------------------------------------------------------Зависимости
.PHONY: all rebuild build run clean clang config push cpp leaks valgrind s21_cat s21_grep

# --------------------------------------------------------------------------Переменные (общие)
SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
BUILD_DIR = ../build
LIBS = -lm -lncurses
C_FILES := $(wildcard *.c)
H_FILES := $(wildcard *.h)
GIT_COMMIT := $(shell git log -1 --pretty=format:%h)
OUTPUT_BUILD = $(BUILD_DIR)/build

# --------------------------------------------------------------------------Переменные (Simple Bash Utils)
CAT_DIR = cat
OUTPUT_CAT = $(CAT_DIR)/s21_cat
GREP_DIR = grep
OUTPUT_GREP = $(GREP_DIR)/s21_grep



# --------------------------------------------------------------------------Реализация (Simple Bash Utils)
# Сборка cat
s21_cat:
	@$(CC) $(CFLAGS) $(CAT_DIR)/*.c -o $(OUTPUT_CAT)
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          cat is ready to work!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# Сборка grep
s21_grep:
	@$(GREP_DIR) $(CC) $(CFLAGS) *.c -o $(OUTPUT_GREP)
	@echo "\033[0;32m"
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃         grep is ready to work!          ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "\033[0m"

# Тесты cat
test_cat:
	-diff <(cat/s21_cat cat/test.txt) <(cat cat/test.txt)
	-diff <(cat/s21_cat -e cat/test.txt) <(cat -e cat/test.txt)
	-diff <(cat/s21_cat -t cat/test.txt) <(cat -t cat/test.txt)
	-diff <(cat/s21_cat -s cat/test.txt) <(cat -s cat/test.txt)
	-diff <(cat/s21_cat --squeeze-blank cat/test.txt) <(cat -s cat/test.txt)
	-diff <(cat/s21_cat -n cat/test.txt) <(cat -n cat/test.txt)
	-diff <(cat/s21_cat --number cat/test.txt) <(cat -n cat/test.txt)
	-diff <(cat/s21_cat -b cat/test.txt) <(cat -b cat/test.txt)
	-diff <(cat/s21_cat --number-nonblank cat/test.txt) <(cat -b cat/test.txt)
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             Тесты выполнены!            ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

clean_cat:
	@rm -rf $(OUTPUT_CAT) \
			$(shell find .. -name '*.o' -or -name '*.a' -or -name '*.so')
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"

# --------------------------------------------------------------------------Компиляция и запуск программы
# Сборка билда и запуск
all: build run

# Пересборка
rebuild: clean build run

# Компиляция
build: 
	@$(CC) $(CFLAGS) *.c -o $(OUTPUT_BUILD)
	@echo "\033[0;32m"
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃           ПРОГРАММА СОБРАНА!            ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "\033[0m"

# Запуск

run:
	@echo "\033[0;32m"
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          ПРОГРАММА ЗАПУЩЕНА!            ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "\033[0m"
	@$(OUTPUT_BUILD)

# Очистка
clean:
	@rm -rf $(BUILD_DIR)/* \
			$(shell find .. -name '*.o' -or -name '*.a' -or -name '*.so')
	@echo "\033[0;31m"
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃             ДАННЫЕ УДАЛЕНЫ!             ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "\033[0m"



# --------------------------------------------------------------------------Полезные команды
# Форматирование кода
clang:
	@cp ../materials/linters/.clang-format .clang-format
	@echo "Файл clang-format скопирован в папку src."
#	@clang-format -n $(C_FILES) $(H_FILES)
#	@clang-format -i $(C_FILES) $(H_FILES)
	@clang-format -n **/*.c **/*.h
	@clang-format -i **/*.c **/*.h
	@echo "Проверка и форматирование кода завершено."
	@rm -f .clang-format
	@echo "Файл clang-format удален из папки src."

# Конфиг пользователя
config:
	@git config --global user.name "Sheriant"
	@git config --global user.email "shariant@student.21-school.ru"
	@echo "Привет Sheriant! Рад видеть тебя снова!"

# git add, commit и push
push:
	@read -p "Введите сообщение коммита: " commit_msg; \
	cd ..; \
	git add .; \
	git commit -m "$$commit_msg"; \
	git push origin develop
	@echo "\033[0;32m"
	@echo "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "┃          БАЦ-БАЦ-БАЦ И В ПРОД           ┃"
	@echo "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "\033[0m"



# --------------------------------------------------------------------------Проверки
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