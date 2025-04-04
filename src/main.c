#include <general.h>
#include <log.h>
#include <utils.h>
#include <global.h>
#include <arp_packet.h>
#include <eth_header.h>
#include <parser.h>

struct GlobalData data;

void	program_interruption()
{
	data.go_on = 0;
	close(data.raw_socket);
	write_on_error("\nInterruption detected. Stopping execution just right now...\n");
	return ;
}

int	initialize_data(struct sigaction *sigact, struct arp_packet *etharp, struct eth_header *ethdata, int *n_bytes_ridden, unsigned char *buf)
{
	sigact->sa_flags = 0;
	sigact->sa_handler = program_interruption;
	sigaction(SIGINT, sigact, NULL);

	*n_bytes_ridden = 0;

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (ERR_SOCK);

	ft_memset(etharp, 0, sizeof(struct arp_packet));
	ft_memset(ethdata, 0, sizeof(struct eth_header));
	ft_memset(buf, 0, sizeof(buf));

	return (OK);
}

int	protocol_cmp(uint16_t p1, uint16_t p2)
{
	if (p1 == p2)
		return (OK);
	return (ERR);
}

int	uint8cmp(uint8_t *a, uint8_t *b, size_t size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (a[i] != b[i])
			return (ERR);
	}
	return (OK);
}

int	macaddr_cmp(uint8_t *a, char *b)
{
	int		y;
	char		byte[THREE];

	y = 0;
	ft_memset(byte, 0, sizeof(byte));

	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (b[y] == ':')
			y++;
		sprintf(byte, "%02x", a[i]);
		if (byte[ZERO] != b[y] || byte[ONE] != b[y + ONE])
			return (ERR);
		ft_memset(byte, 0, sizeof(byte));
		y += 2;
	}
	
	return (OK);
}

int	ip_cmp(uint8_t *ip1, uint8_t *ip2)
{
	if (uint8cmp(ip1, ip2, sizeof(ip1)) != OK)
		return (ERR);
	return (OK);
}

int main(int argc, char **argv)
{
	struct	sigaction	sigact;
	unsigned char		buf[ARP_PACKET_SIZE];
	int			n_bytes_ridden;
	struct	arp_packet	etharp;
	struct	eth_header	ethdata;
	int			status;

	if (argc != 5)
		return (error_log(ERR_NPARAMS, argv));

	if ((status = parse_argv(argv, &data)) != OK)
		return (error_log(status, argv));

	if ((status = initialize_data(&sigact, &etharp, &ethdata, &n_bytes_ridden, buf)) <= 0)
		return (error_log(status, argv));
	
	while (data.go_on)
	{
		n_bytes_ridden = recvfrom(data.raw_socket, buf, ARP_PACKET_SIZE, 0, NULL, 0);

		if (!data.go_on)
			return (0);

		if (n_bytes_ridden < ETH_HEADER_SIZE)
			return (error_log(ERR_RECVPACKET, argv));
		else
		{
			parse_eth_header(buf, &ethdata);
			if ((!protocol_cmp(ethdata.protocol, ARP_PROTOCOL)))
				return (error_log(ERR_PROTOCOL, argv));
			if (!macaddr_cmp(ethdata.sender_ethaddr, data.target_addr))
			{
				malcolm_log("Got a packet from a different source than requested: ");
				print_addr(ethdata.sender_ethaddr);
				ft_memset(buf, 0, sizeof(buf));
			}
			else
			{
				print_eth_header(ethdata);
				printf("\n\n\n");
				parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);
				print_arpdata(etharp);
				data.go_on = -1;
				close(data.raw_socket);
			}
			

		}
	}

	return (0);
}
