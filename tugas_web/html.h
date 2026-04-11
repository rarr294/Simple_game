#ifndef HTML_H
#define HTML_H

const char *resp =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Content-Length: %d\r\n"
"Connection: close\r\n\r\n";

const char *html =
"<!DOCTYPE html>"
"<html>"
"<body>"
    "<p>Nama = %s</p>"
    "<br>"
    "<p>Umur = %s</p>"
"</body>"
"</html>";

#endif
