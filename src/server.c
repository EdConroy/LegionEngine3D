#include "server.h"

void message_ready(GObject* source_obj, GAsyncResult* res, gpointer userdata)
{
	GInputStream *istream = G_INPUT_STREAM(source_obj);
	GError *error = NULL;
	struct ConnData *data = userdata;
	int count;

	count = g_input_stream_read_finish(istream,
		res,
		&error);

	if (count == -1) {
		g_error("Error when receiving message");
		if (error != NULL) {
			g_error("%s", error->message);
			g_clear_error(&error);
		}
	}
	g_message("Message was: \"%s\"\n", data->message);
	g_object_unref(G_SOCKET_CONNECTION(data->connection));
	g_free(data);
}
static lbool incoming_callback(GSocketService* service, GSocketConnection* connection, GObject* source_object, gpointer user_data)
{
	g_message("Received Connection from client!\n");
	GInputStream *istream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
	struct ConnData *data = g_new(struct ConnData, 1);

	data->connection = g_object_ref(connection);

	g_input_stream_read_async(istream,
		data->message,
		sizeof(data->message),
		G_PRIORITY_DEFAULT,
		NULL,
		message_ready,
		data);
	return FALSE;
}
