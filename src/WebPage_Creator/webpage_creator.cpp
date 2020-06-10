#include "webpage_creator.h"


WebPage_Creator::WebPage_Creator()
{



}


WebPage_Creator::~WebPage_Creator()
{



}


void updateDatabasePage()
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

void write_database_table(vector <employee> &data)
{

    FILE  *ptrFile = fopen( "temp.html", "w");

    fprintf(ptrFile, "\t<tr>\n");
    fprintf(ptrFile, "\t\t<th>NAME</th>\n");
    fprintf(ptrFile, "\t\t<th>TGID</th>\n");
    fprintf(ptrFile, "\t\t<th>CONTACT</th>\n");
    fprintf(ptrFile, "\t</tr>\n");

    for (size_t i = 0; i < data.size(); i++)
    {
        fprintf( ptrFile, "\t<tr>\n");
        fprintf( ptrFile, "\t\t<td>%s</td>\n", data.at(i).name);
        fprintf( ptrFile, "\t\t<td>%s</td>\n", data.at(i).tgid);
        fprintf( ptrFile, "\t\t<td>%s</td>\n", data.at(i).contact);
        fprintf( ptrFile, "\t</tr>\n");
    }

    fclose( ptrFile );

}

char * getPage(const char* filename)
{

    char * buffer = 0;
    long length;
    FILE * f = fopen (filename, "rb");
    static char error[50] = "<html><body>Error reading Page</body></html>";

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
        return error;
    }

}
