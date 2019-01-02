#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(void)
{
	int fd;
	int rc;
	struct sockaddr_in in;
	char buf[2000];

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		perror("socket");
		return 1;
	}

	memset(&in, 0, sizeof(in));
	in.sin_family = AF_INET;
	in.sin_port = htons(12345);
	in.sin_addr.s_addr = INADDR_ANY;
	rc = bind(fd, (struct sockaddr*)&in, sizeof(in));
	if (rc != 0)
	{
		perror("bind");
		return 1;
	}
	socklen_t len;
	rc = recvfrom(fd, (struct sockaddr*)&in, &len);
	if (rc < 0)
	{
		perror("recvfrom");
		return 1;
	}
	rc = connect(fd, (struct sockaddr*)&in, len);
}
