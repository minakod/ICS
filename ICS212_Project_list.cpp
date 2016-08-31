#include <iostream>
#include <string>
#include <fstream>
#include "record.h"
#include "llist.h"

using namespace std;

#ifdef DEBUG
	cout << "********DEBUG MODE********" << endl; 
#endif 

void fixTrail(char name[]);

llist::llist()
{
    strcpy(this -> filename, "records.txt");
    readfile(); 
    this -> start = NULL;
}

llist::llist(char key[])
{
    strcpy(this -> filename, key);
    readfile();
    this -> start = NULL;
}

llist::~llist()
{
    strcpy(this -> filename, "records.txt");
    writefile();
    cleanup(); 
}


int llist::addRecord (char name[], char address[], int yob, char telno[])
{
    struct record *newrec; 
    struct record *temp;

    newrec = new struct record;
    temp = new struct record;

    strcpy(newrec -> name, name);
    strcpy(newrec -> address, address);
    newrec -> yearofbirth = yob;
    strcpy(newrec -> telno, telno);
    newrec -> next = NULL;

    if (this -> start == NULL)
    {
        this -> start = newrec;
    }
    else
    {
        temp = this -> start;

        while ( temp -> next != NULL)
        {
            temp = temp -> next;
        }

        temp -> next = newrec;

    }

    cout << "Record Added" << endl;

    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "add record function" << endl;
    #endif

    return 0;
}


int llist::printRecord (char name[])
{
    struct record *temp;
    int valid = 0;

    temp = new struct record;
    temp = this -> start;

    if (temp == NULL)
    {
        cout << "Record not found" << endl;
    }

    while(temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
        {
            cout << "Record Name: " << temp -> name << endl;
            cout << "Address: " << temp -> address << endl;
            cout << "Year of birth: " << temp -> yearofbirth << endl;
            cout << "Telephone number: " << temp -> telno  << "\n" << endl;
            temp = temp -> next;
            valid++;
        }
        else
        {
            temp = temp -> next;
        }
    }


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "print record function" << endl;
    #endif
   
    return valid;
}


int llist::modifyRecord (char name[], char address[], char telno[])
{
    struct record *temp;
    int valid = 0;

    temp = new struct record; 

    temp = this -> start;
    if (temp == NULL)
    {
        cout << "Record not found" << endl;
    }

    while(temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
        {
            strcpy(temp -> address, address);
            strcpy(temp -> telno, telno);
            temp = temp -> next;
            valid++;
            cout << "Record modified successfully" << endl;
        }
        else
        {
            temp = temp -> next;
        }
    }


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "modify record function" << endl;
    #endif
  


    return valid;
}


void llist::printAll()
{
    struct record *temp;

    temp = new struct record;

    temp = this -> start;

    while(temp != NULL)
    {
        cout << "Name: " << temp -> name << endl;
        cout << "Address: " << temp -> address << endl;
        cout << "Year of Birth: " << temp -> yearofbirth << endl;
        cout << "Telephone Number: " << temp -> telno << "\n" << endl;
        temp = temp -> next;
    }


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "print all record function" << endl;
    #endif
  
}


int llist::deleteRecord(char name[])
{
    int valid = 0;
    struct record *temp;
    struct record *prev;
    temp = new struct record;
    prev = new struct record;
    temp = this -> start;
    prev = NULL;

    while(temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
        {
            if(prev == NULL || strcmp(prev -> name, name)==0)
            {
                this -> start = temp -> next;
                prev = this -> start;
                delete(temp);
                temp = prev;
                valid++;
            }
            else
            {
                prev -> next  = temp -> next;
                delete(temp);
                temp = prev;
                valid++;
            }
        }
        else
        {
            prev = temp;
            temp = temp -> next;
        }
    }
    
    if (valid == 0)
        cout << "Record does not exist" << endl;
    
    else
        cout << valid << " record(s) deleted" << endl; 


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "delete record function" << endl;
    #endif
  
    return valid;
}


void llist::cleanup()
{
    struct record *temp;
    struct record *prev;

    temp = new struct record;
    prev = new struct record;
    prev = NULL;
    temp = this -> start;

    while(temp != NULL)
    {
        this -> start = temp -> next;
        prev = this -> start;
        delete(temp);
        temp = prev;
    }


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "clean up record function" << endl;
    #endif
  

}


int llist::readfile()
{
    ifstream filein;

    char buffer[300];
    char name[25];
    char address[80] = "";
    int yearofbirth;
    char telno[15];
    int i = 0;

    filein.open(filename);

    while(filein.getline(buffer, 300) != NULL)
    {
        if(i == 0)
        {
            strcpy(name, buffer);
            fixTrail(name);
            i++;
        }
        else if(i == 1)
        {

            if(buffer[strlen(buffer) - 2] == '*')
            {
                buffer[strlen(buffer) - 2] = '\0';
                strcat(address, buffer);
                i++;
            }
            else
            {
                strcat(address, buffer);
                i = 1;
            }
        }
        else if(i == 2)
        {
            yearofbirth = buffer[i];
            i++;
        }
        else if(i == 3)
        {
            strcpy(telno,buffer);
            addRecord(name, address, yearofbirth, telno);
            strcpy(address,"");
            i = 0;
        }
    }
   
    filein.close();


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "read file function" << endl;
    #endif
  

    return 0;
}

int llist::writefile()
{
    struct record *curr;

    ofstream fileout(filename);
    curr = start;

    while(curr != NULL)
    {
        fileout << curr->name << endl;
        fileout << curr->address << endl;
        fileout << curr->yearofbirth << endl;
        fileout << curr->telno << endl;
        curr = curr->next;
    }


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "write fiel function" << endl;
    #endif
  
    return 0;
}


void llist::reverse()
{
    this -> start = reverse(this -> start);
    cout << "reversed" << endl;


    #ifdef DEBUG
        cout << "********DEBUG MODE********" << endl; 
        cout << "reverse record function" << endl;
    #endif
  

}

record* llist:: reverse(record* start)
{
    struct record *temp;
    temp = new struct record;

    if ( start -> next == NULL)
    {
        temp = start;
    }
    else
    {
        temp = reverse( start -> next);
        (start -> next) -> next = start;
        start -> next = NULL;
    }

    return temp;

}

void fixTrail(char name[])
{
    unsigned int i;
    int fix;
    for(i = 0; i <= strlen(name); i++)
    {
        if(name[i] == '\n')
        {
            fix = i;
        }
    }
    name[fix] = '\0';
} 
