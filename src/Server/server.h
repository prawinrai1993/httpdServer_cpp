/*
 * Server.h
 *
 *  Created on: 10-Jun-2020
 *      Author: praveen
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <sys/types.h>
#include <microhttpd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "tools.h"
#include "webpage_creator.h"

class Database;
class Tools;
class WebPage_Creator;
using namespace std;

#define PORT            8888
#define POSTBUFFERSIZE  2048
#define MAXNAMESIZE     20
#define MAXANSWERSIZE   2048


#define GET             0
#define POST            1


struct connection_info_struct
{
	int connectiontype;
	char *answerstring;
	struct MHD_PostProcessor *postprocessor;
};

class Server{

	public:Server();
	       virtual ~Server();
	       int startServer();
	       void stopServer();

	       /* variables*/
	private:
	    struct MHD_Daemon *_daemon;
	    static Database _database;
	    static WebPage_Creator _webpage_creator;
		static employee _temp_storage;


	       /* functions for server handling*/
	private:
	static int iterate_post (void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
		const char *filename, const char *content_type,
		const char *transfer_encoding, const char *data, uint64_t off,
		size_t size);

	static void request_completed (void *cls, struct MHD_Connection *connection,
		void **con_cls, enum MHD_RequestTerminationCode toe);

	static int answer_to_connection (void *cls, struct MHD_Connection *connection,
		const char *url, const char *method,
		const char *version, const char *upload_data,
		size_t *upload_data_size, void **con_cls);

	static int send_page (struct MHD_Connection *connection, const char *page);
	static void ignore_sigpipe ();
	static void catcher (int sig);


};

#endif /* SERVER_H_ */
