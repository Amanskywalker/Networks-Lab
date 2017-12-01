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
  printf("Enter Polynominal : ");
  scanf("%s", t);
  printf("\nGenerating polynomial is : %s", g);
  a = strlen(t);
  for (e = a; e < a+N-1; e++)
    t[e] = '0';
  printf("\nModified t[u] is : %s", t);
  crc();
  printf("\nChecksum is : %s", cs);
  for (e = a; e < a+N-1; e++)
    t[e] = cs[e-a];
  printf("\n Final codeWord is : %s", t);
  printf("\nTest for the error detection 1(yes)|0(no) ?");
  scanf("%d", &e);
  if (e==1)
  {
    printf("\nenter the position wher erroe to be inserted : ");
    scanf("%d",&e);
    t[e] = ((t[e]=='0')?'1':'0');
    printf("\nDate with error is %s \n",t);
  }
  crc();
  for(e = 0; (e < N-1) && (cs[e]!='1') ; e++ )
  if (e < N-1)
    printf("error\n");
  else
    printf("No error\n");
  return 0;
}
