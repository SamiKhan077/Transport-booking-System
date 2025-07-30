/*
This module will create new user account and add it to the database.
Function : signup()
Return value : Null

*/
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "signin.h"
void signup()
{
    char user[100],check[30]="null",pass[30];
    int flag=0;
    FILE *ptr;
    ptr=fopen("user.dat","a+");

    
        fscanf(ptr,"%s\n",check);
        if(strcmp(check,"null")!=0)
        {
       x:
       printf("Enter the username:\n");
       scanf("%s",user);
       printf("Enter the password:\n");
      y: 
      scanf("%s",pass);
       if(pass_validate(pass)==0)
       {
           printf("Password is not stronger:(\nPlese enter Strong Password:\n");
           goto y;
       }


       do
       {
            if(strcmp(user,check)==0)
        {
            printf("Already exists:(\n");
            flag=1;
            goto x;
       }
       } while (fscanf(ptr,"%s\n",check)!=EOF);
        fprintf(ptr,"\n%s %s",user,pass);
        }
        else
        {
               printf("Enter the username:\n");
             scanf("%s",user);
             printf("Enter the password:\n");
            z: scanf("%s",pass);
               if(pass_validate(pass)==0)
                 {
                    printf("Password is not stronger:(\nPlese enter Strong Password:\n");
                    goto z;
                  }
             fprintf(ptr,"%s %s",user,pass);   
        }
        

       fclose(ptr);
       printf("Account created please Signin :)!\n");
        signin();
       
 }
  


    
    
    
