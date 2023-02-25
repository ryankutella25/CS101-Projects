#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

class Node{
    public:
        string value = "";
        Node *left = nullptr;
        Node *right = nullptr;

};

Node* makeTree(string inO, string levelO){
    Node *temp = new Node();
    if(inO.size() == 0){
        return nullptr;
    }
    //check each value in levelorder to see if its in inorder
    string value = levelO.substr(0,levelO.find(" "));
    int val = levelO.find(" ");
    levelO = levelO.substr(val+1, levelO.size()-val-1);
    //cout << levelO << endl;
    cout << "remaining inO: " << inO << "end" << endl;
    cout << "remaining levelO: " << levelO << endl;
    while(inO.find(value) == string::npos){
        //cout << "not found: " << value << "t"<< endl;
        //cout << "remaining: " << levelO << "t"<< endl;
        cout << "remaining levelO: " << levelO << endl;
        value = levelO.substr(0,levelO.find(" "));
        int val = levelO.find(" ");
        levelO = levelO.substr(val+1, levelO.size()-val-1);
    }
    if(value==""){
        return nullptr;
    }
    cout << "value " << value << "end" << endl;
    int position = inO.find(value);
    temp->value = value;
    //cout << "Value: " << value << endl;

    if(position>1){
        string leftSide = inO.substr(0,position);
        //cout << "going left" <<endl;
        temp->left = makeTree(leftSide,levelO);
    }else {
        //cout << "got to end of left" << endl;
        temp->left = nullptr;
    }

    if(inO.size()-position-value.size()>1){
        //+1 below means it doesn't include space before
        string rightSide = inO.substr(position+value.size()+1,inO.size()-position-value.size()-1);
        //cout << "going right" <<endl;
        temp->right = makeTree(rightSide,levelO);
    }else{
        //cout << "got to end of right" << endl;
        temp->right = nullptr;
    }
    
    return temp;
};

char asciiToString(string s){
    int i = stoi(s);
    char c = char(i);
    return c;
}

void printInOrder(Node* top){
    if(top->left != nullptr && top->left->value != ""){
        printInOrder(top->left);
    }
    cout << top->value << " ";
    if(top->right != nullptr && top->right->value != ""){
        printInOrder(top->right);
    }
}

int main(int argc, char *argv[])
{
    string inputs[3];
    inputs[0] = argv[1];
    inputs[1] = argv[2];
    inputs[2] = argv[3];
    string levelorder = "";
    string inorder = "";
    string decode = "";

    for (int i = 0; i < 3; i++)
    {
        ifstream inFS;
        inFS.open(inputs[i]);
        if (!inFS.is_open())
        {
            cout << "Could not open input file: " << inputs[i] << endl;
        }
        else
        {
            bool tf = true;
            while (tf)
            {
                string nextString = "";
                inFS >> nextString;
                if (nextString == "")
                {
                    tf = false;
                    break;
                }
                else
                {
                    if (i == 0)
                    {
                        inorder += nextString + " ";
                    }
                    else if (i == 1)
                    {
                        levelorder += nextString + " ";
                    }
                    else
                    {
                        decode += nextString + " ";
                    }
                }
            }
            inFS.close();
        }
        if (i == 0)
        {
            cout << inorder << endl;
        }
        else if (i == 1)
        {
            cout << levelorder << endl;
        }
        else
        {
            cout << decode << endl;
        }
    }

    Node* top = makeTree(inorder, levelorder);
    //cout << "HERE " << top->left->right->left->right << endl;

    //printInOrder(top);
    cout << endl;

    // string s = "34 100 390 134";
    // cout << s.find("134") << endl;

    Node* path = top;
    string totals = "";
    while (decode.size() != 0)
    {
        if(decode.substr(0,1)=="0"){
            if(path->left == nullptr || path->left->value == ""){
                totals += string(1,asciiToString(path->value));
                //cout<< asciiToString(path->value) << "RIP" << endl;
                path = top;
            }
            //cout << "left to: " << path->left->value << endl;
            path = path->left;
        }
        else if(decode.substr(0,1)=="1"){
            if(path->right == nullptr || path->right->value == ""){
                totals += string(1,asciiToString(path->value));
                //cout<< asciiToString(path->value) << "RIP" <<endl;
                path = top;
            }
            //cout << "right to: " << path->right->value << endl;
            path = path->right;
        }
        decode.erase(0,1);
    }
    totals += string(1,asciiToString(path->value));
    cout << totals << endl;

    string levelO = "ryan bob ";
    int val = levelO.find(" ");
    cout << levelO.substr(val+1, 2) << "pe" << endl;


}