/*
 * Database.cpp
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#include <iostream>
#include <stdio.h>
#include "database.h"

using namespace std;

Database::Database()
{


	_database_buffer.clear();


}

Database::~Database()
{

}


void Database::add_employee(std::string key_value,employee data)
{
	employee copy_data;
	strcpy(copy_data.contact,data.contact);
	strcpy(copy_data.tgid,data.tgid);
	strcpy(copy_data.name,data.name);
	_database_buffer.insert({key_value,copy_data});

}

void Database::delete_employee(std::string data)
{

	std::map<std::string, employee>::iterator it;

	it = _database_buffer.find(data);

	if(it == _database_buffer.end())
		 cout << "Key-value pair not present in map" ;
	else
	{
	     _database_buffer.erase(it->first);
	}



}

void Database::update_employee(const employee &data)
{
	std::map<std::string, employee>::iterator it;

	it = _database_buffer.find(Tools::convertToString(data.tgid,strlen(data.tgid)));

	if(it == _database_buffer.end())
		cout << "TGID not present in database" ;
	else
	{
		strcpy(it->second.contact,data.contact);
		strcpy(it->second.name,data.name);
		strcpy(it->second.tgid,data.tgid);
	}

}

bool Database::get_empolyee_update(std::string find_data,employee &data)
{
	std::map<std::string, employee>::iterator it;

	it = _database_buffer.find(find_data);

	if(it == _database_buffer.end())
	{
			cout << "TGID not present in database" ;
			return false;
	}
	else
	{
		strcpy(data.contact,it->second.contact);
		strcpy(data.name,it->second.name);
		strcpy(data.tgid,it->second.tgid);
		return true;
	}

	return false;


}
void Database::save_file()
{

	ofstream out(_file_path, ios::binary |std::ofstream::trunc);
	if (!out)
		return;


	for(std::map<std::string, employee>::iterator it = _database_buffer.begin(); it != _database_buffer.end(); it++) {
				//Write the size of the string.
				int size =strlen(it->first.c_str()) + 1;
				out.write(reinterpret_cast<char *>(&size), sizeof(int));
				// writing data
				out.write(it->first.c_str(), size);

				//Write the size of the string.
				size =strlen(it->second.tgid) + 1;
				out.write(reinterpret_cast<char*>(&size), sizeof(int));
				// writing data
				out.write(it->second.tgid, size);

				size =strlen(it->second.name) + 1;
				out.write(reinterpret_cast<char*>(&size), sizeof(int));
				// writing data
				out.write(it->second.name, size);


				size =strlen(it->second.contact) + 1;
				out.write(reinterpret_cast<char*>(&size), sizeof(int));
				// writing data
				out.write(it->second.contact, size);

	        }
	out.close();

}


void Database::read_database()
{

	_database_buffer.clear();						        // clear before reading data
	ifstream in(_file_path, ios::binary);
	if (!in | in.eof())
	{
		in.close();
		return;
	}

	while(!in.eof())
	{

		// Read in the size of the string.
		employee emp;
		std::string key_value = "";
		char temp_str[30];
		int size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(temp_str, size);
		key_value = Tools::convertToString(temp_str,strlen(temp_str));

		size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.tgid, size);

		size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.name, size);

		size = 0;
		in.read(reinterpret_cast<char*>(&size), sizeof(int));
		in.read(emp.contact, size);

		_database_buffer.insert({key_value,emp});
	}

	in.close();

}

std::map <std::string,employee > & Database::getDatabaseContent()
{

	return _database_buffer;

}
