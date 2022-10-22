#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void write(std::string nombre, std::string texto)
{
    std::ofstream archivo;

    archivo.open(nombre, ios::app);
    if(archivo.fail())
    {
        cout<<"The file couldn't be open"<<std::endl;
    }
    fflush(stdin);
    archivo<<texto;

    archivo.close();
}
void del_line(const char *file_name, int n, const char *file_nametemp)   
{    
    std::ifstream fin(file_name);    
    std::ofstream wout;                
    wout.open(file_nametemp, ios::out);
    char ch; 
    int line = 0;    
    std::string sline = "";
    if(fin.is_open())
    {
        /*
        while(fin.get(ch)) 
        {      
            if(ch == '\n') 
                line++; 
            
            getline(fin,sline);
            if(line != n) wout<<sline;
            else 
            {
                wout<<s<<std::endl;
                line++;
            }
        }*/
        while(!fin.eof())
        {
           while(getline(fin,sline))
           {
            line++;
            while (sline.length()==0 ) 
                getline(fin,sline);   
            if(line!=n)wout<<sline<<std::endl;
            else wout<<"."<<std::endl;
           }
        }
    }
    wout.close();  
    fin.close();   
    remove(file_name);        
    rename(file_nametemp, file_name);  
} 
void write_line(const char *file_name, int n, std::string s, const char *file_nametemp)   
{    
  std::ifstream fin(file_name);    
  std::ofstream fout;                
  fout.open(file_nametemp, ios::out); 
  
  char ch; 
  int line = 0;            
  while(fin.get(ch)) 
  {      
    if(ch == '\n') 
      line++; 
     
    if(line != n) fout<<ch;
    else 
    {
        fout<<s<<std::endl;
        line++;
    }
  } 
  fout.close();  
  fin.close();   
  remove(file_name);        
  rename(file_nametemp, file_name);  
} 

void printASCII(std::string nombre)
{
    std::string line = "";
    std::ifstream archivo; 
    archivo.open(nombre);
    if(archivo.fail()) cout<<"El archivo no se puede abrir"<<std::endl;
    if(archivo.is_open())
    {
        while(!archivo.eof())
        {
            getline(archivo,line);
            std::cout<<line<<std::endl;
        }
    }
    else
    {
        cout<<"El archivo no se puede abrir"<<std::endl;
    }
    archivo.close();
};
void printSprite(std::string archivo, double tiempo)
{
    system("cls");
    printASCII(archivo);
    Sleep(tiempo);
};