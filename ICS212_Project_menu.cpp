#include <iostream>
#include <string>
#include "record.h"
#include "llist.h"

using namespace std;

void showMenu();
void fixTrail(char name[]);

int main(int argc, char *argv[])
{
    llist mylist;

    int returnfun;
    int num = 1; 
    int yob, len;
    char name[25];
    char tname[25];
    char tname2[25]; 
    char tname3[25];
    char address[80];
    char naddress[80];
    char telno[15];
    char ntelno[15];
    char testchar[2] = {'z', '\0'}; 
    len = 0;

    while(1)
    {
        showMenu();
        cout << "\nPlease Enter a number from 1-7 to select a choice from the menu." << endl;
        cin >> num;
        cin.ignore();
        if (num == 1)
        {
            cout << "Please enter the full name." << endl;
            cin.getline(name, sizeof(name));
            cout << "Please enter the full address then press ! and enter." << endl;
            while(testchar[0] != '!')
            {
                testchar[0] = cin.get();
                if (testchar[0] != '!')
                {
                    address[len] = testchar[0];
                    len++;
                }
                
                address[len] = '\0';
            }
            len = 0;
            testchar[0] = 'z';

            cout << "Please enter the year of birth." << endl;
            cin >> yob;
            cin.ignore();
            cout << "Please enter telephone number." << endl;
            cin.getline(telno, sizeof(telno));

            if (name[0] == '\0')
            {
                cout << "ERROR: retype a name" << endl;
                cin.getline(name, sizeof(name));
                fixTrail(name);
            }
            returnfun = mylist.addRecord(name, address, yob, telno);
            
        }

        else if (num == 2)
        {
            cout << "Please enter the full name you want to modify." << endl;
            cin.getline(tname, sizeof(tname));
            cout << "Please enter new full address then press ! and enter." << endl;
            while(testchar[0] != '!')
            {
                testchar[0] = cin.get();
                if (testchar[0] != '!')
                {
                    naddress[len] = testchar[0];
                    len++;
                }

                naddress[len] = '\0';
            }
            testchar[0] = 'z';
            cin.ignore();

            cout << "Please enter telephone number." << endl;
            cin.getline(ntelno, sizeof(ntelno));
            
            returnfun = mylist.modifyRecord(tname, naddress, ntelno);

        }

        else if (num == 3)
        {
            cout << "Please enter the full name you want to print." << endl;
            cin.getline(tname2, sizeof(tname2));
            returnfun = mylist.printRecord(tname2);
        }

        else if (num == 4)
        {

            mylist.printAll();
        }

        else if (num == 5)
        {
            cout << "Please enter the full name you want to delete." << endl;
            cin.getline(tname3, sizeof(tname3));
	    returnfun = mylist.deleteRecord(tname3);
        }

        else if (num == 6)
        {
            mylist.reverse();
        }
        
        else if (num == 7)
        {
            cout << "Goodbye!\n" << endl;
            break;
        }
        else
        {
            cout << "invalid input\n" << endl;
            cout << "please input a different command\n" << endl;
        }
    }

    return 0;
}

void showMenu()
{
    cout << "All menu commands:\n" << endl;
    cout << "1. Add new record" << endl;
    cout << "2. Modify record" << endl;
    cout << "3. Print info for a record" << endl;
    cout << "4. Print info for all records" << endl;
    cout << "5. Delete a record" << endl;
    cout << "6. Reverse the order of records" << endl; 
    cout << "7. Quit\n" << endl;
}


