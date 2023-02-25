/* hello.cpp */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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

int main()
{
    string input;
    string output;
    ifstream inFS;
    ofstream outFS;
    cin >> input >> output;
    inFS.open(input);
    if (!inFS.is_open())
    {
        cout << "Could not open input file " << input << endl;
        return 0;
    }

    vector<Files> ray;
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
        for (int i = 0; i < ray.size(); i++)
        {
            string nameAtI = ray.at(i).getName();
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
            indexOfFrom = ray.size();
            ray.push_back(Files(from));
        }
        if (indexOfTo == -1)
        {
            indexOfTo = ray.size();
            ray.push_back(Files(to));
        }
        ray.at(indexOfFrom).addOutput(value);
        ray.at(indexOfTo).addInput(value);
    }

    inFS.close();
    outFS.open(output);
    if (!outFS.is_open())
    {
        cout << "Could not open output file " << output << endl;
        return 0;
    }

    for (int i = 0; i < ray.size(); i++)
    {
        outFS << ray.at(i).getName() << endl;
    }

    outFS << endl;

    for (int i = 0; i < ray.size(); i++)
    {
        if (ray.at(i).getOutput() > 0 && ray.at(i).getInput() > 0)
        {
            outFS << ray.at(i).getName() << " " << ray.at(i).getOutput() << " " << ray.at(i).getInput() << " " << fixed << setprecision(2) << ray.at(i).getRatio() << endl;
        }
    }

    outFS.close();
    return 0;
}