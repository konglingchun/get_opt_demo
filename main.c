#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

static void usage(FILE *fp, int argc, char **argv)
{
	fprintf(fp,
		 "Usage: %s [options]\n"
		 "Options:\n"
		 "-h | --help          Print this message\n"\
		 "-i | --ip            Set ip address\n"\
		 "-p | --port          Set tcp port\n"\
		 "-a | --address       Set address\n",
		 argv[0]);
}

static const char short_options[] = "hi:p:a:";

static const struct option long_options[] = {
	{ "help",   no_argument,       NULL, 'h' },
	{ "ip",	required_argument,	0,	'i' },
	{ "port",	required_argument,	0,	'p' },
	{ "address",	required_argument,	0,	'a' },
	{ 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
	char *g_server_ip = NULL;
	int g_server_port = 19748;
	unsigned int address;
	
	for (;;) {
		int idx;
		int c;

		c = getopt_long(argc, argv,
				short_options, long_options, &idx);

		if (-1 == c)
			break;

		switch (c) {
		case '?': /* getopt_long() flag */
			usage(stderr, argc, argv);
			exit(EXIT_FAILURE);
			break;

		case 'i':
			g_server_ip = strdup(optarg);
			printf("set server ip = %s\n", g_server_ip);
			break;
			
		case 'p':
			g_server_port = atoi(optarg);
			printf("set server port = %d\n", g_server_port);
			break;

		case 'a':
			sscanf(optarg, "%x", &address);
			printf("set device address = %#04x\n", address);
			break;
			
		case 'h':
		default:
			usage(stderr, argc, argv);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
