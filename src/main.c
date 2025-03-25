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

	sprintf(outpt, "Fatal error ocurred: %d\n", errno);
	printf("%s", outpt);
	return (-1);
}

int main()
{
	struct sigaction sigact;


	sigact.sa_flags = 0;
	sigact.sa_handler = program_interruption;

	sigaction(SIGINT, &sigact, NULL);

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, 0)) < 0)
		fatal_error();

	while (data.go_on > 0)
	{
	}

	return (0);
}
