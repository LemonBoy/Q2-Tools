TOOL_PREFIX = arm-none-linux-gnueabi
CC = $(TOOL_PREFIX)-gcc
AR = $(TOOL_PREFIX)-ar

OUTPUT = libQ2
SRC = libQ2.c

all:
	@echo "[CC]"
	@$(CC) -Wall -c $(SRC) -o $(OUTPUT)
	@echo "[AR]"
	@$(AR) rcsv libQ2.a $(OUTPUT)
clean:
	@echo "[CLEAN]"
	@rm -f $(OUTPUT)
