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


typedef struct FractionNodeWanqiC FractionNodeWanqi;
typedef FractionNodeWanqi* FractionNodePtrWanqi;
typedef FractionNodeWanqi* FractionListWanqi;
typedef FractionListWanqi* FractionListPtrWanqi;

//Function Prototypes
void outerMenuWanqiC(void);
void insertMenuWanqiC(void);
void removeMenuWanqiC(void);
int findGCD(int, int);
struct Fraction* createFractionWanqiC(void);
void printFractionInfoWanqiC(struct Fraction*);

bool isEmptyWanqiC(FractionList);
int getLengthWanqiC(FractionList);

void insertFirstWanqiC(FractionListAddr, struct FractionNode*);
void appendWanqiC(FractionListAddr, struct FractionNode*);
void insertAtWanqiC(FractionListAddr, struct FractionNode*, int);

void displayListWanqiC(FractionList);

int main() {

  int outerOption, insertOption, removeOption;
  FractionListAddr myListAddr = (FractionListAddr) malloc(sizeof(FractionList));
  struct FractionNode* myFractionNode = (struct FractionNode*) malloc(sizeof(struct FractionNode));
  struct Fraction* newFractionAddr;

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
              newFractionAddr = createFractionWanqiC();
              printFractionInfoWanqiC(newFractionAddr);

              myFractionNode->frPtr = newFractionAddr;
              myFractionNode->next = NULL;

              insertFirstWanqiC(myListAddr, myFractionNode);
              printf("checking if the list is empty: %s", isEmptyWanqiC(*myListAddr)? "true":"false");
              printf("getting the length of the list: %d", getLengthWanqiC(*myListAddr));
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

struct Fraction* createFractionWanqiC() {
  struct Fraction* tempPtr = NULL;
  int numTemp, denomTemp, gcd;

  tempPtr = (struct Fraction*) malloc(sizeof(struct Fraction));

  printf("\n       Please Enter the Numerator: ");
  scanf("%d", &numTemp);

  do {
    printf("\n       Please Enter a valid Denominator: ");
    scanf("%d", &denomTemp);
  } while (denomTemp == 0);

  gcd = findGCD(numTemp, denomTemp);
  tempPtr->num = numTemp/gcd;

  if (denomTemp < 0) {
    tempPtr->num = -(tempPtr->num);
    tempPtr->denom = -(denomTemp/gcd);    
  } else
    tempPtr->denom = denomTemp/gcd;

  return tempPtr;
}

int findGCD(int n, int m) {
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

void printFractionInfoWanqiC(struct Fraction* frPtr) {
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

bool isEmptyWanqiC(FractionList myList) {
  return (myList == NULL)? true:false;
}

int getLengthWanqiC(FractionList myList) {
  int count = 0;
  FractionList currentNodeAddr = myList;
  
  if (isEmptyWanqiC(myList))
    return 0;

  // printf("current node address: %p", currentNodeAddr->next);

  while (currentNodeAddr) {
    count++;
    currentNodeAddr = currentNodeAddr->next;
  };


  return count;
}


void insertFirstWanqiC(FractionListAddr myListAddr, 
                      struct FractionNode* newNodeAddr) {
  printf("\n       Inserting the Fraction at the Beginning of the List...\n");
  if (*myListAddr != NULL)
    newNodeAddr->next = *myListAddr;
  *myListAddr = newNodeAddr;
}

void appendWanqiC(FractionListAddr myListAddr,
                      struct FractionNode* newNodeAddr) {
  struct FractionNode* currentNodeAddr = *myListAddr;
  if(currentNodeAddr != NULL) {
    while(currentNodeAddr->next) 
      currentNodeAddr = currentNodeAddr->next;

    currentNodeAddr->next = newNodeAddr;
    newNodeAddr->next = NULL;
  } else {
    *myListAddr = newNodeAddr;
  }

}

void insertAtWanqiC(FractionListAddr myListAddr,
           struct FractionNode* newNodeAddr, int index) {
  int myListLength = getLengthWanqiC(*myListAddr), count = 1;
  struct FractionNode* currentNodeAddr = *myListAddr;

  if(index == 0 || myListLength == 0)
    insertFirstWanqiC(myListAddr, newNodeAddr);
  if(index >= myListLength)
    appendWanqiC(myListAddr, newNodeAddr);

  while(count < index){
    count++;
    currentNodeAddr = currentNodeAddr->next;
  }

  newNodeAddr->next = currentNodeAddr->next;
  currentNodeAddr->next = newNodeAddr;
}

void displayListWanqiC(FractionList myList) {
  printf("       Here's the information about the current List:\n");
  FractionList currentNodeAddr = myList;
  printf("here's the memory location of currentNodeAddr: %p", currentNodeAddr);
  printf("Length of the list: %d", getLengthWanqiC(myList));

  // for (int i = 0; i < getLengthWanqiC(myList); i++) {
  //   printf("\n      At index %d\n"
  //                     "Fraction memory Location: %p\n"
  //                     "Fraction Numerator:       %d\n"
  //                     "Fraction Denominator:     %d\n"
  //                     "Next Node in memory:      %p\n\n",
  //                      i, currentNodeAddr->frPtr, currentNodeAddr->frPtr->num, 
  //                      currentNodeAddr->frPtr->denom, currentNodeAddr->next);
  //   currentNodeAddr = currentNodeAddr->next;
  // }
}















