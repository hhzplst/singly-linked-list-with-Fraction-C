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
FractionNodePtrWanqi createFractionNodeWanqiC(void);
void printFractionInfoWanqiC(FractionPtrWanqi);
void printFractionNodeWanqiC(FractionNodePtrWanqi);

bool isEmptyWanqiC(FractionListWanqi);
int getLengthWanqiC(FractionListWanqi);

void insertFirstWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void appendWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void insertAtWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi, int);

void removeFirstWanqiC(FractionListPtrWanqi);
void removeLastWanqiC(FractionListPtrWanqi);
void removeAtWanqiC(FractionListPtrWanqi, int);
void freeFractionNodeWanqiC(FractionNodePtrWanqi);

void displayListWanqiC(FractionListWanqi);

int main() {

  int outerOption, insertOption, removeOption, index;

  FractionListPtrWanqi myListPtr = 
                (FractionListPtrWanqi) malloc(sizeof(FractionListWanqi));
  FractionListWanqi myList;
  myListPtr = &myList;

  FractionNodePtrWanqi newFractionNodePtr = NULL;                      

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
        displayListWanqiC(myList);
        break;
      case 2:
        do {

          insertMenuWanqiC();
          scanf("%d", &insertOption);

          switch(insertOption) {
            case 1: 
              newFractionNodePtr = createFractionNodeWanqiC();
              insertFirstWanqiC(myListPtr, newFractionNodePtr);
              break;
            case 2:
              printf("\n       After which node would you want to insert (start at 1): ");
              scanf("%d", &index);
              newFractionNodePtr = createFractionNodeWanqiC();
              insertAtWanqiC(myListPtr, newFractionNodePtr, index);
              break;
            case 3:
              newFractionNodePtr = createFractionNodeWanqiC();
              appendWanqiC(myListPtr, newFractionNodePtr);
              break;
            case 4:
              displayListWanqiC(myList);
              break;
            case 5:
              break;
            default:
              printf("\n\tWrong option!\n");
          }
        } while (insertOption != 5);
        break;
      case 3:
        do {

          removeMenuWanqiC();
          scanf("%d", &removeOption);

          switch(insertOption) {
            case 1: 
              removeFirstWanqiC(myListPtr);
              break;
            case 2:
              printf("\n       Which node would you want to remove (start at 1): ");
              scanf("%d", &index);
              removeAtWanqiC(myListPtr, index);
              break;
            case 3:
              removeLastWanqiC(myListPtr);
              break;
            case 4:
              displayListWanqiC(myList);
              break;
            case 5:
              break;
            default:
              printf("\n\tWrong option!\n");
          }
        } while (insertOption != 5);
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

FractionNodePtrWanqi createFractionNodeWanqiC() {
  FractionPtrWanqi newFractionPtr = NULL;
  FractionNodePtrWanqi myFractionNodePtr = NULL;

  newFractionPtr = createFractionWanqiC();

  myFractionNodePtr = (FractionNodePtrWanqi) malloc(sizeof(FractionNodeWanqi));
  myFractionNodePtr->frPtr = newFractionPtr;
  myFractionNodePtr->next = NULL;

  return myFractionNodePtr;
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
    printf("\n\t\tMemory Location: NULL\n");
  else {
    printf("\n\t\tMemory Location: %p\n"
           "\t\tNumerator:       %d\n"
           "\t\tDenominator:     %d\n", frPtr, frPtr->num, frPtr->denom);
    if ((frPtr->num)%(frPtr->denom) == 0)
      printf("\t\tResult:          %d\n", (frPtr->num)/(frPtr->denom));
  }
}

void printFractionNodeWanqiC(FractionNodePtrWanqi frNodePtr) {
  printf("\n\t  Current fraction node is at: %p\n\
          Linking to the next node at: %p\n\
          Having the Fraction information:\n"
          , frNodePtr, frNodePtr->next);
  printFractionInfoWanqiC(frNodePtr->frPtr);
}


bool isEmptyWanqiC(FractionListWanqi myList) {
  return (myList == NULL)? true:false;
}

int getLengthWanqiC(FractionListWanqi myList) {
  int count = 1;
  FractionListWanqi currentNodePtr = myList;
  
  if (!currentNodePtr)
    return 0;

  while (currentNodePtr->next != NULL) {
    count++;
    currentNodePtr = currentNodePtr->next;
  };

  return count;
}


void insertFirstWanqiC(FractionListPtrWanqi myListPtr, 
                      FractionNodePtrWanqi newNodePtr) {
  printf("\n       Inserting the Node at the beginning of the list...");
  if (*myListPtr != NULL)
    newNodePtr->next = *myListPtr;
  *myListPtr = newNodePtr;
  printf("Done!\n");
}

void appendWanqiC(FractionListPtrWanqi myListPtr,
                      FractionNodePtrWanqi newNodePtr) {
  FractionNodePtrWanqi currentNodePtr = *myListPtr;

  printf("\n       Inserting the Node at the end of the list...");

  if(currentNodePtr) {
    while(currentNodePtr->next) 
      currentNodePtr = currentNodePtr->next;

    currentNodePtr->next = newNodePtr;
  } else {
    *myListPtr = newNodePtr;
  }
  printf("Done!\n");
}

void insertAtWanqiC(FractionListPtrWanqi myListPtr,
           FractionNodePtrWanqi newNodePtr, int index) {
  int myListLength = getLengthWanqiC(*myListPtr), count = 1;
  FractionNodePtrWanqi currentNodePtr = *myListPtr;

  printf("\n       Inserting the Node after %d-th of the list...", index);

  if (index < 1 || myListLength == 0)
    insertFirstWanqiC(myListPtr, newNodePtr);
  else if (index >= myListLength)
    appendWanqiC(myListPtr, newNodePtr);
  else {
    while(count < index){
      count++;
      currentNodePtr = currentNodePtr->next;
    }

    newNodePtr->next = currentNodePtr->next;
    currentNodePtr->next = newNodePtr;
    printf("Done!\n");
  }
}

void removeFirstWanqiC(FractionListPtrWanqi myListPtr) {
  FractionNodePtrWanqi currentNodePtr = *myListPtr;

  if (!(*myListPtr))
    printf("\n\tCan't remove from an empty list!");
  else {
    printf("\n       Removing the Node at the beginning of the list...");
    *myListPtr = (*myListPtr)->next;
    freeFractionNodeWanqiC(currentNodePtr);
    printf("Done!\n");    
  }
};

void removeLastWanqiC(FractionListPtrWanqi myListPtr) {
  FractionNodePtrWanqi currentNodePtr = *myListPtr;

  printf("\n       Removing the Node at the end of the list...");

  if (!(*myListPtr))
    printf("\n\tCan't remove from an empty list!\n");
  else if (!currentNodePtr->next)
    removeFirstWanqiC(myListPtr);
  else {
    while (currentNodePtr->next->next)
      currentNodePtr = currentNodePtr->next;

    freeFractionNodeWanqiC(currentNodePtr->next);
    currentNodePtr->next = NULL;
    printf("Done!\n");
  }
}

void removeAtWanqiC(FractionListPtrWanqi myListPtr, int index) {
  FractionNodePtrWanqi removeNodePtr = *myListPtr;
  FractionNodePtrWanqi preNodePtr = NULL;
  int count = 1;

  printf("\n       Removing the %d-th Node...", index);

  if (!(*myListPtr))
    printf("\n\tCan't remove from an empty list!\n");
  else if (index <= 1|| !((*myListPtr)->next))
    removeFirstWanqiC(myListPtr);
  else if (index >= getLengthWanqiC(*myListPtr))
    removeLastWanqiC(myListPtr);
  else {
    while (count < index) {
      preNodePtr = removeNodePtr;
      removeNodePtr = removeNodePtr->next;
      count++;
    }
    preNodePtr->next = removeNodePtr->next;  
    freeFractionNodeWanqiC(removeNodePtr);
    printf("Done!\n");
  }


}

void freeFractionNodeWanqiC(FractionNodePtrWanqi frNodePtr) {
  free(frNodePtr->frPtr);
  free(frNodePtr);
}

void displayListWanqiC(FractionListWanqi myList) {
  FractionListWanqi currentNodePtr = myList;
  if (getLengthWanqiC(myList) == 0) {
    printf("\n  Empty List!\n");
  } else {
    printf("\n\tHere's the information about the current List:\n\n\
          Length of the list: %d\n", getLengthWanqiC(myList));
    do {
      printFractionNodeWanqiC(currentNodePtr);
      currentNodePtr = currentNodePtr->next;
    } while (currentNodePtr);
  }
}















