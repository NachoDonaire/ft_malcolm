#ifndef	LOG_H
#define LOG_H	

#include <general.h>
#include <global.h>

enum status_type{
	ERR = 0,
	ERR_NPARAMS,
	ERR_IP_INVALID_ST,
	ERR_IP_INVALID_ND,
	ERR_MAC_INVALID_ST,
	ERR_MAC_INVALID_ND,
	ERR_SOCK,
	ERR_RECVPACKET,
	ERR_PROTOCOL,
	OK
};

int	write_on_error(char *s);
void	print_addr(uint8_t *addr);
void	print_ip(uint32_t ip);
int	malcolm_log(char *s, uint8_t *mac, uint32_t ip, int *n_bytes, unsigned char *buf);
int	error_log(int error, char **argv);


#endif
