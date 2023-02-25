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
        int value = stoi(num);
        input = input + value;
    }
    void addOutput(string num)
    {
        int value = stoi(num);
        output = output + value;
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
    double getRatio()
    {
        double temp = 1.0 * input / output;
        return temp;
    }
};

int main(int argc, char *argv[])
{
    string input = argv[1];
    string output = argv[2];
    ifstream inFS;
    ofstream outFS;
    inFS.open(input);
    if (!inFS.is_open())
    {
        cout << "Could not open input file " << input << endl;
        return 0;
    }
    int raySizeUsed = 0;
    Files ray[1001];
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
        for (int i = 0; i < from.size(); i++)
        {
            from[i] = toupper(from[i]);
        }
        for (int i = 0; i < to.size(); i++)
        {
            to[i] = toupper(to[i]);
        }
        int indexOfFrom = -1;
        int indexOfTo = -1;
        for (int i = 0; i < raySizeUsed; i++)
        {
            string nameAtI = ray[i].getName();
            for (int i = 0; i < nameAtI.size(); i++)
            {
                nameAtI[i] = toupper(nameAtI[i]);
            }

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
            raySizeUsed = raySizeUsed + 1;
        }
        if (indexOfTo == -1)
        {
            indexOfTo = raySizeUsed;
            ray[raySizeUsed] = Files(to);
            raySizeUsed = raySizeUsed + 1;
        }
        ray[indexOfFrom].addOutput(value);
        ray[indexOfTo].addInput(value);
    }

    inFS.close();
    outFS.open(output);
    if (!outFS.is_open())
    {
        cout << "Could not open output file " << output << endl;
        return 0;
    }

    for (int i = 0; i < raySizeUsed; i++)
    {
        outFS << ray[i].getName() << endl;
    }

    outFS << endl;

    for (int i = 0; i < raySizeUsed; i++)
    {
        if (ray[i].getOutput() > 0 && ray[i].getInput() > 0)
        {
            outFS << ray[i].getName() << " " << ray[i].getOutput() << " " << ray[i].getInput() << " " << fixed << setprecision(2) << ray[i].getRatio() << endl;
        }
    }

    outFS.close();
    return 0;
}