/*=======================MOVIE TICKET BOOKING============================

	     BY SIDHARTH A,THOMAS VARGHESE AND JOEL JOSE

			      CLASS: 12 A

		      TOC H PUBLIC SCHOOL,VYTILLA                      */

//----------------------HEADER FILES----------------------------//

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<process.h>
#include<string.h>

int k=100;
//---------------------CLASS DEFINITION----------------------------//

class Theatre
{
  int mcode;
  char mname[20],mtype[20];
  float mtime;
  int n,mcost,totcost;

public:
//-----------------FUNCTION TO ADD NEW MOVIES-------------------//

void Addmovie()
{
   cout<<"\n++++++++++ ENTER THE DETAILS OF THE NEW MOVIE++++++++++\n\n" ;
   cout<<"\n\t\t Enter the movie code         : ";
   cin>>mcode;
   cout<<"\n\t\t Enter the movie name         : ";
   gets(mname);
   cout<<"\n\t\t Enter movie type             : ";
   gets(mtype);
   cout<<"\n\t\t Enter movie timing           : ";
   cin>>mtime;
   cout<<"\n\t\t Enter the cost of one ticket : ";
   cin>>mcost;
}

//------------------FUNCTION TO DISPLAY MOVIE DETAILS-----------------//

void Showmovie()
{
clrscr();
   cout<<"\n Movie code    : "<<mcode<<"\n";
   cout<<"\n Movie name    : ";
   puts(mname);
   cout<<"\n Movie type    : ";
   puts(mtype);
   cout<<"\n Movie timing  : "<<mtime<<"\n";
}


//------------------FUNCTION TO MODIFY MOVIE DETAILS-------------------//

void Modmovie()
{

   Addmovie();
   cout<<"\n The details have been modified.";
}

//------------------FUNCTION TO RETURN THE TOTAL COST----------------------//

int Total()
{
   totcost = n * mcost;
   return totcost;
}

//-------------------FUNCTION TO LIST THE MOVIE DETAILS--------------------//

void List()
{
   cout<<endl<<setw(3)<<mcode<<setw(20)<<mname<<setw(20)<<mtype<<setw(17)<<mtime;
}

//-------------------FUNCTION TO BOOK MOVIE TICKETS--------------------//

void Book()
{
   clrscr();
   cout<<"                          BOOK YOUR MOVIE                      \n ";
   cout<<"\n\tHow many tickets ? ";
   cin>>n;

   if( n < k)
      {
	cout<<"\n\tYour tickets have been booked successfully.Enjoy!";
	Total();
	cout<<"\n\n\tTotal cost: "<<totcost<<" $ ";
	k=k-n;
      }
   else
   cout<<"Sorry but this movie cannot be booked.";
   getch();
   return;
}

//-------------------FUNCTION TO RETURN THE MOVIE CODE------------------//

int retmcode()
{
   return mcode;
}

};

//---------------------* END OF CLASS *--------------------//

fstream f,f2;
Theatre t;
void Option();

//------------FUNCTION TO ACCESS THE CREATORS MENU-----------//

void entry()
{
  clrscr  ();
  char ch[20];
  cout<<"\t\t\tEnter your password: ";
  for(int i=0;i!='\r';i++) {

			    ch[i]=getch();
			    if(ch[i]=='\r')
			    break;
			    cout<<"*";
			    }
  cout<<"\n";
  ch[i]='\0';

if(strcmpi(ch,"1234")==0)
  Option();
else
  cout<<"\n\t\t\tIncorrect password";
  getch();
}

//----------------FUNCTION TO WRITE  MOVIE INTO THE FILE-----------------//

void Write()
{
   char c;
   f.open("movie.dat",ios::app|ios::binary);
   do
   {
     t.Addmovie();
     f.write((char*)&t,sizeof(t));
     cout<<"\n\n Do you want to add another movie ( Y/N ) ";
     cin>>c;
   }
   while(c=='Y'||c=='y');
   f.close();
}
//--------FUNTION TO DISPLAY MOVIE CHOSEN BY THE USER-----------//

void Display(int m)
{
   int h=0;
   f.open("movie.dat",ios::in|ios::binary);
   while(f.read((char*)&t,sizeof(Theatre)))
   {
     if(t.retmcode()==m)
     {
       cout<<"               MOVIE DETAILS             ";
       t.Showmovie();
       h=1;
     }
   }
   f.close();
   if(h==0)
   cout<<"\n\n\tSorry,the movie your looking for is unavailable.";
   getch();
}

//--------------------MOVIE MODIFICATION----------------------//

void Modify()

{
   clrscr();
   int q,w=0,s=0;
   cout<<"\n Enter the movie code that you want to modify: ";
   cin>>q;
   f.open("movie.dat",ios::in|ios::out|ios::binary);
   s=0;
   while(f.read((char*)&t,sizeof(t))&&w==0)
   {
     if(t.retmcode()==q)
     {
       t.Showmovie();
       t.Modmovie();
       int position=-1*sizeof(t);
       f.seekp(position,ios::cur);
       f.write((char*)&t,sizeof(t));
       q++;
       s++;
       cout<<"\n\n";
   }
   }
   f.close();

   if(s==0)
   cout<<"\n\n\tThis movie is unavailable";
   getch();
}

//-----------------------FUNTION TO DELETE MOVIE--------------------//

void mdelete()
{
   clrscr();
   fstream f2;
   int p,q=0;
   cout<<"\n Enter the movie code you want to delete: ";
   cin>>p;
   f.open("movie.dat",ios::in|ios::binary);
   f2.open("temp.dat",ios::out|ios::binary);
   f.seekg(0,ios::beg);
   while(f.read((char*)&t,sizeof(t)))
   {
     if(t.retmcode()!=p)
     f2.write((char*)&t,sizeof(t));
     else
     q=1;
   }
   f.close();
   f2.close();
   remove("movie.dat");
   rename("temp.dat","movie.dat");
   if(q==1)
   cout<<"\n\tThe Movie has been deleted.";
   else
   cout<<"\n\tThe Movie(s) cannot be found";
   getch();
}

//-----------FUNCTION TO LIST THE MOVIES--------------//

void all()
{
  clrscr();
   f.open("movie.dat",ios::in|ios::binary);
   if(!f)
   {
     cout<<"File not found";
     getch();
     return;
   }
   cout<<"\n\n---------------------------- MOVIE LIST---------------------------------\n \n";
   cout<<"CODE"<<"               NAME "<<"              TYPE "<<"             TIMING ";
   cout<<"\n------------------------------------------------------------------------";
   cout<<"\n";
   while(f.read((char*)&t,sizeof(Theatre)))
   {
     t.List();          cout<<"\n";
   }
   f.close();

   cout<<"\n\n\n\n\n\t\t Press any key to CONTINUE           \n";
   getch();
}

//------USERS FUNCTION FOR BOOKING MOVIES-------//

void User()
{
   int p,mc;
   cout<<"Select your movie ";
   all();
   f.open("movie.dat",ios::in|ios::out|ios::binary);
   cout<<"\n Enter the movie code ";
   cin>>mc;
   int flag=0;
   while(f.read((char*)&t,sizeof(Theatre)))
   {
     if(t.retmcode()==mc)
     {
       t.Book();
       flag=1;
     }
   }
   if(flag==0)
   cout<<"\n Movie not available.";
   f.close();
   return;
}

void start()
{
   clrscr();
   cout<<"\n\n\n\t*******************MOVIE TICKET BOOKING********************\n"
       <<"            Made by SIDHARTH A,THOMAS VARGHESE and JOEL JOSE";
   cout<<"\n\n CLASS: XII A\n\n TOC H PUBLIC SCHOOL";
   getch();
}
//---------------------* CREATORS MENU *-----------------------//

void Option()
{
   int choice;
   clrscr();
   cout<<"\t\t...............CREATORS MENU............... \n";
   cout<<"\n\n\t\t\t 1.ADD A NEW MOVIE";
   cout<<"\n\n\t\t\t 2.LIST OF MOVIES";
   cout<<"\n\n\t\t\t 3.DETAILS OF THE MOVIE";
   cout<<"\n\n\t\t\t 4.MODIFY MOVIE";
   cout<<"\n\n\t\t\t 5.DELETE MOVIE";
   cout<<"\n\n\t\t\t 6.EXIT";
   cout<<"\n\n\t\t\t Select your option(1/2/3/4/5/6): ";
   cin>>choice;
   switch(choice)
   {
       case 1:clrscr();
	      Write();
	      break;
       case 2:all();
	      break;
       case 3:clrscr();
	      int j;
	      cout<<"\nEnter the movie code: ";
	      cin>>j;
	      Display(j);
	      break;
       case 4:Modify();
	      break;
       case 5:mdelete();
	      break;
       case 6:return;
       default:cout<<"Invalid option";
   }
   Option();
}

//---------------------* MAIN FUNCTION *-----------------------//

void main()
{
   int opt;
   start();
   do
   {
     clrscr();
     cout<<"\n\n\t\t-------------MAIN MENU-------------                  ";
     cout<<"\n\n\n\t\t\t 1.CREATORS MENU";
     cout<<"\n\n\n\t\t\t 2.USERS MENU";
     cout<<"\n\n\n\t\t\t 3.Exit";
     cout<<"\n\nSelect your choice(1/2/3): ";
     cin>>opt;
     switch(opt)
     {
       case 1:clrscr();
	      entry();
	      break;
       case 2:clrscr();
	      User();
	      break;
       case 3:exit(0);
       default:cout<<"Invalid option";
     }
   }
   while(opt!=3);
}
