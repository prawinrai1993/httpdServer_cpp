/*
 * Database.h
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "string.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include "tools.h"

#define _file_path "employee.dat"


typedef struct {
	char name[30];
	char tgid[30];
	char contact[30];
}employee;

class Database{

	private:
		std::map<std::string,employee> _database_buffer;


	public: Database();
		virtual ~Database();
		void add_employee(std::string key_value,employee data);
		void delete_employee(std::string data);
		void save_file();
		void read_database();
	    std::map <std::string ,employee >& getDatabaseContent();
		void update_employee(const employee &data);
		bool get_empolyee_update(std::string find_data,employee &data);

};


#endif /* DATABASE_H_ */
