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

using namespace std;

bool estaOcupado = false;
bool estaJugando = false;
bool op1;
bool op2;
bool op3;
int myMove; //piedra papel o tijera

class Pai
{
    private:
        string nombre; 
        static std::map<string,int> data;/*int edad, int hambre, int energia*/
        std::chrono::steady_clock::time_point start = chrono::steady_clock::now(); //empieza el tiepo
        pthread_t thread1; //reposo
        pthread_t thread2; //energia
        pthread_t thread3; //hambre
        pthread_t thread4; //edad
        pthread_t thread5; //dormir
        pthread_t thread6; //input
        pthread_t thread7; //comer
        pthread_t thread8; //jugar
    public:
        Pai():nombre("Pai")
        {
            data["edad"]=0;
            data["hambre"]=100;
            data["energia"]=100;
        };
        Pai(string _name, int _energia, int _hambre, int _edad):nombre(_name)
        {
            data["edad"]=_edad;
            data["hambre"]=_hambre;
            data["energia"]=_energia;
        };        
        Pai(string _name): nombre(_name)
        {
            data["edad"]=0;
            data["hambre"]=100;
            data["energia"]=100;
        };
        string getNombre(){return nombre;};
        int getEdad()
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
            return chrono::duration_cast<chrono::seconds>(end - start).count()/60; //cumple 1 anio cada 1min
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
    while(getHambre()>0 && getEnergia()>0)
    {
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",13," ENERGY: "+to_string(getEnergia())); //\r
        pthread_mutex_unlock( &mutex1 );
        Sleep(7102);
        setEnergia(getEnergia()-1);
    }
    pthread_exit(NULL);
};
void Pai::threadHambre()//HILO
{
    while(getHambre()>0 && getEnergia()>0)
    {
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",14," HUNGRY: "+to_string(getHambre())); //\r
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
    int muerte = rand()%20 + 60;
    while(getHambre()>0 && getEnergia()>0)
    {
        setEdad(getEdad());
        pthread_mutex_lock( &mutex1 );
        replace_line("PaiN.txt",3," AGE: "+to_string(getEdad())); //\r
        pthread_mutex_unlock( &mutex1 );
        //Sleep(4500);
        Sleep(1001);
        if(getEdad()>muerte)
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
void Pai::threadReposo()//HILO
{
    int res;
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
                res = pthread_create( &thread7, NULL, ex_threadComer, this);
                if(res != 0){
                    pthread_mutex_lock( &mutex1 );
                    printSprite("Error.txt",10000);
                    exit(EXIT_FAILURE);
                    pthread_mutex_unlock( &mutex1 );
                }
                pthread_join(thread7, NULL);
            }
            if(getEnergia()<1 || op2 == true)
            {
                res = pthread_create( &thread5, NULL, ex_threadDormir, this);
                if(res != 0){
                    pthread_mutex_lock( &mutex1 );
                    printSprite("Error.txt",10000);
                    exit(EXIT_FAILURE);
                    pthread_mutex_unlock( &mutex1 );
                }
                pthread_join(thread5, NULL);
            }
            if(op3 == true)
            {
                res = pthread_create( &thread8, NULL, ex_threadJugar, this);
                if(res != 0){
                    pthread_mutex_lock( &mutex1 );
                    printSprite("Error.txt",10000);
                    exit(EXIT_FAILURE);
                    pthread_mutex_unlock( &mutex1 );
                }
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
            replace_line(nameFile,13," ENERGY: "+to_string(getEnergia())); //\r
            printSprite(nameFile,421);
            if(getEnergia()<100)
                setEnergia(getEnergia()+3);
            if(getEnergia()>100)
                setEnergia(100);
        }
    }
    system("cls");
    op2=false;
    estaOcupado = false;
    run();
    pthread_exit(NULL);
    }
}
void Pai::comer()//HILO
{
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
    op1=false;
    estaOcupado = false;
    pthread_exit(NULL);
    //run();
    }
}
void Pai::jugar()
{
    if(!estaOcupado)
    {
    estaOcupado = true;
    srand (time(NULL));
    int paiMove = rand()%3 + 1;
    myMove =-1;
    int g;
    Sleep(100);
    while(myMove==-1)
    {
        printSprite("PaiPPJ1.txt",551);
        printSprite("PaiPPJ2.txt",551);
        printSprite("PaiPPJ3.txt",551);
    }
    std::string str2 = "PaiPPJ"+to_string(paiMove)+".txt";
    const char * nameFile2 = str2.c_str();
    printSprite(str2,1800);

    if(myMove==paiMove)g=0;
    else if((myMove==1&&paiMove==3)||(myMove==2&&paiMove==1)||(myMove==3&&paiMove==2))g=1;
    else if((myMove==3&&paiMove==1)||(myMove==1&&paiMove==2)||(myMove==2&&paiMove==3))g=2;

    if(g==0)replace_line(nameFile2, 2, "\t\t\tTIE"); 
    else if(g==1)replace_line(nameFile2, 2, "\t\t      YOU WIN"); 
    else if(g==2)replace_line(nameFile2, 2, "\t\t     YOU LOSE"); 
    printSprite(str2,1500);
    system("cls");
    del_line(nameFile2,2);
    op3=false;
    estaOcupado = false;
    pthread_exit(NULL);
    }
}
void Pai::input()//HILO
{
    op1 = false;
    op2 = false;
    op3 = false;
    while(true)
    {
        char n;
        std::cin>>n;
        if(estaOcupado) myMove = int(n-'0');
        else
        {
        switch (n){
        case '1':{op1 = true;break;}
        case '2':{op2 = true;break;}
        case '3':{op3 = true;break;}
        default:break;}
        }
    }
    pthread_exit(NULL);
}
void Pai::run()
{  
    int res1, res2, res3, res4, res5, res6;
    replace_line("PaiN.txt", 2, " NAME: "+getNombre());
    replace_line("PaiRespaldo.txt", 2, " NAME: "+getNombre());

    res1 = pthread_create( &thread1, NULL, ex_threadReposo, this); 
    if(res1 != 0){
        pthread_mutex_lock( &mutex1 );
        printSprite("Error.txt",10000);
        exit(EXIT_FAILURE);
        pthread_mutex_unlock( &mutex1 );
    }
    res2 = pthread_create( &thread2, NULL, ex_threadEnergia, this);
    if(res2 != 0){
        pthread_mutex_lock( &mutex1 );
        printSprite("Error.txt",10000);
        exit(EXIT_FAILURE);
        pthread_mutex_unlock( &mutex1 );
    }
    res3 = pthread_create( &thread3, NULL, ex_threadHambre, this);
    if(res3 != 0){
        pthread_mutex_lock( &mutex1 );
        printSprite("Error.txt",10000);
        exit(EXIT_FAILURE);
        pthread_mutex_unlock( &mutex1 );
    }
    res4 = pthread_create( &thread4, NULL, ex_threadEdad, this);
    if(res4 != 0){
        pthread_mutex_lock( &mutex1 );
        printSprite("Error.txt",10000);
        exit(EXIT_FAILURE);
        pthread_mutex_unlock( &mutex1 );
    }
    res5 = pthread_create( &thread6, NULL, ex_threadInput, this);
    if(res5 != 0){
        pthread_mutex_lock( &mutex1 );
        printSprite("Error.txt",10000);
        exit(EXIT_FAILURE);
        pthread_mutex_unlock( &mutex1 );
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread6, NULL);
}
