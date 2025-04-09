#ifndef	PROCESS_ARP_PACKET_H
#define PROCESS_ARP_PACKET_H

#include <global.h>
#include <general.h>

int	malcolm_process(unsigned char *buf,  struct GlobalData *d, int *n_bytes_ridden, char **argv);

#endif
