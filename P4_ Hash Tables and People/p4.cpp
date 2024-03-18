#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;


uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
};

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
    Person(){
        this->id = "";
        this->first = "";
        this->last ="";
        this->email = "";
        this->phone = "";
        this->city ="";
        this->state = "";
        this->postalCode = "";
    }
    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode){
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
    }
    Person(const Person &temp){
        this->id = temp.id;
        this->first = temp.first;
        this->last = temp.last;
        this->email = temp.email;
        this->phone = temp.phone;
        this->city = temp.city;
        this->state = temp.state;
        this->postalCode = temp.postalCode;
    }
    void print(ostream &os){
        os << id << "," << first << "," << last << "," << email << "," 
        << phone << ","  << city << ","  << state << ","  << postalCode << endl;
    }
};

class HashNode{
    vector<Person> people;
    string nodeName = "";
    int nodeNumber = 0;
    bool empty = true;
    public:
        HashNode(){
            empty = true;
        }
        HashNode(Person temp, string name, int num){
            empty = false;
            people.push_back(Person(temp));
            nodeName = name;
            nodeNumber = num;
        }
        bool isEmpty(){
            return empty;
        }
        void print(ostream &os){
            if (!empty)
            {
                os << nodeNumber << ": " << nodeName << "(" << people.size() << ")," << endl;
            }
        }
        void printPeople(ostream &os){
            if (!empty)
            {
                for(int i = 0;i < people.size(); i++){
                    people[i].print(os);
                }
            }
        }
        string getNodeName(){
            return nodeName;
        }
        void pushBack(Person temp){
            people.push_back(temp);
        }
};

class HashTable {
    vector<HashNode> nodes;
    string hashName;
    public:
    HashTable(int size, string name){
        nodes.resize(size);
        hashName = name;
    }
    void insert(Person person){
        uint64_t hashNumber;
        string nodeName;
        if(hashName == "Id"){
            hashNumber = djb2(person.id);
            nodeName = person.id;
        }else if (hashName == "FirstName"){
            hashNumber = djb2(person.first);
            nodeName = person.first;
        }else if (hashName == "LastName"){
            hashNumber = djb2(person.last);
            nodeName = person.last;
        }else if (hashName == "Email"){
            hashNumber = djb2(person.email);
            nodeName = person.email;
        }else if (hashName == "Phone"){
            hashNumber = djb2(person.phone);
            nodeName = person.phone;
        }else if (hashName == "City"){
            hashNumber = djb2(person.city);
            nodeName = person.city;
        }else if (hashName == "State"){
            hashNumber = djb2(person.state);
            nodeName = person.state;
        }else{
            hashNumber = djb2(person.postalCode);
            nodeName = person.postalCode;
        }
        uint64_t slot = hashNumber%nodes.size();
        int count = 1;
        bool addedToNode = false;
        while (!nodes[slot].isEmpty())
        {
            if(nodes[slot].getNodeName()==nodeName){
                nodes[slot].pushBack(person);
                addedToNode = true;
                break;
            }
            uint64_t squared = pow(count,2);
            slot = (hashNumber + count + squared) % nodes.size();
            count++;
        }
        if(!addedToNode){
            nodes[slot] = HashNode(person, nodeName, slot);
        }
    }
    void print(ostream &os){
        for (int i = 0; i < nodes.size(); i++){
            if(!nodes[i].isEmpty()){
                nodes[i].print(os);
            }
        }
    }
    void lookup(string nodeName, ostream &os){
        uint64_t hashNumber = djb2(nodeName);
        uint64_t slot = hashNumber % nodes.size();
        int count = 1;
        while (!nodes[slot].isEmpty() && nodes[slot].getNodeName() != nodeName)
        {
            int squared = pow(count,2);
            slot = (hashNumber + count + squared) % nodes.size();
            count++;

        }
        if(nodes[slot].isEmpty()){
            cout << "No results" << endl;
        }
        else{
            os << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
            nodes[slot].printPeople(os);
        }
    }
};

void getVal(istream &is, string &str) {
    char ch;
    string line;
    is >> ch;
    getline(is, line);
    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    HashTable table = HashTable(tableSize, key);
    
    string line, token;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);
        string temp[8];
        int count = 0;
        while (getline(iss, token, '\t')) {
            temp[count] = token;
            //cout << token << "\t";
            count++;
        }
        Person tempPerson = Person(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]);
        table.insert(tempPerson);
        //cout << endl;
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            table.print(cout);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            table.lookup(val,cout);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
