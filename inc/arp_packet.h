#ifndef ARP_PACKET_H
#define ARP_PACKET_H

#include <global.h>
#include <general.h>
#include <log.h>

#define	REQUEST	1
#define	REPLY	2
#define	HAS	1
#define	PAS	2048
#define	HAL	6
#define	PAL	4

typedef struct arp_packet {
	uint16_t	has;
	uint16_t	pas;
	uint8_t		hal;
	uint8_t		pal;
	uint16_t	opcode;
	uint8_t		sender_address[ADDR_LEN];
	uint32_t	sender_pro_address;
	uint8_t		target_address[ADDR_LEN];
	uint32_t	target_pro_address;
} arp_packet_t;


void	parse_arp_packet(unsigned char *msg, struct arp_packet *arp);
void	print_arpdata(struct arp_packet etarp);
void	cpy_ip(unsigned char *dst, char *ip);
int	generate_arp_packet(char *dest_addr, char *dest_ip, char *src_addr, char *src_ip, uint16_t opcode, unsigned char *packet);

#endif
