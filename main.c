#include <stdio.h>
#include <glib.h>
#include <i3ipc-glib/i3ipc-glib.h>

#define PDTH_CLASS "steam_app_24240"
#define PDTH_WORKSPACE "5"

void print_change(i3ipcConnection *self, i3ipcWindowEvent *e, gpointer user_data) {
	// Only act on 
	if (g_strcmp0(e->change, "new")) {
		return;
	}

	// Fetch window's class string
	gchar* class;
	g_object_get(e->container, "window-class", &class, NULL);

	// Only take action if the new window is PDTH's window
	if (g_strcmp0(class, PDTH_CLASS)) {
		g_free(class);
		return;
	}
	g_free(class); // TODO: Can this call to g_free be un-duplicated?

	//printf("Change: %s, %s \"%s\"\n", e->change, class, i3ipc_con_get_name(e->container));

	// Set focus to the workspace with PDTH
	/*gchar *reply =*/ i3ipc_connection_message(self, I3IPC_MESSAGE_TYPE_COMMAND, "workspace number " PDTH_WORKSPACE, NULL);
	//printf("Reply: %s\n", reply);
	//g_free(reply);
}

int main() {
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);

	i3ipcConnection *conn = i3ipc_connection_new(NULL, NULL);
	i3ipcCommandReply *cr = i3ipc_connection_subscribe(conn, I3IPC_EVENT_WINDOW, NULL);
	i3ipc_command_reply_free(cr);

	g_object_connect(conn, "signal::window", G_CALLBACK(print_change), NULL, NULL);

	g_main_loop_run(loop);
	g_object_unref(conn);

	return 0;
}
