//ENG.TERA
#include "lifo.h"
#include "stdio.h"
#include "stdlib.h"
BUFF_STATUS LIFO_BUF_init(LIFO_BUF_t* pLIFO, unsigned int* pBUF, unsigned int length){
	if(pLIFO == NULL)
		return LIFO_IS_NULL;
	pLIFO->base = pBUF;
	pLIFO->head = pBUF;
	pLIFO->count = 0;
	pLIFO->length = length;
	printf("Initiation is done\n");
	return LIFO_NO_ERROR;


}
BUFF_STATUS Enqueue(LIFO_BUF_t* pLIFO, unsigned int item){
if(!pLIFO->head || !pLIFO->base)
	return LIFO_IS_NULL;
if(pLIFO->count == pLIFO->length)
{
	return LIFO_FULL;
}
*(pLIFO->head) = item;
pLIFO->head++;
pLIFO->count++;
return LIFO_NO_ERROR;



}
BUFF_STATUS Dequeue(LIFO_BUF_t* pLIFO, unsigned int* item){
	if(!pLIFO->head || !pLIFO->base)
		return LIFO_IS_NULL;
if(pLIFO->count == 0){
 return LIFO_EMPTY;
}
pLIFO->head--;
pLIFO->count--;
*item = *(pLIFO->head);
return LIFO_NO_ERROR;

}

