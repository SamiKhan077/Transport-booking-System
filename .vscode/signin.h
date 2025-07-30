/*
This module will signin the user, who are all already signedup.
Function name: signin()
Return Value: NULL

*/
#include"validation.h"
#include <stdio.h>
#include <string.h>
void signin()
{
    char in_user[100],in_pass[100],in_check[30]={"null"},in_fuser[30],in_fpass[30];
   
    int i=0,flag=0;

    FILE *ptr;
  x:   printf("Enter the username:\n");
        scanf("%s",in_user);
        ptr=fopen("user.dat","a+");
    
       while(fscanf(ptr,"%s %s\n",in_fuser,in_fpass)!=EOF)
       {
           if(strcmp(in_fuser,in_user)==0)
             {
                y: printf("Enter the password:\n");
                scanf("%s",in_pass);
                 if(strcmp(in_fpass,in_pass)==0)
                 {

                     flag=1;
                     printf("You are Logged in :)\n ..........Welcome to ROUTE MASTER.........");
                     break;
                 }
                 else
                 {
                     printf("Incorrect Password:(\n");
                     goto y;
                 }
                 
             }
             fclose(ptr);
       }

       if(flag==0)
       {
           printf("Username does not exists:(\n");
           goto x;
       }

    fclose(ptr);


}