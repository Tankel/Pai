#include <iostream>
#include "Pai.h"
#include <unistd.h>

int main()
{
    std::string name;
    int n;
    char r;
    system("cls");
    Pai p;
    do
    {
      cout<<"Quieres nombrar a tu nuevo amigo? s/n\n";
      std::cin>>r;
      p = Pai();
      //p = Pai("Pai", 100, 1);
      if(r=='S' || r=='s')
      {
        cout<<"Ingrese el mote\n";
        std::cin>>name;
        p = Pai(name);
      }
    } while (r!='s' && r!='S' && r!='n' && r!='N');

    p.run();
    
    //cout<<p.getEnergia()<<endl;

}