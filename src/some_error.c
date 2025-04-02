#include <some_error.h>
#include <unistd.h>

int	write_on_error(char *s)
{
	int i = 0;

	while (s[i])
		write(2, &s[i++], 1);
	return (-1);
}

int	some_error(int error)
{
	if (error == ERR_MAC_INVALID || error == ERR_MAC_LEN)
		return (write_on_error("Invalid MAC address\n"));
	else if (error == ERR_IP_INVALID || error == ERR_IP_LEN)
		return (write_on_error("Invalid IP address\n"));
	
	return (1);
}
