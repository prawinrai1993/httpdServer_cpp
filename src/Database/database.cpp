#include <iostream>
#include <stdio.h>
#include "database.h"

using namespace std;

Database::Database()
{





}

Database::~Database()
{

}


void Database::add_employee(employee data)
{
	_database_buffer.push_back(data);

}


void Database::delete_employee(const char * data)
{
	for(size_t i=0;i < _database_buffer.size();i++)
	{
		if(strcmp(data,_database_buffer.at(i).tgid)== 0)
		{
			_database_buffer.erase(_database_buffer.begin() + i);     /* remove at i*/
			return;
		}

	}

	cout << "no data found....." << endl;

}

void Database::update_employee(const employee &data)
{

	for(size_t i=0;i < _database_buffer.size();i++)
	{
		if(strcmp(data.tgid,_database_buffer.at(i).tgid)== 0)
		{
			strcpy(_database_buffer.at(i).name,data.name);         /* copy at i*/
			strcpy(_database_buffer.at(i).contact,data.contact);   /* update contact*/
			cout << "data updated" << endl;
			return;
		}

	}

}

bool Database::get_empolyee_update(const char * find_data,employee &data)
{

	for(size_t i=0;i < _database_buffer.size();i++)
	{
		if(strcmp(find_data,_database_buffer.at(i).tgid)== 0)
		{
			data = _database_buffer[i];
			return true;
		}
	}

	return false;
}
void Database::save_file()
{

	ofstream out(_file_path, ios::binary);
	if (!out)
		return;

	for(size_t i = 0; i < _database_buffer.size() ; i++)
	{

		// Write the size of the string.
		int size =strlen(_database_buffer.at(i).tgid);
		out.write(reinterpret_cast<char*>(&size), sizeof(int));
		// writing data
		out.write(_database_buffer.at(i).tgid, size);

		size =strlen(_database_buffer.at(i).name);
		out.write(reinterpret_cast<char*>(&size), sizeof(int));
		// writing data
		out.write(_database_buffer.at(i).name, size);


		size =strlen(_database_buffer.at(i).contact);
		out.write(reinterpret_cast<char*>(&size), sizeof(int));
		// writing data
		out.write(_database_buffer.at(i).contact, size);

	}

}


void Database::read_database()
{

	_database_buffer.clear();						        // clear before reading data
	ifstream in(_file_path, ios::binary);
	if (!in)
		return;

	while(!in.eof())
	{

		// Read in the size of the string.
		employee emp;
		int size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.tgid, size);

		size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.name, size);

		size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.contact, size);

		_database_buffer.push_back(emp);
	}

}

vector <employee > & Database::getDatabaseContent()
{

	return _database_buffer;

}
