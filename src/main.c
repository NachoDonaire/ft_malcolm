#include <general.h>
#include <some_error.h>
#include <global.h>
#include <arp_packet.h>
#include <eth_header.h>
#include <parser.h>

struct GlobalData data;

void	program_interruption()
{
	data.go_on = -1;
	close(data.raw_socket);
	printf("\nInterruption detected. Stopping execution just right now...\n");
	return ;
}

void	print_raw_msg(unsigned char *msg, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
		printf("%u, ", ntohs(msg[i++]));
	printf("\n");
}

int fatal_error()
{
	char outpt[1024];

	if (data.go_on > 0)
	{
		sprintf(outpt, "Fatal error ocurred: %d\n", errno);
		write_on_error(outpt);
	}
	else
	{
		sprintf(outpt, "Usage:\n1.Target IP\n2.Target MAC Address\n3.Source IP\n4.Source MAC Address\n\n");
		write_on_error(outpt);
	}

	return (-1);
}

int	initialize_data(struct sigaction *sigact, struct arp_packet *etharp, struct eth_header *ethdata, int *n_bytes_ridden, unsigned char *buf)
{
	sigact->sa_flags = 0;
	sigact->sa_handler = program_interruption;
	sigaction(SIGINT, sigact, NULL);

	*n_bytes_ridden = 0;

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (fatal_error());

	ft_memset(etharp, 0, sizeof(struct arp_packet));
	ft_memset(ethdata, 0, sizeof(struct eth_header));
	ft_memset(buf, 0, sizeof(buf));

	return (1);
}

int main(int argc, char **argv)
{
	struct	sigaction	sigact;
	int			buf_size = ARP_PACKET_SIZE + ONE;
	unsigned char		buf[buf_size];
	int			n_bytes_ridden;
	struct	arp_packet	etharp;
	struct	eth_header	ethdata;

	if (argc != 5)
		return (fatal_error());

	if (parse_argv(argv, &data) != OK)
		return (-1);

	if (initialize_data(&sigact, &etharp, &ethdata, &n_bytes_ridden, buf) <= 0)
		return (fatal_error());
	
	while (data.go_on > 0)
	{
		n_bytes_ridden = recvfrom(data.raw_socket, buf, buf_size, 0, NULL, 0);
		//printf("n_bytes: %d\n", n_bytes_ridden);
		if (n_bytes_ridden < ETH_HEADER_SIZE)
			return (fatal_error());
		else
		{
			/*
			parse_eth_header(buf, &ethdata);
			print_eth_header(ethdata);
			printf("\n\n\n");
			parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);
			print_arpdata(etharp);
			data.go_on = -1;
			close(data.raw_socket);
			*/

		}
	}

	return (0);
}
