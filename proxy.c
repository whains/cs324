#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:97.0) Gecko/20100101 Firefox/97.0";

int all_headers_received(char *);
int parse_request(char *, char *, char *, char *, char *, char *);
void test_parser();
void print_bytes(unsigned char *, int);
int open_sfd(char *argv[]);
void handle_client();


int main(int argc, char *argv[])
{
	//test_parser();
	printf("%s\n", user_agent_hdr);

  open_sfd(argv);

	return 0;
}



int all_headers_received(char *request) {
  if (strstr(request, "\r\n\r\n") != NULL)
    return 1;
	return 0;
}

int parse_request(char *request, char *method, char *hostname, char *port, char *path, char *headers) {
  if (all_headers_received(request)) {
    // METHOD
    memset(method, 0, 16);
    strncpy(method, request, (size_t)(((char*)strchr(request, ' ')) - request));

    // HOST & PORT
    char *hostStrBegins = strstr(request, "Host: ") + 6;
    char *hostStrEnds;
    size_t lenHost;
    char *portColon = strchr(hostStrBegins, ':');

    memset(port, 0, 8);
    if ((char*)strstr(hostStrBegins, "\r\n") > portColon) {
      size_t lenPort = (char*)strchr(hostStrBegins, '\n') - portColon;
      strncpy(port, portColon + 1, lenPort - 2);
      port[strcspn(port, "\r\n")] = 0;
      hostStrEnds = portColon;
    }
    else {
      strcpy(port, "80");
      hostStrEnds = strchr(hostStrBegins, '\n');
    }

    lenHost = hostStrEnds - hostStrBegins;
    memset(hostname, 0, 64);
    strncpy(hostname, hostStrBegins, lenHost);
    hostname[strcspn(hostname, "\r\n")] = 0;

    // PATH
		char *startPath = strchr(strstr(request, ".com"), '/');
    memset(path, 0, 64);
		strncpy(path, startPath, (size_t)((char*)strchr(startPath, ' ') - startPath));

    // HEADERS
    memset(headers, 0, 1024);
    strcpy(headers, (char*)(strchr(request, '\n') + 1));

    return 1;
  }

  return 0;
}

// Create and configure a TCP socket for listening and accepting new client connections.
int open_sfd (char *argv[]) {
  struct addrinfo hints;
  struct addrinfo *result;
  int sfd;
  int s;

  memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

  if ((sfd = socket(result->ai_family, result->ai_socktype, 0)) < 0) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  int optval = 1;
  setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

  if (bind(sfd, result->ai_addr, result->ai_addrlen) < 0) {
    perror("Could not bind");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(result);

  listen(sfd, MAX_OBJECT_SIZE);

  return sfd;
}

void handle_client() {

}



void test_parser() {
	int i;
	char method[16], hostname[64], port[8], path[64], headers[1024];

       	char *reqs[] = {
		"GET http://www.example.com/index.html HTTP/1.0\r\n"
		"Host: www.example.com\r\n"
		"User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0\r\n"
		"Accept-Language: en-US,en;q=0.5\r\n\r\n",

		"GET http://www.example.com:8080/index.html?foo=1&bar=2 HTTP/1.0\r\n"
		"Host: www.example.com:8080\r\n"
		"User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0\r\n"
		"Accept-Language: en-US,en;q=0.5\r\n\r\n",

		"GET http://www.example.com:8080/index.html HTTP/1.0\r\n",

		NULL
	};

	for (i = 0; reqs[i] != NULL; i++) {
		printf("Testing %s\n", reqs[i]);
		if (parse_request(reqs[i], method, hostname, port, path, headers)) {
			printf("METHOD: %s\n", method);
      //printf("METHOD LENGTH: %ld\n", strlen(method));
			printf("HOSTNAME: %s\n", hostname);
      //printf("HOSTNAME LENGTH: %ld\n", strlen(hostname));
			printf("PORT: %s\n", port);
      //printf("PORT LENGTH: %ld\n", strlen(port));
      printf("PATH: %s\n", path);
      //printf("PATH LENGTH: %ld\n", strlen(path));
			printf("HEADERS: %s\n", headers);
      //printf("HEADERS LENGTH: %ld\n", strlen(headers));
		} else {
			printf("REQUEST INCOMPLETE\n");
		}
	}
}

void print_bytes(unsigned char *bytes, int byteslen) {
	int i, j, byteslen_adjusted;

	if (byteslen % 8) {
		byteslen_adjusted = ((byteslen / 8) + 1) * 8;
	} else {
		byteslen_adjusted = byteslen;
	}
	for (i = 0; i < byteslen_adjusted + 1; i++) {
		if (!(i % 8)) {
			if (i > 0) {
				for (j = i - 8; j < i; j++) {
					if (j >= byteslen_adjusted) {
						printf("  ");
					} else if (j >= byteslen) {
						printf("  ");
					} else if (bytes[j] >= '!' && bytes[j] <= '~') {
						printf(" %c", bytes[j]);
					} else {
						printf(" .");
					}
				}
			}
			if (i < byteslen_adjusted) {
				printf("\n%02X: ", i);
			}
		} else if (!(i % 4)) {
			printf(" ");
		}
		if (i >= byteslen_adjusted) {
			continue;
		} else if (i >= byteslen) {
			printf("   ");
		} else {
			printf("%02X ", bytes[i]);
		}
	}
	printf("\n");
}
