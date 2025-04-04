#ifndef GLOBAL_H
#define GLOBAL_H

#define ARP_PACKET_SIZE 42
#define ETH_HEADER_SIZE 14
#define ADDR_LEN 6
#define ARP_PROTOCOL 2054
#define PROT_ADRESS 4
#define H_ADDR_L 6
#define MAC_LEN 17
#define TWO 2
#define ONE 1
#define FOUR 4
#define FIVE 5
#define ZERO 0
#define ADDR_LEN 6
#define THREE 3
#define ERROR -1

typedef struct GlobalData {
	int	raw_socket;
	int	go_on;
	char	*src_ip;
	char	*src_addr;
	char	*target_ip;
	char	*target_addr;
} Global;


#endif
