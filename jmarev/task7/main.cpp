#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

struct node
{
    char symbol;
    int frequency;
    node* left;
    node* right;
    bool flag;
};

struct cipher
{
    char symbol;
    int frequency;
    string code;
};

bool NodeComp(node a, node b) //comparator for node structure
{
    return a.frequency < b.frequency;
}

bool CipherComp(cipher a, cipher b) //comparator for cipher structure
{
    return a.frequency > b.frequency;
}

void PostfixDelete(node* current_node,node* root)
{
    if(current_node!=nullptr)
    {
        PostfixDelete(current_node->left,root);
        PostfixDelete(current_node->right,root);
        if (current_node != root)
        {
            delete (current_node);
        }
    }
}

int main()
{
    node current_node{};
    node* leaf_one,* leaf_two,* current_node_pointer;
    cipher current_result;
    vector <cipher> result;
    string message,encoded_message;
    vector <node> alphabet;
    char current_symbol;
    int i=0,t,current_frequency,size_var;

    do {
        cin>>current_symbol;
        if(current_symbol == '0')
        {
            break;
        }

        cin>>current_frequency;

        alphabet.push_back(current_node);

        alphabet[i].symbol = current_symbol;
        alphabet[i].flag = 0;
        alphabet[i].frequency = current_frequency;
        alphabet[i].left = alphabet[i].right=nullptr;
        i++;

    }while(current_symbol!='0');

    sort(alphabet.begin(),alphabet.end(),NodeComp);
    size_var = alphabet.size();
    result.resize(alphabet.size());

    while(alphabet.size() > 1)
    {
        sort(alphabet.begin(),alphabet.end(),NodeComp);


        leaf_one=new node;
        leaf_two=new node;

        (*leaf_one) = alphabet[0];
        (*leaf_two) = alphabet[1];

        alphabet.erase(alphabet.begin()); //erase one of the leaves from vector

        alphabet[0].frequency = leaf_one->frequency+leaf_two->frequency; // fill the fields of other leaf with parent' values
        alphabet[0].left = leaf_one;
        alphabet[0].right = leaf_two;
        alphabet[0].symbol = '$';       //random technical value, doesnt matter at all
    }

    for(i=0;i<size_var;i++)
    {
        current_node_pointer=&alphabet[0];

        do
        {
            if(current_node_pointer->right->flag && current_node_pointer->left->flag)
            {
                result[i].code.clear();
                i --;
                break;
            }
            else if(!current_node_pointer->right->flag)
            {
                current_node_pointer = current_node_pointer->right;
                result[i].code.insert(result[i].code.end(),'0');
                continue;
            }
            else if(!current_node_pointer->left->flag)
            {
                current_node_pointer = current_node_pointer->left;
                result[i].code.insert(result[i].code.end(),'1');
                continue;
            }
        }while(current_node_pointer->left != nullptr);//if one of the links(i've chosen to check the lef one) is equal to NULL,
        current_node_pointer->flag = true;              //it means that both links are equal to NULL and it's leaf of the tree
        if(current_node_pointer->symbol != '$')
        {
            result[i].symbol = current_node_pointer->symbol;
            result[i].frequency = current_node_pointer->frequency;
        }
    }

    PostfixDelete(&alphabet[0],&alphabet[0]); //free the memory allocated for the tree
    alphabet.clear();         //free the memory allocated for the vector(there is just one element left by this moment)

    sort(result.begin(),result.end(),CipherComp);//sort the code table(cells of the most frequently used symbols go first)
    for(i = 0;i < size_var;i ++)                 //print the code table
    {
        cout << result[i].symbol << "   " << result[i].code << endl;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clean input stream buffer
    getline(cin,message);       //scan message

    for(i = 0;i < message.size();i ++)
    {
        t = 0;
        while(message[i] != result[t].symbol)
        {
            t ++;
        }
        encoded_message.insert(encoded_message.size(),result[t].code);
    }
    result.clear();         //free the memory allocated for the code table
    cout << encoded_message;//print encoded message
    return 0;
}
