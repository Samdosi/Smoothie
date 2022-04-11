/*
 Mohammad Ali Dosi
 smoothie.c
 09/12/2021
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string 25

typedef struct item {
    int itemID;
    int numParts;
    
} item;
typedef struct recipe {
    int numItems;
    item* itemList;
    int totalParts;

}recipe;


// function prototype

char** readIngredients(int numIngredients);
recipe* readRecipe(int numItems);
recipe** readAllRecipes(int numRecipes);
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
void  printOrder(char**  ingredientNames,  double*  orderList,  int numIngredients);
void freeIngredients(char** ingredientList, int numIngredients);
void freeRecipes(recipe** allRecipes, int numRecipes);


int main() {
    int n, s, k, i ;
    char** ingredlist;
    int * smothienum;
    double* ingred_list;
    recipe** recepieread;
    // n is the number of smoothie ingredients
    scanf("%d", &n);
    // reading the ingreduents from from user
    ingredlist=readIngredients(n);
    // s is the number of different smoothie recepie
    scanf("%d", &s);
    recepieread=(recipe**)malloc(s*sizeof(recipe*));
    recepieread=readAllRecipes(s);
    // k is the number of stores making the order
    scanf("%d", &k);
    smothienum=(int*)malloc(k*sizeof(int));
    ingred_list=(double*)malloc(sizeof(double)*n);
    for(i=0; i<k; i++)
    {
    
        scanf("%d", &smothienum[i]);
        ingred_list=calculateOrder(smothienum[i], recepieread,n);
        printf("Store #%d:\n",i+1);
        printOrder(ingredlist, ingred_list, n);


    }
    // free the memory
    free(ingred_list);
    freeIngredients(ingredlist, n);
    freeRecipes(recepieread, s);
    
    
    
    
    return 0;
}

// reads in the ingredients from the user and return a double pointer
char** readIngredients(int numIngredients)
{
    char temp[max_string];
    char** ingredlist=NULL ;
    int i;
    ingredlist= (char**)malloc(numIngredients*sizeof(char*));
    // store the ingredients name into ingredlist[i]
    for(i=0; i<numIngredients;i++)
    {
        ingredlist[i]=(char*)malloc(max_string*sizeof(char));
        scanf("%s", temp);
        strcpy(ingredlist[i], temp);
        
    }
    return ingredlist;
}
// read in the id of the different smoothie and ratio of it and store them into the struc, it return a pointer of type recipe
recipe* readRecipe(int numItems)
{
    recipe* readrecipe;
    readrecipe= (recipe*) malloc(sizeof(recipe));
    // updating the numItems
    readrecipe->numItems=numItems;
    readrecipe->itemList = (item *) malloc (numItems * sizeof (item));
    for(int i=0; i<numItems; i++)
    {
        scanf("%d", &readrecipe->itemList[i].itemID);
               scanf("%d", &readrecipe->itemList[i].numParts);
        
    }
    

    
    
    return readrecipe;
    
    

}
// read in the number of ingredients and and call the readRecepie function, it stores everyting into the struc and return a double pointer of type recepie
recipe** readAllRecipes(int numRecipes)
{
    int i, numingred;
    int total=0;
    recipe** smoothieList;
    smoothieList=(recipe**)malloc(numRecipes*sizeof(recipe*));

    for(i=0; i<numRecipes; i++)
    {
        scanf("%d", &numingred);
        smoothieList[i]=(recipe*)malloc(numingred*2*sizeof(recipe));
        smoothieList[i]=readRecipe(numingred);
        
        
    }
    // finding the total ingredients by summing up the amount of each ingredinets
    for(i=0; i<numRecipes; i++)
        {
            total=0;
            for(int j=0; j< smoothieList[i]->numItems; j++)
            {
                total+= smoothieList[i]->itemList[j].numParts;
            }
            // update the totalParts of the struct
            smoothieList[i]->totalParts=total;
        }
 
    return smoothieList;

}
// calculate the amount of each ingredients and return a double pointer
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients)
{
    double* amtOfEachItem;
    int* choice;
    int* weight;
    int i, j;
    choice=(int*)malloc(numSmoothies*sizeof(int));
    weight=(int*)malloc(numSmoothies*sizeof(int));
    for(i=0; i<numSmoothies; i++)
    {
        scanf("%d", &choice[i]);
        scanf("%d", &weight[i]);
    }
    amtOfEachItem=(double*)malloc(numIngredients*sizeof(double)) ;
    double res=0, rem=0;
    
    // calculating the result by subtracting total parts from the total weight
    for(i=0; i<numSmoothies; i++)
    {
        rem=weight[i]*1.0/(recipeList[choice[i]]->totalParts)*1.0;
    
        for(j=0; j<recipeList[choice[i]]->numItems; j++)
        {
            res=0;
            res=rem * recipeList[choice[i]]->itemList[j].numParts ;
            amtOfEachItem[recipeList[choice[i]]->itemList[j].itemID] += res;
            
        }
    }
    return amtOfEachItem;
}


// printig the result
void  printOrder(char**  ingredientNames,  double*  orderList,  int numIngredients)
{
    int i ;
    for(i=0; i<numIngredients; i++)
    {
        // check to see if the result is more than 0
      if(orderList[i]>0)
     {
     printf("%s  ",ingredientNames[i]);
     printf("%.6lf\n", orderList[i]);
        
      }
    }
}
// free the memory
void freeIngredients(char** ingredientList, int numIngredients)
{
    int i;
    for(i=0; i<numIngredients; i++)
    {
        free(ingredientList[i]);
    }
    free(ingredientList);
}
// free the memory
void freeRecipes(recipe** allRecipes, int numRecipes)
{
    int i;
    for(i=0; i<numRecipes; i++)
    {
        free(allRecipes[i]);
    }
    free(allRecipes);
}

