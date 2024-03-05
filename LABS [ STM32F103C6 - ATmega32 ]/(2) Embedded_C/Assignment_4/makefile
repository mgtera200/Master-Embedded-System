#@copyrights : TERA
CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m4
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name=unit3_lab4_cortexM4

all: $(Project_name).bin
	@echo "Build is done"
%.o: %.c 
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file
	CP $(Project_name).elf $(Project_name).axf
$(Project_name).bin: $(Project_name).elf 
	$(CC)objcopy.exe -O binary $< $@
clean_all:
	rm *.o *.elf *.bin
clean:
	rm *.elf *.bin