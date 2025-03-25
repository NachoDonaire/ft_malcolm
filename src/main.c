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
	struct	ethhdr		ether_header;

	n_bytes_readen = 0;

	sigact.sa_flags = 0;
	sigact.sa_handler = program_interruption;
	sigaction(SIGINT, &sigact, NULL);

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, 0)) < 0)
		return (fatal_error());

	memset((struct ethhdr *)&ether_header, 0, sizeof(ether_header));
	while (data.go_on > 0)
	{
		n_bytes_readen = recvfrom(data.raw_socket, buf, ETH_HDR_LEN + 1, 0, NULL, 0);
		if (n_bytes_readen < 0)
			return (fatal_error());
		else
		{
			buf[n_bytes_readen] = 0;
			memcpy(&ether_header, buf, n_bytes_readen);
			printf("h_dest: %s\nh_source: %s\n", ether_header.h_dest, ether_header.h_source);
			data.go_on = -1;
		}
	}

	return (0);
}
