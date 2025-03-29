#ifndef GLOBAL_H
#define GLOBAL_H

#define ARP_PACKET_SIZE 42
#define ETH_HEADER_SIZE 14
#define EA_HDR_LEN 8
#define PROT_ADRESS 4
#define H_ADDR_L 6
#define TWO 2
#define ONE 1
#define FOUR 4
#define FIVE 5

typedef struct {
	int raw_socket;
	int go_on;
} Global;

#endif
