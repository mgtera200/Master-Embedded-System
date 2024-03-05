// startup.c
//	TERA

#include <stdint.h>

extern int main(void);

void Reset_Handler();

void Default_HAndler()
{
	Reset_Handler();
}

void NMI_Handler(void)__attribute__((weak, alias ("Default_HAndler")));;
void H_fault_Handler(void)__attribute__((weak, alias ("Default_HAndler")));;

//booking 1024 Byte located by .bss thriugh uninitialized array of int 256 element (246 *4 =1024) 
static unsigned long Stack_top[256] ;

/*uint32_t vectors[] __attribute__((section(".vectors")))   = {
	(uint32_t) (&Stack_top[0] + sizeof(Stack_top)),
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_fault_Handler
	
};*/

void (* const g_p_Vectors[])() __attribute__((section(".vectors"))) = 
{
	(void(*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	 &Reset_Handler,
	 &NMI_Handler,
	 &H_fault_Handler
};

extern unsigned int _E_text ;
extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;
void Reset_Handler()
{
	int i ;
	// Copy data section from Flash to RAM
	unsigned int DATA_Size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_scr =(unsigned char*)&_E_text ;
	unsigned char* P_dst =(unsigned char*)&_S_DATA ;
	for( i = 0; i < DATA_Size; ++i)
	{
		*((unsigned char*)P_dst++) = *((unsigned char*)P_scr++);
	}

	// init .bss section in SRAM = 0
	unsigned int bss_Size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss ;
	 P_dst =(unsigned char*)&_S_bss ;
	for( i = 0; i < bss_Size; ++i)
	{
		*((unsigned char*)P_dst++) = 0 ;
	}
	// jump main()
	main();
}