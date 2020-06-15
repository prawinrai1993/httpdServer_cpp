/*
 * Tools.h
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string>

class Tools{

	public:
		Tools();
		virtual ~Tools();
		static int OSCopyFile(const char* source, const char* destination);
		static void replaceAll(char *str, const char *oldWord, const char *newWord);
		static std::string convertToString(const char* a, int size);


};

#endif /* TOOLS_H_ */
