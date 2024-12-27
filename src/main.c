#include <libft.h>
#include <stdio.h>
#include <ft_malcolm.h>
#include <parser.h>

void	write_sentence(int fd, char *s)
{
	for (unsigned long int i = 0; i < ft_strlen(s); i++)
		write(fd, &s[i], 1);
}



void print_target(struct Target t)
{
	write_sentence(1, "IP ADDRESS: ");
	write_sentence(1, t.ip_addr);
	write_sentence(1, "\n");
	write_sentence(1, "MAC ADDRESS: ");
	write_sentence(1, t.mac_addr);
	write_sentence(1, "\n");
	printf("Socket: %d\n", t.socket);
}


void print_source(struct Source t)
{
	write_sentence(1, "IP ADDRESS: ");
	write_sentence(1, t.ip_addr);
	write_sentence(1, "\n");
	write_sentence(1, "MAC ADDRESS: ");
	write_sentence(1, t.mac_addr);
	write_sentence(1, "\n");
	printf("Socket: %d\n", t.socket);
}

int fatal_error(int reason)
{
	if (reason == NARG_ERR)
		write_sentence(2, "Wrong number of arguments\n");
	else if (reason == IP_ERR)
		write_sentence(2, "Error in some ip address. Please, check both.\nFormat: q.q.q.q where q is value between 0 and 255\n");
	else if (reason == MAC_ERR)
		write_sentence(2, "Error in some mac address. Please, check both.\nFormat: ff:ff:ff:ff:ff:ff where ff represents a hexadecimal number\n");
	return (-1);
}	

int main(int argc, char **argv)
{
	struct Target	target;
	struct Source	source;
	int	parse_status;

	if (argc != 5 || argv[0] == NULL)
		return (fatal_error(NARG_ERR));
	parse_status = parse_args(&argv[1], &target, &source);
	if (parse_status != OK)
		return (fatal_error(parse_status));
	print_target(target);
	print_source(source);
	return (0);
}
