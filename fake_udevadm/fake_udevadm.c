#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <time.h>
#include <sys/time.h>

#define UEVENT_BUFFER_SIZE 2048

static int init_hotplug_sock()
{
	const int buffersize = 1024;
	int ret;

	struct sockaddr_nl snl;
	bzero(&snl, sizeof(struct sockaddr_nl));
	snl.nl_family = AF_NETLINK;
	snl.nl_pid = getpid();
	snl.nl_groups = 1;

	int s = socket(PF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
	if (s == -1) {
		perror("socket");
		return -1;
	}
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

	ret = bind(s, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
	if (ret < 0) {
		perror("bind");
		close(s);
		return -1;
	}

	return s;
}

int main(int argc, char* argv[])
{
	char DEVICE[] = "cpu";
	int hotplug_sock = init_hotplug_sock();
	char header[2048];
	char *s;
        struct timespec ts;

        /* only support "udevadm monitor --kernel --subsystem-match=cpu"*/ 
	if (argc != 4 || strcmp(argv[1], "monitor") || strcmp(argv[2], "--kernel") || strcmp(argv[3], "--subsystem-match=cpu")) {
		printf("This is a fake udevadm. This fake udevadm only supports \"udevadm monitor --kernel --subsystem-match=cpu\"\n");
		return -1;
	}

	while(1) {
		/* Netlink message buffer */
		char buf[UEVENT_BUFFER_SIZE * 2] = {0};
		int len = recv(hotplug_sock, &buf, sizeof(buf), 0);
		if (len <= 0)
			continue;

		if (strstr(buf, DEVICE) == NULL)
			continue;

		char action[64];
		char *p = buf;
		int i;
		for (i = 0; *p !='@'; i++, p++) {
			action[i] = *p;
		}
		action[i] = '\0';

		int j;
		char path[1024];
		p++;
		for (j = 0; *p != '\0'; j++, p++) {
			path[j] = *p;
		}
		path[j] = '\0';

        	clock_gettime(CLOCK_MONOTONIC, &ts);
		printf("%-6s[%llu.%06u] %-8s %s (%s)\n",
		       "KERNEL",
		       (unsigned long long) ts.tv_sec, (unsigned int) ts.tv_nsec/1000,
		       action,
		       path,
		       DEVICE
		);
		fflush(stdout);
	}

	return 0;
}
