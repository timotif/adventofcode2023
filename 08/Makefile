PART = 01

usage:
	@echo "Usage: make <partNumber>"

1: PART = 00
1: compile

2: PART = 01
2: compile

compile:
	clang++ -Wall -Wextra -Werror -std=c++17 $(PART)_main.cpp -o $(PART)
	@./$(PART)