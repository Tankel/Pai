#include <iostream>
#include "Pai.h"
#include <unistd.h>

using namespace std;

int main()
{
    string name;
    int n;
    char r;
    Pai p;
    do
    {
      cout<<"Quieres nombrar a tu nuevo amigo? s/n\n";
      std::cin>>r;
      //p = Pai();
      p = Pai("Pai", 100, 3);
      if(r=='S' || r=='s')
      {
        cout<<"Ingrese el mote\n";
        std::cin>>name;
        p = Pai(name);
      }
    } while (r!='s' && r!='S' && r!='n' && r!='N');

    //Sleep(3000);
    p.run();
    
    //Sleep(3000);
    //cout<<p.getEnergia()<<endl;

}