#include <eth_header.h>
#include <utils.h>

void	print_eth_header(struct eth_header ethdr)
{
	printf("dest address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%02x\n", ethdr.dest_ethaddr[i]);
		else
			printf("%02x:", ethdr.dest_ethaddr[i]);
	}
	printf("sender address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%02x\n", ethdr.sender_ethaddr[i]);
		else
			printf("%02x:", ethdr.sender_ethaddr[i]);
	}
	printf("Protocol: 0x%x\n", ethdr.protocol);
}


void	parse_eth_header(unsigned char *buf, struct eth_header *eth_header)
{
	unsigned char *msg;

	msg = buf;

	packet_address(eth_header->dest_ethaddr, msg);
	msg += ADDR_LEN;

	packet_address(eth_header->sender_ethaddr, msg);
	msg += ADDR_LEN;

	onetotwo(*msg, *(msg + 1), &eth_header->protocol);
}
