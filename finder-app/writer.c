
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  size_t len, written = 0;
  ssize_t ret;

  openlog("writer", LOG_PID, LOG_USER);

  if (argc != 3) {
    syslog(LOG_ERR, "Invalid arguments");
    closelog();
    return 1;
  }

  const char *filename = argv[1];
  const char *text = argv[2];

  syslog(LOG_DEBUG, "Writing %s to %s", text, filename);

  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    syslog(LOG_ERR, "open failed: %s", strerror(errno));
    closelog();
    return 1;
  }

  len = strlen(text);

  while (written < len) {
    ret = write(fd, text + written, len - written);

    if (ret == -1) {
      if (errno == EINTR)
        continue;

      syslog(LOG_ERR, "write failed: %s", strerror(errno));
      close(fd);
      closelog();
      return 1;
    }

    if (ret == 0) {
      syslog(LOG_ERR, "write returned zero");
      close(fd);
      closelog();
      return 1;
    }

    written += ret;
  }

  if (close(fd) == -1) {
    syslog(LOG_ERR, "close failed: %s", strerror(errno));
    closelog();
    return 1;
  }

  closelog();
  return 0;
}
