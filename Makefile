CC = gcc
CCFLAGS = -g -O2 -Werror -Wall -Wextra -Wshadow

TARGET = example

.phony: all
all:
	@echo Compiling ...
	@$(CC) ./example.c ./src/csv.c -o $(TARGET) $(CCFLAGS) -I./src
	
.phony: clean
clean:
	@rm example
	
