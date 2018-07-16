#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <cassert>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <functional>
using namespace std;
typedef long long LL;
const int maxn = 111111;
const int INF = 0X7F7F7F7F;
struct AvlTree{
    struct node{
        int val,size,height,delta,cnt;
        node *ch[2];
        node(){
        }
        void pushup(){
            size=ch[0]->size+ch[1]->size+cnt;
            height=max(ch[0]->height,ch[1]->height)+1;
            delta=ch[0]->height-ch[1]->height;
        }
    }data[maxn];
    node *null,*root;
    int cnt;
    void init(){
        cnt=0;
        null=data;
        null->height=0;
        null->ch[0]=null->ch[1]=null;
        null->delta=0;
        null->size=0;
        null->val=INF;
        null->cnt=0;
        root=null;
        ++cnt;
    }
    void maintain(node* &x){  // AVL Rotation
        if(abs(x->delta)>1){
            bool c=x->delta<0;
            node* &t=x->ch[c];
            if(t->ch[c]->height > t->ch[c^1]->height){
                Rotate(x,c^1);
            }else{
                Rotate(t,c);
                Rotate(x,c^1);
            }
        }
    }
    node *NewNode(int val){
        node *p=&data[++cnt];
        p->val=val;
        p->ch[0]=p->ch[1]=null;
        p->size=1;
        p->delta=0;
        p->height=1;
        p->cnt=1;
        return p;
    }
    void Rotate(node* &x,bool c){
        node *t=x->ch[c^1];
        x->ch[c^1]=t->ch[c];
        t->ch[c]=x;
        x->pushup();
        t->pushup();
        x=t;
    }
    void insert(node* &x,int val){
        if(x==null){
            x=NewNode(val);
        }else{
            if(x->val==val){
                x->cnt++;
            }else{
                bool c=x->val<val;
                insert(x->ch[c],val);
            }
        }
        x->pushup();
        maintain(x);
    }
    void Delete(node* &x){
        if(x->ch[0]!=null&&x->ch[1]!=null){
            bool c=x->delta>0;
            Rotate(x,c);
            Delete(x->ch[c]);
        }else{
            bool c=(x->ch[0]==null);
            x=x->ch[c];
        }
        if(x!=null){
            x->pushup();
            maintain(x);
        }
    }
    void Delete(node* &x,int val){
        if(x->val==val){
            x->cnt--;
            if(!x->cnt){
                Delete(x);
            }
        }else{
            bool c=x->val<val;
            Delete(x->ch[c], val);
        }
        if(x!=null){
            x->pushup();
            maintain(x);
        }
        
    }
    int Rank(node *x,int val){
        if(x==null){
            return 0;
        }
        if(x->val<val){
            return x->ch[0]->size+x->cnt+Rank(x->ch[1],val);
        }else{
            return Rank(x->ch[0], val);
        }
        return -1;
    }
    int find_kth(node *x,int k){
        if(k<=x->ch[0]->size){
            return find_kth(x->ch[0],k);
        }
        k -= x->ch[0]->size + x->cnt;
        if(k<=0){
            return x->val;
        }
        return find_kth(x->ch[1], k);
    }
    void find_pre(node *x,int val,int &ans){
        if(x==null)
            return;
        if(x->val<val){
            ans=x->val;
            find_pre(x->ch[1],val,ans);
        }else{
            find_pre(x->ch[0],val,ans);
        }
    }
    void find_succ(node *x,int val,int &ans){
        if(x==null)
            return;
        if(x->val>val){
            ans=x->val;
            find_succ(x->ch[0], val, ans);
        }else{
            find_succ(x->ch[1], val, ans);
        }
    }
    void go(node *x){
        if(x==null){
            return;
        }
        go(x->ch[0]);
        printf("%d ",x->val);
        go(x->ch[1]);
    }
    void debug(){
        puts("beg");
        go(root);
        puts("\nend\n");
    }
    void insert(int x){
        insert(root,x);
    }
    void Delete(int x){
        Delete(root,x);
    }
    int Rank(int val){
        return Rank(root,val)+1;
    }
    int find_kth(int k){
        return find_kth(root,k);
    }
    int find_pre(int x){
        int ans=INF;
        find_pre(root,x,ans);
        return ans;
    }
    int find_succ(int x){
        int ans=INF;
        find_succ(root,x,ans);
        return ans;
    }
};
AvlTree AVL;
int main(){
    AVL.init();
    int n,op,x;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d%d",&op,&x);
        if(op==1){
            AVL.insert(x);
        }else if(op==2){
            AVL.Delete(x);
        }else if(op==3){
            printf("%d\n",AVL.Rank(x));
        }else if(op==4){
            printf("%d\n",AVL.find_kth(x));
        }else if(op==5){
            printf("%d\n",AVL.find_pre(x));
        }else{
            printf("%d\n",AVL.find_succ(x));
        }
    }
    return 0;
}
