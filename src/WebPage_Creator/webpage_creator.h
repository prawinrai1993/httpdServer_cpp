#ifndef WEBPAGE_CREATOR_H
#define WEBPAGE_CREATOR_H

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "database.h"
using namespace std;


#define DATABASE_PAGE "WebPages/database_page.html"
#define ADDUSER_PAGE "WebPages/add_employee.html"
#define DELETEUSER_PAGE "WebPages/delete_employee.html"
#define TEMP_PAGE "WebPages/temp_page.html"
#define CONTACTUS_PAGE "WebPages/contactus_page.html"
#define EMP_DATA_FILE "employee.dat"
#define TEMPLATE_DATABASE_PAGE "template_pages/template_homepage.html"

class WebPage_Creator{

	public:
		WebPage_Creator();
		~WebPage_Creator();
		void updateDatabasePage();
		void write_database_table(vector <employee> &data);
		char * getPage(const char* filename);

};

#endif /*webpage_creator.h*/

