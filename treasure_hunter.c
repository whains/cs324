// Replace PUT_USERID_HERE with your actual BYU CS user id, which you can find
// by running `id -u` on a CS lab machine.

// Will Hainsworth - hainsw

#define USERID 1823693097

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <arpa/inet.h>

int verbose = 0;

unsigned char scripture[500];
int scriptIndex = 0;

int n;
int opCode;
int opParam1;
int opParam2;
int port;
int nonce[4];

int globalLocalPort;

void print_bytes(unsigned char *bytes, int byteslen);

void print_scripture() {
  printf("%s\n", scripture);
}


void concatenate_scripture(unsigned char *bytes) {
  for (int i = 1; i <= n; i++) {
    scripture[scriptIndex] = bytes[i];
    scriptIndex = scriptIndex + 1;
  }
}


void update_response_values(unsigned char *bytes) {
  n = bytes[0];
  opCode = bytes[n+1];

  if (n < 21 && n != 0)
    concatenate_scripture(bytes);

  opParam1 = bytes[n+2];
  opParam2 = bytes[n+3];
  port = (opParam2) | (opParam1 << 8);

  for (int j = 0; j < 4; j++) {
    nonce[j] = bytes[n+4+j];
  }
}


void print_info() {
  printf("Chunk Length: %d\n", n);
  printf("Op Code: %d\n", opCode);
  printf("Op Param: %x, %x Port num: %x\n", opParam1, opParam2, port);
  printf("Nonce: %x, %x, %x, %x", nonce[0], nonce[1], nonce[2], nonce[3]);
  printf("\nThe current scripture: ");
  print_scripture();
  printf("\n");
}


int main(int argc, char *argv[]) {

  unsigned char initialBuf[8] = { 0, (uintptr_t)atoi(argv[3]), 0x6c, 0xb3, 0x59, 0x29,
    (uintptr_t)(atoi(argv[4]) >> (8*1)) & 0xff, (uintptr_t)(atoi(argv[4]) >> (8*0)) & 0xff };
  unsigned char requestBuf[4];
  unsigned char returnBuf[64];

  struct sockaddr_in temp;
  temp.sin_family = AF_INET;
  temp.sin_addr.s_addr = 0;
  temp.sin_port = 0;

  struct sockaddr_in ipv4addr_local_initial;
  struct sockaddr_in ipv4addr_local;
	struct sockaddr_in ipv4addr_remote;

  struct addrinfo hints;
  struct addrinfo *result;
  struct addrinfo *rp;
  int sfd;


  // UDP Setup

  memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

  getaddrinfo(argv[1], argv[2], &hints, &result);

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sfd = socket(rp->ai_family, rp->ai_socktype,
        rp->ai_protocol);

    bind(sfd, (struct sockaddr *)&temp, sizeof(temp));

    if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
	    ipv4addr_remote = *(struct sockaddr_in *)rp->ai_addr;
      break;
    }

    close(sfd);
  }

  if (rp == NULL) {
    fprintf(stderr, "Could not connect\n");
    exit(EXIT_FAILURE);
  }


  // Send & receive loop

  send(sfd, &initialBuf, 8, 0);
  recv(sfd, returnBuf, 64, 0);

  while (1) {

    update_response_values(returnBuf);

    if (n == 0 || n > 127)
      break;

    returnBuf[n+7] = returnBuf[n+7] + 1;
    for (int j = 0; j < 4; j++)
      requestBuf[j] = returnBuf[n + 4 + j];


      // OPCODE 0

    if (opCode == 0) { }


      // OPCODE 1

    else if (opCode == 1) {
      int remotePort = port;
      ipv4addr_remote.sin_port = htons(remotePort);

      connect(sfd, (struct sockaddr *)&ipv4addr_remote, sizeof(struct sockaddr_in));
    }


    // OPCODE 2

    else if (opCode == 2) {
      int localPort = port;

      ipv4addr_local.sin_family = AF_INET;
      ipv4addr_local.sin_port = htons(localPort);
      ipv4addr_local.sin_addr.s_addr = 0;

    	close(sfd);
      sfd = socket(AF_INET, SOCK_DGRAM, 0);

      bind(sfd, (struct sockaddr *)&ipv4addr_local, sizeof(struct sockaddr_in));
      connect(sfd, (struct sockaddr *)&ipv4addr_remote, sizeof(struct sockaddr_in));
    }


    // OPCODE 3

    else if (opCode == 3) {
      int m = port;
      unsigned int len = sizeof(struct sockaddr_in);
      struct sockaddr_in ipv4addr_remote_portless = ipv4addr_remote;
      ipv4addr_remote_portless.sin_port = 0;

      struct sockaddr_in tempAddr;
      tempAddr.sin_family = AF_INET;
      tempAddr.sin_port = htons(globalLocalPort);
      tempAddr.sin_addr.s_addr = 0;

      close(sfd);
      sfd = socket(AF_INET, SOCK_DGRAM, 0);

      bind(sfd, (struct sockaddr *)&tempAddr, sizeof(tempAddr));

      unsigned int sum = 0;
      for (int j = 0; j < m; j++) {
        recvfrom(sfd, returnBuf, 64, 0, (struct sockaddr *)&ipv4addr_remote_portless, &len);
        sum = sum + htons(ipv4addr_remote_portless.sin_port);
      }
      sum = sum + 1;

      requestBuf[0] = (sum>>24) & 0xFF;
      requestBuf[1] = (sum>>16) & 0xFF;
      requestBuf[2] = (sum>>8) & 0xFF;
      requestBuf[3] = sum & 0xFF;

      connect(sfd, (struct sockaddr *)&ipv4addr_remote, sizeof(struct sockaddr_in));
    }


    // OPCODE 4 Extra Credit

    else if (opCode == 4) {
      exit(EXIT_FAILURE);
    }

    bzero(&ipv4addr_local_initial, sizeof(ipv4addr_local_initial));
    socklen_t lenn = sizeof(ipv4addr_local_initial);
    getsockname(sfd, (struct sockaddr *)&ipv4addr_local_initial, &lenn);
    globalLocalPort = ntohs(ipv4addr_local_initial.sin_port);

    send(sfd, &requestBuf, 4, 0);
    recv(sfd, returnBuf, 64, 0);

  }

  print_scripture();

  exit(EXIT_SUCCESS);
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
