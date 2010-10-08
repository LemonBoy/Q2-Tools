TOOL_PREFIX = arm-none-linux-gnueabi
CC = $(TOOL_PREFIX)-gcc
STRIP = $(TOOL_PREFIX)-strip

OUTPUT = neopop-q2

CORE = core
Z80 = z80
TLCS900 = TLCS-900h

NEOPOP_SRC = $(Z80)/Z80.c $(Z80)/dasm.c $(CORE)/Z80_interface.c \
          $(TLCS900)/TLCS900h_registers.c \
          $(TLCS900)/TLCS900h_interpret_src.c \
          $(TLCS900)/TLCS900h_interpret_single.c \
          $(TLCS900)/TLCS900h_interpret_reg.c \
          $(TLCS900)/TLCS900h_interpret_dst.c \
          $(TLCS900)/TLCS900h_interpret.c \
          $(TLCS900)/TLCS900h_disassemble_src.c \
          $(TLCS900)/TLCS900h_disassemble_reg.c \
          $(TLCS900)/TLCS900h_disassemble_extra.c \
          $(TLCS900)/TLCS900h_disassemble_dst.c \
          $(TLCS900)/TLCS900h_disassemble.c \
          $(CORE)/dma.c $(CORE)/bios.c $(CORE)/biosHLE.c $(CORE)/mem.c \
          $(CORE)/interrupt.c $(CORE)/gfx.c $(CORE)/sound.c \
          $(CORE)/gfx_scanline_colour.c $(CORE)/gfx_scanline_mono.c \
          $(CORE)/flash.c $(CORE)/rom.c $(CORE)/state.c $(CORE)/neopop.c
SRC = libQ2.c plat.c $(NEOPOP_SRC)

all:
	@echo "[COMPILE]"
	@$(CC) -I $(CORE) -I $(TLCS900) -I $(Z80) -Wall $(SRC) -o $(OUTPUT)
	@echo "[STRIP]"
	@$(STRIP) -s $(OUTPUT)
clean:
	@echo "[CLEAN]"
	@rm -f $(OUTPUT)
