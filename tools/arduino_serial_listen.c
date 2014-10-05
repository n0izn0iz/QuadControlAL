#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
	char buf;
	int port;
	int n;
	int sum;
	struct termios settings;

	if (argc < 2) {
		fprintf(stderr, "Usage:   serial_listen <port>\n");
		fprintf(stderr, "Example: serial_listen /dev/ttyACM0\n");
		return 1;
	}

	// Open the serial port
	port = open(argv[1], O_RDWR);
	if (port < 0) {
		fprintf(stderr, "Unable to open %s\n", argv[1]);
		return 1;
	}

	// Configure the port
	tcgetattr(port, &settings);
	cfmakeraw(&settings);
	tcsetattr(port, TCSANOW, &settings);

	// Read data until we get a see the end string or get an error
	printf("Reading from %s\n", argv[1]);
	while (1) {
		n = read(port, &buf, sizeof(buf)); 
		if (n > 0) {
			printf("%c", buf);
			sum += n;
		}
		else if(n < 0)
			break;
	}

	close(port);
	printf("Total bytes read: %ld\n", sum);
	printf("Speed %.2f kbytes/sec\n", sum / 10000.0);
	return 0;
}


