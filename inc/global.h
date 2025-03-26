#ifndef GLOBAL_H
#define GLOBAL_H

#define ETH_HDR_LEN 14
#define EA_HDR_LEN 8
#define PROT_ADRESS 4
#define TWO 2
#define ONE 1

typedef struct {
	int raw_socket;
	int go_on;
} Global;

#endif
