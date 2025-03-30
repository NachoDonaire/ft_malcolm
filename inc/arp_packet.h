#ifndef ETER_ARP_H
#define ETER_ARP_H


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

#endif
