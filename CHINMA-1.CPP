/*

PROJECT NAME :- PARKING LOT MANAGEMENT SYSTEM
DEVELOPED IN :- C++
DEVELOPED BY :- CHINMAY MAHAJAN

*/

	/* !!!!!!!!!!!!!!!!!!!!!    HEADER FILES    !!!!!!!!!!!!!!!!!!!!! */

#include<ctype.h>
#include<iostream.h>
#include<conio.h>
#include<time.h>
#include<fstream.h>
#include<iomanip.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<process.h>


	/*----------------GLOBAL VARIABLES----------------*/

int arr[10][10],arr1[10][10];
int ohr,omin,osec;//for out time



	/* *****************PARKING CLASS******************* */

class parking
{
public: char no[30],model[50];
	char name[50];
	int hr,min,sec;//for time
	int lot,btoken;

	void set_null();
	void get_time(time_t &now1);
	void show_details();
	void getout_time(time_t &now2);
};// parking class


/*--------------------------VOID SET_NULL()---------------------------------*/

void parking::set_null()
{

ofstream towrite;
towrite.open("bikelot.bin",ios::out);

	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		arr[i][j]=0;
		}//inner_for (j)

	}//inner_for (i)

towrite.write((char *) &arr,sizeof(arr));
}//void set_null() to empty all parking

/*--------------------------VOID GET_TIME()---------------------------------*/

void parking::get_time(time_t &now1)
{


	struct tm *current;
	now1 = time(0);
	current = localtime(&now1);
	hr=current->tm_hour;
	min= current->tm_min;
	sec= current->tm_sec;


}//time

/*--------------------------VOID GETOUT_TIME()---------------------------------*/

void parking::getout_time(time_t &now2)
{


	struct tm *current;
	now2 = time(0);
	current = localtime(&now2);
	ohr=current->tm_hour;
	omin= current->tm_min;
	osec= current->tm_sec;


}//time
/*--------------------------VOID SHOW_DETAILS()---------------------------------*/

void parking::show_details()
{
  textcolor(9);
cout<<"\n------------------------------------\n";
cout<<"\nLOT NUMBER IS :"<<lot<<"\n";
cout<<"VEHICLE NUMBER IS :"<<no<<"\n";
cout<<"MODEL IS:"<<model<<"\n";
cout<<"DRIVERS NAME IS:"<<name<<"\n";
cout<<"IN-TIME IS :"<<hr<<":"<<min<<":"<<sec<<"\n";
}


	/* ***************TWO WHEELER CLASS******************* */

class twowheeler : public parking
{
public:
	void get_details();
	void show_lot();
	void allot();
	void write(twowheeler tw1);
	void read(twowheeler tw2);
	void exit(twowheeler tw3);
	void deletelot(int lotno);
	int check(int blot);
	int search();
	void display_all(twowheeler tw4);

	char no[20],model[20];
	char name[20];
      //	int hr,min,sec;//for time
	int lot,btoken;
};

/*--------------------------VOID GET_DETAILS()---------------------------------*/

void twowheeler::get_details()
{
int val_lot;
do
{
		textcolor(9);
		gotoxy(00,18);
cprintf("ENTER THE LOT NUMBER :");
textcolor(8);
cin>>lot;

val_lot=check(lot);

}while(val_lot==1);

		textcolor(9);
		gotoxy(00,20);
cprintf("ENTER VEHICLE NUMBER :");
textcolor(8);
cin>>no;
		textcolor(9);
		gotoxy(00,22);
cprintf("ENTER THE MODEL :");
textcolor(8);
cin>>model;
		textcolor(9);
		gotoxy(00,24);
cprintf("ENTER DRIVERS NAME :");
textcolor(8);
cin>>name;

}//void get_details (function of class two wheeler)

/*--------------------------VOID SHOW_LOT()---------------------------------*/

void twowheeler::show_lot()
{

ifstream toread;
toread.open("bikelot.bin",ios::in);
toread.read((char *) &arr,sizeof(arr));

	int cnt=1;
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		if(arr[i][j]==0)
		{
		textcolor(GREEN);

		//cprintf("|  %d | ",cnt);
		cout<<"|"<<setw(3)<<setfill('0')<<cnt<<"|\t";
		cnt++;
		}//if
		else if(arr[i][j]==1)
		{
			highvideo();
		textattr(RED+BLINK);
		cprintf("| A |   ");
		cnt++;
		}
		else
		cnt++;
		
		} //inner_for (j)
		cout<<"\n";
	} //outer_for  (i)

}//show_lot

/*--------------------------VOID ALLOT()---------------------------------*/

void twowheeler::allot()
{
int cnt=1;

ofstream towrite;
towrite.open("bikelot.bin",ios::out);

	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		if(lot==cnt)
		{
		arr[i][j]=1;

		cnt++;
		}

		else

		cnt++;

		}//for

	}  //for

towrite.write((char *) &arr,sizeof(arr));
towrite.close();
}

/*--------------------------VOID WRITE()---------------------------------*/

void twowheeler::write(twowheeler tw1)
{

ofstream towrite;
towrite.open("twowheeler.bin",ios::app|ios::binary);//for writing in file

towrite.write((char *) &tw1,sizeof(tw1));
towrite.close();
}//erite in file

/*--------------------------VOID READ()---------------------------------*/

void twowheeler::read(twowheeler tw2)
{
ifstream toread;//for reading from file
toread.open("twowheeler.bin",ios::binary);

	while(toread.read((char *)&tw2,sizeof (tw2)))
	{

cout<<"\n------------------------------------\n";
cout<<"\nLOT NUMBER IS :"<<tw2.lot<<"\n";
cout<<"VEHICLE NUMBER IS :"<<tw2.no<<"\n";
cout<<"MODEL IS:"<<tw2.model<<"\n";
cout<<"DRIVERS NAME IS:"<<tw2.name<<"\n";
cout<<"IN-TIME IS :"<<tw2.hr<<":"<<tw2.min<<":"<<tw2.sec<<"\n";

	}//while loop


toread.close();
}//read from file function

/*--------------------------VOID EXIT()---------------------------------*/

void twowheeler::exit(twowheeler tw3)
{
char bikno[10];
int flag=0;
int tok,bmin,bhour=0;
float bill=0;
char a=179;

ifstream toread;
toread.open("twowheeler.bin",ios::binary);

ofstream towrite;
towrite.open("temptwowheeler.bin",ios::out|ios::binary);

	cout<<"\nENTER THE BIKE NUMBER :\t";
	cin>>bikno;

	while(toread.read((char *)&tw3,sizeof(tw3)))
	{

		if(strcmp(tw3.no,bikno)==0)
		{       flag=1;
			clrscr();
			for(int k=0;k<15;k++)
			{      //cout<<endl;
				gotoxy(1,k);
				cprintf("%c",a);
			}
				for(int i=1;i<35;i++)
				{
					gotoxy(i,1);
					cprintf("--");
				}
					for(int j=1;j<35;j++)
				{
					gotoxy(j,15);
					cprintf("--");
				}

				for(k=1;k<15;k++)
			{      //cout<<endl;
				gotoxy(35,k);
				cprintf("%c",a);
			}


  textcolor(11);

		gotoxy(10,3);
		cprintf("***RECEIPT***");

	gotoxy(5,5);
//"\n------------------------------------\n";
cprintf("\nLOT NUMBER IS :%d",tw3.lot);
	gotoxy(5,6);
cprintf("VEHICLE NUMBER IS : %s",tw3.no);
	gotoxy(5,7);
cprintf("MODEL IS: %s",tw3.model);
	gotoxy(5,8);
cprintf("DRIVERS NAME IS: %s",tw3.name);
	gotoxy(5,9);
cprintf("IN-TIME IS : %d:%d:%d",tw3.hr,tw3.min,tw3.sec);

		deletelot(tw3.lot);
			gotoxy(5,10);
		cprintf("OUT-TIME IS -> %d:%d:%d",ohr,omin,osec);
		bhour=ohr-tw3.hr;
		bmin=omin-tw3.min;
		if(bhour<0)
		bhour*=(-1);
		bhour*=60;
		bmin+=bhour;

		if(bmin<0)
		bmin*=(-bmin);

		bill=(bmin*0.50);
			gotoxy(5,11);
		cprintf("TOTAL MINUITES ARE :",bmin);
			gotoxy(5,12);
		cprintf("TOTAL BILL IS = %f RS",bill);
			gotoxy(5,14);
		cprintf("***THANK YOU VISIT AGAIN***");
		}

		else
		{//for writing in file
		towrite.write((char *) &tw3,sizeof(tw3));
		}

	}//while loop
	if(flag==0)
	{
	clrscr();
		gotoxy(5,14);
	cprintf("%s NUMBER'S BIKE IS NOT PRESENT IN PARKING",bikno);
	}
towrite.close();
toread.close();

remove("twowheeler.bin");
rename("temptwowheeler.bin","twowheeler.bin");

}

/*--------------------------VOID DELETELOT()---------------------------------*/

void twowheeler::deletelot(int lotno)
{
int cnt=1,ch;

ifstream toread;
fstream towrite;

toread.open("bikelot.bin",ios::in);
towrite.open("tempbklot.bin",ios::out);

toread.read((char *) &arr,sizeof(arr));
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		 if(lotno==cnt)
		 {
		 arr[i][j]=0;
		 cnt++;
		 }

		else if(arr[i][j]==1)
		 {
		 arr[i][j]=1;
		 cnt++;
		 }
		 else if(arr[i][j]==0)
		 {

		 arr[i][j]=0;


		 cnt++;
		 }

		 else
		 cnt++;

		}//for

	}  //for

towrite.write((char *) &arr,sizeof(arr));
towrite.close();
toread.close();
remove("bikelot.bin");
rename("tempbklot.bin","bikelot.bin");

}

/*--------------------------INT CHECK()---------------------------------*/

int twowheeler::check(int blot)
{
twowheeler tw4;
ifstream toread("twowheeler.bin",ios::binary);

	while(toread.read((char *)&tw4,sizeof tw4))
	{

		if(blot==tw4.lot)
		{
		cout<<"\nLOT NUMBER "<<blot<<" ALREADY ALLOTED\n";

		return 1;

		}

		if(blot>100||blot<1)
	       {
	       cout<<"\nINVALID LOT NUMBER\n";
		return 1;
		}
		//else

	}//while loop
		return 0;

}

/*--------------------------VOID SEARCH()---------------------------------*/

int twowheeler::search()
{
twowheeler tw5;
char sbikno[15],sdriver[15],smodel[15];
int stok,sbmin,sbhour=0,flag=0;
	float sbill=0;
int slot,sch;


ifstream toread;
toread.open("twowheeler.bin",ios::binary);

gotoxy(25,6);
cprintf("1. SEARCH BY LOT NUMBER\n\n");
gotoxy(25,8);
cprintf("2. SEARCH BY VEHICLE NUMBER\n\n");
gotoxy(25,10);
cprintf("3. SEARCH BY MODEL\n\n");
gotoxy(25,12);
cprintf("4. SEARCH BY DRIVER'S NAME\n\n");
gotoxy(25,14);
cprintf("INPUT -");
			gotoxy(35,14);
			cprintf("[");
			gotoxy(37,14);
			cprintf("]");

gotoxy(36,14);
cin>>sch;

if(sch>4)
{
gotoxy(40,18);
flag=1;
cprintf("!!! INCORRECT CHOICE");

}

	if(sch==1)
		{
		cout<<"\n\nENTER THE LOT NUMBER :\t";
		cin>>slot;
		}
	if(sch==2)
		{
		cout<<"\nENTER THE VEHICLE NUMBER :\t";
		cin>>sbikno;
		}
	if(sch==3)
		{
		cout<<"\ENTER THE MODEL NAME :\t";
		cin>>smodel;
		}

	if(sch==4)
		{
		cout<<"ENTER DRIVER'S NAME :\t";
		cin>>sdriver;
		}


	while(toread.read((char *)&tw5,sizeof(tw5)))
	{


			 //	 cout<<tw5.lot;


			if(sch==1 && slot==tw5.lot)
			goto lab;

			else if(sch==2&&strcmp(tw5.no,sbikno)==0)
			goto lab;

			else if(sch==3&&(strcmp(tw5.model,smodel)==0))
			goto lab;

			else if((sch==4&&strcmp(tw5.name,sdriver)==0))
			goto lab;

			else
			{goto exit;}

		     lab:
			{


		flag=1;
	textcolor(11);
	cout<<"\n------------------------------------\n";
	cout<<"\nLOT NUMBER IS :"<<tw5.lot<<"\n";
	cout<<"VEHICLE NUMBER IS :"<<tw5.no<<"\n";
	cout<<"MODEL IS:"<<tw5.model<<"\n";
	cout<<"DRIVERS NAME IS:"<<tw5.name<<"\n";
	cout<<"IN-TIME IS :"<<tw5.hr<<":"<<tw5.min<<":"<<tw5.sec<<"\n";

		textcolor(9);

		cout<<"CURRENT-TIME IS -> "<<ohr<<":"<<omin<<":"<<osec<<"\n";
		sbhour=ohr-tw5.hr;
		sbmin=omin-tw5.min;
		if(sbhour<0)
		sbhour*=(-1);

		sbhour*=60;

		sbmin+=sbhour;


		if(sbmin<0)
		sbmin*=(-sbmin);


		sbill=(sbmin*0.50);

			textcolor(RED);
		cout<<"\n\nTOTAL MINUITES UPTILL NOW ARE :"<<sbmin;
		cout<<"\nTOTAL BILL IS UPTILL NOW = "<<sbill<<" Rs ";
		cout<<"\n[ PERSS ENTER ]" ;
		getch();

		}//if

exit:

}//while
toread.close();
if(flag==0)
{	        gotoxy(36,18);
		textcolor(11);
		gotoxy(35,18);
		cprintf("NOT PRESENT IN PARKING");
		getch();
		return 0;
}//if


return 1;

}//search

/*--------------------------VOID DISPLAY_ALL()---------------------------------*/

void twowheeler::display_all(twowheeler tw4)
{
ifstream toread;//for reading from file
toread.open("twowheeler.bin",ios::binary);

	while(toread.read((char *)&tw4,sizeof (tw4)))
	{

	textcolor(7);
cprintf("--------------------------------------------------------------------------\n");
cout<<"\nLOT NUMBER IS :"<<tw4.lot<<"\t";
cout<<"VEHICLE NUMBER IS :"<<tw4.no<<"\t ";
//cout<<"MODEL IS:"<<tw4.model<<"\n";
//cout<<"DRIVERS NAME IS:"<<tw4.name<<"\t";
cout<<"IN-TIME IS :"<<tw4.hr<<":"<<tw4.min<<":"<<tw4.sec<<"\n";

	}//while loop


toread.close();
}//read from file function

	/* ***************FOUR WHEELER CLASS******************* */

class fourwheeler : public parking
{
public:
	void get_details(fourwheeler fw1);
	void show_lot();
	void allot(int);
	void read(fourwheeler fw2);
	void exit(fourwheeler fw3);
	void deletelot(int clotno);
	int check(int clot);
	int searchcar();
	void display_all(fourwheeler fw4);

	char cno[20],cmodel[20];
	char owname[20],valle[10];

	int carlot;
};
/*--------------------------VOID SHOW_LOT()---------------------------------*/

void fourwheeler::show_lot()
{
ifstream toread;
toread.open("carlot.bin",ios::in);
toread.read((char *) &arr1,sizeof(arr1));

	int cnt=1;
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		if(arr1[i][j]==0)
		{
		textcolor(YELLOW);

		cout<<"|"<<setw(3)<<setfill('0')<<cnt<<"|\t";
		cnt++;
		}//if
		else if(arr1[i][j]==1)
		{
		textattr(RED+BLINK);
			highvideo();
		cprintf("| A |   ");
		cnt++;
		}
		else
		cnt++;

		} //inner_for (j)

		cout<<"\n";
	} //outer_for  (i)

}//show_lot
/*--------------------------VOID GET_DETAILS()---------------------------------*/

void fourwheeler::get_details(fourwheeler fw1)
{
int vallot;
		textcolor(9);
		gotoxy(00,18);
do
{
cprintf("ENTER THE LOT NUMBER :");
textcolor(8);
cin>>fw1.carlot;

vallot=check(fw1.carlot);

}while(vallot==1);


allot(fw1.carlot);

		textcolor(9);
		gotoxy(00,22);
cprintf("ENTER VEHICLE NUMBER :");
textcolor(8);
cin>>fw1.cno;
		textcolor(9);
		gotoxy(00,24);
cprintf("ENTER THE MODEL :");
textcolor(8);
cin>>fw1.cmodel;
		textcolor(9);
		gotoxy(00,26);
cprintf("ENTER OWNER'S NAME :");
textcolor(8);
cin>>fw1.owname;


ofstream towrite;
towrite.open("fourwheeler.bin",ios::app|ios::binary);//for writing in file

towrite.write((char *) &fw1,sizeof(fw1));

towrite.close();

}//void get_details (function of class parking)

/*--------------------------INT CHECK()---------------------------------*/

int fourwheeler::check(int clot1)
{
fourwheeler fw4;
//int blot;
ifstream toread("fourwheeler.bin",ios::binary);



	while(toread.read((char *)&fw4,sizeof fw4))
	{

		if(clot1==fw4.carlot)
		{
		cout<<"\nLOT NUMBER "<<clot1<<" ALREADY ALLOTED\n";

		return 1;

		}

		if(clot1>100||clot1<1)
	       {
	       cout<<"\nINVALID LOT NUMBER\n";
		return 1;
		}
		//else

	}//while loop
		return 0;


}

/*--------------------------VOID ALLOT()---------------------------------*/

void fourwheeler::allot(int carlot1)
{
int cnt=1;

fstream towrite;
towrite.open("carlot.bin",ios::out);

	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		if(carlot1==cnt)
		{
		arr1[i][j]=1;

		cnt++;
		}

		else

		cnt++;

		}//for

	}  //for

towrite.write((char *) &arr1,sizeof(arr1));

}//lot allot
/*--------------------------VOID READ()---------------------------------*/

void fourwheeler::read(fourwheeler fw2)
{
fstream toread;//for reading from file
toread.open("fourwheeler.bin",ios::in|ios::binary);
toread.clear();
toread.seekg(0L);
	while(toread.read((char *)&fw2,sizeof (fw2)))
	{

cout<<"\n------------------------------------\n";
cout<<"\nLOT NUMBER IS :"<<fw2.carlot<<"\n";
cout<<"VEHICLE NUMBER IS :"<<fw2.cno<<"\n";
cout<<"MODEL IS:"<<fw2.cmodel<<"\n";
cout<<"DRIVERS NAME IS:"<<fw2.owname<<"\n";
cout<<"IN-TIME IS :"<<fw2.hr<<":"<<fw2.min<<":"<<fw2.sec<<"\n";


	}//while loop

toread.close();
}//read from file function

/*--------------------------VOID EXIT()---------------------------------*/

void fourwheeler::exit(fourwheeler fw3)
{
char carno[10],a=179;
int flag=0;
int cmin,chour=0,clot;
float cbill=0;

ifstream toread;
toread.open("fourwheeler.bin",ios::in|ios::binary);

ofstream towrite;
towrite.open("tempfourwheeler.bin",ios::out|ios::binary);

	cout<<"\n ENTER THE CAR'S NUMBER :\t";
	cin>>carno;

	while(toread.read((char *)&fw3,sizeof(fw3)))
	{

		if(strcmp(fw3.cno,carno)==0)

		{       flag=1;
			clrscr();
			for(int k=0;k<15;k++)
			{      //cout<<endl;
				gotoxy(1,k);
				cprintf("%c",a);
			}
				for(int i=1;i<35;i++)
				{
					gotoxy(i,1);
					cprintf("--");
				}
					for(int j=1;j<35;j++)
				{
					gotoxy(j,15);
					cprintf("--");
				}

				for(k=1;k<15;k++)
			{      //cout<<endl;
				gotoxy(35,k);
				cprintf("%c",a);
			}

  textcolor(10);
//cout<<"\n------------------------------------\n";
		gotoxy(10,3);
		cprintf("***RECEIPT***");

	gotoxy(5,5);

cprintf("\nLOT NUMBER IS :%d",fw3.carlot);
	gotoxy(5,6);
cprintf("VEHICLE NUMBER IS :%s",fw3.cno);
	gotoxy(5,7);
cprintf("MODEL IS: %s",fw3.cmodel);
	gotoxy(5,8);
cprintf("DRIVERS NAME IS: %s",fw3.owname);
	gotoxy(5,9);
cprintf("IN-TIME IS : %d:%d:%d",fw3.hr,fw3.min,fw3.sec);


		deletelot(fw3.carlot);
			gotoxy(5,10);
		cprintf("OUT-TIME IS -> %d:%d:%d",ohr,omin,osec);
		chour=ohr-fw3.hr;
		cmin=omin-fw3.min;
		if(chour<0)
		chour*=(-1);
		chour*=60;
		cmin+=chour;
		if(cmin<0)
		cmin*=(-cmin);
		cbill=(cmin*1);
		gotoxy(5,11);
		cprintf("TOTAL MINUITES ARE : %d",cmin);
		gotoxy(5,12);
		cprintf("TOTAL BILL IS =  %f",cbill);
		gotoxy(5,14);
		cprintf("***THANK YOU VISIT AGAIN***");
		}  //if

		else
		{//for writing in file
		towrite.write((char *) &fw3,sizeof(fw3));
		}

	}//while loop

	if(flag==0)
	{

	clrscr();
		gotoxy(5,14);
	cprintf("%s NUMBER'S CAR IS NOT PRESENT IN PARKING",carno);
	}
towrite.close();
toread.close();

remove("fourwheeler.bin");
rename("tempfourwheeler.bin","fourwheeler.bin");

}

/*--------------------------VOID DELETELOT()---------------------------------*/

void fourwheeler::deletelot(int clotno)
{

int cnt=1,ch;

ifstream toread;
fstream towrite;

toread.open("carlot.bin",ios::in|ios::binary);
towrite.open("tempcarlot.bin",ios::out,ios::binary);

toread.read((char *) &arr1,sizeof(arr1));

	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
		 if(clotno==cnt)
		 {
		 arr1[i][j]=0;
		 cnt++;
		 }

		else if(arr1[i][j]==1)
		 {
		 arr1[i][j]=1;
		 cnt++;
		 }
		 else if(arr1[i][j]==0)
		 {

		 arr1[i][j]=0;

		 cnt++;
		 }

		 else
		 cnt++;

		}//for

	}  //for

towrite.write((char *) &arr1,sizeof(arr1));
towrite.close();
toread.close();
remove("carlot.bin");
rename("tempcarlot.bin","carlot.bin");

//cout<<"\nLOT DE-ALLOCATED\n";
}

/*--------------------------VOID SEARCHCAR()---------------------------------*/

int fourwheeler::searchcar()
{
fourwheeler fw5;
char scikno[15],scdriver[15],scmodel[15];
int stok,sbmin,sbhour=0,flag=0;
float sbill=0;
int sclot,sch;


ifstream toread;
toread.open("fourwheeler.bin",ios::binary);
gotoxy(25,6);
cprintf("1. SEARCH BY LOT NUMBER\n\n");
gotoxy(25,8);
cprintf("2. SEARCH BY VEHICLE NUMBER\n\n");
gotoxy(25,10);
cprintf("3. SEARCH BY MODEL\n\n");
gotoxy(25,12);
cprintf("4. SEARCH BY DRIVER'S NAME\n\n");
gotoxy(25,14);
cprintf("INPUT -");
			gotoxy(35,14);
			cprintf("[");
			gotoxy(37,14);
			cprintf("]");

gotoxy(36,14);
cin>>sch;

if(sch>5)
{

cout<<"\n\nINCORRECT CHOICE\n\n";
flag=1;
}

	if(sch==1)
		{
		cout<<"\n\nENTER THE LOT NUMBER :\t";
		cin>>sclot;
		}
	if(sch==2)
		{
		cout<<"\nENTER THE VEHICLE NUMBER :\t";
		cin>>scikno;
		}
	if(sch==3)
		{
		cout<<"\ENTER THE MODEL NAME :\t";
		cin>>scmodel;
		}

	if(sch==4)
		{
		cout<<"ENTER DRIVER'S NAME :\t";
		cin>>scdriver;
		}
		
	while(toread.read((char *)&fw5,sizeof(fw5)))
	{

			if(sch==1 && sclot==fw5.carlot)
			goto labe;

			else if(sch==2&&strcmp(fw5.cno,scikno)==0)
			goto labe;

			else if(sch==3&&(strcmp(fw5.cmodel,scmodel)==0))
			goto labe;

			else if((sch==4&&strcmp(fw5.owname,scdriver)==0))
			goto labe;

			else
			{goto exit1;}


		     labe:
			{


		flag=1;
	textcolor(9);
	cout<<"\n------------------------------------\n";
	cout<<"\nLOT NUMBER IS :"<<fw5.carlot<<"\n";
	cout<<"VEHICLE NUMBER IS :"<<fw5.cno<<"\n";
	cout<<"MODEL IS:"<<fw5.cmodel<<"\n";
	cout<<"DRIVERS NAME IS:"<<fw5.owname<<"\n";
	cout<<"IN-TIME IS :"<<fw5.hr<<":"<<fw5.min<<":"<<fw5.sec<<"\n";

		textcolor(9);

		cout<<"CURRENT-TIME IS -> "<<ohr<<":"<<omin<<":"<<osec<<"\n";
		sbhour=ohr-fw5.hr;
		sbmin=omin-fw5.min;
		if(sbhour<0)
		sbhour*=(-1);

		sbhour*=60;

		sbmin+=sbhour;


		if(sbmin<0)
		sbmin*=(-sbmin);


		sbill=(sbmin*1);

	     //		textcolor(RED);
		textcolor(9);
		cout<<"\n\nTOTAL MINUITES UPTILL NOW ARE :"<<sbmin;
		cout<<"\nTOTAL BILL IS UPTILL NOW = "<<sbill<<" Rs ";
		cout<<"\n[ PRESS ENTER ]" ;
		getch();

		}//if

exit1:

}//while

toread.close();


if(flag==0)
{

		     gotoxy(36,18);
	       textcolor(10);
	       gotoxy(35,18);
	       cprintf("NOT PRESENT IN PARKING");
	       getch();
	       return 0;
}//if


return 1;
}//search

/*--------------------------VOID DISPLAY_ALL()---------------------------------*/

void fourwheeler::display_all(fourwheeler fw4)
{
ifstream toread;//for reading from file
toread.open("fourwheeler.bin",ios::binary);

	while(toread.read((char *)&fw4,sizeof (fw4)))
	{

	textcolor(7);
cprintf("---------------------------------------------------------------------------\n");
cout<<"\nLOT NUMBER IS :"<<fw4.carlot<<"\t";
cout<<"VEHICLE NUMBER IS :"<<fw4.cno<<"\t";
//cout<<"MODEL IS:"<<fw4.cmodel<<"\n";
//cout<<"DRIVERS NAME IS:"<<fw4.owname<<"\n";
cout<<"IN-TIME IS :"<<fw4.hr<<":"<<fw4.min<<":"<<fw4.sec<<"\n";

  //	tw2.show_details();
	}//while loop


toread.close();

}//read from file function

	/* ***************MAIN_SCREEN******************* */

class main_screen:public fourwheeler,public twowheeler
{

public:
	time_t now;
	int ch,bch,opt,caropt,ll;
	char choice;
public:
	twowheeler tw;
	fourwheeler fw;

	void greeting();
	void new_entry();
	void exiting();
	void twowheeler_screen();
	void home();
	void fourwheeler_screen();
	void carnew_entry();
	void carexiting();
	void date_time();

//void home();
};

/*--------------------------VOID DATE_TIME()---------------------------------*/

void main_screen::date_time()
{
 //  clrscr();
   int chr,cmin,csec;
   time_t now2;
   struct date d;

   getdate(&d);

	gotoxy(60,02);

   cprintf("%d/%d/%d",d.da_day,d.da_mon,d.da_year);
   gotoxy(60,03);

	struct tm *current;
	now2 = time(0);
	current = localtime(&now2);
	chr=current->tm_hour;
	cmin= current->tm_min;
	csec= current->tm_sec;
	cprintf("%d:%d:%d",chr,cmin,csec);
}

/*--------------------------VOID NEW_ENTRY()---------------------------------*/
void main_screen::new_entry()
{
			tw.show_lot();
			tw.get_time(now);
			tw.get_details();

			tw.allot();

			tw.write(tw);

}
/*--------------------------VOID CARNEW_ENTRY()---------------------------------*/

void main_screen::carnew_entry()
{
			fw.show_lot();
			fw.get_time(now);
			fw.get_details(fw);

}

/*--------------------------VOID EXITING()---------------------------------*/

void main_screen::exiting()
{

			tw.getout_time(now);
			tw.read(tw);
			tw.exit(tw);
}

/*--------------------------VOID CAREXITING()---------------------------------*/

void main_screen::carexiting()
{

				fw.getout_time(now);
				fw.read(fw);

				fw.exit(fw);
}

/*--------------------------VOID TWOWHEELER_SCREEN()---------------------------------*/

void main_screen::twowheeler_screen()
{
	twhome:
		date_time();
		textcolor(11);
		gotoxy(32,10);
		cprintf("1. NEW ENTRY");
		gotoxy(32,12);
		cprintf("2. EXITING");
		gotoxy(32,14);
		cprintf("3. SEARCH");
		gotoxy(32,16);
		cprintf("4. DISPLAY ALL");
		gotoxy(32,18);
		cprintf("5. BACK");
		gotoxy(32,20);
		cprintf("6. EXIT");
			gotoxy(39,22);
			cprintf("[");
			gotoxy(41,22);
			cprintf("]");

		gotoxy(32,22);

		cprintf("INPUT -");
		gotoxy(40,22);
		cin>>opt;


		clrscr();
}

/*--------------------------VOID FOURWHEELER_SCREEN()---------------------------------*/

void main_screen::fourwheeler_screen()
{
		gotoxy(25,14);
		date_time();
		textcolor(10);
		gotoxy(32,10);
		cprintf("1. NEW ENTRY");
		gotoxy(32,12);
		cprintf("2. EXITING");
		gotoxy(32,14);
		cprintf("3. SEARCH");
		gotoxy(32,16);
		cprintf("4. DISPLAY ALL");
		gotoxy(32,18);
		cprintf("5. BACK");
		gotoxy(32,20);
		cprintf("6. EXIT");
			gotoxy(39,22);
			cprintf("[");
			gotoxy(41,22);
			cprintf("]");


		gotoxy(32,22);
		cprintf("INPUT -");
		gotoxy(40,22);
		cin>>caropt;
		clrscr();
}

/*--------------------------VOID GREETING()---------------------------------*/

void main_screen::greeting()
{

char str[31]="PARKING LOT MANAGEMENT SYSTEM";

textcolor(14);
gotoxy(25,6);


for(int j=0;j<30;j++)
{
//cout<<str[j];
//cprintf("-");
//cprintf("\\");delay(20);
gotoxy(25+j,6);
cprintf("|"); delay(30);
gotoxy(25+j,6);
cprintf("/"); delay(30);
gotoxy(25+j,6);
cprintf("-"); delay(30);
gotoxy(25+j,6);
cprintf("\\"); delay(30);
gotoxy(25+j,6);
cprintf("|"); delay(30);
gotoxy(25+j,6);
cprintf("%c",str[j]);
delay(50);
}//for

}//greeting

/*--------------------------VOID HOME()---------------------------------*/

void main_screen::home()
{

do
{
textcolor(5);
gotoxy(25,6);
	highvideo();
cprintf("PARKING LOT MANAGEMENT SYSTEM");
gotoxy(25,14);
date_time();
gotoxy(32,10);
	normvideo();
	textcolor(14);
cprintf("1. TWO-WHEELER");
gotoxy(32,12);
cprintf("2. FOUR-WHEELER");
gotoxy(32,14);
cprintf("3. EXIT");

gotoxy(30,20);

cprintf("INPUT -");
		gotoxy(37,20);
		cprintf("[");
		gotoxy(39,20);
		cprintf("]");

gotoxy(38,20);
cin>>ch;

clrscr();
	switch(ch)
	{
	case 1:
	      //	 twowheeler_screen();
		tlab:	 twowheeler_screen();
		//if(!isalpha(opt))
	       //	if(opt < 0 && opt >= 6)

		switch(opt)
		{

		case 1:
			new_entry();
			break;

		case 2:
			exiting();
			getch();
			break;

		case 3: int flag=0;
			char con;
			cont:
			tw.getout_time(now);
			flag=search();
			  gotoxy(30,20);
			  textcolor(11);
			  if(flag==0)
			  {
			cprintf("DO YOU WANT TO SEARCH IN OTHER WAY..??(Y/N)");
			gotoxy(75,20);
			cprintf("[");
			gotoxy(77,20);
			cprintf("]");
			gotoxy(76,20);
			cin>>con;
			if(con=='y'||con=='Y')
			{
			clrscr();
			goto cont;
			}//inner_if
			} //outer_if
		       //	getch();
			break;

		case 4:
			gotoxy(32,16);
			textcolor(11);
			gotoxy(32,14);
			cprintf("1.LOT");
			gotoxy(32,16);
			cprintf("2.LIST");
			gotoxy(32,18);
			cprintf("INPUT - ");

			gotoxy(39,18);
			cprintf("[");
			gotoxy(41,18);
			cprintf("]");

			gotoxy(40,18);
			cin>>ll;
			clrscr();
			if(ll==2)
			{
			tw.display_all(tw);
			cprintf("[ PRESS ENTER ]");
			}
		       else if(ll==1)
			{
			tw.show_lot();
			cprintf("[ PRESS ENTER ]");
			}
			else
			{
			cout<<"\n!!!INCORRECT CHOICE\n";
			}
			  getch();
			  clrscr();

			goto tlab;

		       //	 getch();
		       //	break;
		case 5:	home();
			break;
		case 6:
			_exit(0);
			break;

		default:
			clrscr();
			gotoxy(32,20);
			cout<<"!!!INCORRECT CHOICE!!!";
			delay(600);
			clrscr();
		      // twowheeler_screen();
			goto tlab;
		} //inner switch

		break;   //case 1

	case 2:

	   //	fourwheeler_screen();
		flab: fourwheeler_screen();
		switch(caropt)
		{
		case 1:
			carnew_entry();

			break;
		case 2:
		       carexiting();
			getch();
			break;
		case 3:
			 int flag=0;
			 char con;
		       //	searchcar();
		       //	getch();
		       conti:
		       fw.getout_time(now);
			flag=searchcar();
			gotoxy(30,20);
			  textcolor(10);
			  if(flag==0)
			  {
			cprintf("DO YOU WANT TO SEARCH IN OTHER WAY..??(Y/N)");
			gotoxy(75,20);
			cprintf("[");
			gotoxy(77,20);
			cprintf("]");
			gotoxy(76,20);
			cin>>con;

			if(con=='y'|| con=='Y')
			{
			clrscr();
			goto conti;
			}//inner_if
			} //outer_if
		       //	getch();

			break;

		case 4:
			gotoxy(32,16);
			textcolor(11);
			gotoxy(32,14);
			cprintf("1.LOT");
			gotoxy(32,16);
			cprintf("2.LIST");
			gotoxy(32,18);
			cprintf("INPUT - ");

			gotoxy(39,18);
			cprintf("[");
			gotoxy(41,18);
			cprintf("]");

			gotoxy(40,18);
			cin>>ll;
			clrscr();
			if(ll==2)
			{
			fw.display_all(fw);
			cprintf("[ PRESS ENTER ]");
			}
		       else if(ll==1)
			{
			fw.show_lot();
			cprintf("[ PRESS ENTER ]");
			}
			else
			{
			cout<<"\n!!!INCORRECT CHOICE\n";

			}
				getch();
				clrscr();

					goto flab;
		      //	break;

		case 5:
			home();
			break;
		case 6:
			_exit(0);
			break;
		default:cout<<"\n!!!INCORRECT CHOICE";
			break;
		}
		break;  //case 2

	case 3:
		_exit(0);
		break;          //case 3
	default: clrscr();
		gotoxy(32,20);
		cout<<"!!!INCORRECT CHOICE!!!";
		delay(600);
		break;

	}//outer switch of ch

//}while(ch!=3);


clrscr();

	highvideo();
textcolor(15);
gotoxy(32,12);
cprintf("***THANK YOU***");
gotoxy(22,15);
cprintf("DO YOU WANT TO CONTINUE THE SYSTEM: (Y/N) ");
gotoxy(65,15);
cprintf("[");
gotoxy(67,15);
cprintf("]");
gotoxy(66,15);
cin>>choice;

clrscr();
}while(choice=='y'||choice=='Y');

}//home
	/* ***************VOID MAIN******************* */

void main()
{
clrscr();

main_screen m;
m.greeting();
m.date_time();
m.home();

//getch();

}
