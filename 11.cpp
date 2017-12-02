#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define number long long int

using namespace std;

number gcd(number a, number b)
{
  if( a == 0 ) return b;
  if( b == 0 ) return a;
  return gcd(b, a%b);
}

number isprime(number a)
{
  for (number i = 2; i < a/2; i++)
    if( (a%i) == 0 )
      return 0;
  return 1;
}

number encrypt(char ch, number n, number e)
{
  number temp = ch;
  for (number i = 1; i < e; i++)
    temp = (temp*ch) % n;
  return ch;
}

char decrypt(number ch, number n, number d)
{
  number temp = ch;
  for (number i = 1; i < d; i++)
    ch = (temp*ch) % n;
  return ch;
}

int main(int argc, char const *argv[]) {
  number len, p, q, phi, n, e, d, chiper[50];
  char text[50];
  cout << "Enter the message" << '\n';
  cin.getline(text, sizeof(text));
  len = strlen(text);
  do{
    p = rand()%100;
  }while(!isprime(p));
  do{
    q = rand()%100;
  }while(!isprime(q));
  n = p * q;
  phi = (p-1) * (q-1);
  do {
    e = rand()%phi;
  } while(gcd(phi,e)!=1);
  do {
    d = rand()%phi;
  } while( (d*e)%phi !=1);
  cout << "\nTwo prime numbers are \np = "<< p << "\nq = " << q ;
  cout << "\nn = ( p * q ) : ( " << p << " * " << q << " ) = " << n ;
  cout << "\nPublic key ( n , e ) : ( " << n << " , " << e << " ) = " << n*e ;
  cout << "\nPrivate key ( n , d ) : ( " << n << " , " << d << " ) = " << n*d ;
  cout << "\nEncrypted message : ";
  for (number i = 0; i < len; i++)
  {
    chiper[i] = encrypt(text[i], n, e);
    cout << chiper[i] ;
  }
  cout << "\nDecrypted message : ";
  for (number i = 0; i < len; i++)
  {
    text[i] = encrypt(chiper[i], n, d);
    cout << text[i];
  }
  cout << '\n';
  return 0;
}
