#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void write(string nombre, string texto)
{
    ofstream archivo;

    archivo.open(nombre, ios::app);
    if(archivo.fail())
    {
        cout<<"The file couldn't be open"<<endl;
    }
    fflush(stdin);
    archivo<<texto;

    archivo.close();
}
void del_line(const char *file_name, int n, const char *file_nametemp)   
{    
    ifstream fin(file_name);    
    ofstream wout;                
    wout.open(file_nametemp, ios::out);
    char ch; 
    int line = 0;    
    string sline = "";
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
                wout<<s<<endl;
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
            if(line!=n)wout<<sline<<endl;
            else wout<<"."<<endl;
           }
        }
    }
    wout.close();  
    fin.close();   
    remove(file_name);        
    rename(file_nametemp, file_name);  
} 
void write_line(const char *file_name, int n, string s, const char *file_nametemp)   
{    
  ifstream fin(file_name);    
  ofstream fout;                
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
        fout<<s<<endl;
        line++;
    }
  } 
  fout.close();  
  fin.close();   
  remove(file_name);        
  rename(file_nametemp, file_name);  
} 

void printASCII(string nombre)
{
    string line = "";
    ifstream archivo; 
    archivo.open(nombre);
    if(archivo.fail()) cout<<"El archivo no se puede abrir"<<endl;
    if(archivo.is_open())
    {
        while(!archivo.eof())
        {
            getline(archivo,line);
            cout<<line<<endl;
        }
    }
    else
    {
        cout<<"El archivo no se puede abrir"<<endl;
    }
    archivo.close();
};
void printSprite(string archivo, double tiempo)
{
    system("cls");
    printASCII(archivo);
    Sleep(tiempo);
};