#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>

//adaptive array DB
typedef struct AdptArray_{
    int Max_Elements;
    PElement * ArrElements;
    COPY_FUNC copyFunc;
    DEL_FUNC DelElementFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

//by creating the adaptive array it will save the desired functions on the adaptive array DB, and make a default init
PAdptArray CreateAdptArray(COPY_FUNC CpyFunc, DEL_FUNC DelFunc,PRINT_FUNC PrintFunc){
    PAdptArray arr;
    arr = (PAdptArray)malloc(sizeof(AdptArray));
    if(arr==NULL) return NULL;
    arr->Max_Elements = 1;
    arr->ArrElements=(PElement*) calloc(1,sizeof (PElement));
    arr->copyFunc = CpyFunc;
    arr->DelElementFunc = DelFunc;
    arr->printFunc = PrintFunc;
    return arr;
}

//using free() function to free the memory allocated, the actual elements are freed on the demo.c file
void DeleteAdptArray(PAdptArray arr){
    free(arr->ArrElements);
    free(arr);
}

//this function checks if the input is valid, and if so, it will replace the current element with the new element
//requested, finally, it will place the requested element in the right place, then return SUCCESS
Result SetAdptArrayAt(PAdptArray arr, int i, PElement Pelement){
    PElement * newArrElements;
    if (arr==NULL)return FAIL;
    if(i>=arr->Max_Elements){
        if ((newArrElements = (PElement*)calloc(i+1,sizeof (PElement))) == NULL)
            return FAIL;
        memcpy(newArrElements, arr->ArrElements, (arr->Max_Elements) * sizeof(PElement));
        free(arr->ArrElements);
        arr->ArrElements = newArrElements;
    }
    if(arr->ArrElements[i]!=NULL) arr->DelElementFunc((arr->ArrElements)[i]);
    (arr->ArrElements)[i] = arr->copyFunc(Pelement);
    arr->Max_Elements = (i >= arr->Max_Elements) ? (i + 1) : arr->Max_Elements;
    return SUCCESS;
}

//if the element is not NULL return the element pointer
PElement GetAdptArrayAt(PAdptArray arr, int i){
    if(arr->ArrElements[i]==NULL)return NULL;
    return (arr->ArrElements[i]);
}

//if arr is not NULL the functions should return the size of the array
int GetAdptArraySize(PAdptArray arr){
    if (arr == NULL) return -1;
    return arr->Max_Elements;
}

//if the element is not NULL, the function should use the print method for each element on DB array list
void PrintDB(PAdptArray arr){
    for (int i = 0; i < arr->Max_Elements; ++i) {
        if (arr->ArrElements[i]==NULL) continue;
        arr->printFunc(arr->ArrElements[i]);
    }
}