// TCP/IP socket programming
// client code
 #include <stdio.h>
 #include <arpa/inet.h>
 #include <fcntl.h>
 #include <unistd.h>

 int main(int argc, char const *argv[])
{
  int soc, n;
  char buffer[1024], fname[50];
  struct sockaddr_in addr;

  soc = socket(PF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(4567);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (connect(soc, (struct sockaddr *) &addr, sizeof(addr)));

  printf("connected to server\n");
  printf("Enter the file name : ");
  scanf("%s",fname);
  send(soc, fname, sizeof(fname), 0);
  printf("\nRecived response \n");
  while ((n = recv(soc, buffer, sizeof(buffer),0))>0)
    printf("%s",buffer);
  return 0;
}
