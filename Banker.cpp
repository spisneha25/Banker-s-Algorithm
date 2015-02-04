#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#define MAX 20

void tblshp(int ,int a[MAX][MAX],int b[MAX][MAX],int c[MAX][MAX],int d[MAX]);
int nop, al[MAX][MAX],m[MAX][MAX],n[MAX][MAX],avail[MAX],result[MAX];

class bankers
{
	private:
		int nor,k,pnum,work[MAX],finish[MAX];
	public:
		bankers();
		void input();
		void method();
		int search(int);
		void display();
};

bankers::bankers()
{
	k=0;
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			al[i][j]=0;
			m[i][j]=0;
			n[i][j]=0;
		}
	avail[i]=0;
	result[i]=0;
	finish[i]=0;
	}
}

void bankers::input()
{
	int i,j;
	cout<<"Enter the number of processes:";
	cin>>nop;
	nor=3;
	cout<<"Enter the allocated resources for each process: "<<endl;
	for(i=0;i<nop;i++)
	{
		cout<<"\nProcess "<<i;
		for(j=0;j<nor;j++)
		{
			cout<<"\nResource "<<j<<":";
			cin>>al[i][j];
		}
	}
	cout<<"Enter the maximum resources that are needed for each process: "<<endl;
	for(i=0;i<nop;i++)
	{
		cout<<"\nProcess "<<i;
		for(j=0;j<nor;j++)
		{
			cout<<"\nResouce "<<j<<":";
			cin>>m[i][j];
			n[i][j]=m[i][j]-al[i][j];	
		}
	}
	cout<<"Enter the currently available resources in the system: ";
	for(j=0;j<nor;j++)
	{
		cout<<"Resource "<<j<<":";
		cin>>avail[j];
		work[j]=-1;
	}
	for(i=0;i<nop;i++)
		finish[i]=0;
}

void bankers::method()
{
	int i=0,j,flag;
	while(1)
	{
		if(finish[i]==0)
		{
			pnum =search(i);
			if(pnum!=-1)
			{
				result[k++]=i;
				finish[i]=1;
				for(j=0;j<nor;j++)
				{
					avail[j]=avail[j]+al[i][j];
				}
			}
		}
		i++;
		if(i==nop)
		{
			flag=0;
			for(j=0;j<nor;j++)
				if(avail[j]!=work[j])
					flag=1;
			for(j=0;j<nor;j++)
				work[j]=avail[j];
			if(flag==0)
				break;
			else
				i=0;
		}
	}
}

int bankers::search(int i)
{
	int j;
	for(j=0;j<nor;j++)
		if(n[i][j]>avail[j])
			return -1;
	return 0;
}

void bankers::display()
{
	int i,j;
	cout<<endl<<"OUTPUT:";
	cout<<endl<<"========";
	cout<<endl<<"PROCESS\t     ALLOTED\t     MAXIMUM\t     NEED";
	for(i=0;i<nop;i++)
	{
		cout<<"\nP"<<i+1<<"\t     ";
		for(j=0;j<nor;j++)
		{
			cout<<al[i][j]<<"  ";
		}
		cout<<"\t     ";
		for (j=0;j<nor;j++)
		{
			cout<<m[i][j]<<"  ";
		}
		cout<<"\t     ";
		for(j=0;j<nor;j++ )
		{
			cout<<n[i][j]<<"  ";
		}	
	}
	cout<<"\nThe sequence of the safe processes are: \n";
	for(i=0;i<k;i++)
	{
		int temp = result[i]+1 ;
		cout<<"P"<<temp<<" ";
	}
	cout<<"\nThe sequence of unsafe processes are: \n";
	int flg=0;
	for (i=0;i<nop;i++)
	{
		if(finish[i]==0)
		{
			flg=1;
		}
		cout<<"P"<<i<<" ";
	}
	cout<<endl<<"RESULT:";
	cout<<endl<<"=======";
	if(flg==1)
		cout<<endl<<"The system is not in safe state and deadlock may occur!!";
	else	
		cout<<endl<<"The system is in safe state and deadlock will not occur!!";
}

int main()
{
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	clrscr();
	cout<<" DEADLOCK BANKER’S ALGORITHM "<<endl;
	bankers B;
	B.input ( );
	B.method ( );
	B.display ( );
	clrscr();
	tblshp(nop,al,m,n,result);
	getch();
}

void tblshp(int i,int x[20][20],int y[20][20],int z[20][20],int result[20])
{ //int i=5;
  	int n;
	setcolor(RED);
	settextstyle(4,0,6);
	outtextxy(100,4,"Banker's Algorithm");
	rectangle(90,10,530,70);
	settextstyle(0,0,0);
	int a[]={1,2,3,4,5},l;
	char p[]={'A','B','C'};
 	for(n=0,l=0;n<=i;n++,l++)
 	{
 		for(int k=0; k<4; k++)
  		{
   			rectangle(0+k*160,120+n*50,150+k*160,170+n*50);
    			if (k!=0)
    			{
    				for(int j=0;j<3;j++)
    				{
    					rectangle(160*k+j*50,120+n*50,210+160*(k-1)+j*50,170+n*50);
    					gotoxy(23+7*j+(k-1)*20,10);
    					cout<<p[j];
    					if (l!=0)
    					{
    						gotoxy(23+7*j+(k-1)*20,10+n*3);
    						switch(k-1)
    						{
    							case 0:
    								cout<<x[l-1][j];
    								break;
							case 1:
								cout<<y[l-1][j];
							  	break;
							case 2:
							    	cout<<z[l-1][j];
							    	break;
    						}
    					}
    				}
    			}
  		}
  		if (n!=0)
  		{
  			gotoxy(14,10+n*3);
  			cout<<n;
  		}
 	}
  	outtextxy(0,110,"Process name");
  	outtextxy(160,110,"Allocation");
  	outtextxy(320,110,"Maximum need");
  	outtextxy(480,110,"Available");
  	getch();
  	clrscr();
  	outtextxy(0,20,"safe sequence");
  	for(n=0;n<nop;n++)
  	{
  		rectangle(0+50*n,30,50+50*n,80);
  		gotoxy(4+6*n,4);
  		cout<<result[n];
  		gotoxy(14,4);
  	}
}

