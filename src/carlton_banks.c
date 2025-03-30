#include <eter_arp.h>

int	check_arp(struct eth_header ethhdr)
{
	if (ethhdr.protocol != ARP_PROTOCOL)
		return (ERROR);
	return (OK);
}

int	carlton_banks(unsigned char *buf, struct arp_packet *arp, struct eth_header *eth,  int n_bytes_ridden)
{
	parse_arp_packet(buf + ETH_HEADER_SIZE, &eter_arp);
