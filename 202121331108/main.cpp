#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <cctype>
 
using namespace std;
 
typedef struct Statement{
    string statement;	
    int nums;		
}Statement;     
 
typedef struct similarStatement{
    string org;     
	string text;   
    int tnums;	
	int snums;	   
}similarStatement;
 
similarStatement allstorage[1000];   
 
Statement orgStatement[1000];  
int words[1000][1000];  
float grade[1000][1000];      
string str1[1000],str2[1000];  
     
int orgnums = 0;     
int textnums = 0;    
 
void orgsStatement( string file);  
void textsStatement( string file );   
float max( float a, float b );
float maxs( float a, float b, float c );
int main()
{
	int j;
	string orgfile = "D://org.txt";
	string textfile = "D://text.txt";
 
	orgsStatement( orgfile );
 
	textsStatement( textfile );
 
	for( j=0; j<textnums; j++ )
	{
		cout<<"第"<<j+1<<"句对比"<<endl;
		cout<<allstorage[j].text<<endl;
		cout<<allstorage[j].org<<endl;
		cout<<allstorage[j].snums<<"\t"<<allstorage[j].tnums<<endl;
		cout<<"\n"<<endl;
	}
 
	return 0;
}
float max( float a, float b )
{
	if( a > b )
		return a;
	else
		return b;
} 
 
 
float maxs( float a, float b, float c )
{
	float temp = a;
	
	if( temp < b )
		temp = b;
	if( temp < c )
		temp = c;
	
	return temp;
}
