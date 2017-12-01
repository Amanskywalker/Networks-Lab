// leaky bucket
#include <stdio.h>
#include <stdlib.h>

int min(int x, int y)
{
  if(x < y) return x;
  return y;
}

int main(int argc, char const *argv[]) {
  int drop, mini, nsec, cap, count = 0, i, inp[25], process;
  printf("\nEnter bucket size : ");
  scanf("%d", &cap);
  printf("\nEnter transmission rate : ");
  scanf("%d", &process);
  printf("\nEnter the Simualtion Duration in seconds : ");
  scanf("%d", &nsec);
  for (i = 0; i < nsec; i++)
    inp[i] = rand()%100;
  printf("\nSecond | P recived | P sent | p Left | P dropped\n");
  printf("------------------------------------------------\n");
  for (i = 0; i < nsec; i++)
  {
    count = inp[i];
    if (count > cap)
    {
        drop =  count - cap;
        count = cap;
    }
    mini = min(count, process);
    count =  count - mini;
    printf("     %d |        %d |     %d |     %d |        %d\n", i+1, inp[i], mini, count, drop);
    drop = 0;
    sleep(1);
  }
  for (; count != 0; i++)
  {
    if (count > cap)
    {
        drop =  count - cap;
        count = cap;
    }
    mini = min(count, process);
    count =  count - mini;
    printf("     %d |        -  |     %d |     %d |        %d\n", i+1, mini, count, drop);
    drop = 0;
    sleep(1);
  }
  return 0;
}
