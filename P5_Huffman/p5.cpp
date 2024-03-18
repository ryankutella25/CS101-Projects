#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <vector>
using namespace std;


class Node{
    public:
        string value = "";
        Node *left = nullptr;
        Node *right = nullptr;

};

class Point{
    public:
        string value = "";
        Point *next = nullptr;
};

class pointerRay{
    public:
        Point *head = nullptr;
        Point *tail = nullptr;
        
        void addItem(string s){
            if(head==nullptr){
                head = new Point;
                head->value = s;
                tail = head;
            }
            else{
                tail->next = new Point;
                tail = tail->next;
                tail->value = s;
            }
        }
        bool deleteFront(){
            if(head!=nullptr){
                head = head->next;
                if(head!=nullptr){
                    return true;
                }
            }
            return false;
        }
        void addFrom(Point *p){
            if(p != nullptr){
                p = p->next;
                while(p != nullptr){
                    addItem(p->value);
                    p = p->next;
                }
            }
        }
        void addUntil(Point *start, Point *p){
            if(p != nullptr){
                while (start !=nullptr && start->value!=p->value)
                {   
                    addItem(start->value);
                    start = start->next;
                }
            }
        }
        void print(ostream &os){
            Point *p = head;
            while (p!=nullptr)
            {
                os << p->value + " ";
                p = p->next;
            }
            os << endl;
        }
};

Node* makeTree(pointerRay inO, pointerRay levelO){
    Node *temp = new Node();

    //check each value in levelorder to see if its in inorder
    if(levelO.head==nullptr||inO.head==nullptr){
        return nullptr;
    }
    string value = levelO.head->value;
    Point *current = inO.head;
    bool found = false;
    while (levelO.head != nullptr && !found)
    {
        //cout << "went thru" << endl;
        while(current!=nullptr&&current->value!=value){
            //cout << current->value << " != " << value << endl;
            current = current->next;
        }
        if(current==nullptr){
            if(levelO.deleteFront()){
                value = levelO.head->value; 
                current = inO.head;
            }
            else{
                break;
            }
        }else{
            found = true;
        }
    }
    if(!found){
        return nullptr;
    }
    //cout << "value: " << value << endl;
    temp->value = value;
    //cout << "inO: ";
    //inO.print(cout);
    //cout << "levelO: ";
    //levelO.print(cout);
    //cout << "Value: " << value << endl;

    if(value!=inO.head->value){
        //cout << "ran left" << endl;
        pointerRay leftSide;
        leftSide.addUntil(inO.head, current);
        //leftSide.print(cout);
        //cout << "going left" <<endl;
        temp->left = makeTree(leftSide,levelO);
    }else {
        //cout << "got to end of left" << endl;
        temp->left = nullptr;
    }

    if(value!=inO.tail->value){
        //cout << "ran right" << endl;
        pointerRay rightSide;
        rightSide.addFrom(current);
        //rightSide.print(cout);
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
    pointerRay levelorder;
    pointerRay inorder;
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
                        inorder.addItem(nextString);
                    }
                    else if (i == 1)
                    {
                        levelorder.addItem(nextString);
                    }
                    else
                    {
                        decode = decode + nextString;
                    }
                }
            }
            inFS.close();
        }
    }

    Node* top = makeTree(inorder, levelorder);
    //cout << top->value << endl;

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
    cout << totals;
}