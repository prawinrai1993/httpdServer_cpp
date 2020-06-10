#ifndef DATABASE_H
#define DATABASE_H

#include "string.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#define _file_path "../../employee.dat"

using namespace std;

typedef struct {
	char name[30];
	char tgid[30];
	char contact[30];
}employee;

class Database{

	private:
		vector<employee> _database_buffer;

	public: Database();
		~Database();

		void add_employee(employee data);
		void delete_employee(const char * data);
		void save_file();
		void read_database();
		vector <employee >& getDatabaseContent();
		void update_employee(const employee &data);
		bool get_empolyee_update(const char * find_data,employee &data);

};

#endif  /* database.h */
