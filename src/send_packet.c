#include <send_packet.h>
#include <sys/socket.h>

int	send_packet(unsigned char *msg, int sock, struct GlobalData *data)
{
	if (sendto(sock, msg, ARP_PACKET_SIZE, 0, (struct sockaddr *)&data->comminfo, (socklen_t )data->addrlen) < ZERO)
		return (ERR);
	return (OK);
}
