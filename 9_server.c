// TCP/IP socket programming
// server code
 #include <stdio.h>
 #include <arpa/inet.h>
 #include <fcntl.h>
 #include <unistd.h>

 int main(int argc, char const *argv[])
{
  int soc, n, new_soc, fd;
  char buffer[1024], fname[50];
  struct sockaddr_in addr;

  soc = socket(PF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(4567);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(soc, (struct sockaddr *) &addr, sizeof(addr));
  printf("Server Online\n");

  listen(soc, 5);

  new_soc = accept(soc, NULL, NULL);

  recv(new_soc, fname, 50, 0);
  printf("\n Requesting for the file : %s", fname );

  fd = open(fname, O_RDONLY);

  if (fd < 0)
    send (new_soc, "\n file not found\n", 20, 0);
  else
    while ((n = recv(soc, buffer, sizeof(buffer),0))>0)
      printf("%s",buffer);

  printf("Request send\n");

  return 0;
}
