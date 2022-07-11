#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <ctype.h>
int count=0;//indicates the number of bookings
int seat[5][3][4];//rows columns and flights
void sett()
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<4;k++)
                seat[i][j][k]=0;
        }
    }
}
char from1[80]="Bengaluru",to1[90]="Chennai";
char from2[80]="Hyderabad",to2[90]="Mumbai";
char from3[80]="New Delhi",to3[90]="New York";
char from4[80]="California",to4[90]="Singapore";
char fro[80],tt[80];
struct customer
{
    int pers;
    char fname[50];
    char lname[50];
    int phno;
    char seats[30];//business or Economy
    int type;//window/aisle/middle
    char acc[20];
    char gen[8];
    char from[80],to[90];
    char dept[10];
    char seatnum;
    int dig;
    struct customer *link;
};
typedef struct customer * node;

struct airfrieght
{
    char name[65];
    char origin[75];
    char destination[85];
    char date[75];
    int quant;
    int weight;
    char cargo[75];
    char fadd[60];
    char tadd[60];
    double cost;
    int phno;
    int awbno;
    struct airfrieght *link;
};
typedef struct airfrieght * Node;
node getnode()
{
    node temp;
    temp=(node)malloc(sizeof(struct customer));
    return temp;
}
Node getnode1()
{
    Node temp;
    temp=(Node)malloc(sizeof(struct airfrieght));
    return temp;
}
node c=NULL;
int numb_gen() //this is used to generate AWB no. /booking no. 
{

    int n;
    for(int i = 0; i<1; i++)
    {
        n=rand();//random number is generated using rand()
    }
    return n;
}
int lo_details()
{
    char user[30];
    char pass[30];
    int len;
    printf("\nEnter username:\n");
    scanf("%s",user);
    len=strlen(user);
    if(user[len-4]=='.' && user[len-3]=='c' && user[len-2]=='o' && user[len-1]=='m') //if username is in .com format 
    { //then oly it accepts
        printf("\nEnter password:\n");
        scanf("%s",pass);
        printf("\nLogin Successfull*\n\n");
        return 1;
    }
    else
    {
    printf("\nInvalid username\n\n");
    return 0;
    }

}
int allot(int k,node temp)
{
    int a;
    printf("Available seats in the flight\n");
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(seat[i][j][k]==0)
                printf("%c%d,",i+65,j);//type casting
        }
    }
    printf("\b \b");
    printf("\n");
    int l=0;
    printf("Enter seat needed\n1.window\n2.aisle\n3.middle\n");
    scanf("%d",&a);
    a=a-1;
    printf("Seat Marker:\n");
    for(int i=0;i<5;i++)
    {
        if(seat[i][a][k]==0)
        {
            l=1;
            printf("%c%d,",i+65,a);
        }    
    }
    printf("\b \b");
    printf("\n");
    if(l!=1)
    {
        printf("no seats available\ntry other seats\n");
        allot(k,temp);
    }
    while(1)
    {
        char z;
        int p,r;
        printf("enter the series(alphabets) needed\n");
        scanf(" %c",&z);
        z=toupper(z);
        printf("enter the seat number needed\n");
        scanf("%d",&r);
        p=z-65;
        if(seat[p][r][k]==0)
        {
            seat[p][r][k]=1;
            printf("seat conirmed\n");
            temp->seatnum=z;
            temp->dig=r;
            return a;
        }
    }    
}
int checkseat(int n,int k)
{
    int s=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(seat[i][j][k]==0)
                s++;
        }
    }
    if(s>=n)
        return 1;
    return 0;    
}
int airfind()
{
    int a;
    printf("available flights\n");
    printf("1. %s -----> %s\n",from1,to1);
    printf("2. %s -----> %s\n",from2,to2);
    printf("3. %s -----> %s\n",from3,to3);
    printf("4. %s -----> %s\n",from4,to4);
    printf("enter the flight needed\n");
    scanf("%d",&a);
    switch(a)
    {
        case 1:strcpy(fro,from1);
                strcpy(tt,to1);
                break;
        case 2:strcpy(fro,from2);
                strcpy(tt,to2);
                break;
        case 3:strcpy(fro,from3);
                strcpy(tt,to3);
                break;
        case 4:strcpy(fro,from4);
                strcpy(tt,to4);
                break;
        default:a=airfind();
                a=a+1;
                break;
    }
    return a-1;
}
void insertfun(node temp)
{
    if(c==NULL)
    {
        temp->link=NULL;
    }
    temp->link=c;
    c=temp;
}
void reserve()
{
    int k=airfind();
    node temp;
    int ch,a,b,d,z;
    char depart[20];
    char accomp[20];
    printf("Enter no of \n\tAdults(Above 12 years)\n\tChildren(Between 2-12years)\n\tInfants(Below 2 years) \n");
    scanf("%d%d%d",&a,&b,&d);
    int n=a+b+d;
    int l=checkseat(n,k);
    if(l==0)
    {
        printf("seats for those many passangers are not available\n");
        return;
    }
    printf("Enter departure date:\n");
    scanf("%s",depart);
    printf("------Enter customer details:------- \n");
    printf("Select the preferred class\n");
    printf("1.Business class \t\t 2.Economy class\n");
    scanf("%d",&z);
    while(1)
    {
        if(a==0 && b==0 && d==0) //termination condt
        {
            break;
        }
        printf("Enter details:\n 1.Select Adult\t\t2. Select Children\t\t3. Select Infants\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:if(a!=0)
                    {
                        for(int i=0;i<a;i++)
                        {
                            temp=getnode();
                            temp->pers=1;
                            strcpy(temp->from,fro);
                            strcpy(temp->to,tt);
                            strcpy(temp->dept,depart);
                            printf("Enter first name\n");
                            scanf("%s",temp->fname);
                            printf("Enter last name\n");
                            scanf("%s",temp->lname);
                            printf("Enter phone Number\n");
                            scanf("%d",&(temp->phno));
                            if(z==1)
                                strcpy(temp->seats,"Business");
                            else
                                strcpy(temp->seats,"Economy");
                            temp->type=allot(k,temp);
                            strcpy(accomp,temp->fname);
                            printf("Gender?[M/F]\n");
                            scanf("%s",temp->gen);
                            insertfun(temp);
                        }
                        a=0;
                    }    
                    break;
            case 2:if(b!=0)
                    {
                        for(int i=0;i<b;i++)
                        {
                            temp=getnode();
                            temp->pers=2;
                            strcpy(temp->from,fro);
                            strcpy(temp->to,tt);
                            strcpy(temp->dept,depart);
                            strcpy(temp->acc,accomp);
                            printf("Enter first name\n");
                            scanf("%s",temp->fname);
                            printf("Enter last name\n");
                            scanf("%s",temp->lname);
                            if(z==1)
                                strcpy(temp->seats,"Business");
                            else
                                strcpy(temp->seats,"Economy");
                            temp->type=allot(k,temp);
                            printf("Gender?[1 for M|2 for F]\n");
                            scanf("%s",temp->gen);
                            insertfun(temp);
                        }
                        b=0;
                    }
                    break;
            case 3:if(d!=0)
                    {
                        for(int i=0;i<d;i++)
                        {
                            temp=getnode();
                            temp->pers=3;
                            strcpy(temp->from,fro);
                            strcpy(temp->to,tt);
                            strcpy(temp->dept,depart);
                            strcpy(temp->acc,accomp);
                            printf("Enter first name\n");
                            scanf("%s",temp->fname);
                            printf("Enter last name\n");
                            scanf("%s",temp->lname);
                            if(z==1)
                                strcpy(temp->seats,"Business");
                            else
                                strcpy(temp->seats,"Economy");
                            temp->type=allot(k,temp);
                            printf("Gender?[1 for M|2 for F]\n");
                            scanf("%s",temp->gen);
                            insertfun(temp);
                        }
                        d=0;
                    }    
                    break;
        }
    }
    printf("Seat Booked Successfully\n");
} 
void display()
{
    int ch;
    node cur=c;
    int count=1;
    while(1)
    {
        cur=c;
        printf("1. Select Adult\n2. Select Children\n3. Select Infants\n4.Exit\n");
        scanf("%d",&ch);
        if(ch>3)
        {
            break;
        }
        while(cur!=NULL)
        {
            if(ch==1 && cur->pers==1)
            {
                printf("Adult\n");
                printf("\n----------------------------------\n");
                printf("First name: %s\n",cur->fname);
                printf("Last name: %s\n",cur->lname);
                printf("Gender?[M|F]:%s\n",cur->gen);
                printf("Frm:%s\nTo:%s\nphno:%d\nDeparture date:%s\n",cur->from,cur->to,cur->phno,cur->dept);
                printf("Seat Class:%s\n",cur->seats);
                if(cur->type==0)
                    printf("Seat type:Window seat\n");
                if(cur->type==1)
                    printf("Seat type:Aisle seat\n");
                if(cur->type==2)
                    printf("Seat type:Middle seat\n");
                printf("Seat Number:%c%d",cur->seatnum,cur->dig);    
                printf("\n----------------------------------\n");    
            }
                        
            if(ch==2 && cur->pers==2)
            {
                printf("Child\n");
                printf("\n----------------------------------\n");
                printf("First name: %s\n",cur->fname);
                printf("Last name: %s\n",cur->lname);
                printf("Gender:%s\n",cur->gen);
                printf("Frm:%s\nTo:%s\nDeparture date:%s\n",cur->from,cur->to,cur->dept);
                printf("Accompanied by:%s\n",cur->acc);
                printf("Seat Class:%s\n",cur->seats);
                if(cur->type==0)
                    printf("Seat type:Window seat\n");
                if(cur->type==1)
                    printf("Seat type:Aisle seat\n");
                if(cur->type==2)
                    printf("Seat type:Middle seat\n"); 
                printf("Seat Number:%c%d",cur->seatnum,cur->dig);    
                printf("\n----------------------------------\n");    
            }
            if(ch==3 && cur->pers==3)
            {
                printf("Infant\n");
                printf("\n----------------------------------\n");
                printf("First name: %s\n",cur->fname);
                printf("Last name: %s\n",cur->lname);
                printf("Gender?[M|F]:%s\n",cur->gen);
                printf("Frm:%s\nTo:%s\nDeparture date:%s\n",cur->from,cur->to,cur->dept);
                printf("Accompanied by:%s\n",cur->acc);
                printf("Seat Class:%s\n",cur->seats);
                if(cur->type==0)
                    printf("Seat type:Window seat\n");
                if(cur->type==1)
                    printf("Seat type:Aisle seat\n");
                if(cur->type==2)
                    printf("Seat type:Middle seat\n"); 
               printf("Seat Number:%c%d",cur->seatnum,cur->dig);     
                printf("\n----------------------------------\n");    
            }
        cur=cur->link;
        }
    }
}
void calculate_air(Node temp) //used to calculate the cost of the package being transported
{
    int a=(temp->weight);
    int b=(temp->quant);
   printf("\nThe total weight is: %d\n",a*b);
   if(a*b<=5)
   {
        temp->cost=750*a*b;
        printf("\nThe total shipping cost is %lf\n",temp->cost);
   }
   if(a*b>5)
   {
        temp->cost=550*a*b;
        printf("\nThe total shipping cost is %lf\n",temp->cost);
   } 
   
}

Node air_f(Node f)
{
    Node temp=getnode1();
    int g;
    printf("\n-------$$$-----The easiest way to book air cargo-----$$$--------\n");
    printf("\nEnter name\n");
    scanf("%s",temp->name);
    printf("\nEnter the origin airport\n");
    scanf("%s",temp->origin);
    printf("\nEnter the destination airport\n");
    scanf("%s",temp->destination);
    printf("\nEnter FROM address\n");
    scanf("%s",temp->fadd);
    printf("\n Enter TO address\n");
    scanf("%s",temp->tadd);
    printf("\nEnter PHONE NO\n");
    scanf("%d",&(temp->phno));
    printf("\nSelect service\n1.BAGGAGE AS CARGO\n 2.LIVE ANIMALS (AVI)\n3.HUMAN REMAINS(HUM)\n4. VALUABLE CARGO (VAL)\n 5.FRAGILE\n 6.INTERNATIONAL/DOMESTIC POST OFFICE MAIL\n");
    scanf("%d",&g);
    switch(g)
    {
        case 1: printf("\nCargo selected:\t");
                char str1[25]= "BAGGAGE AS CARGO";
                puts(str1);
                break;
        case 2: printf("\nCargo selected:\t");
                char str2[25]= "LIVE ANIMALS";
                puts(str2);
                break;
        case 3: printf("\nCargo selected:\t");
                char str3[25] ="HUMAN REMAINS";
                puts(str3);
                break;
        case 4: printf("\nCargo selected:\t");
                char str4[25] ="VALUABALE CARGO";
                puts(str4);
                break;
        case 5:  printf("\nCargo selected:\t");
                char str5[25] ="FRAGILE";
                puts(str5);
                break;
        case 6: printf("\nCargo selected:\t");
                char str6[100] ="INTERNATIONAL/DOMESTIC POST OFFICE MAIL";
                puts(str6);
                break;
        default: exit(0);

    }
    printf("\nEnter the quantity\n");
    scanf("%d",&(temp->quant));
    printf("\n Enter the weight\n");
    scanf("%d",&(temp->weight));
    temp->awbno=numb_gen();
    printf("\nPlease note your AWB NUMBER:\t%d",temp->awbno);
    printf("\n-----------BOOKING CONFIRMED-------------\n");
    if(f==NULL) //empty linked list
    {
        temp->link=NULL;
        return temp;
    }
    temp->link=f; //insert front 
    return temp;
}
void display_air(Node f)
{
    Node temp=f;
    int awb;
    int ch=0;
    while(1)
    {
        printf("\nEnter your AWB number\n");
        scanf("%d",&awb);
        while(temp!=NULL)
        {
            if(awb==temp->awbno)
            {
    
                char h[6];
                printf("%s\t",temp->name);
                printf("%d",temp->phno);
                printf("\n%.4s",temp->origin);  //displays first four letters
                printf("\n%.4s",temp->destination); //displays first four letters
                time_t t;
                time(&t);
                printf("\nBooking date:%s",ctime(&t)); //displays system time
                printf("\n%s",temp->fadd); //From address
                printf("\n----->%s",temp->tadd);
                printf("\nQuantity--->%d",(temp->quant));
                printf("\nWeight---->%d",(temp->weight));
                printf("\nIf above details correct , please confirm with 'yes'\n");
                scanf("%s",h);
                if(strcmp(h,"yes")==0)
                {
                    calculate_air(temp);
                }
                else
                {
                    printf("\nWe dont have any other bookings with that awb number\n");
                    return;
                }
                ch=0;
                break;
            }
            else
            {
                temp=temp->link;
                ch=1;
            }
        }  
        if(ch==1)
        {
            printf("\nWrong AWB number\n");
            printf("\nEnter the correct AWB number and TRY AGAIN!\n");
        }
        else
        {
            break;
        }
    }
}

void cus_supp()
{
    int af;
    printf("\nWelcome to BEST Airlines. Please choose your queries\n");
    int cs;
    printf("\nSelect your type of service\n1. Passenger booking\n2. Air frieght\n3.Exit\n");
    scanf("%d",&af);
    switch(af)
    {
        case 1:printf("\nPASSENGER BOOKING SERVICES\n");
               while(1)
               {
                    printf("\nFAQS\n 1.Can I cancel the ticket within 24 hours of booking \n2. What is medical clearance and when do I need one? \n 3. Assistance when my flight has been delayed or cancelled\n 4. Can we make reservations and purchase tickets as far in advance as possible\n");
                    scanf("%d",&cs);
                    switch(cs)
                    {
                        case 1:printf("\nYes, u can cancel the ticket but 50 percent of money will be deducted\n");
                               break;
                        case 2:printf("\nMost people with existing medical conditions are able to fly without difficulty.However sometimes certain precautions need to be taken.\n");
                               break;
                        case 3:printf("\nWhenever a flight is cancelled or delayed then you will get SMS about flight details\n");
                               break;
                        case 4:printf("\nYou can reserve and book tickets before 1 month of your travel\n");  
                               break;
                        default:printf("\nFor any other queries and support please write to us at \n wecare@bestairlines.com\n Contacts us on \t +919742744458");
                                break;     
                    }
               }
               exit(0);

        case 2: printf("\nAIR FRIEGHT SERVICES\n");
                int afs;
                while(1)
                {
                   printf("\nFAQS\n1.What are the customs requirement for dispatch of international shipments?\n 2.What are the articles that are banned on your services?\n3. How can I find the delivery status of the consignment\n4.Are there any holidays that may affect service schedules?\n" );
                   scanf("%d",&afs);
                   switch(afs)
                   {
                        case 1:printf("\nINDIVIDUAL SAMPLES/GIFT:-  Need Photo proof : PAN card OR DL\n");
                               printf("\nCOMPANY SAMPLES:- Need Invoice, GST certificate, Address proof, Import export code\n");
                               printf("\nCHEMICAL:- Need Company Invoice and Non DGR certificate, Lab Analysis Certificate & MSDS \n");
                               printf("\nMEDICINE:- Need original doctor prescription, original medicine purchase bill, Doctor certificate\n");
                               break;
                        case 2:printf("\nCurrency\n Toxic materials\n Flammables \n Perishables\nRadioactive materials \n Explosive materials\n");
                               break;
                        case 3:printf("\nThe consumer will recieve SMS with AWB number for tracking purpose\n");
                               break;
                        case 4:printf("\nNational Holidays might affect the services\n");
                               break;
                        default: printf("\nFor any other queries and support please write to us at \n wecare@bestairlines.com\n Contacts us on \t+919742744458");
                                break;
                    }
                }   
                exit(0);
    }
}
int main()
{
    int ch,flag1=0;
    printf("\t\t\t\t\t$$-------II------------II-------$$\n");
    printf("\t\t\t\t\t\tWELCOME TO BEST AIRLINES\n");
    printf("\t\t\t\t\tII-------$$------------$$-------IIn\n");
    Node f=NULL;
    int flag=lo_details();
    sett();
    while(flag==0) //Invalid username
    {
        flag=lo_details();
    }
    while(1)
    {
        printf("\t");
		printf("-");
		printf("\n");
		printf("  *  |HOMEPAGE|  * \n");
		printf("\t");
		printf(" Please enter your CHOICE:");
		printf("\n\n");
		printf("\n Enter 1 ->   RESERVE SEAT");
		printf("\n----------------------------------");
		printf("\n Enter 2 ->   DISPLAY SEAT");
		printf("\n----------------------------------");
		printf("\nEnter 3 -> AIR FREIGHT SERVICES ");
		printf("\n----------------------------------");
		printf("\nEnter 4 -> TRACKING DETAILS ");
		printf("\n-----------------------------------");
		printf("\n Enter 5 -> CUSTOMER SUPPORT ");
		printf("\n-----------------------------------");
		printf("\n");
		printf("\n");
		scanf("%d",&ch);
		switch(ch)
		{
		    case 1:reserve();
		            break;
		    case 2: display(c);
		            break;
		    case 3: f=air_f(f);
		            break;
		    case 4: display_air(f);
		            break;
		    case 5: cus_supp();
		            break;
		    default: exit(0);    
		
		}
    }
}
