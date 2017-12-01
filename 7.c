//CRC-CGITT (16 bit)

#include <stdio.h>
#include <string.h>
#define N strlen(g)

char t[128], cs[128], g[]="10001000000100001";
int a,e,c;

void xor()
{
  for (c = 0; c < N; c++)
    cs[c] = (cs[c]==g[c]?'0':'1');
}

void crc()
{
  for(c = 0; c < N; c++)
    cs[c] = t[c];
  do
  {
    if (cs[0]=='1') xor();
    for (c = 0; c < N-1; c++)
      cs[c] = cs[c+1];
    cs[c] = t[e++];
  }while(e <= a+N-1);
}

int main(int argc, char const *argv[])
{
  printf("Enter Polynominal\n");
  scanf("%s", t);
  printf("Generating polynomial is %s\n", g);
  a = strlen(t);
  for (e = a; e < a+N-1; e++)
    t[e] = '0';
  printf("Modified t[u] is %s\n", t);
  crc();
  printf("Checksum is %s\n", cs);
  for (e = a; e < a+N-1; e++)
    t[e] = cs[e-a];
  printf("Final codeWord is %s\n", t);
  return 0;
}
