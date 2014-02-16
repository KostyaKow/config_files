#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/inotify.h>

void create_resolvconf(void)
{
  int fd = open("/etc/resolv.conf", O_CREAT | O_RDWR | O_TRUNC);

  const char* content = "nameserver 8.8.8.8\nnameserver 8.8.4.4\n";
  write(fd, content, strlen(content));

  close(fd);
}

int add_monitor(int fd)
{
  return inotify_add_watch(fd, "/etc/resolv.conf", IN_MODIFY | IN_DELETE | IN_CREATE);
}

void rm_monitor(int fd, int wd)
{
  inotify_rm_watch(fd, wd);
}

int main()
{
  create_resolvconf();
  int fd = inotify_init(), wd = add_monitor(fd);

  void* buff = malloc(2048);
  struct inotify_event event;

  while (1) {
    /* TODO: get all events, not just one */
    int n = read(fd, &event, sizeof(struct inotify_event));
    event = *(struct inotify_event*)buff;
    printf("\nevent\n");

    rm_monitor(fd, wd);
    create_resolvconf();
    wd = add_monitor(fd);

    usleep(999999);
  }

  //int f_resolv_conf = open("/etc/resolv.conf", O_CREAT | )

  return 0;
}
