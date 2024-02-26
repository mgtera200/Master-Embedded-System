MEMORY {
flash(RX) : ORIGIN = 0x08000000, LENGTH = 128k
SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {
	.text : {
		*(.vectors)
		*(.text)
		*(.rodata)
		_E_TEXT = .;
	}> flash
	.data : {
		_S_DATA = .;
		*(.data)
		_E_DATA = .;
	}> SRAM AT> flash
	.bss : {
		_S_BSS = .;
		*(.bss)
		_E_BSS = .;
	}> SRAM


}