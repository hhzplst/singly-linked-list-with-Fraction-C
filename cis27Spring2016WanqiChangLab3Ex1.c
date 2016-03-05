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
FractionNodePtrWanqi createFractionNodeWanqiC(void);
void printFractionNodeWanqiC(FractionNodePtrWanqi);

bool isEmptyWanqiC(FractionListWanqi);
int getLengthWanqiC(FractionListWanqi);
void displayListWanqiC(FractionListWanqi);

void insertFirstWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void appendWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi);
void insertAtWanqiC(FractionListPtrWanqi, FractionNodePtrWanqi, int);

void removeFirstWanqiC(FractionListPtrWanqi);
void removeLastWanqiC(FractionListPtrWanqi);
void removeAtWanqiC(FractionListPtrWanqi, int);
void freeFractionNodeWanqiC(FractionNodePtrWanqi);


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

          switch(removeOption) {
            case 1: 
              removeFirstWanqiC(myListPtr);
              break;
            case 2:
              if (!myList)
                printf("\n\tCan't remove from an empty list!\n");
              else {
                printf("\n       Which node would you want to remove (start at 1): ");
                scanf("%d", &index);
                removeAtWanqiC(myListPtr, index);                
              }
              break;
            case 3:
              if (!myList)
                printf("\n\tCan't remove from an empty list!\n");
              else 
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
        } while (removeOption != 5);
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
  int numTemp, denomTemp, gcd;
  FractionPtrWanqi tempPtr = NULL;
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
  
  while(n != 0) {
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

  while(currentNodePtr->next != NULL) {
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

  if (currentNodePtr) {
    while(currentNodePtr->next) 
      currentNodePtr = currentNodePtr->next;
    currentNodePtr->next = newNodePtr;
  } else
    *myListPtr = newNodePtr;

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
    while(count < index) {
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
    printf("\n\tCan't remove from an empty list!\n");
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
    while(currentNodePtr->next->next)
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
    
  if (index <= 1|| !((*myListPtr)->next))
    removeFirstWanqiC(myListPtr);
  else if (index >= getLengthWanqiC(*myListPtr))
    removeLastWanqiC(myListPtr);
  else {
    while(count < index) {
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
    printf("\n\tEmpty List!\n");
  } else {
    printf("\n\tHere's the information about the current List:\n\n\
          Length of the list: %d\n", getLengthWanqiC(myList));
    do {
      printFractionNodeWanqiC(currentNodePtr);
      currentNodePtr = currentNodePtr->next;
    } while (currentNodePtr);
  }
}

/********************OUTPUT***********************

CIS 27 - C Programming
Laney College
Wanqi Chang

Assignment Information --
  Assignment Number:  Lab 03,
                      Coding Assignment -- Excercise #1
  Written by:         Wanqi Chang
  Submitted Date:     2016/03/10

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 3

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 1

  Can't remove from an empty list!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 2

  Can't remove from an empty list!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 3

  Can't remove from an empty list!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 4

  Empty List!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 1

  Empty List!

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 1

  Empty List!

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 2

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 3

       Please Enter the Numerator: 4

       Please Enter a valid Denominator: 9

       Inserting the Node at the end of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 1

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 1 

       Please Enter the Numerator: 3

       Please Enter a valid Denominator: -9

       Inserting the Node at the beginning of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 2

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       -1
    Denominator:     3

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 2

       Please Enter the Numerator: 2

       Please Enter a valid Denominator: 11

       Inserting the Node after 2-th of the list...
       Inserting the Node at the end of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 3

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       -1
    Denominator:     3

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 3

       Please Enter the Numerator: 8

       Please Enter a valid Denominator: -15

       Inserting the Node at the end of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 4

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       -1
    Denominator:     3

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 1

  Here's the information about the current List:

          Length of the list: 4

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       -1
    Denominator:     3

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 3

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): -1

  Wrong option!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 1

       Removing the Node at the beginning of the list...Done!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 3

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 2

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 2

       Please Enter the Numerator: 5

       Please Enter a valid Denominator: 101

       Inserting the Node after 2-th of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 4

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 1

       Please Enter the Numerator: 1

       Please Enter a valid Denominator: 4

       Inserting the Node at the beginning of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 5

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       1
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 1

       Please Enter the Numerator: 5

       Please Enter a valid Denominator: 12

       Inserting the Node after 1-th of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 6

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       1
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 3

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 1

       Removing the Node at the beginning of the list...Done!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 5

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 2

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 0

       Please Enter the Numerator: 3

       Please Enter a valid Denominator: 4

       Inserting the Node after 0-th of the list...
       Inserting the Node at the beginning of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 6

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       3
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 5

       Please Enter the Numerator: 6

       Please Enter a valid Denominator: 17

       Inserting the Node after 5-th of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 7

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       3
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500080
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500080
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3403310
    Numerator:       6
    Denominator:     17

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 3

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 2

       Which node would you want to remove (start at 1): 6

       Removing the 6-th Node...Done!

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 6

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       3
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ***********************
     *    Removing Menu    *
     * 1.  First node      *
     * 2.  n-th node       *
     * 3.  Last node       *
     * 4.  Displaying      *
     * 5.  Quit            *
     ***********************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 2

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 2

       Please Enter the Numerator: 3

       Please Enter a valid Denominator: -7

       Inserting the Node after 2-th of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 7

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       3
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500090
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500090
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500080
    Numerator:       -3
    Denominator:     7

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 2

       After which node would you want to insert (start at 1): 6

       Please Enter the Numerator: 6

       Please Enter a valid Denominator: 17

       Inserting the Node after 6-th of the list...Done!

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 4

  Here's the information about the current List:

          Length of the list: 8

    Current fraction node is at: 0x7fd4d3500050
          Linking to the next node at: 0x7fd4d3500070
          Having the Fraction information:

    Memory Location: 0x7fd4d3403300
    Numerator:       3
    Denominator:     4

    Current fraction node is at: 0x7fd4d3500070
          Linking to the next node at: 0x7fd4d3500090
          Having the Fraction information:

    Memory Location: 0x7fd4d3500060
    Numerator:       5
    Denominator:     12

    Current fraction node is at: 0x7fd4d3500090
          Linking to the next node at: 0x7fd4d3500010
          Having the Fraction information:

    Memory Location: 0x7fd4d3500080
    Numerator:       -3
    Denominator:     7

    Current fraction node is at: 0x7fd4d3500010
          Linking to the next node at: 0x7fd4d3500030
          Having the Fraction information:

    Memory Location: 0x7fd4d3500000
    Numerator:       4
    Denominator:     9

    Current fraction node is at: 0x7fd4d3500030
          Linking to the next node at: 0x7fd4d3500020
          Having the Fraction information:

    Memory Location: 0x7fd4d3400280
    Numerator:       2
    Denominator:     11

    Current fraction node is at: 0x7fd4d3500020
          Linking to the next node at: 0x7fd4d35000b0
          Having the Fraction information:

    Memory Location: 0x7fd4d3401350
    Numerator:       5
    Denominator:     101

    Current fraction node is at: 0x7fd4d35000b0
          Linking to the next node at: 0x7fd4d3500040
          Having the Fraction information:

    Memory Location: 0x7fd4d35000a0
    Numerator:       6
    Denominator:     17

    Current fraction node is at: 0x7fd4d3500040
          Linking to the next node at: 0x0
          Having the Fraction information:

    Memory Location: 0x7fd4d3400020
    Numerator:       -8
    Denominator:     15

     ************************
     *    Inserting Menu    *
     * 1.  As first node    *
     * 2.  After n-th node  *
     * 3.  As last node     *
     * 4.  Displaying       *
     * 5.  Quit             *
     ************************
     Select the option (1 through 5): 5

************************************
*    LINKED LIST MENU: Fraction    *
* 1.  Displaying current list      *
* 2.  Inserting                    *
* 3.  Removing                     *
* 4.  Quit                         *
************************************
Select the option (1 through 4): 4

  Fractions and Linked Lists!

******************END OF OUTPUT*******************/


/********************COMMENT**********************

                    NO COMMENT

**************************************************/