#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
/**
 * Created by hzg on 2016/11/19.
 * 合法的括号序列，序列x是由（、）、{、}这四种序号组成：
 * 1、若x是空号，则x是合法的序列。
 * 2、若x是合法的括号序列，则（X）、{X}都是合法的括号序列
 * 3、若x、y是合法的括号序列，则xy是合法的括号序列。
 *
 * 输入括号序列，如（）{，输出最少添加的括号数和添加的位置，输出结果是：最少添加 1 个 } 括号，添加位置是 3
 */
using namespace std;
using std::vector;
#define N 102
#define INF 1e9
//保存从i到j所需要的最少括号数:result[i][j]代表的是要让字符串索引从i到j的子字符串中括号匹配所要添加的最少括号数                          
int result[N][N];
char s[N];
vector<int> index;
vector<int>::iterator it;
vector<string> bracket;
vector<string>::iterator bit=bracket.begin();

int min(int m,int n){	
	return m <= n ? m : n;
}
//Min（1,n）从1到n需要添加的最少括号数，也可以说是最少括号数的result[i][j]策略，因为返回值是result[][]
int Min(int i,int j){
	int type;
	bool flag=true;
	//string[] type;//下标跟括号类型
	if (result[i][j]!=INF)
	{
		return result[i][j];
	}else{
		for (int t=i;t<j;t++)
		{
			//拆分两部分，分别求最小
			int tempa=Min(i,t);
			int tempb=Min(t+1,j);
			//如果第i和第j匹配的话，比较result[i][j]和result[i+1][j-1]，减一 的原因是i是从1开始，而装着括号的数组是从0开始
			if (s[i-1]=='('&&s[j-1]==')')
			{
				//比较匹配后添加的括号数和不匹配添加的括号数，取最小(两种方案取最小)
				if (result[i][j]<=result[i+1][j-1])
				{
					for (it=index.begin();it!=index.end();++it)
					{
						cout<<*it<<" ";
						//if (*it==i)
						//{
						//	it=index.erase(it);
						//	--it;
						//	//bracket.erase(bit+i);
						//	//--bit;
						//}
						//if (*it==j)
						//{
						//	it=index.erase(it);
						//	--it;
						//	//bracket.erase(bit+j);
						//	//--bit;
						//}
					}
					cout<<"aaaaaaaaaaaaaaa"<<endl;
				}				
				result[i][j]=min(result[i][j],result[i+1][j-1]);
			}else if(s[i-1]=='{'&&s[j-1]=='}'){
				/*if (result[i][j]<=result[i+1][j-1])
				{
				for (it=index.begin();it!=index.end();++it)
				{
				if (*it==i)
				{
				index.erase(it);
				--it;
				bracket.erase(bit+i);
				--bit;
				}
				if (*it==j)
				{
				index.erase(it);
				--it;
				bracket.erase(bit+j);
				--bit;
				}
				}
				}*/
				result[i][j]=min(result[i][j],result[i+1][j-1]);
			}else{
 				if (s[i-1]=='('){
					for (int k=0;k<index.size();k++)
					{
						if ((i-1)==index[k])
						{
							flag=false;
						}
					}
					if(flag){
						index.push_back(i-1);
						bracket.push_back(")");
					}
					flag=true;
 				}else if (s[i-1]==')'){
					for (int k=0;k<index.size();k++)
					{
						if ((i-1)==index[k])
						{
							flag=false;
						}
					}
					if(flag){
						index.push_back(i-1);
						bracket.push_back("(");
					}
					flag=true;
 				}
 				if (s[j-1]=='('){
					for (int k=0;k<index.size();k++)
					{
						if ((j-1)==index[k])
						{
							flag=false;
						}
					}
					if(flag){
						index.push_back(j-1);
						bracket.push_back(")");
					}
					flag=true;
 				}else if (s[j-1]==')'){
					for (int k=0;k<index.size();k++)
					{
						if ((j-1)==index[k])
						{
							flag=false;
						}
					}
					if(flag){
						index.push_back(j-1);
						bracket.push_back("(");
					}
					flag=true;
 				}
			}
		    //比较分开两部分添加的括号少还是不分开的括号少，取最小
			result[i][j]=min(result[i][j],tempa+tempb);
		}
		return result[i][j];
	}
}

int main(){
	 int n,T,i,j;
	 bool flag=false;
	 cin>>T;
	 while (T--){
		 scanf("%s",s);
		 n=strlen(s);//计数     
		 for (int k=0;k<n;k++)
		 {
			 //cout<<s[k]<<endl;
			 if (s[k]=='('||s[k]==')'||s[k]=='{'||s[k]=='}')
			 {
				 flag=true;
			 }else{
				 cout<<"输入的括号序列不合法，请重新输入！"<<endl;
				 flag=false;
				 break;
			 }
		 }
		 //如果flag=true就是说输入的括号序列合法
		 if (flag)
		 {
			 for (i=1;i<=n;i++){
				 for (j=i+1;j<=n;j++)
				 {
					 result[i][j]=INF;
				 }
			 }
			 result[n][n]=1;
			 for (i=1;i<n;i++)
			 {
				 result[i][i]=1;//一个括号添加一个括号就可以匹配
				 result[i+1][i]=0;//i+1>i，非法
			 }
			 cout<<"最少添加括号数:";
			 cout<<Min(1,n)<<endl;

			 cout<<"************************"<<endl; 
			 for(i=1;i<=n;i++) 
			 { 
				 for(j=1;j<=n;j++) 
				 { 
					 cout<<result[i][j]<<" "; 
				 } 
				 cout<<endl; 
			 }
			 cout<<"************************"<<endl; 
			 cout<<"插入位置分别是：";
			 for (int k=0;k<index.size();k++)
			 {
				 cout<<index[k];
			 }
			 index.clear();
			 cout<<endl;
			 cout<<"插入的括号类型分别是：";
			 for (int k=0;k<bracket.size();k++)
			 {
				 cout<<bracket[k];
			 }
			 cout<<endl;
			 bracket.clear();
			 cout<<"------------------------"<<endl;
		 }
	}
	 return 0; 
 }

