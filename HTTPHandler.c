#include "HTTPHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>

ServerStats g_stats = {0, 0, 0};

void parse_request_line(const char *line, char *method, char *path, char *query) {
    sscanf(line, "%s %s HTTP", method, path);
    
    char *q = strchr(path, '?');
    if (q) {
        strncpy(query, q + 1, 255);
        path[q - path] = '\0';
    } else {
        query[0] = '\0';
    }
}

void send_json_response(int socket, const char *json_body, int status_code) {
    const char *status_str = (status_code == 200) ? "OK" : 
                            (status_code == 404) ? "Not Found" : "Error";
    
    char response[4096];
    int content_len = strlen(json_body);
    
    snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code, status_str, content_len, json_body);
    
    send(socket, response, (int)strlen(response), 0);
    g_stats.total_bytes_sent += strlen(response);
}

void send_html_response(int socket, const char *html_body) {
    char response[16384];
    int content_len = strlen(html_body);
    
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        content_len, html_body);
    
    send(socket, response, (int)strlen(response), 0);
    g_stats.total_bytes_sent += strlen(response);
}

void handle_api_status(int socket) {
    char json[512];
    time_t uptime = time(NULL) - g_stats.start_time;
    
    snprintf(json, sizeof(json),
        "{"
        "\"status\":\"running\","
        "\"uptime_seconds\":%ld,"
        "\"requests_handled\":%d,"
        "\"bytes_sent\":%d"
        "}",
        uptime, g_stats.request_count, g_stats.total_bytes_sent);
    
    send_json_response(socket, json, 200);
}

void handle_api_time(int socket) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char json[512];
    
    strftime(json, sizeof(json),
        "{\"timestamp\":\"%Y-%m-%d %H:%M:%S\",\"epoch\":%s}",
        timeinfo);
    
    send_json_response(socket, json, 200);
}

void handle_api_store(int socket, const char *body) {
    char json[256];
    // Simple parse: key=value&key2=value2
    // For demo, just acknowledge
    snprintf(json, sizeof(json), "{\"stored\":true,\"message\":\"Data stored in Dictionary\"}");
    send_json_response(socket, json, 200);
}

void handle_api_retrieve(int socket, const char *key) {
    char json[512];
    // Dummy: would retrieve from Dictionary in real implementation
    snprintf(json, sizeof(json), 
        "{\"key\":\"%s\",\"value\":\"sample_value\",\"found\":true}", 
        key);
    send_json_response(socket, json, 200);
}

void handle_api_stats(int socket) {
    char json[512];
    time_t uptime = time(NULL) - g_stats.start_time;
    
    snprintf(json, sizeof(json),
        "{"
        "\"requests\":%d,"
        "\"uptime_seconds\":%ld,"
        "\"bytes_sent\":%d,"
        "\"avg_request_size\":%d"
        "}",
        g_stats.request_count, uptime, g_stats.total_bytes_sent,
        g_stats.request_count > 0 ? g_stats.total_bytes_sent / g_stats.request_count : 0);
    
    send_json_response(socket, json, 200);
}

void handle_api_bst(int socket) {
    char json[512];
    snprintf(json, sizeof(json),
        "{"
        "\"structure\":\"Binary Search Tree\","
        "\"status\":\"Demo - ready for data insertion\","
        "\"features\":[\"insert\",\"search\",\"traverse\"]"
        "}");
    send_json_response(socket, json, 200);
}

void handle_dashboard(int socket) {
    const char *html = 
        "<!DOCTYPE html>"
        "<html lang='en'>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
        "<title>C Web Server Dashboard</title>"
        "<style>"
        "body { font-family: Arial, sans-serif; margin: 20px; background: #f5f5f5; }"
        ".container { max-width: 900px; margin: 0 auto; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }"
        "h1 { color: #333; }"
        ".stats { display: grid; grid-template-columns: repeat(3, 1fr); gap: 20px; margin: 20px 0; }"
        ".stat-box { background: #f0f0f0; padding: 15px; border-radius: 5px; text-align: center; }"
        ".stat-value { font-size: 24px; font-weight: bold; color: #0066cc; }"
        ".stat-label { color: #666; margin-top: 5px; }"
        ".button { background: #0066cc; color: white; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer; margin: 5px; }"
        ".button:hover { background: #0052a3; }"
        ".form-group { margin: 15px 0; }"
        "input { padding: 8px; border: 1px solid #ddd; border-radius: 4px; }"
        "textarea { padding: 8px; border: 1px solid #ddd; border-radius: 4px; width: 100%; height: 100px; font-family: monospace; }"
        ".response { background: #f9f9f9; border-left: 4px solid #0066cc; padding: 10px; margin: 10px 0; font-family: monospace; }"
        "</style>"
        "</head>"
        "<body>"
        "<div class='container'>"
        "<h1>⚙️ C Web Server Interactive Dashboard</h1>"
        "<p>Built with Socket Programming | Data Structures: BST & Dictionary</p>"
        
        "<h2>Server Status</h2>"
        "<div class='stats'>"
        "<div class='stat-box'>"
        "<div class='stat-value' id='requests'>0</div>"
        "<div class='stat-label'>Requests</div>"
        "</div>"
        "<div class='stat-box'>"
        "<div class='stat-value' id='uptime'>0s</div>"
        "<div class='stat-label'>Uptime</div>"
        "</div>"
        "<div class='stat-box'>"
        "<div class='stat-value' id='bytes'>0 B</div>"
        "<div class='stat-label'>Bytes Sent</div>"
        "</div>"
        "</div>"
        
        "<h2>API Endpoints</h2>"
        "<button class='button' onclick=\"fetchAPI('status')\">GET /api/status</button>"
        "<button class='button' onclick=\"fetchAPI('time')\">GET /api/time</button>"
        "<button class='button' onclick=\"fetchAPI('stats')\">GET /api/stats</button>"
        "<button class='button' onclick=\"fetchAPI('bst')\">GET /api/bst-structure</button>"
        
        "<h2>Key-Value Store (Dictionary)</h2>"
        "<div class='form-group'>"
        "<label>Key:</label><br>"
        "<input type='text' id='storeKey' placeholder='Enter key'>"
        "</div>"
        "<div class='form-group'>"
        "<label>Value:</label><br>"
        "<input type='text' id='storeValue' placeholder='Enter value'>"
        "</div>"
        "<button class='button' onclick=\"storeData()\">Store Data</button>"
        
        "<div class='form-group'>"
        "<label>Retrieve Key:</label><br>"
        "<input type='text' id='retrieveKey' placeholder='Enter key to retrieve'>"
        "</div>"
        "<button class='button' onclick=\"retrieveData()\">Retrieve Data</button>"
        
        "<h2>Response</h2>"
        "<div class='response' id='response'>Response will appear here...</div>"
        
        "<h2>Demo Code Architecture</h2>"
        "<ul>"
        "<li><strong>HTTP Parser:</strong> Custom request parser extracts method, path, query string</li>"
        "<li><strong>Router:</strong> Dispatch requests to appropriate handler functions</li>"
        "<li><strong>Data Storage:</strong> Binary Search Tree (BST) and Dictionary for O(log n) lookups</li>"
        "<li><strong>JSON Builder:</strong> Generate responses dynamically</li>"
        "<li><strong>Multi-Socket Handling:</strong> Handles concurrent client connections</li>"
        "</ul>"
        
        "</div>"
        
        "<script>"
        "function formatBytes(bytes) {"
        "  if(bytes === 0) return '0 B';"
        "  const k = 1024;"
        "  const sizes = ['B', 'KB', 'MB'];"
        "  const i = Math.floor(Math.log(bytes) / Math.log(k));"
        "  return (bytes / Math.pow(k, i)).toFixed(2) + ' ' + sizes[i];"
        "}"
        
        "function fetchAPI(endpoint) {"
        "  const urls = {"
        "    status: '/api/status',"
        "    time: '/api/time',"
        "    stats: '/api/stats',"
        "    bst: '/api/bst-structure'"
        "  };"
        "  fetch(urls[endpoint])"
        "    .then(r => r.json())"
        "    .then(data => {"
        "      document.getElementById('response').innerHTML = '<strong>' + endpoint.toUpperCase() + ':</strong><br>' + JSON.stringify(data, null, 2);"
        "      if(data.requests !== undefined) document.getElementById('requests').innerHTML = data.requests;"
        "      if(data.bytes_sent !== undefined) document.getElementById('bytes').innerHTML = formatBytes(data.bytes_sent);"
        "    })"
        "    .catch(e => document.getElementById('response').innerHTML = 'Error: ' + e);"
        "}"
        
        "function storeData() {"
        "  const key = document.getElementById('storeKey').value;"
        "  const value = document.getElementById('storeValue').value;"
        "  if(!key || !value) { alert('Enter key and value'); return; }"
        "  fetch('/api/store?key=' + encodeURIComponent(key) + '&value=' + encodeURIComponent(value), {method: 'POST'})"
        "    .then(r => r.json())"
        "    .then(data => document.getElementById('response').innerHTML = '<strong>STORE:</strong><br>' + JSON.stringify(data, null, 2))"
        "    .catch(e => document.getElementById('response').innerHTML = 'Error: ' + e);"
        "}"
        
        "function retrieveData() {"
        "  const key = document.getElementById('retrieveKey').value;"
        "  if(!key) { alert('Enter key'); return; }"
        "  fetch('/api/retrieve?key=' + encodeURIComponent(key))"
        "    .then(r => r.json())"
        "    .then(data => document.getElementById('response').innerHTML = '<strong>RETRIEVE:</strong><br>' + JSON.stringify(data, null, 2))"
        "    .catch(e => document.getElementById('response').innerHTML = 'Error: ' + e);"
        "}"
        
        "setInterval(() => fetchAPI('status'), 2000);"
        "</script>"
        "</body>"
        "</html>";
    
    send_html_response(socket, html);
}

void handle_not_found(int socket) {
    const char *html = 
        "<!DOCTYPE html><html><body>"
        "<h1>404 Not Found</h1>"
        "<p>Try <a href='/'>visiting the dashboard</a> or use /api/ endpoints.</p>"
        "</body></html>";
    
    send_html_response(socket, html);
}
