#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//mode that works with negative numbers
int mod(int a, int b);


//python style string slicing that can also do reversed strings
char* sliceString(char *string, int start, int end);



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


