// FiFO
// server side
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
  char fname[50], buffer[1024];
  int req, res, n, file;
  mkfifo("req.fifo", 0777);
  mkfifo("res.fifo", 0777);
  printf("Waiting for the request\n");
  req = open("req.fifo", O_RDONLY);
  res = open("res.fifo", O_WRONLY);
  read(req, fname,sizeof(fname));
  printf("Recived request for : %s\n", fname);
  file = open(fname, O_RDONLY);
  if(file<0)
    write(res, "File not found\n", 15);
  else
  {
    while ((n = read(file, buffer, sizeof(buffer))) > 0)
      write(res, buffer, n);
  }
  close(req);
  close(res);
  unlink("req.fifo");
  unlink("res.fifo");
  return 0;
}
