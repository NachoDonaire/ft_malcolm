#ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include <sys/types.h>
#include <sys/socket.h>
#include<linux/if_packet.h>
#include<net/ethernet.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024

enum status {
	OK = 1,
	NARG_ERR,
	IP_ERR,
	MAC_ERR,
	SOCKET_ERR
};

#endif
