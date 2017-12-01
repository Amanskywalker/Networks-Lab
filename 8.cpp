// distance vector

#include <iostream>

using namespace std;

struct node{
  int dist[20];
  int from[20];
}route[10];

int main(int argc, char const *argv[]) {
  int dm[20][20], no;
  cout << "Enter the number of nodes \n";
  cin >> no;
  cout << "Enter the distance matrix \n";
  for (int i = 0; i < no; i++)
  {
    for (int j = 0; j < no; j++)
    {
      cin >> dm[i][j];
      route[i].dist[j] = dm[i][j];
      route[i].from[j] = j;
    }
  }
  int flag;
  do
  {
    flag = 0;
    for (int i = 0; i < no; i++)
    {
      for (int j = 0; j < no; j++)
      {
        for (int k = 0; k < no; k++)
        {
          if (route[i].dist[j] > route[i].dist[k] + route[k].dist[j])
          {
            route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
            route[i].from[j] = k;
            flag = 1;
          }
        }
      }
    }
  } while(flag);
  for (int i = 0; i < no; i++)
  {
    cout << "Route info for route : " << i+1 <<"\nDest\t Next Hop \t Dist \n";
    for (int j = 0; j < no; j++)
      cout << j+1 << "\t" << route[i].from[j]+1 << "\t" << route[i].dist[j] << "\n";
  }
  return 0;
}
