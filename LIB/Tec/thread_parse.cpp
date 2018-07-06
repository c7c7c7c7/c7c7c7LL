#include <bits/stdc++.h>
using namespace std;
int idx;
string s;
string yaml[100009];
struct tree{
    map<string,tree*>child;
    int is;
    string name,val;
};
void make_tree(tree *root,int id,int &ln){
    while( ln < idx ){
        int cnt=0;
        string nm="";
        tree *next = new tree();
        string st =  yaml[ln];
        while(st[cnt]==' ')cnt++;
        if(cnt<=id)return;
        int cur=cnt;
        while(st[cur]!=':')nm+=st[cur++];
        cur++;ln++;
        next->name=nm;
        if(cur==st.size())make_tree(next,cnt,ln);
        else{
            next->is=1;
            next->val=st.substr(cur+1);
        }
        root->child[nm]=next;
    }
}
string sol(){
    tree *root=new tree();
    int ln=0,cur=0;
    make_tree(root,-1,ln);
    while( cur < s.size() ){
        string obj="";
        cur++;
        while(cur<s.size() && s[cur]!='.')obj+=s[cur++];
        if(root->child.count(obj)==0)return "no such property";
        root = root->child[obj];
    }
    if(root->is)return "string \""+root->val+"\"";
    return "object";
}
int main(){
    getline(cin,s);
    while(getline(cin,yaml[idx]))idx++;
    cout<<sol()<<endl;
}