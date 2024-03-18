/* p1.cpp */
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class Files
{
private:
    string name;
    int input;
    int output;

public:
    Files()
    {
        name = "NoName";
        input = 0;
        output = 0;
    }
    Files(string x)
    {
        name = x;
        input = 0;
        output = 0;
    }
    void addInput(string num)
    {
        input = input + stoi(num);
    }
    void addOutput(string num)
    {
        output = output + stoi(num);
    }
    string getName()
    {
        return name;
    }
    int getInput()
    {
        return input;
    }
    int getOutput()
    {
        return output;
    }
    // is full double, will need to make fixed and setprecision to 2 later when out'ing
    double getRatio()
    {
        return 1.0 * input / output;
    }
};

int main(int argc, char *argv[])
{
    cout << "Ran " <<endl;
    string input = argv[1];
    string output = argv[2];
    ifstream inFS;
    ofstream outFS;
    inFS.open(input);
    if (!inFS.is_open())
    {
        cout << "Could not open input file: " << input << endl;
        return 0;
    }
    int raySizeUsed = 0;
    Files ray[1001];
    //loops until a fullline of input is ""
    //sets tf to false when above happens
    bool tf = true;
    while (tf)
    {
        string fullLine = "";
        getline(inFS, fullLine);
        if (fullLine == "")
        {
            tf = false;
            break;
        }
        string from = "";
        string to = "";
        string value = "";
        istringstream iss(fullLine);
        iss >> from >> to >> value;
        // make everything uppercase
        for (int i = 0, max = from.size(); i < max; i++)
        {
            from[i] = toupper(from[i]);
        }
        for (int i = 0, max = to.size(); i < max; i++)
        {
            to[i] = toupper(to[i]);
        }
        // see if to and from strings are already in Files ray
        // and set index to indexes below
        int indexOfFrom = -1;
        int indexOfTo = -1;
        for (int i = 0; i < raySizeUsed; i++)
        {
            string nameAtI = ray[i].getName();
            if (nameAtI == from)
            {
                indexOfFrom = i;
            }
            if (nameAtI == to)
            {
                indexOfTo = i;
            }
        }
        if (indexOfFrom == -1)
        {
            indexOfFrom = raySizeUsed;
            ray[raySizeUsed] = Files(from);
            raySizeUsed++;
        }
        if (indexOfTo == -1)
        {
            indexOfTo = raySizeUsed;
            ray[raySizeUsed] = Files(to);
            raySizeUsed++;
        }
        ray[indexOfFrom].addOutput(value);
        ray[indexOfTo].addInput(value);
    }
    inFS.close();
    // starting output
    outFS.open(output);
    if (!outFS.is_open())
    {
        cout << "Could not open output file: " << output << endl;
        return 0;
    }
    // print all file names in array on new line
    for (int i = 0; i < raySizeUsed; i++)
    {
        outFS << ray[i].getName() << endl;
    }
    // blank line
    outFS << endl;
    // print all files that send and receive, "Name Output Input Ratio" ex. "RYAN 200 100 .50"
    for (int i = 0; i < raySizeUsed; i++)
    {
        // if checks that it received and sends info (if it didn't one would be 0)
        if (ray[i].getOutput() > 0 && ray[i].getInput() > 0)
        {
            outFS << ray[i].getName() << " " << ray[i].getOutput() << " " << ray[i].getInput() << " " << fixed << setprecision(2) << ray[i].getRatio() << endl;
        }
    }
    outFS.close();
    return 0;
    
}