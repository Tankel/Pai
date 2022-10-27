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
      cout<<"Do you want to name your new friend? y/n\n";
      std::cin>>r;
      p = Pai();
      //p = Pai("Pai", 100, 2, 0);
      //p = Pai("Pai", 2, 100, 0);
      //p = Pai("Pai", 100, 100, 60);
      if(r=='Y' || r=='y')
      {
        cout<<"Enter the nickname\n";
        std::cin>>name;
        p = Pai(name);
      }
    } while (r!='y' && r!='Y' && r!='n' && r!='N');

    p.run();
}