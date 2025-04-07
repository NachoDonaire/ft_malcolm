#include <send_packet.h>
#include <sys/socket.h>

int	send_packet(unsigned char *msg, char *ip, int sock, struct GlobalData *data)
{
	(void)ip;
	
	//struct sockaddr_ll	dest;
	//socklen_t		addrlen;

	//dest.sin_family = AF_INET;
	//dest.sin_port = htons(12345);
	//inet_pton(AF_INET, ip, &dest.sin_addr);


	printf("AHI VA EL MSG DE VUELTA\n\n");
	for (int i = 0; i < ARP_PACKET_SIZE; i++)
		write(1, &msg[i], 1);
	printf("\n\n");
	if (sendto(sock, msg, ARP_PACKET_SIZE, 0, (struct sockaddr *)&data->comminfo, (socklen_t )data->addrlen) < ZERO)
		return (ERR);
	return (OK);
}
