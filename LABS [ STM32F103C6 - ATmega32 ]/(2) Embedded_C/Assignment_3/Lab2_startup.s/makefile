#@copyrights : TERA
CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m3
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name=learn-in-depth

all: $(Project_name).bin
	@echo "Build is done"
%.o: %.c 
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
startup.o: startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@
$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file
$(Project_name).bin: $(Project_name).elf 
	$(CC)objcopy.exe -O binary $< $@
clean_all:
	rm *.o *.elf *.bin
clean:
	rm *.elf *.bin