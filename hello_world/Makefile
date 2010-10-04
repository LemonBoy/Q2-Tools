Q := @
TOOL_PREFIX = arm-none-linux-gnueabi
CC = $(TOOL_PREFIX)-gcc
STRIP = $(TOOL_PREFIX)-strip

OUTPUT = hello
SRC = hello.c

all:
	@echo "[COMPILE]"
	@$(CC) -Wall $(SRC) -o $(OUTPUT)
	@echo "[STRIP]"
	@$(STRIP) -s $(OUTPUT)
clean:
	@echo "[CLEAN]"
	@rm -f $(OUTPUT)
