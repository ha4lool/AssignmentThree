#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "customerInfo.h"
//This program is to test the read/write/update of 2 customers records
int main(){
   customer customerArr[100];
   printf("\nEnter 2 Customers Records:");
   for (int i = 0 ; i <2 ; i++)
      customerArr[i] = enter_customerInfo();
//write on the file
   if (writeCustomer( customerArr) != 0) {
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Writing file: Error by perror is");
      exit (EXIT_FAILURE );
   }
//read the written records from the file
   customer* C =  loadCustomer ( "info.dat", 2);
   printf("\nDisplay All Customers Records:\n-----------------\n");
   for (int i = 0 ; i <2 ; i++)
        print_customer(C+i);
//update the last recored in the file
   if ( updateCustomer ( "info.dat") != 0){
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("updating file: Error by perror is");
      exit (EXIT_FAILURE );
   }
//read again from the file after updating
   customer* newC = loadCustomer ( "info.dat", 2);
   printf("\nDisplay All Customers Records AFTER the Update:\n-----------------\n");
          for ( int i =0;i<2;i++)
         print_customer(newC+i);
   return 0;
}
