#include<bits/stdc++.h>
using namespace std;
namespace listns{
	struct STRUCT{
		vector<int> type;
		string name;
		struct{
	        vector<int> Int;
	        vector<double> Double;
	        vector<long long> Longlong;
	        vector<long> Long;
			vector<short> Short;
			vector<float> Float;
			vector<string> String;
			vector<char> Char;
			vector<bool> Bool;
			vector<STRUCT> Struct;
	    }data;
	};
	struct Value{
		int type;
		struct{
	        int Int;
	        double Double;
	        long long Longlong;
	        long Long;
			short Short;
			float Float;
			string String;
			char Char;
			bool Bool;
			STRUCT Struct;
	    }data;
	};
	struct LIST{
		int l,r;
		Value value;
	};
	struct List{
		private:
			priority_queue<int,vector<int>,greater<int> >q;
			int list_cnt,list_sum;
			int list_st,list_ed;
			int N_ls;
			vector<LIST> ls;
		public:
			void list_init(){
				list_st=list_ed=-1;
				while(!q.empty())q.pop();
				list_cnt=list_sum=0;
				N_ls=20000000;
				LIST t=(LIST){-1,-1,(Value){0}};
				ls.push_back(t);
			}
			bool push_middle(int lid,int rid,Value value){
				if(list_sum==N_ls||lid>list_cnt||rid>list_cnt||ls[lid].l==-1||ls[rid].l==-1)return false;
				int tid;
				if(q.empty()){
					tid=++list_cnt;
					LIST t=(LIST){-1,-1,(Value){0}};
					ls.push_back(t);
				}
				else{
					tid=q.top();
					q.pop();
				}
				list_sum++;
				ls[lid].r=tid;
				ls[rid].l=tid;
				ls[tid].l=lid;
				ls[tid].r=rid;
				ls[tid].value=value;
				return true;
			}
			bool push_start(Value value){
				if(list_sum==N_ls)return false;
				int tid;
				if(q.empty()){
					tid=++list_cnt;
					LIST t=(LIST){-1,-1,(Value){0}};
					ls.push_back(t);
				}
				else{
					tid=q.top();
					q.pop();
				}
				list_sum++;
				if(list_ed==-1)list_ed=tid;
				if(list_st==-1)list_st=tid;
				ls[list_ed].r=tid;
				ls[list_st].l=tid;
				ls[tid].l=list_ed;
				ls[tid].r=list_st;
				ls[tid].value=value;
				list_st=tid;
				return true;
			}
			bool push_end(Value value){
				if(list_sum==N_ls)return false;
				int tid;
				if(q.empty()){
					tid=++list_cnt;
					LIST t=(LIST){-1,-1,(Value){0}};
					ls.push_back(t);
				}
				else{
					tid=q.top();
					q.pop();
				}
				list_sum++;
				if(list_st==-1)list_st=tid;
				if(list_ed==-1)list_ed=tid;
				ls[list_ed].r=tid;
				ls[list_st].l=tid;
				ls[tid].l=list_ed;
				ls[tid].r=list_st;
				ls[tid].value=value;
				list_ed=tid;
				return true;
			}
			bool pop(int tid){
				if(list_sum==0||tid>list_cnt||ls[tid].l==-1)return false;
				ls[ls[tid].l].r=ls[tid].r;
				ls[ls[tid].r].l=ls[tid].l;
				q.push(tid);
				list_sum--;
				if(list_st==tid)list_st=ls[tid].r;
				if(list_ed==tid)list_ed=ls[tid].l;
				if(list_st==tid)list_st=-1,list_ed=-1;
				ls[tid].l=-1,ls[tid].r=-1;
				ls[tid].value=(Value){0};
				return true;
			}
			bool revise(int tid,Value value){
				if(tid>list_cnt||ls[tid].l==-1)return false;
				ls[tid].value=value;
			}
			int size(){
				return list_sum;
			}
			int length(){
				return list_cnt;
			}
			bool empty(){
				if(list_sum>0)return false;
				return true;
			}
			void anew(){
				int tid=list_st;
				while(!empty()){
					int tmp=tid;
					tid=ls[tid].r;
					pop(tmp);
				}
			}
			bool swap(int tid1,int tid2){
				if(tid1>list_cnt||tid2>list_cnt||ls[tid1].l==-1||ls[tid2].l==-1)return false;
				Value x=ls[tid1].value;
				ls[tid1].value=ls[tid2].value;
				ls[tid2].value=x;
			}
			int headid(){
				return list_st;
			}
			int tailid(){
				return list_ed;
			}
			int leftid(int tid){
				return ls[tid].l;
			}
			int rightid(int tid){
				return ls[tid].r;
			}
		private:
			bool print_struct(STRUCT Struct,string wheel=""){
				cout<<wheel<<Struct.name;
				STRUCT x=Struct;
				string tmp="";
				for(int i=1;i<=100;i++){
					tmp+=" ";
				}
				string t=wheel+Struct.name;
				int len=t.size();
				string y=tmp.substr(0,len);
				for(int i=0;i<x.type.size();i++){
					if(x.type[i]==1){
						cout<<"-"<<x.data.Int[0]<<endl;
						for(int i=1;i<x.data.Int.size();i++){
							cout<<y<<"-"<<x.data.Int[i]<<endl;
						}
					}
					else if(x.type[i]==2){
						cout<<"-"<<x.data.Double[0]<<endl;
						for(int i=1;i<x.data.Double.size();i++){
							cout<<y<<"-"<<x.data.Double[i]<<endl;
						}
					}
					else if(x.type[i]==3){
						cout<<"-"<<x.data.Longlong[0]<<endl;
						for(int i=1;i<x.data.Longlong.size();i++){
							cout<<y<<"-"<<x.data.Longlong[i]<<endl;
						}
					}
					else if(x.type[i]==4){
						cout<<"-"<<x.data.Long[0]<<endl;
						for(int i=1;i<x.data.Long.size();i++){
							cout<<y<<"-"<<x.data.Long[i]<<endl;
						}
					}
					else if(x.type[i]==5){
						cout<<"-"<<x.data.Short[0]<<endl;
						for(int i=1;i<x.data.Short.size();i++){
							cout<<y<<"-"<<x.data.Short[i]<<endl;
						}
					}
					else if(x.type[i]==6){
						cout<<"-"<<x.data.Float[0]<<endl;
						for(int i=1;i<x.data.Float.size();i++){
							cout<<y<<"-"<<x.data.Float[i]<<endl;
						}
					}
					else if(x.type[i]==7){
						cout<<"-"<<x.data.String[0]<<endl;
						for(int i=1;i<x.data.String.size();i++){
							cout<<y<<"-"<<x.data.String[i]<<endl;
						}
					}
					else if(x.type[i]==8){
						cout<<"-"<<x.data.Char[0]<<endl;
						for(int i=1;i<x.data.Char.size();i++){
							cout<<y<<"-"<<x.data.Char[i]<<endl;
						}
					}
					else if(x.type[i]==9){
						cout<<"-"<<x.data.Bool[0]<<endl;
						for(int i=1;i<x.data.Bool.size();i++){
							cout<<y<<"-"<<x.data.Bool[i]<<endl;
						}
					}
					else if(x.type[i]==10){
						print_struct(x.data.Struct[0],"-");
						for(int i=1;i<x.data.Struct.size();i++){
							print_struct(x.data.Struct[i],y+"-");
						}
					}
					else{
						return false;
					}
				}
				return true;
			}
		public:
			bool print(int tid){
				if(tid>list_cnt||ls[tid].l==-1)return false;
				Value x=ls[tid].value;
				if(x.type==1){
					cout<<x.data.Int<<endl;
					return true;
				}
				else if(x.type==2){
					cout<<x.data.Double<<endl;
					return true;
				}
				else if(x.type==3){
					cout<<x.data.Longlong<<endl;
					return true;
				}
				else if(x.type==4){
					cout<<x.data.Long<<endl;
					return true;
				}
				else if(x.type==5){
					cout<<x.data.Short<<endl;
					return true;
				}
				else if(x.type==6){
					cout<<x.data.Float<<endl;
					return true;
				}
				else if(x.type==7){
					cout<<x.data.String<<endl;
					return true;
				}
				else if(x.type==8){
					cout<<x.data.Char<<endl;
					return true;
				}
				else if(x.type==9){
					cout<<x.data.Bool<<endl;
					return true;
				}
				else if(x.type==10){
					bool t=print_struct(x.data.Struct);
					if(!t)return false;
					return true;
				}
				else{
					return false;
				}
			}
	};
}
using namespace listns;
/*
相关说明:

1. List 链表需要using namespace listen
2. List相关函数列表:[List类型变量用~代替]
   --1: void ~.list_init()                                   给List链表初始化(必要)
   --2: bool ~.push_middle(int lid,int rid,Value value)      在List链表中间插入一个结点,[注意:不要用这个函数在List链表的前端或末端插入结点],lid为插入的那个变量结点的左节点编号,rid为插入的那个变量结点的右节点编号,value为要插入结点的变量(值),如果成功返回true,如果失败返回false
   --3: bool ~.push_start(Value value)                       在List链表的前端插入一个结点,value为该结点的变量(值),如果成功返回true,如果失败返回false
   --4: bool ~.push_end(Value value)                         在List链表的末端插入一个结点,value为该结点的变量(值),如果成功返回true,如果失败返回false
   --5: bool ~.pop(int tid)                                  删除List链表tid编号的结点,如果成功返回true,如果失败返回false
   --6: bool ~.revise(int tid,Value value)                   给List链表tid编号的结点的变量(值)重新赋value,如果成功返回true,如果失败返回false
   --7: int ~.size()                                         返回List链表的结点个数
   --8: int ~.length()                                       返回List链表目前所使用过的最大空间大小(不得超过2*10^7)
   --9: bool ~.empty()                                       返回List链表是否为空,为空返回true,否则返回false
   -10: void ~.anew()                                        将List链表清空
   -11: bool ~.swap(int tid1,int tid2)                       将List链表编号为tid1的结点和编号为tid2的结点的变量(值)互换
   -12: int ~.headid()                                       返回List链表前端结点的编号
   -13: int ~.tailid()                                       返回List链表末端结点的编号
   -14: int ~.leftid(int tid)                                将List链表编号为tid的结点的左节点的编号(由于是双向循环链表,所以如果为前端结点,左节点就为末端节点)
   -14: int ~.rightid(int tid)                               将List链表编号为tid的结点的右节点的编号(由于是双向循环链表,所以如果为末端结点,右节点就为前端节点)
   -15: bool ~.print(int tid)                                输出List链表编号为tid的结点的变量(值)
3. 编译器为DEV_C++ 6.7.5，MinGW GCC10.2.0 64-bit Release
4. 主函数为示例
5. 用法见介绍帖子
*/
List L;
int main(){
	L.list_init();
	Value x;
	x.type=1;
	x.data.Int=123;
	L.push_start(x);
	x.type=2;
	x.data.Double=3.14;
	L.push_end(x);
	x.type=10;
	STRUCT y;
	y.name="abc";
	y.type.push_back(1);
	y.data.Int.push_back(10);
	y.data.Int.push_back(10);
	y.data.Int.push_back(10);
	x.data.Struct=y;
	L.push_middle(L.headid(),L.tailid(),x);
	int hi=L.headid();
	int ti=L.tailid();
	for(int i=hi;i!=ti;i=L.rightid(i)){
		L.print(i);
	}
	L.print(ti);
	return 0;
}
