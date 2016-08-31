#ifndef H_POINTER
#define H_POINTER

struct record
{
    char name[25];
    char address[80];
    int yearofbirth;
    char telno[15];
    struct record *next;
};

#endif
