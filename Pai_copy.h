#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <pthread.h>
#include <thread>
#include "archivos.h"
#include <time.h> 
#include <cstdio>
#include <map>
#include <conio.h>

using namespace std;

#define UP 72
#define DOWN 80
#define ENTER 0x0D
//std:: mutex mu
//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
bool estaOcupado = false;
bool estaJugando = false;
bool op1;
bool op2;
bool op3;
int myMove; //piedra papel o tijera
int index = 0;

class Pai //INCLUIIIIIIIIIIIIIR PTHREAD_EXIT(NUll)
{
    private:
        string nombre; 
        static std::map<string,int> data;/*int edad, int hambre, int energia*/
        std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
        pthread_t thread1; //reposo
        pthread_t thread2; //energia
        pthread_t thread3; //hambre
        pthread_t thread4; //edad
        pthread_t thread5; //dormir
        pthread_t thread6; //input
        pthread_t thread7; //comer
        pthread_t thread8; //jugar
    public:
        Pai():nombre("Pai"){data["edad"]=0;data["hambre"]=100;data["energia"]=100;};
        Pai(string _name, int _energia, int _hambre):nombre(_name){data["edad"]=0;data["hambre"]=_hambre;data["energia"]=_energia;};        
        Pai(string _name): nombre(_name){data["edad"]=0;data["hambre"]=100;data["energia"]=100;};
        string getNombre(){return nombre;};
        int getEdad()
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
            return chrono::duration_cast<chrono::seconds>(end - start).count()/90; //cumple 1 anio cada 3min
        };
        int getHambre(){return data["hambre"];};
        int getEnergia(){return data["energia"];};
        void setEnergia(int _energia){data["energia"] = _energia;};
        void setEdad(int _edad){data["edad"] = _edad;};
        void setHambre(int _hambre){data["hambre"] = _hambre;};
        void comer();
        void dormir();
        void jugar();
        void run();
        void threadReposo();
        void threadEnergia();
        void threadHambre();
        void threadEdad();
        void input();
        static void* ex_threadEnergia(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> threadEnergia();
        };
        static void* ex_threadHambre(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> threadHambre();
        };
        static void* ex_threadEdad(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> threadEdad();
        };
        static void* ex_threadReposo(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> threadReposo();
        };
        static void* ex_threadDormir(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> dormir();
        };
        static void* ex_threadComer(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> comer();
        };
        static void* ex_threadInput(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> input();
        };
        static void* ex_threadJugar(void * This)
        {
            Pai* cptr = (Pai*)This;
            cptr -> jugar();
        };
};
std::map<string,int> Pai::data;
void Pai::threadEnergia()//HILO
{
    while(getHambre()>0 && getEnergia()>0 && !estaOcupado)
    {
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",13," ENERGIA: "+to_string(getEnergia())); //\r
        pthread_mutex_unlock( &mutex1 );
        Sleep(7102);
        setEnergia(getEnergia()-1);
    }
    pthread_exit(NULL);
};
void Pai::threadHambre()//HILO
{
    while(getHambre()>0 && getEnergia()>0 && !estaOcupado)
    {
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",14," HAMBRE: "+to_string(getHambre())); //\r
        pthread_mutex_unlock( &mutex1 );
        Sleep(5001);
        setHambre(getHambre()-1);
        if(getHambre()<1)
        {
            pthread_mutex_lock( &mutex1 );
            printSprite("GameOver.txt",200);
            system("pause");
            exit(3);
            pthread_mutex_unlock( &mutex1 );
        }
    }
    pthread_exit(NULL);
};
void Pai::threadEdad()//HILO
{
    int muerte = rand()%100 + 50;
    while(getHambre()>0 && getEnergia()>0 && !estaOcupado)
    {
        setEdad(getEdad());
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",3," EDAD: "+to_string(getEdad())); //\r
        pthread_mutex_unlock( &mutex1 );
        Sleep(4500);
        if(getEdad()>muerte)
        {
            printSprite("GameOver.txt",200);
            system("pause");
            exit(3);
        }
    }
    pthread_exit(NULL);
};
void Pai::threadReposo()//HILO
{
    while(getHambre()>0 && getEnergia()>0 &&!estaOcupado)
    {
        for(int i=0; i<8; i++)
        {
            pthread_mutex_lock( &mutex1 );            
            replace_line("PaiN.txt",8,"[]               | |_|  v  |_| |               []");
            replace_line("PaiN.txt",7,"[]               |  _       _  |               []");
            system("cls");
            printASCII("PaiN.txt");
            pthread_mutex_unlock( &mutex1 );
            Sleep(1000);
            if(op1 == true)
            {
                pthread_create( &thread7, NULL, ex_threadComer, this);
                pthread_join(thread7, NULL);
            }
            if(getEnergia()<1 || op2 == true)
            {
                pthread_create( &thread5, NULL, ex_threadDormir, this);
                pthread_join(thread5, NULL);
            }
            if(op3 == true)
            {
                pthread_create( &thread8, NULL, ex_threadJugar, this);
                pthread_join(thread8, NULL);
            }
        }
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",8,"[]               | -.-  v  -.- |               []");
        replace_line("PaiN.txt",7,"[]               |             |               []");
        system("cls");
        printASCII("PaiN.txt");
        pthread_mutex_unlock( &mutex1 );
        Sleep(220);
    }
    pthread_exit(NULL);
};
void Pai::dormir()//HILO
{
    if(!estaOcupado)
    {
    estaOcupado = true;
    while(getEnergia()<100)
    {
        system("cls");
        for(int i=1; i<4; i++)
        {
            std::string str = "PaiSleep"+to_string(i)+".txt";
            const char * nameFile = str.c_str();
            replace_line(nameFile,13," ENERGIA: "+to_string(getEnergia())); //\r
            printSprite(nameFile,260);
            if(getEnergia()<100)
                setEnergia(getEnergia()+1);
            //del_line(nameFile,13);
        }
    }
    system("cls");
    estaOcupado = false;
    //op2 = false;
    //pthread_exit(NULL);
    run();
    }
    //pthread_exit(NULL);
}
void Pai::comer()//HILO
{
    //jei
    //ssssssssssssss
    if(!estaOcupado)
    {
    estaOcupado = true;
    for(int i=1; i<14; i++)
    {
        printSprite("PaiEat"+to_string(i)+".txt",100);
    }
    for(int i=0; i<4; i++)
    {
        printSprite("PaiEat15.txt",150);
        printSprite("PaiEat16.txt",150);
    }
    printSprite("PaiEat17.txt",100);
    printSprite("PaiEat18.txt",100);

    setHambre(getHambre()+30);
    if(getHambre()>99)
        setHambre(100);

    system("cls");
    estaOcupado = false;
    //op1=false;
    //pthread_exit(NULL);
    run();
    }
    //pthread_exit(NULL);
}
void Pai::input()//HILO
{
    op1 = false;
    op2 = false;
    op3 = false;
    int index2=0;
    while(true)
    {
        char n,m, c;
        if(estaOcupado)
        {
            //index2=0;
            //myMove = int(n-'0');
            m='a';
            while(m!=ENTER)
            {
            //m='1';
            switch (m=getch())
            {
                //cout<<n<<endl;
                case UP:{index2--;break;}
                case DOWN:{index2++;break;}
                case ENTER:{myMove=index2+1;break;}
                default:break;
            }
            if(index2<0)index2=2;
            else if(index2>2) index2=0;

            //cout<<index<<endl;
            switch (index2)
            {
            case 0:
            {
                //op1 = true;
                pthread_mutex_lock( &mutex1 );     
                replace_line("PaiPPJ1.txt",16,"< 1 - Rock >");
                replace_line("PaiPPJ1.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ1.txt",18,"  3 - Scissor");
                replace_line("PaiPPJ2.txt",16,"< 1 - Rock >");
                replace_line("PaiPPJ2.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ2.txt",18,"  3 - Scissor  ");
                replace_line("PaiPPJ3.txt",16,"< 1 - Rock >");
                replace_line("PaiPPJ3.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ3.txt",18,"  3 - Scissor  ");
                pthread_mutex_unlock( &mutex1 );  
                break;
            }
            case 1:
            {
                //op2 = true;
                pthread_mutex_lock( &mutex1 );  
                replace_line("PaiPPJ1.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ1.txt",17,"< 2 - Paper >");
                replace_line("PaiPPJ1.txt",18,"  3 - Scissor  ");
                replace_line("PaiPPJ2.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ2.txt",17,"< 2 - Paper >");
                replace_line("PaiPPJ2.txt",18,"  3 - Scissor  ");
                replace_line("PaiPPJ3.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ3.txt",17,"< 2 - Paper >");
                replace_line("PaiPPJ3.txt",18,"  3 - Scissor  ");
                pthread_mutex_unlock( &mutex1 );  
                break;
            }
            case 2:
            {
                //op3 = true;
                pthread_mutex_lock( &mutex1 );  
                replace_line("PaiPPJ1.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ1.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ1.txt",18,"< 3 - Scissor >");
                replace_line("PaiPPJ2.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ2.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ2.txt",18,"< 3 - Scissor >");
                replace_line("PaiPPJ3.txt",16,"  1 - Rock  ");
                replace_line("PaiPPJ3.txt",17,"  2 - Paper ");
                replace_line("PaiPPJ3.txt",18,"< 3 - Scissor >");
                pthread_mutex_unlock( &mutex1 );  
                break;
            }
            }
            } 
            myMove=index2+1;
        }
        n='1';
        do
        {
        switch (n=getch())
        {
            //cout<<n<<endl;
            case UP:{index--;break;}
            case DOWN:{index++;break;}
            case ENTER:
            {
                switch (index)
                {
                    case 0:
                    {
                        c = '1';
                        op1 = true;
                    }
                    case 1:
                    {
                        c = '2';
                        op2 = true;
                    }
                    case 2:
                    {
                        c = '3';
                        op3 = true;
                    }
                }
            }
        }
        if(index<0)index=2;
        else if(index>2) index=0;
        if(estaJugando)break;
        //cout<<index<<endl;
        switch (index)
        {
        case 0:
        {
            //op1 = true;
            pthread_mutex_lock( &mutex1 );     
            replace_line("PaiN.txt",16,"< 1 - Feed >");
            replace_line("PaiN.txt",17,"  2 - Sleep ");
            replace_line("PaiN.txt",18,"  3 - Play  ");
            pthread_mutex_unlock( &mutex1 );  
            break;
        }
        case 1:
        {
            //op2 = true;
            pthread_mutex_lock( &mutex1 );  
            replace_line("PaiN.txt",16,"  1 - Feed  ");
            replace_line("PaiN.txt",17,"< 2 - Sleep >");
            replace_line("PaiN.txt",18,"  3 - Play  ");
            pthread_mutex_unlock( &mutex1 );  
            break;
        }
        case 2:
        {
            //op3 = true;
            pthread_mutex_lock( &mutex1 );  
            replace_line("PaiN.txt",16,"  1 - Feed  ");
            replace_line("PaiN.txt",17,"  2 - Sleep ");
            replace_line("PaiN.txt",18,"< 3 - Play >");
            pthread_mutex_unlock( &mutex1 );  
            break;
        }
        default:break;;
        }
        
        /*
        char n;
        std::cin>>n;
        if(estaOcupado) myMove = int(n-'0');
        switch (n){
        case '1':{op1 = true;break;}
        case '2':{op2 = true;break;}
        case '3':{op3 = true;break;}
        default:break;}*/
        //}
        }while(n!=ENTER);
    }
    pthread_exit(NULL);
}
void Pai::jugar()
{
    estaJugando = true;
    if(!estaOcupado)
    {
    estaOcupado = true;
    srand (time(NULL));
    int paiMove = rand()%3 + 1;
    //cout<<paiMove<<endl;
    myMove =-1;
    int g;
    Sleep(100);
    while(myMove==-1)
    {
        estaJugando = true;
        printSprite("PaiPPJ1.txt",1001);
        printSprite("PaiPPJ2.txt",1001);
        printSprite("PaiPPJ3.txt",1001);
    };
    std::string str2 = "PaiPPJ"+to_string(paiMove)+".txt";
    const char * nameFile2 = str2.c_str();
    printSprite(str2,1000);

    if(myMove==paiMove)g=0;
    else if((myMove==1&&paiMove==3)||(myMove==2&&paiMove==1)||(myMove==3&&paiMove==2))g=1;
    else if((myMove==3&&paiMove==1)||(myMove==1&&paiMove==2)||(myMove==2&&paiMove==3))g=2;

    if(g==0)replace_line(nameFile2, 2, "\t\t      EMPATE"); 
    else if(g==1)replace_line(nameFile2, 2, "\t\t    HAS GANADO"); 
    else if(g==2)replace_line(nameFile2, 2, "\t\t   HAS PERDIDO"); 
    printSprite(str2,3400);
    system("cls");
    del_line(nameFile2,2);

    estaOcupado = false;
    estaJugando = false;
    op3 = false;
    pthread_exit(NULL);
    //run();
    }
}
void Pai::run()
{  
    replace_line("PaiN.txt", 2, " NOMBRE: "+getNombre());
    replace_line("PaiRespaldo.txt", 2, " NOMBRE: "+getNombre());

    pthread_create( &thread1, NULL, ex_threadReposo, this); 
    pthread_create( &thread2, NULL, ex_threadEnergia, this);
    pthread_create( &thread3, NULL, ex_threadHambre, this);
    pthread_create( &thread4, NULL, ex_threadEdad, this);
    pthread_create( &thread6, NULL, ex_threadInput, this);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread6, NULL);
}