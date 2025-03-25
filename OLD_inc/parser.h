#ifndef PARSER_H
#define PARSER_H

struct Target {
	int	socket;
	char	*mac_addr;
	char	*ip_addr;
} ;


struct Source {
	int	socket;
	char	*mac_addr;
	char	*ip_addr;
} ;

int parse_args(char **argv, struct Target *t, struct Source *s);

#endif
