// ENG.TERA
#include "fifo.h"
#include "stdio.h"
#include "stdlib.h"
BUFF_STATUS FIFO_BUF_init(FIFO_BUF_t* pFIFO, unsigned char* pBUF, unsigned char length){
	if(pBUF == NULL){
		return FIFO_IS_NULL;
	}
	pFIFO->base = pBUF;
	pFIFO->head = pBUF;
	pFIFO->tail = pBUF;
	pFIFO->count = 0;
	pFIFO->length = length;
	printf("Initiation is done! \n");
	return FIFO_NO_ERROR;
}
BUFF_STATUS Enqueue(FIFO_BUF_t* pFIFO, unsigned char item){
	if(!pFIFO->base || !pFIFO->tail || !pFIFO->head){
		return FIFO_IS_NULL;
	}
	if(pFIFO->head == pFIFO->tail && pFIFO->tail != pFIFO->base){
		return FIFO_FULL;
	}
	if(pFIFO->count == pFIFO->length){
		if(pFIFO->tail == pFIFO->base){
			return FIFO_FULL;
		}
		else
			pFIFO->count = 0;
		pFIFO->head = pFIFO->base;
		*pFIFO->head = item;
		pFIFO->head++;
		pFIFO->count++;
		return FIFO_NO_ERROR;

	}
	else
		*pFIFO->head = item;
				pFIFO->head++;
				pFIFO->count++;
				return FIFO_NO_ERROR;

}
BUFF_STATUS Dequeue(FIFO_BUF_t* pFIFO, unsigned char* item){
	if(!pFIFO->base || !pFIFO->tail || !pFIFO->head){
			return FIFO_IS_NULL;
}
	if(pFIFO->count == 0 && pFIFO->tail == pFIFO->base){
		return FIFO_EMPTY;
	}
if(pFIFO->tail == pFIFO->base + (4 * sizeof(unsigned char))){
	*item = *pFIFO->tail;
	pFIFO->tail = pFIFO->base;
	return FIFO_NO_ERROR;
}
else{
	*item = *pFIFO->tail;
	pFIFO->tail++;
	return FIFO_NO_ERROR;
}

}
