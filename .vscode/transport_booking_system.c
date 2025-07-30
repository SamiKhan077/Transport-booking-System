#include<stdio.h>
#include<string.h>
char a[20][20]={"Kalabagan","Shaymoli","Mirpur","Gulshan","Banasree","Uttara","Rampura","Tongi","Savar","New Market"};
int from,to,ticket_count=0;
char in_user[100];

    struct user
    {
        char name[100];
        //char dob[10]
        //int mobile;
        int avbalance;
        char gender[10];
        //char from[100];
        //char to[100];
        char username[100];
        char password[100];


    };


    struct ticket
    {	int flag;
        int price;
        char from[100];
        char to[100];
        int serialno;



    };


    struct bus
    {
        int seatavb;
        int busno;
        int totalseats;
        struct ticket tickets[60];
        char from[20];
        char to[20];
        float time;

    }bus_obj[48];


int abs(int x){
	if(x<0)
		return -x;
	else
		return x;
}
int checkp(char* a);
void signin();
//function to sign up
/*
This module will create new user account and add it to the database.
Function : signup()
Return value : Null

*/
void signup()
{
    char user[100],check[30],pass[30];
    int rs,flag=0;
    FILE *ptr;
    ptr=fopen("user.dat","r");
    
    if(ptr == NULL) {
        // File doesn't exist, create it
        ptr = fopen("user.dat", "w");
        fclose(ptr);
        ptr = fopen("user.dat", "r");
    }
    
    // Check if username already exists
    printf("Enter the username:\n");
    scanf("%s",user);
    
    while(fscanf(ptr,"%s %s",check,pass)!=EOF)
    {
        if(strcmp(user,check)==0)
        {
            printf("Oh sorry! Somebody took that!,try again by different name:)\n");
            fclose(ptr);
            signup();
            return;
        }
    }
    fclose(ptr);
    
    // Username is available, get password
    p1:
    printf("Enter the secret code:\n");
    scanf("%s",pass);
    rs=checkp(pass);
    if(rs<3)
        goto p1;

    // Write to file
    ptr = fopen("user.dat", "a");
    fprintf(ptr,"%s %s\n",user,pass);
    fclose(ptr);
    
    printf("Account created please Login :) !\n");
    signin();
}

 //function to check password strength
 /*This module validate the password criteria :
Funcion name: pass_validate(String)
Return value: 
    1->Password Accepted
    0->Password not Accepted
*/
int checkp(char* a)
{
  int num_flag=0,A_flag=0,a_flag=0,spl_flag=0,signal;
   for(int i=0;a[i]!='\0';i++)
   {
     if(a[i]>=48 && a[i]<=57)
      num_flag=1;
     if(a[i]>=65 && a[i]<=90)  // Fixed: uppercase letters A-Z
      A_flag=1;
     if(a[i]>=97 && a[i]<=122)  // lowercase letters a-z
      a_flag=1;
     if(a[i]=='!'||a[i]=='@'||a[i]=='#'||a[i]=='$'||a[i]=='%'||a[i]=='^'||a[i]=='&'||a[i]=='*'||a[i]=='('||a[i]==')'||a[i]=='-'||a[i]=='+')
      spl_flag=1;
  }
  signal=num_flag+A_flag+a_flag+spl_flag;
  if(signal==4)
    printf("woW,Strong Password\n");
  if(signal==3)
    printf("oK,Moderate Password\n");
  if(signal<3)
    printf("No its too Weak password,we cannot accept that:(\n");
  return signal;
}
//function to signin
/*
This module will signin the user, who are all already signedup.
Function name: signin()
Return Value: NULL

*/
void signin()
{
    char in_pass[100],in_fuser[30],in_fpass[30];
    int flag=0;
    FILE *ptr;
    
    ptr=fopen("user.dat","r");
    if(ptr == NULL) {
        printf("No users found. Please sign up first.\n");
        return;
    }
    
  x:   printf("Enter the username:\n");
        scanf("%s",in_user);

       while(fscanf(ptr,"%s %s",in_fuser,in_fpass)!=EOF)
       {
           if(strcmp(in_fuser,in_user)==0)
             {
                y: printf("Enter your secret code:\n");
                scanf("%s",in_pass);
                 if(strcmp(in_fpass,in_pass)==0)
                 {

                     flag=1;
                     printf("You are Logged in :)\n ..........Welcome to ROUTE MASTER.........\n\n");
                     break;
                 }
                 else
                 {
                     printf("No,its not your secret code,Tryagain:(\n");
                     goto y;
                 }

             }

       }
       fclose(ptr);

       if(flag==0)
       {
           printf("First create your account or check the Spelling:(\n");
           goto x;
       }
}

void login()
{
    printf("                  ***Route Master***\n\n\n              Enter a choice\n          1. I don't have an account..Help me to create one.\n          2. I am an Existing user let me sign in.\n");
    char choice;
 

    l:
    scanf("%c",&choice);
    getchar();

    if (choice=='1')
    {
        
    }
    else if(choice=='2')
    {
        
    }
    else
    {
        printf("I think you hit a wrong Button:(\n");
        printf("Please Hit Again:)\n");
        goto l;
    }
    
    
    switch (choice)
    {
    case '1':
        signup();
        break;
    case '2':
        signin();
        break;

    }

}

    void print_ticket(struct ticket t1)
   {
   	printf("\n");
	printf("E-Ticket : ");
	printf("\n");
	printf("\t\t\t\t\t\t************************************\n");
	printf("\t\t\t\t\t\t***********Ticket Details***********\n");
	printf("\t\t\t\t\t\t     UserName : %s\n",in_user);
	printf("\t\t\t\t\t\t     From     : %s\n",t1.from);
	printf("\t\t\t\t\t\t     To       : %s\n",t1.to);
	printf("\t\t\t\t\t\t     Price    :RS.%d\n",t1.price);
	printf("\t\t\t\t\t\t***********Ticket Booked***********\n");
	printf("\t\t\t\t\t\t***********************************\n");
   }

int ticket_price(int from,int to)
{
  int i,temp=0,p=5;
  temp=abs(from-to);
  if(temp==1)
   return p;
  if(temp>1)
  {
    for(i=0;i<temp-1;i++)
     {
	p=p+2;
     }
    return p;
  }
return 0;
}

void select_from_to()
{
int loc_count=10; // Fixed: there are exactly 10 locations
printf("Choose the Boarding Stop: \n");
for(int i=0;i<loc_count;i++)
{
printf("%d.%s\n",i+1,a[i]);
}
do
{
scanf("%d",&from);
if(from>loc_count || from<1)
{
 printf("Can't get that! Please select from given location:)\n");
 printf("Choose Boarding Stop: \n");
}

}while(from>loc_count || from<1);

printf("Choose the destination stop: \n");
for(int i=0;i<loc_count;i++)
{
  if(i!=from-1)
{
printf("%d.%s\n",i+1,a[i]);

}
}
do
{
scanf("%d",&to);
if(to>loc_count || to<1 || to==from)
{
 printf("Can't get that! Please select from given location:)\n");
 printf("Choose the Destination stop: \n");
}

}while(to>loc_count || to<1 || to==from);
}

int find_location(char location[])
{	
	for(int i=0;i<10;i++)
	{
		if(strcmp(a[i],location)==0)
		{
			return 1;
		}
	}
	return 0;
}

void Buses_in_From_To_Destination(char from_input[],char dest_input[],float time1)
{
    printf("The Available Buses Are:\n");
	printf("__________________________________________________________________________________\n");
    printf("|Bus_No\t|Start_Location\t|Destionation_location\t|Seats_Available  |Arrival_Time |\n");
	printf("__________________________________________________________________________________\n");
	for(int i=0;i<48;i++)
	{
		if(from<to)
		{
		if((find_location(from_input)&&find_location(dest_input))&&bus_obj[i].time>=time1&&bus_obj[i].busno<=24)
		{	printf("|  %d \t|  %s \t|    %s \t|\t%d \t  | %.2f\t|\n",bus_obj[i].busno,bus_obj[i].from,bus_obj[i].to,bus_obj[i].seatavb,bus_obj[i].time);
		}
		}
		else
		{
	        if((find_location(from_input)&&find_location(dest_input))&&bus_obj[i].time>=time1&&bus_obj[i].busno>=25)
		{	printf("|  %d \t|  %s \t|    %s \t|\t%d \t  | %.2f\t|\n",bus_obj[i].busno,bus_obj[i].from,bus_obj[i].to,bus_obj[i].seatavb,bus_obj[i].time);
		}
		}
	}
	printf("__________________________________________________________________________________\n");

}

int no_of_seats(int index,int flag){
	if(flag==1){
		// Calculate available seats based on existing tickets
		int occupied_seats = 0;
		for(int i=0;i<ticket_count;i++){
			if(strcmp(bus_obj[index].tickets[i].from,a[from-1])==0){
				occupied_seats++;
			}
		}
		return bus_obj[index].totalseats - occupied_seats;
	}
	else{
		return bus_obj[index].seatavb;
	}
}

//To Book the ticket
void book_ticket(int index)
{	
	char flag;
	int available_seats = no_of_seats(index,1);
	printf("\nThe estimated available seats for you is %d\n",available_seats);
	
    printf("Do you wanna book(1/0)?\n");
    getchar();
	l:scanf("%c",&flag);
    getchar();
    
    if(flag!='1' && flag!='0')
    {
        printf("Just select from the given option:)\n");
        goto l;
    }
    
	if(flag=='1'){
		if(available_seats>0){
			bus_obj[index].seatavb--;
			strcpy(bus_obj[index].tickets[ticket_count].from,a[from-1]);
			strcpy(bus_obj[index].tickets[ticket_count].to,a[to-1]);
			bus_obj[index].tickets[ticket_count].price=ticket_price(from,to);
			bus_obj[index].tickets[ticket_count].serialno = ticket_count + 1;
			print_ticket(bus_obj[index].tickets[ticket_count]);
			ticket_count++;
			}
	
	else{
		printf("Unfortunately,The seats are full\n");
		return;
	}
    }
}

void main()
{
    struct user u1,u2,u3,u4;
    struct ticket t1,t2,t3,t4;
    float tk=0.0;
    int bus_id,aks;

    // Initialize bus objects
    for(int i=0;i<48;i++)
    {
        bus_obj[i].busno=i+1;
        bus_obj[i].totalseats=bus_obj[i].seatavb=60;
	bus_obj[i].time=tk;
	tk=tk+1.0;
	if(i<=24)
	{
		strcpy(bus_obj[i].from, a[0]);
		strcpy(bus_obj[i].to, a[9]);
        }
	else
	{
		strcpy(bus_obj[i].from, a[9]);
		strcpy(bus_obj[i].to, a[0]);
	}
	if(tk>=24.00)
	tk=0.0;
    }
    
    login();
    
    do{
	select_from_to();
	float t;
	//Enter from location
	printf("Enter the time you want to board(24hr):\n");

	l:scanf("%f",&t);

	if(t<0 || t>23.59)
	{
	    printf("Just enter the time,not something:)\n");
	    goto l;
	}
	Buses_in_From_To_Destination(a[from-1],a[to-1],t);
	printf("Book Tickets(Enter the bus ID)\n");
	scanf("%d",&bus_id);
	
	if(bus_id < 1 || bus_id > 48) {
		printf("Invalid bus ID. Please enter a number between 1 and 48.\n");
		continue;
	}
	
	book_ticket(bus_id-1);
	printf("Do you wanna Book Tickets Again(1.yes 2.no)\n");
	scanf("%d",&aks);
	if(aks==2)
		break;
    }while(1);
}
