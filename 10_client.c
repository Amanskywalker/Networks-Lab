// FiFO
// client side
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
  char fname[50], buffer[1024];
  int req, res, n, file;
  req = open("req.fifo", O_WRONLY);
  res = open("res.fifo", O_RDONLY);
  if(req < 0 || res < 0)
    printf("Please star the server\n");
  printf("Enter the file name : ");
  scanf("%s",fname);
  write(req, fname, sizeof(fname));
  file = open(fname, O_RDONLY);
  printf("Recived respones\n");
  while ((n = read(res, buffer, sizeof(buffer))) > 0)
    write(1, buffer, n);
  close(req);
  close(res);
  return 0;
}
