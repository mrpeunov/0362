#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct st
    {
        int z;
        char c;
        string s;
        struct st  *left;// левый потомок в дереве
        struct st  *right;// правый потомок в дереве
    } ss1;

vector <st> sett;
vector <st*> setp;
st *p, *ss;

bool sf (st i,st j) { return (i.z<=j.z); }
bool sf1 (st *i,st *j) { return (i->z<=j->z); }

void create () // create the tree
{
    if (setp.size()!=2)
    {
       ss = new st;
       ss->z=setp[0]->z+setp[1]->z;
       ss->c=setp[0]->c+setp[1]->c;
       ss->s="";
       ss->left=setp[0];// левый потомок в дереве
       ss->right=setp[1];// правый потомок в дереве
       setp.erase(setp.begin());
       setp.erase(setp.begin());
       setp.push_back(ss);
       sort (setp.begin(), setp.end(), sf1);
       create();
    }

}
int collect (st *p, string sss)
{
    if (p->left == 0 && p->right == 0)

    {
        p->s=sss;
        cout<<"Code: "<<p->c<<" "<<sss<<endl;

        return 0;
    }
     if (p->right != 0)
    {

        collect (p->right, sss+'1');
    }
    if (p->left != 0)
    {

        collect (p->left, sss+'0');
    }

    return 0;
}

int main()
{

    vector<st>::iterator it;
    vector<st*>::iterator it1;
    int i,n;
    cout<<"enter the number of items"<<endl;
    cin>>n;
    for (i=0; i<n; i++)
    {
       cout<<"Enter a letter"<<endl;
       cin>>ss1.c;
       cout<<"Enter the frequency"<<endl;
       cin>>ss1.z;
       ss1.s="";
       ss1.left=NULL;// левый потомок в дереве
       ss1.right=NULL;// правый потомок в дереве
       sett.push_back(ss1);
    }
    if (n!=1)
    {
    sort (sett.begin(), sett.end(), sf);
    for (it=sett.begin();it!=sett.end(); it++)
    {
        setp.push_back(&*it);
    }
    sort (setp.begin(), setp.end(), sf1);

    create(); // создание "дерева"
    cout<<endl;
    collect(setp[0], "0"); //собиралка
    collect(setp[1], "1"); //собиралка

    cout<<endl<<"sett"<<endl;
    }
    else
    sett[0].s="0";
    string ssss;
    cout<<"enter the message (from the letters of your alphabet)"<<endl;
    cin.ignore();
    getline(cin,ssss);
    for (i=0; i<ssss.length(); i++)
    {
        it=sett.begin();
        while (ssss[i]!=it->c) it++;
        cout<<it->s;
    }

    return 0;
}
