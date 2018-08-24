#include<bits/stdc++.h>
using namespace std;

//tree Npode
class Node{
public:
    int nodeNumber;
    int data;
    string nodeId;
    Node* refNodeId;
    vector<Node*> childRef;
    Node* genNodeId;
    Node(int nnum,int d,Node* ref,Node* gen){
        nodeNumber = nnum;
        data = d;
        nodeId = to_string(nodeNumber);
        refNodeId = ref;
        genNodeId = gen;
    }
    int getSumChild(){
        int val = 0;
        for(auto i = childRef.begin();i!=childRef.end();i++){
            val += (*i)->data;
        }
        return val;
    }
};
//Insert Node
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

int main(){
    int nodeNum = 0;
    int data;
    cin>>data;
    Node genesisNode(++nodeNum,data,NULL,NULL);
    while(true){
        cin>>data;
        addNode(data,&genesisNode,++nodeNum,&genesisNode);
    }
    return 0;
}