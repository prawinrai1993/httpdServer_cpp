#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

class Tools{

	public:
		Tools();
		~Tools();
		static int OSCopyFile(const char* source, const char* destination);
		static void replaceAll(char *str, const char *oldWord, const char *newWord);


};


#endif    /* tools.h*/
