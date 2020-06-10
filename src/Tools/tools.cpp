#include "tools.h"

Tools::Tools()
{



}


Tools::~Tools()
{




}


int Tools::OSCopyFile(const char* source, const char* destination)
{
	int input, output;
	if ((input = open(source, O_RDONLY)) == -1)
	{
		return -1;
	}
	if ((output = creat(destination, 0660)) == -1)
	{
		close(input);
		return -1;
	}

	//Here we use kernel-space copying for performance reasons
	off_t bytesCopied = 0;
	struct stat fileinfo;
	fstat(input, &fileinfo);
	int result = sendfile(output, input, &bytesCopied, fileinfo.st_size);

	close(input);
	close(output);

	return result;

}
void Tools::replaceAll(char *str, const char *oldWord, const char *newWord)
{
	char *pos, temp[2048];
	int index = 0;
	int owlen;

	owlen = strlen(oldWord);
	/*
	 * Repeat till all occurrences are replaced.
	 */
	while ((pos = strstr(str, oldWord)) != NULL)
	{
		// Bakup current line
		strcpy(temp, str);

		// Index of current found word
		index = pos - str;

		// Terminate str after word found index
		str[index] = '\0';

		// Concatenate str with new word
		strcat(str, newWord);

		// Concatenate str with remaining words after
		// oldword found index.
		strcat(str, temp + index + owlen);
	}



}
