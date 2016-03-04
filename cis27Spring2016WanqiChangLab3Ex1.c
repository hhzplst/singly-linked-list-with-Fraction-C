/************************************************************
*   Program Name: cis27Spring2016WanqiChangLab3Ex1.c
*   Discussion:   Lab3 Exercise #1
*   Written By:   Wanqi Chang
*   Date:         2016/03/10
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Type Definitions
struct FractionWanqiC {
  int num;
  int denom;
};

struct FractionNodeWanqiC {
  struct FractionWanqiC* frPtr;
  struct FractionNodeWanqiC* next;
};

typedef struct FractionWanqiC FractionWanqi;
typedef FractionWanqi* FractionPtrWanqi;
typedef struct FractionNodeWanqiC FractionNodeWanqi;
typedef FractionNodeWanqi* FractionNodePtrWanqi;
typedef FractionNodeWanqi* FractionListWanqi;
typedef FractionListWanqi* FractionListPtrWanqi;

//Function Prototypes
void outerMenuWanqiC(void);
void insertMenuWanqiC(void);
void removeMenuWanqiC(void);
int findGCDWanqiC(int, int);
FractionPtrWanqi createFractionWanqiC(void);
void printFractionInfoWanqiC(FractionPtrWanqi);

bool isEmptyWanqiC(FractionListWanqi);
int getLengthWanqiC(FractionListWanqi);

void insertFirstWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void appendWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void insertAtWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi, int);

void displayListWanqiC(FractionListWanqi);

int main() {

  int outerOption, insertOption, removeOption;
  FractionListPtrWanqi myListPtr = 
                            (FractionListPtrWanqi) malloc(sizeof(FractionListWanqi));
  FractionNodePtrWanqi myFractionNodePtr = 
                            (FractionNodePtrWanqi) malloc(sizeof(FractionNodeWanqi));
  FractionPtrWanqi newFractionPtr;

  printf("CIS 27 - C Programming\n"
         "Laney College\n"
         "Wanqi Chang\n\n"
         "Assignment Information --\n"
         "  Assignment Number:  Lab 03,\n"
         "                      Coding Assignment -- Excercise #1\n"
         "  Written by:         Wanqi Chang\n"
         "  Submitted Date:     2016/03/10\n");

  do {

    outerMenuWanqiC();
    scanf("%d", &outerOption);

    switch(outerOption) {
      case 1:
        break;
      case 2:
        do {

          insertMenuWanqiC();
          scanf("%d", &insertOption);

          switch(insertOption) {
            case 1:
              newFractionPtr = createFractionWanqiC();
              printFractionInfoWanqiC(newFractionPtr);

              myFractionNodePtr->frPtr = newFractionPtr;
              myFractionNodePtr->next = NULL;

              insertFirstWanqiC(myListPtr, myFractionNodePtr);
              printf("checking if the list is empty: %s", isEmptyWanqiC(*myListPtr)? "true":"false");
              printf("getting the length of the list: %d", getLengthWanqiC(*myListPtr));
              break;
            case 2:
              break;
            case 3:

              break;
            case 4:
              break;
            case 5:
              break;
            default:
              printf("\n    Wrong option!\n");
          }
        } while (insertOption != 5);
        break;
      case 3:
        break;
      case 4:
        printf("\n  Fractions and Linked Lists!\n\n");
        exit(0);
      default:
        printf("\n  You should not be in this class!\n");
    }
  } while (outerOption != 4);

  
}

//Function Definitions
void outerMenuWanqiC() {

  printf("\n************************************\n"
           "*    LINKED LIST MENU: Fraction    *\n"
           "* 1.  Displaying current list      *\n"
           "* 2.  Inserting                    *\n"
           "* 3.  Removing                     *\n"
           "* 4.  Quit                         *\n"
           "************************************\n"
           "Select the option (1 through 4): ");

}

void insertMenuWanqiC() {

 printf("\n     ************************\n"
          "     *    Inserting Menu    *\n"
          "     * 1.  As first node    *\n"
          "     * 2.  After n-th node  *\n"
          "     * 3.  As last node     *\n"
          "     * 4.  Displaying       *\n"
          "     * 5.  Quit             *\n"
          "     ************************\n"
          "     Select the option (1 through 5): ");

}

void removeMenuWanqiC() {

  printf("\n     ***********************\n"
           "     *    Removing Menu    *\n"
           "     * 1.  First node      *\n"
           "     * 2.  n-th node       *\n"
           "     * 3.  Last node       *\n"
           "     * 4.  Displaying      *\n"
           "     * 5.  Quit            *\n"
           "     ***********************\n"
           "     Select the option (1 through 5): ");

}

FractionPtrWanqi createFractionWanqiC() {
  FractionPtrWanqi tempPtr = NULL;
  int numTemp, denomTemp, gcd;

  tempPtr = (FractionPtrWanqi) malloc(sizeof(FractionWanqi));

  printf("\n       Please Enter the Numerator: ");
  scanf("%d", &numTemp);

  do {
    printf("\n       Please Enter a valid Denominator: ");
    scanf("%d", &denomTemp);
  } while (denomTemp == 0);

  gcd = findGCDWanqiC(numTemp, denomTemp);
  tempPtr->num = numTemp/gcd;

  if (denomTemp < 0) {
    tempPtr->num = -(tempPtr->num);
    tempPtr->denom = -(denomTemp/gcd);    
  } else
    tempPtr->denom = denomTemp/gcd;

  return tempPtr;
}

int findGCDWanqiC(int n, int m) {
  int gcd, remainder;
  
  while (n != 0){
    remainder = m % n;
    m = n;
    n = remainder;
  } 
    gcd = m;
   
    if (gcd < 0)
      return -gcd;
    else
      return gcd;
}

void printFractionInfoWanqiC(FractionPtrWanqi frPtr) {
  if (frPtr == NULL)
    printf("\n           Memory Location: NULL\n");
  else {
    printf("\n           Memory Location: %p\n"
           "           Numerator:       %d\n"
           "           Denominator:     %d\n", frPtr, frPtr->num, frPtr->denom);
    if ((frPtr->num)%(frPtr->denom) == 0)
      printf("           Result:      %d\n", (frPtr->num)/(frPtr->denom));
  }
}

bool isEmptyWanqiC(FractionListWanqi myList) {
  return (myList == NULL)? true:false;
}

int getLengthWanqiC(FractionListWanqi myList) {
  int count = 0;
  FractionListWanqi currentNodePtr = myList;
  
  if (isEmptyWanqiC(myList))
    return 0;

  // printf("current node Ptress: %p", currentNodePtr->next);

  while (currentNodePtr) {
    count++;
    currentNodePtr = currentNodePtr->next;
  };


  return count;
}


void insertFirstWanqiC(FractionListPtrWanqi myListPtr, 
                      FractionNodePtrWanqi newNodePtr) {
  printf("\n       Inserting the Fraction at the Beginning of the List...\n");
  if (*myListPtr != NULL)
    newNodePtr->next = *myListPtr;
  *myListPtr = newNodePtr;
}

void appendWanqiC(FractionListPtrWanqi myListPtr,
                      FractionNodePtrWanqi newNodePtr) {
  FractionNodePtrWanqi currentNodePtr = *myListPtr;
  if(currentNodePtr != NULL) {
    while(currentNodePtr->next) 
      currentNodePtr = currentNodePtr->next;

    currentNodePtr->next = newNodePtr;
    newNodePtr->next = NULL;
  } else {
    *myListPtr = newNodePtr;
  }

}

void insertAtWanqiC(FractionListPtrWanqi myListPtr,
           FractionNodePtrWanqi newNodePtr, int index) {
  int myListLength = getLengthWanqiC(*myListPtr), count = 1;
  FractionNodePtrWanqi currentNodePtr = *myListPtr;

  if(index == 0 || myListLength == 0)
    insertFirstWanqiC(myListPtr, newNodePtr);
  if(index >= myListLength)
    appendWanqiC(myListPtr, newNodePtr);

  while(count < index){
    count++;
    currentNodePtr = currentNodePtr->next;
  }

  newNodePtr->next = currentNodePtr->next;
  currentNodePtr->next = newNodePtr;
}

void displayListWanqiC(FractionListWanqi myList) {
  printf("       Here's the information about the current List:\n");
  FractionListWanqi currentNodePtr = myList;
  printf("here's the memory location of currentNodePtr: %p", currentNodePtr);
  printf("Length of the list: %d", getLengthWanqiC(myList));

  // for (int i = 0; i < getLengthWanqiC(myList); i++) {
  //   printf("\n      At index %d\n"
  //                     "Fraction memory Location: %p\n"
  //                     "Fraction Numerator:       %d\n"
  //                     "Fraction Denominator:     %d\n"
  //                     "Next Node in memory:      %p\n\n",
  //                      i, currentNodePtr->frPtr, currentNodePtr->frPtr->num, 
  //                      currentNodePtr->frPtr->denom, currentNodePtr->next);
  //   currentNodePtr = currentNodePtr->next;
  // }
}















