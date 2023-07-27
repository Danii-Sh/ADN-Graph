#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
int AdjMat[12][12];


void FillGraph()
{

	/*     n=0   n=1   n=2
	 *  i=1
	 *  i=2
	 *   ..
	 * /**/
srand(time(0));
int n=0;
for (int i=0;i!=12;i++)
{
	AdjMat[n][i]=0;
	for(int m=i+1;m!=12;m++)
	{AdjMat[m][i]=rand()%2;
	}
	n++;
}
for (int i=0;i!=12;i++)
{
	for(int m=i+1;m!=12;m++)
	{AdjMat[i][m]=AdjMat[m][i];
	}
}
}

void PrintGraph()
{
	
//int x=12;
for (int i=0;i!=12;i++)
{	for(int n=0;n!=12;n++)
	{cout<<AdjMat[n][i];
	cout<<" ";
	}
	//x--;
	cout<<endl;

}
}

void Luby()
{   
//cout<<"Debug Check Point";

int I[12];     ///According to MIS.pdf :: Luby Paper  ::  Final Independent Set Result
int Dv[12];     ///According to MIS.pdf :: Luby Paper :: Node Degree , Initialized at first
int S[12];     ///According to MIS.pdf :: Luby Paper :: will be U with final result
int Gprime[12];      ///According to MIS.pdf :: Luby Paper  :: Initialized By full Graph, decremented by chosen node and its neighbours
int NodeClass[12]; //my own aux parameter

int ChosenNodeDegree,ChosenNodeNo, RemainingNodeNo=12; ////Parameters to set Node No. and Degree No. of Max degree Node, and Check Luby Condition 

int i,k,a,n,x;

for(i=0;i!=12;i++)
{Dv[i]=0;}

for(i=0;i!=12;i++)
{
	for(k=0;k!=12;k++)
	{
	Dv[i] = (AdjMat[i][k])+Dv[i];
	}
	I[i]=0;
	Gprime[i]=1;
}


cout<<"                              ";

while( RemainingNodeNo !=0 ) ////Sharte Luby
//for(int X=0;X!=400;X++)   ////Sharte Luby for Debug
{


cout<<"Dv is ";         ///Debug Degree Of Node Updates
for(int D=0;D!=12;D++)  ///Debug Degree Of Node Updates
{cout<<Dv[D]<<" ";}     ///Debug Degree Of Node Updates


for(a=0;a!=12;a++)
{S[a]=0;
NodeClass[a]=-1;}



for(a=0;a!=12;a++)    ////Choosing Nodes
{if(Gprime[a]==1)
{
if((Dv[a]!=0) && (rand()%(2*Dv[a])==1)) ////Choosing Nodes
{S[a]=1;}   ////Choosing Nodes
if(Dv[a]==0)  ////Choosing Nodes
{S[a]=2;}}   ////Choosing Nodes
}



cout<<"S[i] ";
for(x=0;x!=12;x++)
{cout<<S[x]<<" ";}






for(x=0;x!=12;x++)
	{
	for(n=x+1;n!=12;n++)
	{
	if(S[x]==1 && S[n]==1)
	{
		if((AdjMat[x][n])==1)
		{if(NodeClass[x]==-1)
			{NodeClass[x]=x;}	
		NodeClass[n]=NodeClass[x];
		}		
	}}
	if(S[x]==1 &&  NodeClass[x]==-1)
	{NodeClass[x]=x;
	cout<<"xo"<<x<<"xo";}
	
	}


cout<<"NodeClass ";
for(x=0;x!=12;x++)
{cout<<NodeClass[x]<<" ";}



///&&&&/// Updating I and G routine
for(x=0;x!=12;x++)
{


if(S[x]==2)      ////Add Isolated Nodes
{I[x]=1;         ////Add Isolated Nodes
Gprime[x]=0;}    ////Add Isolated Nodes



ChosenNodeDegree=0;
ChosenNodeNo=-1;
for (n=0;n!=12;n++)
{if(NodeClass[n]==x)
	{if(ChosenNodeDegree<Dv[n])
	{ChosenNodeDegree=Dv[n];
	ChosenNodeNo=n;}
}}



if(ChosenNodeNo!=-1)
{I[ChosenNodeNo]=1;   //Add to I
Gprime[ChosenNodeNo]=0; //Remove From G'
for(a=0;a!=12;a++)
{if(AdjMat[ChosenNodeNo][a]==1)  ////Remove Neighbours
{Gprime[a]=0;}}}
}
///&&&&/// Up to This Point 

cout<<endl;
cout<<" I is ";
RemainingNodeNo=0;
for(a=0;a!=12;a++)
{ RemainingNodeNo = Gprime[a] +  RemainingNodeNo;
//if(Gprime[a]==1)
//{//cout<<a<<":"<<Dv[a]<<" ";
cout<<I[a]<<" ";
}
   }

cout<<endl;


}

int main()
{	

	FillGraph();

	PrintGraph();

	Luby();
}



/*
algorithm:::

..
. .
.  .
.   .
...
.. .
..  .
...


/**/
