#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

vector < vector <int> > AllSubsets;
vector <int> IndependentSets;


int AdjMat[12][12];


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

cout<<"Number of Maximal Independet sets are "<< IndependentSets.size();
cout<<endl;
cout<<"All Maximal Independent Sets are as Followed:";
cout<<endl<<"{"<<endl;
for(int a=0;a!=IndependentSets.size();a++)
{
cout<<IndependentSets[a]<<" ";	
}
cout<<endl<<"}"<<endl;

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
cout<<"Max Independent Set Size is "<<result[0] <<" Nodes , which is(are) Subset(s) No. [";	
for(int x=0;x!=k;x++)
{cout<<result[x+1]<<" ";}
cout <<"]";


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



int main()
{

FillGraph();

			cout<<endl;

PrintGraph();

//			cout<<endl;

BruteForce();
			cout<<endl;
}
