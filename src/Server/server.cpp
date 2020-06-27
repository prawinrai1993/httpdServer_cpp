/*
 * Server.cpp
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#include "server.h"

Database Server::_database;
WebPage_Creator Server::_webpage_creator;
employee  Server::_temp_storage;

Server::Server()
{
	_daemon = NULL;

}

Server::~Server()
{
}

int Server::startServer()
{
	/* start demon method*/
	_daemon = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
			Server::answer_to_connection, NULL,
			MHD_OPTION_NOTIFY_COMPLETED, &Server::request_completed,
			NULL, MHD_OPTION_END);
			
	ignore_sigpipe();


	if (NULL == _daemon)	/* returns null on failure of demon creation*/
		return 0;


	printf("%s", "server started....\n");
	return 1;

}


void Server::stopServer()
{

	/* stop demon method*/
	MHD_stop_daemon (_daemon);
	printf("server stopped......\n");

}

void Server::ignore_sigpipe ()
{
  struct sigaction oldsig;
  struct sigaction sig;

  sig.sa_handler = &catcher;
  sigemptyset (&sig.sa_mask);
#ifdef SA_INTERRUPT
  sig.sa_flags = SA_INTERRUPT;  /* SunOS */
#else
  sig.sa_flags = SA_RESTART;
#endif
  if (0 != sigaction (SIGPIPE, &sig, &oldsig))
    fprintf (stderr,
             "Failed to install SIGPIPE handler: %s\n", strerror (errno));
}

void Server::catcher (int sig)
{
  (void) sig;  /* Unused. Silent compiler warning. */
  /* do nothing */
}

int Server::send_page (struct MHD_Connection *connection, const char *page)
{
	int ret;
	struct MHD_Response *response;


	response =
			MHD_create_response_from_buffer (strlen (page), (void *) page,
					MHD_RESPMEM_PERSISTENT);
	if (!response)
		return MHD_NO;

	ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);

	return ret;
}


int Server::iterate_post (void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
		const char *filename, const char *content_type,
		const char *transfer_encoding, const char *data, uint64_t off,
		size_t size)
{
	struct connection_info_struct *con_info = reinterpret_cast <connection_info_struct *> (coninfo_cls);
	(void)kind;               /* Unused. Silent compiler warning. */
	(void)filename;           /* Unused. Silent compiler warning. */
	(void)content_type;       /* Unused. Silent compiler warning. */
	(void)transfer_encoding;  /* Unused. Silent compiler warning. */
	(void)off;                /* Unused. Silent compiler warning. */


	if (0 == strcmp (key, "home"))
	{
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			_database.read_database();                          // read binary database file
			_webpage_creator.write_database_table(_database.getDatabaseContent());                  // create temp table file
			Tools::OSCopyFile(TEMPLATE_DATABASE_PAGE, TEMP_PAGE);      // copy template to temp file, to be mofified
			_webpage_creator.updateDatabasePage();             // update database to webpage
			char *answerstring;
			answerstring = (char*)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}

	if (0 == strcmp (key, "contact_us")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char*)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			char * page_str = _webpage_creator.getPage(CONTACTUS_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}

	if (0 == strcmp (key, "add")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			char * page_str = _webpage_creator.getPage(ADDUSER_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}


	if (0 == strcmp (key, "remove")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			char * page_str = _webpage_creator.getPage(DELETEUSER_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}

	if (0 == strcmp (key, "ask")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			char * page_str = _webpage_creator.getPage(ASKUSER_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}

	if (0 == strcmp (key, "tgid_ask")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);

			if (!answerstring)
				return MHD_NO;

			employee check_data;
			bool check = _database.get_empolyee_update(Tools::convertToString(data,strlen(data)),check_data);
			if(check == false){
				char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
				strncpy(answerstring,page_str,MAXANSWERSIZE);
				free(page_str);
				con_info->answerstring = answerstring;
			}
			else
			{
				char * page_str = _webpage_creator.getPage(UPDATEUSER_PAGE);
				snprintf (answerstring, MAXANSWERSIZE, page_str, check_data.name,check_data.tgid,check_data.contact);
				free(page_str);
				con_info->answerstring = answerstring;
			}

		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}



	if (0 == strcmp (key, "tgid_delete")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			if (!answerstring)
				return MHD_NO;
			_database.delete_employee(Tools::convertToString(data,strlen(data)));                                       // delete using key id
			_database.save_file();
			_database.read_database();                                             // read binary database file

			_webpage_creator.write_database_table(_database.getDatabaseContent());                        // create temp table file
			Tools::OSCopyFile(TEMPLATE_DATABASE_PAGE, TEMP_PAGE);                   // copy template to temp file, to be mofified
			_webpage_creator.updateDatabasePage();
			// update database to webpage
			char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}



	if (0 == strcmp (key, "name")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			strcpy(_temp_storage.name,"\0");
			strcpy(_temp_storage.tgid,"\0");
			strcpy(_temp_storage.contact,"\0");
			strcpy(_temp_storage.name, data);
		}
		else
			return MHD_NO;

		return MHD_YES;
	}


	if (0 == strcmp (key, "tgid")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			strcpy(_temp_storage.tgid, data);
		}
		else
			return MHD_NO;

		return MHD_YES;
	}

	if (0 == strcmp (key, "contact")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			strcpy(_temp_storage.contact, data);
			_database.add_employee(Tools::convertToString((_temp_storage.tgid),strlen(_temp_storage.tgid)),_temp_storage);               // add to database
			_database.save_file();
			_database.read_database();                          // read binary database file
			_webpage_creator.write_database_table(_database.getDatabaseContent());                     // create temp table file
			Tools::OSCopyFile(TEMPLATE_DATABASE_PAGE, TEMP_PAGE);      // copy template to temp file, to be mofified
			_webpage_creator.updateDatabasePage();                               // update database to webpage
			char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}


	if (0 == strcmp (key, "name_update")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			strcpy(_temp_storage.name,"\0");
			strcpy(_temp_storage.tgid,"\0");
			strcpy(_temp_storage.contact,"\0");
			strcpy(_temp_storage.name, data);
		}
		else
			return MHD_NO;

		return MHD_YES;
	}


	if (0 == strcmp (key, "tgid_update")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			strcpy(_temp_storage.tgid, data);
		}
		else
			return MHD_NO;

		return MHD_YES;
	}

	if (0 == strcmp (key, "contact_update")) {
		if ((size > 0) && (size <= MAXNAMESIZE))
		{
			char *answerstring;
			answerstring = (char *)malloc (MAXANSWERSIZE);
			strcpy(_temp_storage.contact, data);
			_database.update_employee(_temp_storage);
			_database.save_file();
			_database.read_database();                          // read binary database file
			_webpage_creator.write_database_table(_database.getDatabaseContent());                     // create temp table file
			Tools::OSCopyFile(TEMPLATE_DATABASE_PAGE, TEMP_PAGE);      // copy template to temp file, to be mofified
			_webpage_creator.updateDatabasePage();                               // update database to webpage
			char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
			strncpy(answerstring,page_str,MAXANSWERSIZE);
			free(page_str);
			con_info->answerstring = answerstring;
		}
		else
			con_info->answerstring = NULL;

		return MHD_NO;
	}

	return MHD_YES;


}

void Server::request_completed (void *cls, struct MHD_Connection *connection,
		void **con_cls, enum MHD_RequestTerminationCode toe)
{
	struct connection_info_struct *con_info = reinterpret_cast <connection_info_struct * > (*con_cls);
	(void)cls;         /* Unused. Silent compiler warning. */
	(void)connection;  /* Unused. Silent compiler warning. */
	(void)toe;         /* Unused. Silent compiler warning. */

	if (NULL == con_info)
		return;

	if (con_info->connectiontype == POST)
	{
		MHD_destroy_post_processor (con_info->postprocessor);
		if (con_info->answerstring)
			free (con_info->answerstring);
	}

	free (con_info);
	*con_cls = NULL;

	strcpy(_temp_storage.name,"\0");
	strcpy(_temp_storage.tgid,"\0");
	strcpy(_temp_storage.contact,"\0");
}


int Server::answer_to_connection (void *cls, struct MHD_Connection *connection,
		const char *url, const char *method,
		const char *version, const char *upload_data,
		size_t *upload_data_size, void **con_cls)
{
	(void)cls;               /* Unused. Silent compiler warning. */
	(void)url;               /* Unused. Silent compiler warning. */
	(void)version;           /* Unused. Silent compiler warning. */

	if (NULL == *con_cls)
	{
		struct connection_info_struct *con_info;

		con_info = (struct connection_info_struct *)malloc (sizeof (struct connection_info_struct));
		if (NULL == con_info)
			return MHD_NO;
		con_info->answerstring = NULL;

		if (0 == strcmp (method, "POST"))
		{
			//    	Server* this_ptr = (Server *) cls;
			con_info->postprocessor =
					MHD_create_post_processor (connection, POSTBUFFERSIZE,
							iterate_post, (void *) con_info);

			if (NULL == con_info->postprocessor)
			{
				free (con_info);
				return MHD_NO;
			}

			con_info->connectiontype = POST;
		}
		else
			con_info->connectiontype = GET;

		*con_cls = (void *) con_info;

		return MHD_YES;
	}

	if (0 == strcmp (method, "GET"))
	{
		char *user;
		char *pass;
		int fail;
		int ret;
		struct MHD_Response *response;
		//basic authentication code
		pass = NULL;
		user = MHD_basic_auth_get_username_password (connection,
				&pass);
		fail = ( (NULL == user) ||
				(0 != strcmp (user, "praveen")) ||
				(0 != strcmp (pass, "password") ) );
		if (NULL != user) MHD_free (user);
		if (NULL != pass) MHD_free (pass);
		if (fail)
		{
			const char *page = "<html><body>Go away.</body></html>";
			response =
					MHD_create_response_from_buffer (strlen (page), (void *) page,
							MHD_RESPMEM_PERSISTENT);
			ret = MHD_queue_basic_auth_fail_response (connection,
					"my realm",
					response);
			return ret;
		}
		else
		{
			_database.read_database();                                             // read binary database file
			_webpage_creator.write_database_table(_database.getDatabaseContent());                       // create temp table file
			Tools::OSCopyFile(TEMPLATE_DATABASE_PAGE, TEMP_PAGE);                          // copy template to temp file, to be mofified
			_webpage_creator.updateDatabasePage();                                 // update database to webpage
			char * page_str = _webpage_creator.getPage(DATABASE_PAGE);
			ret = send_page (connection, page_str);
			free(page_str);
			return ret;
		}

	}

	if (0 == strcmp (method, "POST"))
	{
		struct connection_info_struct *con_info = (struct connection_info_struct *) *con_cls;

		if (*upload_data_size != 0)
		{
			MHD_post_process (con_info->postprocessor, upload_data,
					*upload_data_size);
			*upload_data_size = 0;

			return MHD_YES;
		}
		else if (NULL != con_info->answerstring) {
			return send_page (connection, con_info->answerstring);
		}
	}

	return send_page (connection, error_page);

}
