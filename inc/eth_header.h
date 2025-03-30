#ifndef ETHER_HEADER_H
#define ETHER_HEADER_H

#include <general.h>
#include <global.h>


typedef struct eth_header {
	uint8_t		dest_ethaddr[ADDR_LEN];
	uint8_t		sender_ethaddr[ADDR_LEN];
	uint16_t	protocol;
} etherheader_t ;

void	print_eth_header(struct eth_header ethdr);
void	parse_eth_header(unsigned char *buf, struct eth_header *eth_header);



#endif
