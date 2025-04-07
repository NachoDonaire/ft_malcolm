#ifndef UTILS_H
#define UTILS_H


#include <general.h>
#include <global.h>
#include <arp_packet.h>


void		onetotwo(uint8_t wolfgang, uint8_t amadeus, uint16_t *m);
void		onetofour(uint8_t *wolfgangs, uint32_t *m);
void		packet_address(uint8_t *filled, uint8_t *msg);
void		fillfourbytes(uint8_t *laquesis, uint8_t *msg);
int		protocol_cmp(uint16_t p1, uint16_t p2);
uint32_t	get_ippos(unsigned int pos, uint32_t rawson);
int		macaddr_cmp(uint8_t *a, char *b);
int		check_request(struct arp_packet etharp, char *ip);
int		is_broadcast(uint8_t *mac);


#endif
