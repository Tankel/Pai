#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h> 
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void fileCopy(std::string copy)
{
    string line;
    ifstream ini_file{"PaiNRespaldo.txt"};
    ofstream out_file{copy};
    if (ini_file && out_file)
    {
        while (getline(ini_file, line)) {
            out_file << line << "\n";
        }
    }
    ini_file.close();
    out_file.close();
};

void del_line(const char *file_name, int n)   
{    
    srand (time(NULL));
    int tempn = rand();   
    std::ifstream fin(file_name);    
    std::ofstream wout;     
    std::string tempfile = "temp"+to_string(tempn)+".txt"; 
    const char * tempp = tempfile.c_str(); 
    wout.open(tempfile, ios::out);
    if(wout.fail())
    {
        fileCopy(file_name);
    }
    char ch; 
    int line = 0;    
    std::string sline = "";
    if(fin.is_open())
    {
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
    rename(tempp, file_name);
} 

void write_line(const char *file_name, int n, std::string s)   
{    
    srand (time(NULL));
    int tempn = rand();   
    std::ifstream fin(file_name);    
    std::ofstream wout;
    std::string tempfile = "temp"+to_string(tempn)+".txt"; 
    const char * tempp = tempfile.c_str();               
    wout.open(tempfile, ios::out); 
    if(wout.fail())
    {
        fileCopy(file_name);
    }
    char ch; 
    int line = 0;            
    while(fin.get(ch)) 
    {      
        if(ch == '\n') 
        line++; 
        
        if(line != n) wout<<ch;
        else 
        {
            wout<<s<<std::endl;
            line++;
        }
    } 
    wout.close();  
    fin.close();     
    remove(file_name);        
    rename(tempp, file_name); 
} 

void replace_line(const char *file_name, int n, std::string s)   
{    
    del_line(file_name, n);
    write_line(file_name, n, s);
}

void printASCII(std::string file_name)
{
    std::string line = "";
    std::ifstream archivo; 
    archivo.open(file_name);
    if(archivo.fail())
    {
        fileCopy(file_name);
    }
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
        fileCopy(file_name);
    }
    archivo.close();
};
void printSprite(std::string file_name, double tiempo)
{
    system("cls");
    printASCII(file_name);
    Sleep(tiempo);
};