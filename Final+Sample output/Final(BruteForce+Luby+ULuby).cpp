#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>

using namespace std;

vector < vector <int> > AllSubsets;
vector <int> IndependentSets;


int AdjMat[12][12];
int output[3];

//////Graph SubFunctions
//
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
	{if(rand()%4==1)
		{AdjMat[m][i]=1;}
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

void PrintGraph()    ////Debug Constructedc Graph
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
//
//////Graph SubFunctions


}


void find_subsets()
{
int i,t,counter,shift;
for(t=0;t!=4096;t++)
	{
	AllSubsets.push_back(vector <int>());
	for(shift=0;shift!=12;shift++)
		{
		AllSubsets[t].push_back((t>>shift)& 1);	
		}
	//cout<<t<<" ";  //Debug Subset Number
	}

}


void print_subsets()
{
for(int i=0;i!=4096;i++)              ////Debug
{
	for(int x=0;x!=12;x++)       /////Debug
	cout<< AllSubsets[i][x]<<" "; ////Debug

}
}


void Check_Pairs()
{
int n,x,Connected_Nodes,Subset_No;	
for(Subset_No=0;Subset_No!=4096;Subset_No++)
	{
	Connected_Nodes=0;
	for(x=0;x!=12;x++)
		{
		for(n=x+1;n!=12;n++)
		{
		if(AllSubsets[Subset_No][x]==1 && AllSubsets[Subset_No][n]==1)
			{
			if((AdjMat[x][n])==1)
			{Connected_Nodes=1;}
			}		
	
		//cout<<x<<','<<n<<' ';//Debug  for Checked Links
		//Check Matrix [x][n]
		}

		//cout<<endl;
		}
	if(Connected_Nodes==0)
		{
		IndependentSets.push_back(Subset_No);
		}
	}
}



void Print_results()
{

//cout<<"Number of Maximal Independet sets are "<< IndependentSets.size();
//cout<<endl;
//cout<<"All Maximal Independent Sets are as Followed:";
//cout<<endl<<"{"<<endl;
//for(int a=0;a!=IndependentSets.size();a++)
//{
//cout<<IndependentSets[a]<<" ";	
//}
//cout<<endl<<"}"<<endl;

int t,result[(IndependentSets.size())+1];
int k=0;
result[0]=0;//Number of Nodes
for(t=1;t!=IndependentSets.size();t++)
{result[t]=0;}//Subset Number
for(int a=0;a!=IndependentSets.size();a++)
{
	t=0;
	for(int x=0;x!=12;x++)
		{
		t=t+((IndependentSets[a]>>x) & 1);
		}
	if(t==result[0])
	{
	result[k+2]=IndependentSets[a];
	k++;
	}
	if(t>result[0])
	{result[0]=t;
	result[1]=IndependentSets[a];
	k=0;
	}
	
}
// cout<<k; debug : Number of repeated Subsets with same Size of Max Indie. Set
cout<<"Max Independent Set Size found using Brute Force is "<<result[0];	
//for(int x=0;x!=k;x++)
//{cout<<result[x+1]<<" ";}
//cout <<"]";

output[0]=result[0];

cout<<endl;


}


void BruteForce()
{
find_subsets();

//			cout<<endl;

//print_subsets();

//			cout<<endl;

Check_Pairs();

			cout<<endl;

Print_results();



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


//cout<<"                              ";

while( RemainingNodeNo !=0 ) ////Sharte Luby
//for(int X=0;X!=400;X++)   ////Sharte Luby for Debug
{


//cout<<"Dv is ";         ///Debug Degree Of Node Updates
//for(int D=0;D!=12;D++)  ///Debug Degree Of Node Updates
//{cout<<Dv[D]<<" ";}     ///Debug Degree Of Node Updates


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



//cout<<"S[i] ";
//for(x=0;x!=12;x++)
//{cout<<S[x]<<" ";}






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
	/**cout<<"xo"<<x<<"xo";**/}
	
	}


//cout<<"NodeClass ";
//for(x=0;x!=12;x++)
//{cout<<NodeClass[x]<<" ";}



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

//cout<<endl;
//cout<<" I is ";
RemainingNodeNo=0;
for(a=0;a!=12;a++)
{ RemainingNodeNo = Gprime[a] +  RemainingNodeNo;
//if(Gprime[a]==1)
//{//cout<<a<<":"<<Dv[a]<<" ";
//cout<<I[a]<<" ";
}
   }

int o=0;
for(a=0;a!=12;a++)
{o=o+I[a];}
//cout<<"Maximum Independent Set Size found using Original Luby is "<<o;
//cout<<endl;
output[1]=o+output[1];

}


void UpdatingLuby()
{   
//cout<<"Debug Check Point";

int I[12];     ///According to MIS.pdf :: Luby Paper  ::  Final Independent Set Result
int Dv[12];     ///According to MIS.pdf :: Luby Paper :: Node Degree , Initialized at first
int S[12];     ///According to MIS.pdf :: Luby Paper :: will be U with final result
int Gprime[12];      ///According to MIS.pdf :: Luby Paper  :: Initialized By full Graph, decremented by chosen node and its neighbours
int NodeClass[12]; //my own aux parameter

int ChosenNodeDegree,ChosenNodeNo, RemainingNodeNo=12; ////Parameters to set Node No. and Degree No. of Max degree Node, and Check Luby Condition 

int i,k,a,n,x;

int AdjMat2[12][12];


for(i=0;i!=12;i++)
{for(k=0;k!=12;k++)
{AdjMat2[i][k]=AdjMat[i][k];}
}
for(i=0;i!=12;i++)
{
	I[i]=0;
	Gprime[i]=1;
}


//cout<<"                              ";

while( RemainingNodeNo !=0 ) ////Sharte Luby
//for(int X=0;X!=400;X++)   ////Sharte Luby for Debug
{




for(i=0;i!=12;i++)
{Dv[i]=0;}

for(i=0;i!=12;i++)
{
	for(k=0;k!=12;k++)
	{
	Dv[i] = (AdjMat2[i][k])+Dv[i];
	}
}





//cout<<"Dv is ";          ///Debug Degree Of Node Updates
//for(int D=0;D!=12;D++)  ///Debug Degree Of Node Updates
//{cout<<Dv[D]<<" ";}     ///Debug Degree Of Node Updates







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



//cout<<"S[i] ";
//for(x=0;x!=12;x++)
//{cout<<S[x]<<" ";}






for(x=0;x!=12;x++)
	{
	for(n=x+1;n!=12;n++)
	{
	if(S[x]==1 && S[n]==1)
	{
		if((AdjMat2[x][n])==1)
		{if(NodeClass[x]==-1)
			{NodeClass[x]=x;}	
		NodeClass[n]=NodeClass[x];
		}		
	}}
	if(S[x]==1 &&  NodeClass[x]==-1)
	{NodeClass[x]=x;
	/**cout<<"xo"<<x<<"xo";**/}
	
	}


//cout<<"NodeClass ";
//for(x=0;x!=12;x++)
//{cout<<NodeClass[x]<<" ";}



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
{if(AdjMat2[ChosenNodeNo][a]==1)  ////Remove Neighbours
{Gprime[a]=0;
AdjMat2[ChosenNodeNo][a]=0;
AdjMat2[a][ChosenNodeNo]=0;
}}}
}
///&&&&/// Up to This Point 

//cout<<endl;
//cout<<" I is ";
RemainingNodeNo=0;
for(a=0;a!=12;a++)
{ RemainingNodeNo = Gprime[a] +  RemainingNodeNo;
//if(Gprime[a]==1)
//{//cout<<a<<":"<<Dv[a]<<" ";
//cout<<I[a]<<" ";
}
   }


int o=0;
for(a=0;a!=12;a++)
{o=o+I[a];}
//cout<<"Maximum Independent Set Size found using Updating Luby is "<<o;
//cout<<endl;

output[2]=o+output[2];

}



int main()
{
			clock_t t;

FillGraph();

			cout<<endl;

PrintGraph();

//			cout<<endl;
			output[0]=0;
			t = clock();
BruteForce();
						
			t = clock() - t;
			printf ("Runnig Brute Force took %f seconds.\n",((float)t)/CLOCKS_PER_SEC);
			cout<<endl;
			output[1]=0;
			t = clock();
			for(int i=0;i!=999;i++)
{Luby();
}
			t = clock() - t;
cout<<"Average Maximum Independent Set Size found using Original Luby is "<<float(output[1])/ float(1000);
			cout<<endl;
			printf ("Runnig Original Luby took averagely %f seconds.\n",((float)t)/((CLOCKS_PER_SEC)*1000));
cout<<"Sub-Optimality of Original Luby is "<<float(output[1])/ float(1000*output[0]);
cout<<endl;
			cout<<endl;
			output[2]=0;
			t = clock();
			for(int i=0;i!=999;i++)
{UpdatingLuby();
}
			t = clock() - t;
cout<<"Average Maximum Independent Set Size found using Updating Luby is "<<float(output[2])/ float(1000);
			cout<<endl;
			printf ("Runnig Updating Luby took averagely %f seconds.\n",((float)t)/((CLOCKS_PER_SEC)*1000));
cout<<"Sub-Optimality of Updating Luby is "<<float(output[2])/ float(1000*output[0]);
cout<<endl;

			cout<<endl;



}
