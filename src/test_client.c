//
// Created by moritzmg on 17/01/18.
//
#include <glib.h>
#include <gio/gio.h>
#include <string.h>
#include "cJSON.h"

int
main (int argc, char *argv[])
{

    GError * error = NULL;

    /* create a new connection */
    GSocketConnection * connection = NULL;
    GSocketClient * client = g_socket_client_new();

    /* connect to the host */
    connection = g_socket_client_connect_to_host (client,
                                                  (gchar*)"localhost",
                                                  2345, /* your port goes here */
                                                  NULL,
                                                  &error);

    /* don't forget to check for errors */
    if (error != NULL)
    {
        g_error (error->message);
        return -1;
    }
    else
    {
        g_print ("Connection successful!\n");
    }


    cJSON *json = cJSON_CreateObject();
    cJSON *message_type = cJSON_CreateString("test");

    cJSON_AddItemToObject(json, "message_type", message_type);

    char* message = cJSON_PrintUnformatted(json);

//    g_print(message);

//    g_print("sadsad");

    cJSON_Delete(json);


    /* use the connection */
    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
    GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));
    g_output_stream_write  (ostream,
                            message, /* your message goes here */
                            strlen(message) + 1, /* length of your message */
                            NULL,
                            &error);
    /* don't forget to check for errors */

    g_free(message);

    if (error != NULL)
    {
        g_error (error->message);
    }
    return 0;
}
