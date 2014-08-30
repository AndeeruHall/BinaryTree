#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <conio.h>
#include"phones.h"

PLNK * init(void);
void attachNode(PLNK *, PLNK *);
void printAll(PLNK *);
void searchForDelete(PLNK * *);
void deleteNode(PLNK * *, char[], char[]);
void addNode(PLNK *);
void formatNode(PLNK *);
void printOne(char [], PLNK *);
void recieveInput(PLNK *);
void searchForModify(PLNK * *);
PLNK * modifyNode(PLNK * *, char[], char[]);
void printLeaf(PLNK *);
void printPrefix(PLNK *, int);
void typePrefix(PLNK *);

int main()
{
	PLNK * ptrRoot = init();
    int choice = 0;
	if('q'<'h')
	{
		printf("true");
	}
	else
	{
		printf("false");
	}
    

    do
    {
    printf("\n1. PRINT ONE");
    printf("\n2. PRINT All");
    printf("\n3. ADD FRIEND");
    printf("\n4. DELETE ENTRY");
	printf("\n5. MODIFY RECORD");
	printf("\n6. PRINT LEAF");
	printf("\n7. PRINT PREFIX");
	printf("\n0. EXIT");
	printf("\nEnter -> ");
	scanf("%d", &choice);
	fflush(stdin);
	switch(choice)
		{
			case 1 :  recieveInput(ptrRoot);
				            break;
			case 2:   printAll(ptrRoot);
			                break;
			case 3:   addNode(ptrRoot);
			                break;
			case 4:   searchForDelete(&ptrRoot);
			                break;  
			case 5:   searchForModify(&ptrRoot);
				            break;
			case 6:   printLeaf(ptrRoot);
							break;
			case 7:   typePrefix(ptrRoot);
			case 0:
							break;
		}
    }while(choice);

    system("pause");
    return(0);
 
}

PLNK * init(void)
{
   PLNK * ptrRoot = NULL;
   PLNK * ptrAttach = NULL;
   FILE * fptr = NULL;

   if(!(fptr = fopen("phones.dat", "r")))
   {
     printf("ERROR opening file");
     system("pause");
     return(0);
   }

   ptrRoot = (PLNK *)malloc(sizeof(PLNK));
   ptrRoot->left = NULL;
   ptrRoot->right = NULL;
   fread(ptrRoot, sizeof(PREC), 1, fptr);
  

   ptrAttach = (PLNK *)malloc(sizeof(PLNK));
   ptrAttach->left = NULL;
   ptrAttach->right = NULL;
   fread(ptrAttach, sizeof(PREC), 1, fptr);
   while( !feof(fptr) )
   {
     attachNode(ptrRoot, ptrAttach);
     ptrAttach = (PLNK *)malloc(sizeof(PLNK));
     ptrAttach->left = NULL;
     ptrAttach->right = NULL;
     fread(ptrAttach, sizeof(PREC), 1, fptr);
   }
   free(ptrAttach);
   fclose(fptr);
   return ptrRoot;
}
void attachNode(PLNK * ptrCurrent, PLNK *ptrAttach)
{
  char fullNameAttach[27];
  char fullNameHead[27];
  char fullNameCurrent[27];
  int compare = 0;

  sprintf(fullNameAttach,"%s %s",ptrAttach->lname, ptrAttach->fname);
  sprintf(fullNameCurrent,"%s %s",ptrCurrent->lname, ptrCurrent->fname);  
  compare = strcmp(fullNameAttach, fullNameCurrent);

  while(1)
  {
    if(compare  < 0)  
    {
      if(ptrCurrent->left==NULL) 
      {
        ptrCurrent->left = ptrAttach;
        break;
      }
      else
      {
        ptrCurrent=ptrCurrent->left;
      }
    }
    else
    {
      if(ptrCurrent->right==NULL)
      {
         ptrCurrent->right = ptrAttach;
         break;
      }
      else
      {
         ptrCurrent=ptrCurrent->right;
      }
    }
	 sprintf(fullNameCurrent,"%s %s",ptrCurrent->lname, ptrCurrent->fname);  
     compare = strcmp(fullNameAttach, fullNameCurrent);
  }
  return;
}
void printAll(PLNK * ptrPrintMe)
{
  if(ptrPrintMe->left != NULL)
  {
    printAll(ptrPrintMe->left);
  } 

  printf("\n%-15s%-10s%d-%04d", ptrPrintMe->lname, ptrPrintMe->fname, ptrPrintMe->prefix, ptrPrintMe->ph_num );

  if(ptrPrintMe->right != NULL)
  {
    printAll(ptrPrintMe->right);
  }
}
void searchForDelete(PLNK * * dblAbove)
{
   PLNK * ptrCurrent;
   char lastName[15];
   char firstName[10];
   printf("\n Enter the last name: " );
   scanf("%s", lastName);
   printf("\n Enter the first name: " );
   scanf("%s", firstName);

   deleteNode(dblAbove, lastName, firstName);
}
void deleteNode(PLNK * * dblAbove, char lastName[], char firstName[])
{
   PLNK * ptrCurrent = *dblAbove;
   int compare = 0;
   char fullNameCurrent[27];
   char fullNameCompare[27];

   sprintf(fullNameCompare,"%s %s",lastName, firstName);
   sprintf(fullNameCurrent,"%s %s",ptrCurrent->lname, ptrCurrent->fname);  

   if((*dblAbove) == NULL)
   {
     printf("not found");
     return;
   }

   if( ((!strcmp(ptrCurrent->lname, lastName)) &&  (!strcmp(ptrCurrent->fname, firstName))) ) // found
   {   
     
	 if(ptrCurrent->left == NULL)
     {
       *dblAbove = ptrCurrent->right;
       free(ptrCurrent);
       return ;
     }
     if(ptrCurrent->right == NULL)
     {
       *dblAbove = ptrCurrent->left;
       free(ptrCurrent);
       return ;
     }
     *dblAbove = ptrCurrent->left;
     attachNode(*dblAbove, ptrCurrent->right);
     free(ptrCurrent);
     return ;
   }
   else // left or right
   {
     compare = strcmp(fullNameCompare, fullNameCurrent); 
     if(compare < 0)
     {       
         deleteNode(&ptrCurrent->left, lastName, firstName);
     }
     else
     {       
         deleteNode(&ptrCurrent->right, lastName, firstName);
     }
   }
}
void addNode(PLNK* ptrRoot)
{
	PLNK* ptrCurrent;
	ptrCurrent = (PLNK *)malloc(sizeof(PLNK));
    ptrCurrent->left = NULL;
    ptrCurrent->right = NULL;

	formatNode(ptrCurrent);
	attachNode(ptrRoot, ptrCurrent);

	return;
}
void formatNode(PLNK * ptrEntry)
{
   int i = 0;	
	
   printf("\n Enter the last name: " );
   scanf("%s", ptrEntry->lname);
   fflush(stdin);
   printf("\n Enter the first name: " );
   scanf("%s", ptrEntry->fname);
   fflush(stdin);

   while(ptrEntry->lname[i] != '\0')
   {	
	   ptrEntry->lname[i] = tolower(ptrEntry->lname[i]);
	   i++;
   }
   ptrEntry->lname[0] = toupper(ptrEntry->lname[0]);

   i=0;
   while(ptrEntry->fname[i] != '\0')
   {	
	   ptrEntry->fname[i] = tolower(ptrEntry->fname[i]);
	   i++;
   }
   ptrEntry->fname[0] = toupper(ptrEntry->fname[0]);

   printf("\n Enter the prefix (xxx): " );
   scanf("%d", &ptrEntry->prefix);
   fflush(stdin);
   printf("\n Enter the phone number (xxxx): " );
   scanf("%d", &ptrEntry->ph_num);
   fflush(stdin); 
   return;
}
void printOne(char fullNamePrint[], PLNK * ptrRoot)
{
   PLNK * ptrCurrent = ptrRoot;
   char fullNameCurrent[27];
   int compare = 0;

   sprintf(fullNameCurrent,"%s %s",ptrCurrent->lname, ptrCurrent->fname);  
   compare = strcmp(fullNamePrint, fullNameCurrent);

   if(compare == 0)
   {
	   printf("\n%-15s%-10s%d-%04d", ptrCurrent->lname, ptrCurrent->fname, ptrCurrent->prefix, ptrCurrent->ph_num );
   }
   if(compare < 0)
   {
	   if(ptrRoot->left == NULL)
	   {
		   printf("not found");
		   return;
	   }
	   ptrRoot = ptrRoot->left;
	   printOne(fullNamePrint, ptrRoot);
	   return;
   }
   if(compare > 0)
   {
	   if(ptrRoot->right == NULL)
	   {
		   printf("not found");
		   return;
	   }
	   ptrRoot = ptrRoot->right;
	   printOne(fullNamePrint, ptrRoot);
	   return;
   }
}
void recieveInput(PLNK * ptrRoot)
{
   char lastName[15];
   char firstName[10];
   char fullName[27];   

   printf("\n Enter the last name: " );
   scanf("%s", lastName);
   printf("\n Enter the first name: " );
   scanf("%s", firstName);
   sprintf(fullName,"%s %s",lastName, firstName);

   printOne(fullName, ptrRoot);
   return;
}
void searchForModify(PLNK * * dblAbove)
{
   PLNK * ptrCurrent;
   char lastName[15];
   char firstName[10];
   printf("\n Enter the last name: " );
   scanf("%s", lastName);
   printf("\n Enter the first name: " );
   scanf("%s", firstName);

   ptrCurrent = modifyNode(dblAbove, lastName, firstName);
   attachNode(*dblAbove, ptrCurrent);
}
PLNK * modifyNode(PLNK * * dblAbove, char lastName[], char firstName[])
{
   PLNK * ptrCurrent = *dblAbove;
   int compare = 0;
   char fullNameCurrent[27];
   char fullNameCompare[27];

   sprintf(fullNameCompare,"%s %s",lastName, firstName);
   sprintf(fullNameCurrent,"%s %s",ptrCurrent->lname, ptrCurrent->fname);  

   if((*dblAbove) == NULL)
   {
     printf("not found");
     return NULL;
   }

   if( ((!strcmp(ptrCurrent->lname, lastName)) &&  (!strcmp(ptrCurrent->fname, firstName))) ) // found
   {   
     
	 if(ptrCurrent->left == NULL)
     {
       *dblAbove = ptrCurrent->right;
	   printf("\nNew Record");
       formatNode(ptrCurrent);
       return ptrCurrent;
     }
     if(ptrCurrent->right == NULL)
     {
       *dblAbove = ptrCurrent->left;
	   printf("\nNew Record");
       formatNode(ptrCurrent);
       return ptrCurrent;
     }
     *dblAbove = ptrCurrent->left;
     attachNode(*dblAbove, ptrCurrent->right);
	 printf("\nNew Record");
     formatNode(ptrCurrent);
     return ptrCurrent;
   }
   else // left or right
   {
     compare = strcmp(fullNameCompare, fullNameCurrent); 
     if(compare < 0)
     {       
         modifyNode(&ptrCurrent->left, lastName, firstName);
     }
     else
     {       
         modifyNode(&ptrCurrent->right, lastName, firstName);
     }
   }
}
void printLeaf(PLNK * ptrPrintMe)
{
  if((ptrPrintMe->left == NULL) && (ptrPrintMe->right == NULL))
  {
	  printf("\n%-15s%-10s%d-%04d", ptrPrintMe->lname, ptrPrintMe->fname, ptrPrintMe->prefix, ptrPrintMe->ph_num );
  }
  else
  {
	if(ptrPrintMe->left != NULL)
	{
		printLeaf(ptrPrintMe->left);
    }
	if(ptrPrintMe->right != NULL)
    {
		printLeaf(ptrPrintMe->right);
    }
  }
}
void printPrefix(PLNK * ptrPrintMe, int prefix)
{  
  if(ptrPrintMe->left != NULL)
  {
    printPrefix(ptrPrintMe->left, prefix);
  } 
  if(ptrPrintMe->prefix == prefix)
  {
	printf("\n%-15s%-10s%d-%04d", ptrPrintMe->lname, ptrPrintMe->fname, ptrPrintMe->prefix, ptrPrintMe->ph_num );
  }
  if(ptrPrintMe->right != NULL)
  {
    printPrefix(ptrPrintMe->right, prefix);
  }
}
void typePrefix(PLNK * ptrPrintMe)
{
	int prefix = 0;
	printf("\nEnter the prefix you are searching for: ");
	scanf("%d", &prefix);
	
	printPrefix(ptrPrintMe, prefix);

}

