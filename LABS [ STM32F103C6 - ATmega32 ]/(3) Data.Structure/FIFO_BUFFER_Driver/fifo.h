//ENG.TERA

#ifndef FIFO_H_
#define FIFO_H_
//type definitions
typedef struct {
	unsigned char count;
	unsigned char length;
	unsigned char* head;
	unsigned char* base;
	unsigned char* tail;
}FIFO_BUF_t;
typedef enum {
FIFO_NO_ERROR,
FIFO_FULL,
FIFO_NOT_FULL,
FIFO_EMPTY,
FIFO_NOT_EMPTY,
FIFO_IS_NULL
}BUFF_STATUS;

//APIS
BUFF_STATUS FIFO_BUF_init(FIFO_BUF_t* pFIFO, unsigned char* pBUF, unsigned char length);
BUFF_STATUS Enqueue(FIFO_BUF_t* pFIFO, unsigned char item);
BUFF_STATUS Dequeue(FIFO_BUF_t* pFIFO, unsigned char* item);

#endif /* FIFO_H_ */
