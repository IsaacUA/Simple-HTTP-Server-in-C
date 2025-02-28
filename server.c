#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096
#define MAX_INPUT_SIZE 20

void handle_client(int client_socket, char *html_path);
void handle_server(char *html_path, int PORT);
int main(void)
{
    int PORT;
    char html_path[MAX_INPUT_SIZE], str[MAX_INPUT_SIZE];

    printf("---------------\n");
    printf("SERVER TERMINAL\n\n");
    printf("Path to index.html:\n");
    printf("> ");
    if (fgets(html_path, MAX_INPUT_SIZE, stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }
    html_path[strcspn(html_path, "\n")] = 0;
    printf("Port:\n");
    printf("> ");
    if (fgets(str, MAX_INPUT_SIZE, stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }
    PORT = atoi(str);
    printf("---------------\n");
    printf("Configured with:\n");
    printf("index.html path: %s\n", html_path);
    printf("localhost port: %d\n", PORT);
    printf("---------------\n");
    printf("Server is listen on PORT: %d\n", PORT);

    handle_server(html_path,  PORT);
}

void handle_server(char *html_path, int PORT)
{
	int server_fd, client_fd;
	struct sockaddr_in server_address, client_address;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        fprintf(stderr, "Socket not created\n");
    }
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_fd, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_fd, 5);

	while ((client_fd = accept(server_fd, NULL, NULL)) > 0)
	{
		handle_client(client_fd, html_path);
		close(client_fd);
	}
	close(server_fd);
}


void handle_client(int client_socket, char *html_path) 
{
    FILE *file = fopen(html_path, "r");
    if (file == NULL) {
        fprintf(stderr, "HTML file not found\n");
        return;
    }
    char html_content[BUFFER_SIZE];
    size_t content_length = fread(html_content, 1, BUFFER_SIZE - 1, file);
    fclose(file);
    html_content[content_length] = '\0';

    char response[BUFFER_SIZE];
    int header_length = snprintf(response, BUFFER_SIZE,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "\r\n",
        content_length);

    if (header_length + content_length < BUFFER_SIZE) {
        memcpy(response + header_length, html_content, content_length);
    } else {
        perror("Response too large");
        close(client_socket);
        return ;
    }
    send(client_socket, response, header_length + content_length, 0);
    close(client_socket);
}
