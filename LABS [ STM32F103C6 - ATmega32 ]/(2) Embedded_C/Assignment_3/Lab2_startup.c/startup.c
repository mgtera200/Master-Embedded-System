#define STACK_Start_SP 0x20001000
extern int main();
void Reset_Handler();
void Default_Hanlder()
{
	Reset_Handler();
}
void NMI_Handler()__attribute__((weak, alias ("Default_Hanlder")));;
void H_fault_Handler()__attribute__((weak, alias ("Default_Hanlder")));;
void MM_Fault_Handler()__attribute__((weak, alias ("Default_Hanlder")));;
void Bus_fault_Handler()__attribute__((weak, alias ("Default_Hanlder")));;
void Usage_Fault_Handler()__attribute__((weak, alias ("Default_Hanlder")));;


unsigned int vectors[]__attribute__((section(".vectors"))) = {
STACK_Start_SP,
(unsigned int)&Reset_Handler,
(unsigned int)&NMI_Handler,
(unsigned int)&H_fault_Handler,
(unsigned int)&MM_Fault_Handler,
(unsigned int)&Bus_fault_Handler,
(unsigned int)&Usage_Fault_Handler,
};
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_BSS;
extern unsigned int _E_BSS;
extern unsigned int _E_TEXT;
void Reset_Handler()
{
	unsigned int DATA_Size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA; 
	unsigned char* P_src = (unsigned char*)&_E_TEXT;
	unsigned char* P_dst = (unsigned char*)&_S_DATA;
	for(int i=0; i<DATA_Size; i++)
	{
		*P_dst = *P_src;
		P_dst++;
		P_src++;
	}
	unsigned int bss_size = (unsigned char*)&_E_BSS - (unsigned char*)&_S_BSS;
	P_dst = (unsigned char*)&_S_BSS;
	for(int i=0; i<bss_size; i++)
	{
		*P_dst = 0;
		P_dst++;
	}
	main();
}