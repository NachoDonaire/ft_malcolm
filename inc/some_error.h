#ifndef	SOME_ERROR_H
#define	SOME_ERROR_H

enum error_type{
	ERR_IP_INVALID = -4,
	ERR_IP_LEN,
	ERR_MAC_LEN,
	ERR_MAC_INVALID,
};

int	some_error(int error);
int	write_on_error(char *s);


#endif
