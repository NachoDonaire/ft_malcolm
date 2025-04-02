#include <eth_header.h>
#include <arp_packet.h>
#include <global.h>
#include <general.h>
#include <utils.h>
#include <some_error.h>

int	check_arp(struct eth_header ethhdr)
{
	if (ethhdr.protocol != ARP_PROTOCOL)
		return (ERROR);
	return (OK);
}

int	carlton_banks(unsigned char *buf, struct arp_packet *arp, struct eth_header *eth,  int n_bytes_ridden)
{
	parse_eth_packet(buf, eth);
	if (eth.protocol != ARP_PROTOCOL)
		some_error(ARP_PROTOCOL);

	if (n_bytes_ridden != ARP_PACKET_SIZE)
		some_error(ARP_PACKET_SIZE);

	parse_arp_packet(buf + ETH_HEADER_SIZE, &eter_arp);
