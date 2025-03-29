#include <general.h>
#include <global.h>
#include <eter_arp.h>


Global data;

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
	

void	print_data(char *dt, unsigned long t)
{
	unsigned int i;

	i = 0;
	while (i < t)
		printf("%02x, ", dt[i++]);
	/*i = 0;
	while (i < t)
		printf("%d, ", dt[i++]);
		*/
	printf("\n");
}

int fatal_error()
{
	char outpt[1024];

	if (data.go_on > 0)
	{
		sprintf(outpt, "Fatal error ocurred: %d\n", errno);
		printf("%s", outpt);
	}
	return (-1);
}

int main()
{
	struct	sigaction	sigact;
	int			buf_size = ARP_PACKET_SIZE;
	unsigned char		buf[buf_size + ONE];
	int			n_bytes_readen;
	struct	eter_arp	etharp;

	n_bytes_readen = 0;

	sigact.sa_flags = 0;
	sigact.sa_handler = program_interruption;
	sigaction(SIGINT, &sigact, NULL);

	//(void)eth_header;
	//printf("tamanio: %lu\n", sizeof(struct	ether_arp));
	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (fatal_error());

	//etharp = NULL;
	//memset((struct ethhdr *)eth_header, 0, sizeof(struct ethhdr ));
	memset(&etharp, 0, sizeof(struct eter_arp));
	memset(buf, 0, sizeof(buf));
	while (data.go_on > 0)
	{
		n_bytes_readen = recvfrom(data.raw_socket, buf, buf_size, 0, NULL, 0);
		printf("n_bytes: %d\n", n_bytes_readen);
		if (n_bytes_readen < 0)
			return (fatal_error());
		else
		{
			buf[n_bytes_readen + ONE] = 0;
			print_raw_msg(buf, n_bytes_readen);
			parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);
			print_etarp(etharp);
			data.go_on = -1;
			close(data.raw_socket);
		}
	}

	return (0);
}
