#include <stdlib.h>
#include <stdio.h>

/**
 * Local
 */
#include "../include/parser.h"
#include "log.h"

/*******************************
 * FUNCTION : myFileOpen
 * PURPOSE  : reads data, holds them in heap
 * IN       : char *fname
 * OUT      : pointer to myFile <-- Sucees
 *            NULL              <---fail
 */
__file myFileOpen(char *fileName){
	TRACE_IN
	FILE *fp;
	if ( ( fp = fopen(fileName, "r") ) == NULL ){
		FATAL("Cannot open file")
		TRACE_OUT
		return NULL;
	}
	__file f;
	if ( (f=malloc(sizeof(myFile) ) ) == NULL ){
		FATAL("Malloc failed")
		TRACE_OUT
		return NULL;
	}
	f->data = NULL;
	f->offset = 0;
	f->size = 0;
	char c;
	while(1){
		c = fgetc(fp);
		if( feof(fp) )break ;
		printf("%c", c);
	}
	TRACE_OUT
	return NULL;
}

/********************************
 * FUNCTION : myFileClose
 * INPUT    : File *
 * OUTPUT   : void
 * PURPOSE  : free buffers
 */
void myFileClose(__file *file){
	TRACE_IN
	TRACE_OUT
}

