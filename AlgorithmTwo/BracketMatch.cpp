#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
/**
 * Created by hzg on 2016/11/19.
 * �Ϸ����������У�����x���ɣ�������{��}�����������ɣ�
 * 1����x�ǿպţ���x�ǺϷ������С�
 * 2����x�ǺϷ����������У���X����{X}���ǺϷ�����������
 * 3����x��y�ǺϷ����������У���xy�ǺϷ����������С�
 *
 * �����������У��磨��{�����������ӵ�����������ӵ�λ�ã��������ǣ�������� 1 �� } ���ţ����λ���� 3
 */
using namespace std;
using std::vector;
#define N 102
#define INF 1e9
//�����i��j����Ҫ������������:result[i][j]�������Ҫ���ַ���������i��j�����ַ���������ƥ����Ҫ��ӵ�����������                          
int result[N][N];
char s[N];
vector<int> index;
vector<int>::iterator it;
vector<string> bracket;
vector<string>::iterator bit=bracket.begin();

int min(int m,int n){	
	return m <= n ? m : n;
}
//Min��1,n����1��n��Ҫ��ӵ�������������Ҳ����˵��������������result[i][j]���ԣ���Ϊ����ֵ��result[][]
int Min(int i,int j){
	int type;
	bool flag=true;
	//string[] type;//�±����������
	if (result[i][j]!=INF)
	{
		return result[i][j];
	}else{
		for (int t=i;t<j;t++)
		{
			//��������֣��ֱ�����С
			int tempa=Min(i,t);
			int tempb=Min(t+1,j);
			//�����i�͵�jƥ��Ļ����Ƚ�result[i][j]��result[i+1][j-1]����һ ��ԭ����i�Ǵ�1��ʼ����װ�����ŵ������Ǵ�0��ʼ
			if (s[i-1]=='('&&s[j-1]==')')
			{
				//�Ƚ�ƥ�����ӵ��������Ͳ�ƥ����ӵ���������ȡ��С(���ַ���ȡ��С)
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
		    //�ȽϷֿ���������ӵ������ٻ��ǲ��ֿ��������٣�ȡ��С
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
		 n=strlen(s);//����     
		 for (int k=0;k<n;k++)
		 {
			 //cout<<s[k]<<endl;
			 if (s[k]=='('||s[k]==')'||s[k]=='{'||s[k]=='}')
			 {
				 flag=true;
			 }else{
				 cout<<"������������в��Ϸ������������룡"<<endl;
				 flag=false;
				 break;
			 }
		 }
		 //���flag=true����˵������������кϷ�
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
				 result[i][i]=1;//һ���������һ�����žͿ���ƥ��
				 result[i+1][i]=0;//i+1>i���Ƿ�
			 }
			 cout<<"�������������:";
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
			 cout<<"����λ�÷ֱ��ǣ�";
			 for (int k=0;k<index.size();k++)
			 {
				 cout<<index[k];
			 }
			 index.clear();
			 cout<<endl;
			 cout<<"������������ͷֱ��ǣ�";
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

