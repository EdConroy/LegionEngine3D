#include <glib.h>
#include <gio\gio.h>
#include "lbool.h"

#define BLOCK_SIZE 1024
#define PORT 2345

struct ConnData
{
	GSocketConnection* connection;
	char message[BLOCK_SIZE];
};

void message_ready(GObject* source_obj, GAsyncResult* res, gpointer userdata);
static lbool incoming_callback(GSocketService* service, GSocketConnection* connection, GObject* source_object, gpointer user_data);