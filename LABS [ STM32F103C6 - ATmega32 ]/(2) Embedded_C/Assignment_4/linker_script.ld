/*linker_script_cortexM4
ENG.TERA
*/

MEMORY
{
flash(RX) : ORIGIN = 0X00000000, LENGTH = 512M
sram(RWX) : ORIGIN = 0X20000000, LENGTH = 512M

}


SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		*(.rodata*)
		_E_text = . ;
	} > flash

	.data : {
		_S_DATA = . ;
		*(.data*)
		. = ALIGN(4) ;
		_E_DATA = . ;
	} > sram AT> flash

	.bss : {
		_S_bss = . ;
		*(.bss*)
		_E_bss = . ;
	} > sram
}