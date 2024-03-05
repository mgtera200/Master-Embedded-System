//ENG.TERA

#ifndef LIFO_H_
#define LIFO_H_
//type definitions
typedef struct {
	unsigned int count;
	unsigned int length;
	unsigned char* head;
	unsigned char* base;
}LIFO_BUF_t;
typedef enum {
LIFO_NO_ERROR,
LIFO_FULL,
LIFO_NOT_FULL,
LIFO_EMPTY,
LIFO_NOT_EMPTY,
LIFO_IS_NULL
}BUFF_STATUS;

//APIS
BUFF_STATUS LIFO_BUF_init(LIFO_BUF_t* pLIFO, unsigned int* pBUF, unsigned int length);
BUFF_STATUS Enqueue(LIFO_BUF_t* pLIFO, unsigned int item);
BUFF_STATUS Dequeue(LIFO_BUF_t* pLIFO, unsigned int* item);

#endif /* LIFO_H_ */
