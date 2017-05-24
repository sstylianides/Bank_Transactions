/* ----------------------------------------------------------------------------
 Program file: sstylia5.c
 Author: Stephan Stylianides
 Date: April 1st, 2017
 Objective: This program allows the user to make some simple banking transactions.
 It will first prompt the user to enter the current balance of their bank
 account (in dollars and cents, not less than zero). The program will
 then prompt the user to enter the number of withdrawals to make, and then
 the number of deposits to make (max 5). It will also give errors if words,
 negative numbers are used. Will also not allow the user to withdraw more than
 they have in their account

 NOTE: this program improves upon assignment #4 by using functions
 ------------------------------------------------------------------------------- */



#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Declare and initalize all global constants
const int ARRAY_MAX = 100;

int isInvalid(char parameter[])
{
    int flag=0;
    for(int counter=0; counter<strlen(parameter); counter++)
    {
        if(parameter[counter]=='.') continue;

        //Flag changes to 1 since input is not a digit
        else if(isdigit(parameter[counter])==0)
        {
            flag=1;
            if(parameter[counter]=='-') printf("\nPlease enter only postive numbers.\n\n");
            else printf("\nPlease enter only numbers.\n\n");
            break;
        }
    }
    return flag;
}

void menu1(float* balance, float *tot, int MAX[])
{
    char input[ARRAY_MAX]={};

    printf("Welcome to the Computer Banking System.\n\n");

    do
    {
        //give an error message when a negative number or words are used
        printf ("Enter your current balance in dollars and cents: ");
        scanf ("%s", input);

    }while(isInvalid(input)==1);

    *balance=atof(input);
    *tot=*balance;

    do
    {
        printf ("\nEnter the number of deposits (0-5): ");
        scanf ("%s", input);
    }while(isInvalid(input)==1 || atof(input) > 5 || atof(input)<0);

    MAX[0]=atof(input);

    do
    {
        printf ("\nEnter the number of withdrawls (0-5): ");
        scanf ("%s", input);
    }while(isInvalid(input)==1 || atof(input) > 5 || atof(input)<0);

    MAX[1]=atof(input);
}

void getDepWith(float* total ,int MAX[], float deposit[], float withdraw[])
{
    int flag=0;
    char input[ARRAY_MAX]={};

    for(int counter=0; counter<2; counter++)
    {
        //give an error message when a negative number or words are used
        for(int counter1 = 0; counter1 < MAX[counter]; counter1++)
        {
            //If we are looking at deposits gather the deposit data
            if(counter==0)
            {
                do
                {
                    printf ("Enter the ammount of deposit #%i: ", counter1+1);
                    scanf ("%s", input);
                }while(isInvalid(input)==1);

                *total+=atof(input);
                deposit[counter1]=atof(input);
            }

            else
            {
                do
                {
                    flag=0;
                    do
                    {
                        printf ("Enter the ammount of withdrawal #%i: ", counter1+1);
                        scanf ("%s", input);

                    }while(isInvalid(input)==1);

                    if(atof(input) > *total)
                    {
                        flag=1;
                        printf("\nOverdraft error.\n\n");

                    }

                    else
                    {
                        *total-=atof(input);
                        withdraw[counter1]=atof(input);
                    }

                }while(flag==1);


            }

        }
    }

}

void finalMenu(float* balance, float* total, int MAX[], float deposit[], float withdraw[])
{
    printf("\n$%0.2f\n\n", *total);

    //give a message after closing balance
    if(*total>=50000) printf("*** It's time to invest some money! ***");
    else if(*total>=15000 && *total<49999.99) printf("*** Maybe you should consider a CD. ***");
    else if(*total>=1000 && *total<14999.99) printf("*** Keep up the good work! ***");
    else if(*total>=0 && *total<999.99) printf("*** Your balance is getting low! ***");


    //give a bank record with starting balance, deposits & withdrawals with transaction ammounts and ending balance
    printf("\n\nBank Record: \n");


    printf("\nStarting Balance: $%0.2f\n", *balance);

    for(int counter=0; counter<2; counter++)
    {
        for(int counter1=0; counter1<MAX[counter]; counter1++)
        {
            if(counter==0) printf("\nDeposit #%i: $%0.2f", counter1+1, deposit[counter1]);
            else printf("\nWithdrawal #%i: $%0.2f", counter1+1, withdraw[counter1]);
        }
    }

    printf("\n\nEnding Balance: $%0.2f\n", *total);
}


int main()
{
    // declare and initalize all local variables
    float deposit[5], withdraw[5], balance;
    float total=0;

    //For array MAX the deposit max is MAX[0]
    //the withdrawl max is MAX[1]
    int MAX[2];

    menu1(&balance, &total, MAX);

    getDepWith(&total, MAX, deposit, withdraw);

    finalMenu(&balance, &total, MAX, deposit, withdraw);

    getchar( );
    return 0;
}
