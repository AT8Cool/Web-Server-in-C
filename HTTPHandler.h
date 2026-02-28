#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <time.h>

typedef struct {
    time_t start_time;
    int request_count;
    int total_bytes_sent;
} ServerStats;

// Server-wide stats
extern ServerStats g_stats;

// Parse request line (GET /path HTTP/1.1)
void parse_request_line(const char *line, char *method, char *path, char *query);

// Send JSON response with proper headers
void send_json_response(int socket, const char *json_body, int status_code);

// Send HTML response
void send_html_response(int socket, const char *html_body);

// API Handlers
void handle_api_status(int socket);
void handle_api_time(int socket);
void handle_api_store(int socket, const char *body);
void handle_api_retrieve(int socket, const char *key);
void handle_api_stats(int socket);
void handle_api_bst(int socket);
void handle_dashboard(int socket);
void handle_not_found(int socket);

#endif
