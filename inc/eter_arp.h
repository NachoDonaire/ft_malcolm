#ifndef ETER_ARP_H
#define ETER_ARP_H

#define ADDR_LEN 6

typedef struct eter_arp {
	uint16_t	has;
	uint16_t	pas;
	uint8_t		hal;
	uint8_t		pal;
	uint16_t	opcode;
	uint8_t		sender_address[ADDR_LEN];
	uint32_t	sender_pro_address;
	uint8_t		target_address[ADDR_LEN];
	uint32_t	target_pro_address;
} eter_arp_t;


void	onetotwo(uint8_t wolfgang, uint8_t amadeus, uint16_t *m);
void	onetofour(uint8_t *wolfgangs, uint32_t *m);
void	packet_address(uint8_t *filled, uint8_t *msg);
void	fillfourbytes(uint8_t *laquesis, uint8_t *msg);
void	parse_arp_packet(unsigned char *msg, struct eter_arp *arp);
void	print_etarp(struct eter_arp etarp);

#endif
