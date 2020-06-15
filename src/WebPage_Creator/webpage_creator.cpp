/*
 * WebPageCreator.cpp
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#include "webpage_creator.h"


WebPage_Creator::WebPage_Creator()
{



}


WebPage_Creator::~WebPage_Creator()
{



}


void WebPage_Creator::updateDatabasePage()
{
	/* File pointer to hold reference of input file */
	FILE * fPtr;
	FILE * fTemp;
	char path[100] = TEMP_PAGE;
	char buffer[2048];
	char oldWord[20] = "replace_part";


	char * newWord = 0;
	long length;
	FILE * f = fopen ("temp.html", "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		newWord = (char *)malloc (length);
		if (newWord)
		{
			fread (newWord, 1, length, f);
		}
		fclose (f);
	}

	if (newWord == 0)
	{
		return;
	}


	/*  Open all required files */
	fPtr  = fopen(TEMP_PAGE, "r");
	fTemp = fopen(DATABASE_PAGE, "w");

	/* fopen() return NULL if unable to open file in given mode. */
	if (fPtr == NULL || fTemp == NULL)
	{
		/* Unable to open file hence exit */
		printf("\nUnable to open file.\n");
		printf("Please check whether file exists and you have read/write privilege.\n");
		exit(EXIT_SUCCESS);
	}


	/*
	 * Read line from source file and write to destination
	 * file after replacing given word.
	 */
	while ((fgets(buffer, 2048, fPtr)) != NULL)
	{
		// Replace all occurrence of word from current line
		Tools::replaceAll(buffer, oldWord, newWord);

		// After replacing write it to temp file.
		fputs(buffer, fTemp);
	}


	/* Close all files to release resource */
	fclose(fPtr);
	fclose(fTemp);


	/* Delete original source file */
	remove(path);

}

void WebPage_Creator::write_database_table(std::map <std::string,employee> &data)
{

	FILE  *ptrFile = fopen( "temp.html", "w");

	fprintf(ptrFile, "\t<tr>\n");
	fprintf(ptrFile, "\t\t<th>NAME</th>\n");
	fprintf(ptrFile, "\t\t<th>TGID</th>\n");
	fprintf(ptrFile, "\t\t<th>CONTACT</th>\n");
	fprintf(ptrFile, "\t</tr>\n");

	if(data.empty())
	{
		fclose( ptrFile );
		return;
	}
	for(std::map<std::string, employee>::iterator it = data.begin(); it != data.end(); it++) {
		fprintf( ptrFile, "\t<tr>\n");
		fprintf( ptrFile, "\t\t<td>%s</td>\n", it->second.name);
		fprintf( ptrFile, "\t\t<td>%s</td>\n", it->second.tgid);
		fprintf( ptrFile, "\t\t<td>%s</td>\n", it->second.contact);
		fprintf( ptrFile, "\t</tr>\n");
	}

	fclose( ptrFile );

}

char * WebPage_Creator::getPage(const char* filename)
{

	char * buffer = 0;
	char * error = 0;
	long length;
	FILE * f = fopen (filename, "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = (char*)malloc (length);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}

	if (buffer)
	{
		return buffer;
	}
	else
	{
		error = (char*)malloc (strlen(error_page) + 1);	// to avoid returning constant string
		strcpy(error,error_page);
		return error;
	}

}
