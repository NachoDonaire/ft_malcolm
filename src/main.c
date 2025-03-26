#include <general.h>
#include <global.h>


Global data;

void	program_interruption()
{
	data.go_on = -1;
	close(data.raw_socket);
	printf("\nInterruption detected. Stopping execution just right now...\n");
	return ;
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
	int			buf_size = EA_HDR_LEN + ETH_ALEN * TWO + PROT_ADRESS * TWO;
	char			buf[buf_size + ONE];
	int			n_bytes_readen;
	struct	ether_arp	etharp;

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
	memset(buf, 0, sizeof(char));
	while (data.go_on > 0)
	{
		n_bytes_readen = recvfrom(data.raw_socket, buf, buf_size, 0, NULL, 0);
		printf("n_bytes: %d\n", n_bytes_readen);
		if (n_bytes_readen < 0)
			return (fatal_error());
		else
		{
			buf[n_bytes_readen] = 0;
			memcpy(&etharp, buf, sizeof(etharp));
			//etharp = (struct ether_arp )buf;
			//size_t var_size = sizeof(etharp.ea_hdr);
			//printf("joder ya estamos como chempre :)) : %lu\n", var_size);
			printf("adressida del sender: %x:%x:%x:%x:%x:%x\n", ((&etharp + 8)->arp_sha[0]), ((etharp).arp_sha[1]),((etharp).arp_sha[2]),((etharp).arp_sha[3]), ((etharp).arp_sha[4]),((etharp).arp_sha[5]));
			//printf("h_dest: %d\nh_source: %d\n", (eth_header.dst), ((eth_header + 6).src));
			data.go_on = -1;
		}
	}

	return (0);
}
