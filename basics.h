#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>


//structure for a dynamic array
typedef struct {
    union {
        int   *i_data;
        char  *c_data;
        char **s_data;
    };
    int size;
} DA;


//modulo that works with negative numbers
int mod(int a, int b);

//python style string slicing that can also do reversed strings
char* sliceString(char *string, int start, int end);

//functions for a dynamic array filled with integers 
void DaAppendInt(DA *da, int item);
int DaPopInt(DA *da);
void DaPrintInt(DA *da);

//functions for a dynamic array filled with characters
void DaAppendChar(DA *da, char item);
char DaPopChar(DA *da);
void DaPrintChar(DA *da);

//functions for a dynamic array filled with strings
void DaAppendString(DA *da, char *item);
char *DaPopString(DA *da);
void DaPrintString(DA *da);

//functions for easier file management
bool ReadEntireFileIntoDA(DA *da, char * filePath);

//--------------------------------------------------
//        Code Implementation Starts Here
//--------------------------------------------------

char* sliceString(char *string, int start, int end){
    //gets size of new string
    //add 1 because of null byte
    int size;
    char *newString;
    if (start <= end){
        size = end-start+1;
        newString = (char *)malloc(size * sizeof(char));
        for (int i = 0; start <= end; start++, i++){
            newString[i] = string[start];
        }
    }
    else{
        size = start-end+1;
        newString = (char *)malloc(size * sizeof(char));
        for (int i = 0; start >= end; start--, i++){
             newString[i] = string[start];
        }
    }

    newString[size] = '\0';
    return newString;
}

int mod(int a, int b){
    return (a%b + b)%b;
}


void DaAppendInt(DA *da, int item){
    if (da->size == 0){
        da->i_data = (int *)malloc(sizeof(int));
        da->i_data[0] = item;
        da->size++;
    }
    else{
        da->size++;
        da->i_data = (int *)realloc(da->i_data, da->size*sizeof(int));
        da->i_data[da->size-1] = item;
    }
}

int DaPopInt(DA *da){
    if (da->size == 0){
        printf("ERROR: The dynamic array is empty! You cannot pop anything off of it");
        return 0;
    }
    da->size--;
    int v = da->i_data[da->size];
    da->i_data = realloc(da->i_data, da->size);
    return v;
}

void DaPrintInt(DA *da){
    if (!da->size){
        printf("Dynamic Array is empty\n");
        return;
    }
    printf("Printing Dyanmic Array:\n");
    for (int i = 0; i < da->size; i++){
        (i == da->size-1) ? printf("%d", da->i_data[i]) : printf("%d, ", da->i_data[i]);
    }
    printf("\n");
}

void DaAppendChar(DA *da, char item){
    if (da->size == 0){
        da->c_data = (char *)malloc(sizeof(char));
        da->c_data[0] = item;
        da->size++;
    }
    else{
        da->size++;
        da->c_data = (char *)realloc(da->c_data, da->size*sizeof(char));
        da->c_data[da->size-1] = item;
    }
}

char DaPopChar(DA *da){
    if (da->size == 0){
        printf("ERROR: The dynamic array is empty! You cannot pop anything off of it");
        return 0;
    }
    da->size--;
    char v = da->c_data[da->size];
    da->c_data = realloc(da->c_data, da->size);
    return v;
}

void DaPrintChar(DA *da){
    if (!da->size){
        printf("Dynamic Array is empty\n");
        return;
    }
    printf("Printing Dyanmic Array:\n");
    for (int i = 0; i < da->size; i++){
        (i == da->size-1) ? printf("%c", da->c_data[i]) : printf("%s, ", da->c_data[i]);
    }
    printf("\n");
}

void DaAppendString(DA *da, char *item){
    if (da->size == 0){
        da->s_data = (char **)malloc(sizeof(char *));
        da->s_data[0] = (char *)malloc(strlen(item)*sizeof(char));
        strcpy(da->s_data[0], item);
        da->size++;
    }
    else{
        da->size++;
        da->s_data = (char **)realloc(da->s_data, da->size*sizeof(char *));
        da->s_data[da->size-1] = (char *)malloc(strlen(item)*sizeof(char));
        strcpy(da->s_data[da->size-1], item);
    }
}

char *DaPopString(DA *da){
    if (da->size == 0){
        printf("ERROR: The dynamic array is empty! You cannot pop anything off of it");
        return 0;
    }
    da->size--;
    char *v = (char *)malloc(strlen(da->s_data[da->size])*sizeof(char));
    strcpy(v,da->s_data[da->size]);
    free(da->s_data[da->size]);
    da->s_data = realloc(da->s_data, da->size);
    return v;
}

void DaPrintString(DA *da){
    if (!da->size){
        printf("Dynamic Array is empty\n");
        return;
    }

    printf("Printing Dyanmic Array:\n");
    for (int i = 0; i < da->size; i++){
        (i == da->size-1) ? printf("%s", da->s_data[i]) : printf("%s, ", da->s_data[i]);
    }
    printf("\n");
}


bool ReadEntireFileIntoDA(DA *da, char * filePath){
    FILE *f = fopen(filePath, "r");
    if (f == NULL){
        printf("ERROR: Could not open %s", filePath);
        return false;
    }
    char s[100];
    while (fgets (s, 100, f) != NULL){
        DaAppendString(da, s);
    }
    return true;
}
