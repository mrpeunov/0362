#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Node
{
public:
    int a;
    char c;
    Node* left, * right;

    Node() {}
    Node(Node* L, Node* R)
    {
        left = L;
        right = R;
        a = L->a + R->a;
    }
};

struct compare
{
    bool operator()(Node* l, Node* r) const
    {
        return l->a < r->a;
    }

};

vector<bool> code;
map<char, vector<bool> >table;

void shannon(Node* root)
{
    if (root->left != NULL)
    {
        code.push_back(0);
        shannon(root->left);
    }

    if (root->right != NULL)
    {
        code.push_back(1);
        shannon(root->right);
    }

    if (root->c) table[root->c] = code;
    code.pop_back();

}

void work(string str)
{
    map<char, int> m;

    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];
        m[c]++;
    }

    list<Node*> t;

    map<char, int>::iterator zxc;
    for (zxc = m.begin(); zxc != m.end(); ++zxc)
    {
        Node* p = new Node;
        p->c = zxc->first;
        p->a = zxc->second;
        t.push_back(p);
    }

    while (t.size() != 1)
    {
        t.sort(compare());
        Node *L = t.front();
        t.pop_front();
        Node *R = t.front();
        t.pop_front();
        Node* Root = new Node(L, R);
        t.push_back(Root);
    }

    Node* root = t.front();
    shannon(root);
}

int main()
{
    string str ;
    cout<<"Enter rhe string to be encoded!"<<endl;
    getline(cin,str);
    work(str);

    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        vector<bool> x = table[c];

        for (int n = 0; n < x.size(); n++)
        {
            cout << x[n];
        }
        cout<<" ";
    }

    return 0;
}