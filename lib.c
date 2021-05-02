#include <windows.h>//Used for date
#include <stdio.h>
#include <conio.h>
#include <string.h>//Used for some basic string function
#include <unistd.h>//Used for sleep


void bookmenu();
void addbook();
void removebook();
void issuebook();
void submitbook();
char *substring(char *string, int position, int length)
{
   char *p;
   int c;

   p = malloc(length+1);

   if (p == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }

   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position-1);
      string++;
   }

   *(p+c) = '\0';

   return p;
}

void main()
{
  char admindata[1000];
  char adminuser[1000]={NULL},adminpass[1000]={NULL};
  char inputadminuser[1000]={ NULL },inputadminpass[1000]={ NULL };
  FILE *adminid;
  int x,y,i,adminlength,count;
  printf("\t\t*******************************************\n");
  printf("\t\t* WELCOME TO THE LIBRARY MANAGMENT SYSTEM *\n");
  printf("\t\t*******************************************\n");
  printf("\t\t|                                          |\n");
  printf("\t\t|PLEASE ENTER THE ADMIN LOGIN DETAILS \t   |\n");
  //which is provided by the administration of the owner!
  printf("\t\t|USERNAME : ");
  scanf("%s",&inputadminuser);
  printf("\t\t|PASSWORD : ");
  scanf("%s",&inputadminpass);
  adminid=fopen("admin.txt","r");
  //used to read the first line of the file in the directory
  fscanf(adminid,"%[^\n]",admindata);
  adminlength=strlen(admindata);
  for (i=0,count=0;i<adminlength;i++)
  {
    //Manually !(Exclamation) entered in the file to bifurcate between id and password
    if(admindata[i]!='!' && count==0)
    {
      strncat(adminuser,&admindata[i],1);
    }
    else if(admindata[i]=='!')
    {
      count=1;
    }
    else if(admindata[i]!='@' && count==1)
    {
      strncat(adminpass,&admindata[i],1);
    }
  }
  //Comparing the username and password with the admin file to verify the security
  x=strcmp(inputadminuser,adminuser);
  y=strcmp(inputadminpass,adminpass);
  printf("\n\t\t|------------------------------------------|");
  //If the password and id are correct the program in transferred to book menu or else the program is terminated
  if(x==0 && y==0)
  {
    printf("\n\t\t|SUCCESSFULLY LOGGED IN \t\t   |\n");
    printf("\t\t|__________________________________________|\n");
    //sleep(5);
    system("cls");
    bookmenu();
  }
  else
  {
    printf("\n\t\t|WRONG PASSWORD\t\t\t\t   |\n");
    printf("\t\t|__________________________________________|\n");
    sleep(5);
    system("cls");
  }
  return 0;
}

void bookmenu()
{
  int choice;
  printf("\t\t*******************************************\n");
  printf("\t\t* WELCOME TO THE BOOK MENU                *\n");
  printf("\t\t*******************************************\n");
  printf("\t\t|CHOOSE THE OPTION BELOW:-                |\n");
  printf("\t\t|1.ADD BOOK                               |\n");
  printf("\t\t|2.REMOVE BOOK                            |\n");
  printf("\t\t|3.ISSUE BOOK                             |\n");
  printf("\t\t|4.SUBMIT BOOK                            |\n\n");
  printf("\t\t|ENTER YOUR ACTION :- ");
  scanf("%d",&choice);
  printf("\t\t|_________________________________________|\n");
  switch(choice)
  {
    case 1:
    addbook();
    break;

    case 2:
    removebook();
    break;

    case 3:
    issuebook();
    break;

    case 4:
    submitbook();
    break;

    default:
    printf("\t\t+Invalid Entry.!                         +\n");
  }

}


void addbook()
{
  //As per the name, this function creates the file that stores the data of the book.
  FILE *addbook;
  char bookname[1000]={NULL},bookdata[1000]={NULL},filename[1000]={NULL};
  char bookid[1000]={NULL};
  printf("\t\t+Please enter book name:- ");
  scanf("%s",&bookname);
  printf("\t\t+Please enter book ID:- ");
  scanf("%s",&bookid);
  //storing the book id for the creation of the file
  strcpy(filename,bookid);
  //In each steps copying each variable to create data that can be inserted in the file
  strncat(bookid,"!",1);
  strncat(bookname,"@",1);
  strcat(bookdata,&bookid);
  strcat(bookdata,&bookname);
  //.txt added to open the file
  strcat(filename,".txt");
  //This statement checks whether the file is already there in the directory or not
  if (addbook=fopen(filename,"r"))
  {
    printf("\t\t+THE BOOK IS ALREADY THERE!!  \t          +\n");
    printf("\t\t++++++++++++++++++++++++++++++\t+++++++++++\n");
    fclose(addbook);
  }
  else
  {
    //Adding the file in the directory
    addbook=fopen(filename,"w");
    fprintf(addbook,"%s",bookdata);
    fclose(addbook);
    printf("\t\t+BOOK ADDED SUCCESSFULLY!!!  \t          +\n");
    printf("\t\t++++++++++++++++++++++++++++++\t+++++++++++\n");
  }
}

void removebook()
{
  //As per the name, this fucntion removes the file from the directory
  FILE *removebook;
  char bookid[1000]={NULL};
  printf("\t\t+Please enter book ID:- ");
  scanf("%s",&bookid);
  strcat(bookid,".txt");
  if(removebook=fopen(bookid,"r"))
  {
    fclose(removebook);
    //This function delete the file from the directory
    remove(bookid);
    printf("\t\t+FILE SUCCESSFULLY DELETED!!      \t  +\n");
    printf("\t\t++++++++++++++++++++++++++++++\t+++++++++++\n");
  }
  else
  {
    printf("\t\t+SORRY!! NO SUCH BOOK ID AVAILABLE!    \t  +\n");
    printf("\t\t++++++++++++++++++++++++++++++\t+++++++++++\n");
  }
}

void issuebook()
{
  //As per the name, this function issue a book to the customer
  SYSTEMTIME t;
  FILE *issuebook;
  FILE *customerfile;
  int i,moblen,month,count,day;
  int bookdetailslen;
  char custname[1000]={NULL},custmob[1000]={NULL},custfile[1000]={NULL},charday[10]={NULL},charmonth[10]={NULL},charyear[10]={NULL};
  char bookid[1000]={NULL},bookidcheck[1000]={NULL},bookdetails[1000]={NULL};
  char mobcop[10]={NULL},keep[1000]={NULL};

  //Converted time to string so that can be inputed in file
  GetLocalTime(&t);
  sprintf(charday,"%d",t.wDay);
  sprintf(charmonth,"%d",t.wMonth);
  sprintf(charyear,"%d",t.wYear);

  printf("\t\t+Please enter your name :- ");
  scanf("%s",&custname);
  printf("\t\t+Please enter your mobile number :- ");
  scanf("%s",&custmob);
  moblen=strlen(custmob);
  if (moblen > 10)
  {
    printf("\t\t+MOBILE NUMBER SHOULD BE 10 DIGITS!          +\n");
    return 0;
  }
  else
  {
    //Copied mobile number for creating a user file
    strcat(custfile,custmob);
    strcat(custfile,".txt");
    customerfile=fopen(custfile,"a");
    printf("\t\t+PLEASE PROVIDE THE BOOK ID :- ");
    scanf("%s",&bookid);
    strcpy(bookidcheck,bookid);
    strcat(bookidcheck,".txt");
    //The below code checks wheter the book is already to issued someone or not
    if(issuebook=fopen(bookidcheck,"r"))
    {
      fscanf(issuebook,"%[^\n]",bookdetails);
      fclose(issuebook);
      bookdetailslen=strlen(bookdetails);
      for(i=0;i<bookdetailslen;i++)
      {
        if(bookdetails[i]=='^')
        {
          count=1;
        }
        else if(count==1 && bookdetails[i]!='&')
        {
          strncat(mobcop,&bookdetails[i],1);
        }
      }
      if(count == 1)
      {
        printf("\t\t+BOOK IS ALREADY ISSUED TO (%s)   \t     +",mobcop);
        fclose(customerfile);
        remove(custfile);
        return 0;
      }
      //Now the below code will add the date of issue in the file as well as the users mobile number
      printf("\t\t+(YOU CAN ISSUE THE BOOK ONLY FOR 30 DAYS!!!)   \t  \n");
      printf("\t\t+(THE BOOK IS FREE FOR THE FIRST 5 DAYS!!!)   \t  \n");
      printf("\t\t+(LATER ON IT WILL BE CHARGED 5 RS PER DAY!!!)   \t  \n");
      printf("\t\t+(LATE CAHRGES : 100RS PER DAY!!!)   \t  \n\n");

      printf("\t\t+FOR HOW MANY DAYS YOU WANT TO KEEP THE BOOK :- ");
      scanf("%s",&keep);
      day=atoi(keep);
      if(day > 30)
      {
        printf("\t\t+CANNOT ISSUE THE BOOK MORE THAN 30 DAYS!!!   \t  \n");
        return 0;
      }
      strcat(bookdetails,"#");
      strcat(bookdetails,charday);
      strcat(bookdetails,"$");
      strcat(bookdetails,charmonth);
      strcat(bookdetails,"%");
      strcat(bookdetails,charyear);
      fprintf(customerfile,"\n");
      fprintf(customerfile,"%s",bookdetails);
      issuebook=fopen(bookidcheck,"w");
      strcat(bookdetails,"^");
      strcat(bookdetails,custmob);
      strcat(bookdetails,"&");
      strcat(bookdetails,keep);
      strcat(bookdetails,"*");
      fprintf(issuebook,"%s",bookdetails);
      fclose(issuebook);
    }
    else
    {
      printf("\t\t+SORRY THE BOOK IS NOT AVAILABLE!!!   \t  +\n");
    }
  }
}


void submitbook()
{
  //As per the name, this function enter the data of the user who want to return the book
  SYSTEMTIME t;
  FILE *subbook;
  int i,booklen,count;
  char *p;
  char bookid[1000]={NULL},bookcopy[1000]={NULL},datacopy[1000]={NULL};
  char issueday[10]={NULL},issuemonth[10]={NULL},issueyear[10]={NULL};
  char subday[10]={NULL},submonth[10]={NULL},subyear[10]={NULL},keepday[10]={NULL};
  int poshas,posdollar,posper,pospower,posamp,posstar,len;
  //Converted time to string so that can be inputed in file
  GetLocalTime(&t);
  sprintf(subday,"%d",t.wDay);
  sprintf(submonth,"%d",t.wMonth);
  sprintf(subyear,"%d",t.wYear);

  printf("\t\t+Enter the book id:- ");
  scanf("%s",&bookid);
  strcat(bookid,".txt");
  if(subbook=fopen(bookid,"r"))
  {
    //reading the data of the book with the help of book id
    fscanf(subbook,"%[^\n]",bookcopy);
    booklen=strlen(bookcopy);
    for (i=0;i<booklen;i++)
    {
      if(bookcopy[i]=='#')
      {
        count=1;
        poshas=i;

      }
    }
    //if # is there in the data that means that the book was already issued
    if(count == 1)
    {
      for (i=0;i<booklen;i++)
      {
        if(bookcopy[i]=='$')
        {
          posdollar=i;
        }
        else if(bookcopy[i]=='%')
        {
          posper=i;
        }
        else if(bookcopy[i]=='^')
        {
          pospower=i;
        }
        else if(bookcopy[i]=='&')
        {
          posamp=i;
        }
        else if(bookcopy[i]=='*')
        {
          posstar=i;
        }
      }
    }
    if(count == 1)
    {
      for (i=0;i<booklen;i++)
      {
        if(bookcopy[i]!='#')
        {
          //copying the id and the book name (deleting the date adn number)
          strncat(datacopy,&bookcopy[i],1);
        }
        else
        {
          break;
        }
      }
    }
    else //(count==0)
    {
      printf("\t\t+NO ONE HAS ISSUED THIS BOOK!!   \t   +");
      return 0;
    }
    len=posdollar-poshas;
    strncpy(subday,bookcopy + poshas+1, len-1);
    ///printf("\nday = %s",subday);
    len=posper-posdollar;
    strncpy(submonth,bookcopy + posdollar+1, len-1);
    //printf("\nmonth =%s",submonth);
    len=pospower-posper;
    strncpy(subyear,bookcopy + posper+1, len-1);
    //printf("\nyear =%s",subyear);
    len=posstar-posamp;
    strncpy(keepday,bookcopy + posamp+1, len-1);
    //printf("\nkeep =%s",keepday);
    fclose(subbook);
    //Writing the data back to the file
    subbook=fopen(bookid,"w");
    fprintf(subbook,"%s",datacopy);
    printf("\t\t+YOU HAVE SUCCESSFULLY SUBMITTED THE BOOK!   \t  +");
    fclose(subbook);
  }
  else
  {
    printf("\t\t+THIS BOOK ID IS NOT AVAILABLE!!    \t   +\n");
  }

}
