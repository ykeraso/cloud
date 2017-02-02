#ifndef __parser
#define __parser

#include "../../include/shared.h"

typedef struct _SmyFile{
	char *data;
	int size;
	ptr offset;
}myFile;

typedef myFile * __file;

/*******************************
 * FUNCTION : myFileOpen
 * PURPOSE  : reads data, holds them in heap
 * IN       : char *fname
 * OUT      : pointer to myFile <-- Sucees
 *            NULL              <---fail
 */
__file myFileOpen(char *fileName);

/********************************
 * FUNCTION : myFileClose
 * INPUT    : File *
 * OUTPUT   : void
 * PURPOSE  : free buffers
 */
void myFileClose(__file *);


#endif
