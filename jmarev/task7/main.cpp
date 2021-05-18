#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


struct node
{
    char symbol;
    int frequency;
    node* left;
    node* right;
};

/*struct cipher
{
    char symbol;
    int frequency;
    string code;
};*/

bool comp(node a, node b) //comparator
{
    return a.frequency < b.frequency;
}

void PrintInInfixOrder(node* current_node)
{
    if(current_node!=nullptr)
    {
        PrintInInfixOrder(current_node->left);
        printf("%c    %d\n",current_node->symbol,current_node->frequency);
        PrintInInfixOrder(current_node->right);
    };
}

int main()
{
    node current_node;
    node* leaf_one,* leaf_two;
    //cipher* result;
    string message,encoded_message;
    vector<node> alphabet;
    char current_symbol;
    int i=0,current_frequency;
    //int t;
    do {
        cin>>current_symbol;
        if(current_symbol=='0')
        {
            break;
        }
        cin>>current_frequency;
        alphabet.push_back(current_node);
        alphabet[i].symbol=current_symbol;
        alphabet[i].frequency=current_frequency;
        alphabet[i].left=alphabet[i].right=nullptr;
        i++;
    }while(current_symbol!='0');
    /*result=new cipher[alphabet.size()];
    sort(alphabet.begin(),alphabet.end(),comp);
    for(i=0;i<alphabet.size();i++)
    {
        result[i].symbol=alphabet[i].symbol;
        result[i].frequency=alphabet[i].frequency;
    }*/

    while(alphabet.size()>1)
    {
        sort(alphabet.begin(),alphabet.end(),comp);
        printf("Next iteration:\n");
        for(i=0;i < alphabet.size();i++)
        {
            printf("%c    %d\n",alphabet[i].symbol,alphabet[i].frequency);
        }
        /*for (i=0;i<sizeof(result);i++)
        {
            cout<<result[i].code<<"\n";
        }*/

        printf("\n");

        leaf_one=new node;
        leaf_two=new node;

        (*leaf_one)=alphabet[0];
        /*i=0;
        while(result[i].symbol!=alphabet[0].symbol)
        {
        i++;
        }
        result[i].code="1"+result[i].code;*/
        (*leaf_two)=alphabet[1];
        /*i=0;
        while(result[i].symbol!=alphabet[1].symbol)
        {
            i++;
        }
        result[i].code="0"+result[i].code;*/
        alphabet.erase(alphabet.begin()); //erase one of the leafs from vector

        alphabet[0].frequency=leaf_one->frequency+leaf_two->frequency; // fill the fields of other leaf with parent' values
        alphabet[0].left=leaf_one;
        alphabet[0].right=leaf_two;
        alphabet[0].symbol='$';       //random technical value, doesnt matter at all
    }
    printf("Next iteration:\n");
    printf("%c    %d\n",alphabet[0].symbol,alphabet[0].frequency);
    printf("\n");
    printf("Infix tree print:\n");
    PrintInInfixOrder(&alphabet[0]);     //infix printf of the tree with algorithm iterations

    /*for (i=0;i<sizeof(result);i++)
    {
        printf("%c   %d   ",result[i].symbol,result[i].frequency);
        cout<<result[i].code<<"\n";
    }
    cin>>message;         //scan message without spaces
    for(i=0;i<message.size();i++)
    {
        t=0;
        while(message[i]!=result[t].symbol)
        {
            t++;
        }
        encoded_message=encoded_message+result[t].code;
    }
    cout<<encoded_message;*/            //print encoded message
    return 0;
}
