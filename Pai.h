#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <pthread.h>
#include <thread>
#include "archivos.h"
//#include <mutex>
//#if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)

using namespace std;

//std:: mutex mu;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
bool estaDurmiendo=false;
bool op1;
bool op2;
bool op3;

class Pai
{
    private:
        string nombre; 
        int edad;
        int hambre; 
        int energia; 
    public:
        Pai():nombre("Pai"),edad(0),hambre(100),energia(100){};
        Pai(string _name, int _energia, int _hambre): nombre(_name),edad(0),hambre(_hambre),energia(_energia){};        
        Pai(string _name): nombre(_name),edad(0),hambre(100),energia(100){};
        string getNombre(){return nombre;};
        int getEdad() //en segundos
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); 
            return chrono::duration_cast<chrono::seconds>(end - start).count()/180; //cumple 1 anio cada 3min
        };
        int getHambre(){return hambre;};
        int getEnergia(){return energia;};
        void setEnergia(int _energia){energia = _energia;};
        void setEdad(int _edad){edad = _edad;};
        void setHambre(int _hambre){hambre = _hambre;};
        //void alimentar(Comida);
        void comer();
        void dormir();
        void jugar();
        void run();
        void threadReposo();
        void threadEnergia();
        void threadHambre();
        void threadEdad();
        void input();
        std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
        pthread_t thread1;
        pthread_t thread2;
        pthread_t thread3;
        pthread_t thread4;
        pthread_t thread5;
        pthread_t thread6;
        pthread_t thread7;
        pthread_t thread8;
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
void Pai::threadEnergia()//HILO
{
    while(getHambre()>0 && getEnergia()>0 && !estaDurmiendo)
    {
        setEnergia(getEnergia()-1);
        pthread_mutex_lock( &mutex1 );
        del_line("PaiN.txt",13, "temp1.txt");
        del_line("PaiN1.txt",13, "temp1_.txt");
        write_line("PaiN.txt",13," ENERGIA: "+to_string(getEnergia()), "temp1.txt"); //\r
        write_line("PaiN1.txt",13," ENERGIA: "+to_string(getEnergia()), "temp1_.txt");
        pthread_mutex_unlock( &mutex1 );
        Sleep(7102);
    }
    
};
void Pai::threadHambre()//HILO
{
    while(getHambre()>0 && getEnergia()>0 && !estaDurmiendo)
    {
        setHambre(getHambre()-1);
        pthread_mutex_lock( &mutex1 );
        del_line("PaiN.txt",14, "temp2_.txt");
        del_line("PaiN1.txt",14, "temp2.txt");
        write_line("PaiN.txt",14," HAMBRE: "+to_string(getHambre()), "temp2.txt"); //\r
        write_line("PaiN1.txt",14," HAMBRE: "+to_string(getHambre()), "temp2_.txt");
        if(getHambre()<1)
        {
            printSprite("GameOver.txt",200);
            system("pause");
            exit(3);
        }
        pthread_mutex_unlock( &mutex1 );
        Sleep(5001);
    }
};
void Pai::threadEdad()//HILO
{
    while(getHambre()>0 && getEnergia()>0)
    {
        setEdad(getEdad());
        pthread_mutex_lock( &mutex1 );
        del_line("PaiN.txt",3, "temp3.txt"); //BORRAR POR NUMERO DE RENGLON MEJOR Y QUITAR PUNTOS EN TXT 
        del_line("PaiN1.txt",3, "temp3_.txt");
        write_line("PaiN.txt",3," EDAD: "+to_string(getEdad()), "temp3.txt"); //\r
        write_line("PaiN1.txt",3," EDAD: "+to_string(getEdad()), "temp3_.txt");
        pthread_mutex_unlock( &mutex1 );
        Sleep(4500);
    }
};
void Pai::threadReposo()//HILO
{
    while(getHambre()>0 && getEnergia()>0)
    {
        for(int i=0; i<8; i++)
        {
            pthread_mutex_lock( &mutex1 );
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
        system("cls");
        printASCII("PaiN1.txt");
        pthread_mutex_unlock( &mutex1 );
        Sleep(220);
    }
};
void Pai::dormir()//HILO
{
    estaDurmiendo = true;
    while(getEnergia()<100)
    {
        system("cls");
        for(int i=1; i<4; i++)
        {
        write_line("PaiSleep"+to_string(i)+".txt",13," ENERGIA: "+to_string(getEnergia()), "temp1.txt"); //\r
        printSprite("PaiSleep"+to_string(i)+".txt",260);
        if(getEnergia()<100)
            setEnergia(getEnergia()+1);
        del_line("PaiSleep"+to_string(i)+"txt",13, "temp1.txt");
    }
    system("cls");
    estaDurmiendo = false;
    run();
}

void Pai::comer()//HILO
{
    //jei
    //ssssssssssssss
    estaDurmiendo = true;
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
    if(getHambre()>99
        setHambre(100);

    system("cls");
    estaDurmiendo = false;
    run();
}
void Pai::input()//HILO
{
    op1 = false;
    op2 = false;
    op3 = false;
    while(true)
    {
        char n;
        cin>>n;
        switch (n)
        {
        case '1':
        {
            op1 = true;
            break;
        }
        
        case '2':
        {
            op2 = true;
            break;
        }
        
        case '3':
        {
            op3 = true;
            break;
        }
        
        default:
            break;
        }
    }
}
void Pai::jugar()
{
    while(true)
    {
        printASCII("PaiSleep1.txt");
        Sleep(220);
        system("cls");
    }
}
void Pai::run()
{  
    del_line("PaiN.txt",2, "temp4.txt");
    del_line("PaiN1.txt",2, "temp4.txt");
    write_line("PaiN.txt", 2, " NOMBRE: "+getNombre(), "temp4.txt");
    write_line("PaiN1.txt", 2, " NOMBRE: "+getNombre(), "temp4.txt");

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

class Comida
{
    private: 
        string sprite;
        double m_salud;
        double m_energia;
    public:
        Comida(){};
        void setm_salud(double m)
        {
            m_salud = m;
        }
        void setm_energia(double m)
        {
            m_energia = m;
        }
};

class Fruta: public Comida
{
    public:
        Fruta();
        void setSprite();
};
Fruta::Fruta()
{
    setm_energia(40);
    setm_salud(30);
};
class Pizza: public Comida
{
    public:
        Pizza();
        void setSprite();
};
Pizza::Pizza()
{
    setm_energia(60);
    setm_salud(10);
};
class Taco: public Comida
{
    public:
        Taco();
        void setSprite();
};
Taco::Taco()
{
    setm_energia(20);
    setm_salud(20);
};