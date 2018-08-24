#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int nodeNumber;        //Node Number
    int data;            //Data
    string nodeId;        //Node Id equals Node Number but stored in string form
    Node* refNodeId;        //parent Node Id address
    vector<Node*> childRef;        //Child Node Ids address
    Node* genNodeId;        //Genesis Node Id address

    Node(int nnum,int d,Node* ref,Node* gen){
        nodeNumber = nnum;
        data = d;
        nodeId = to_string(nodeNumber);
        refNodeId = ref;
        genNodeId = gen;
    }
   
    //Function to return Sum of data of all child
    int getSumChild(){
        int val = 0;
        for(auto i = childRef.begin();i!=childRef.end();i++){
            val += (*i)->data;
        }
        return val;
    }
};

// Provide value of longest chain possible
int longestChain(Node* p){
    if(p == NULL){
        return 0;
    }
    if(p->childRef.size() == 0){
        return 1;
    }
    int longest= INT_MIN;
    for(auto i = p->childRef.begin();i!=p->childRef.end();i++){
        longest = max(longest,longestChain(*i));
    }
    return longest + 1;
}

// Adds Node to given Parent Node
bool addNode(int data,Node* p,int nnum,Node* gen){
    Node* r;
    if(data + p->getSumChild() < p->data){
        r = new Node(nnum,data,p,gen);
        p->childRef.push_back(r);
        return true;
    }
    for(auto i = p->childRef.begin();i!=p->childRef.end();i++){
        bool flag = addNode(data,*i,nnum,gen);
        if(flag){
            return true;
        }
    }
    return false;
}

// Adds Node to certain Node and return false if not possible
bool insertToANode(int data,Node* p,int nnum,Node* gen){
    Node* r;
    if(data + p->getSumChild() < p->data){
        r = new Node(nnum,data,p,gen);
        p->childRef.push_back(r);
        return true;
    }
    return false;
}

// Merge Node
void mergeNode(Node* n1,Node* n2){
    if(longestChain(n1) > longestChain(n2)){
        n1->data += n2->data;
        delete n2;
        return ;
    }
    n1->data += n2->data;
    delete n2;
}

int main(){
    int nodeNum = 0;
    int data;
    cout<<"Enter Data for genesis node : ";
    cin>>data;
    Node gen(++nodeNum,data,NULL,NULL);
    int values;
    do{
        cout<<"Select Option :"<<endl;
        cout<<"1 : Add Node to genesis Node"<<endl;
        cout<<"2 : Merge Two Nodes"<<endl;
        cout<<"3 : Add Node to certain Node by providing address of it."<<endl;
        cout<<"4 : Find longest chain of genesis node."<<endl;
        cout<<"5 : Find longest chain of Node by providing address of it."<<endl;
        cout<<"6 : Exit"<<endl;
        cout<<"Enter value : ";
        cin>>values;
        switch(values){
            case 1:
                cout<<"Enter data : ";
                cin>>data;
                bool add = addNode(data,&gen,++nodeNum,&gen);
                add ? cout<<"Added"<<endl : cout<<"Can't Add"<<endl;
                break;
           
        }
    }
    while(values != 6);
    return 0;
}