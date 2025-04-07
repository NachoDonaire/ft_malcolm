#ifndef SEND_PACKET_H
#define SEND_PACKET_H


#include <general.h>
#include <global.h>
#include <log.h>

int	send_packet(unsigned char *msg, char *ip, int sock, struct GlobalData *data);


#endif
