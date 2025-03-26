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
	char			buf[ETH_HDR_LEN];
	int			n_bytes_readen;
	struct	arphdr		arp_header;

	n_bytes_readen = 0;

	sigact.sa_flags = 0;
	sigact.sa_handler = program_interruption;
	sigaction(SIGINT, &sigact, NULL);

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (fatal_error());

	memset((struct arphdr *)&arp_header, 0, sizeof(arp_header));
	memset(buf, 0, sizeof(char));
	while (data.go_on > 0)
	{
		n_bytes_readen = recvfrom(data.raw_socket, buf, ETH_HDR_LEN + 1, 0, NULL, 0);
		printf("n_bytes: %d\n", n_bytes_readen);
		if (n_bytes_readen < 0)
			return (fatal_error());
		else
		{
			buf[n_bytes_readen] = 0;
			memcpy(&arp_header, buf, n_bytes_readen);
			printf("h_dest: %d\nh_source: %d\n", arp_header.ar_hrd, arp_header.ar_pro);
			data.go_on = -1;
		}
	}

	return (0);
}
