/*
 * WebPageCreator.h
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#ifndef WEBPAGECREATOR_H_
#define WEBPAGECREATOR_H_

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "database.h"


#define DATABASE_PAGE "WebPages/database_page.html"
#define ADDUSER_PAGE "WebPages/add_employee.html"
#define ASKUSER_PAGE "WebPages/ask_employee.html"
#define UPDATEUSER_PAGE "WebPages/update_employee.html"
#define DELETEUSER_PAGE "WebPages/delete_employee.html"
#define TEMP_PAGE "WebPages/temp_page.html"
#define CONTACTUS_PAGE "WebPages/contactus_page.html"
#define EMP_DATA_FILE "employee.dat"
#define TEMPLATE_DATABASE_PAGE "template_pages/template_homepage.html"
#define error_page  "<html><body><h1>page not found!!!<h1></body></html>"

class WebPage_Creator{

	public:
		WebPage_Creator();
		virtual ~WebPage_Creator();
		void updateDatabasePage();
		void write_database_table(std::map <std::string,employee> &data);
		char * getPage(const char* filename);

};


#endif /* WEBPAGECREATOR_H_ */
