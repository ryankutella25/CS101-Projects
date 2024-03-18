#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

void Merge(int numbers[], int i, int j, int k)
{
    int mergedSize; // Size of merged partition
    int mergePos;   // Position to insert merged number
    int leftPos;    // Position of elements in left partition
    int rightPos;   // Position of elements in right partition
    int *mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                         // Initialize left partition position
    rightPos = j + 1;                    // Initialize right partition position
    mergedNumbers = new int[mergedSize]; // Dynamically allocates temporary array
                                         // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k)
    {
        if (numbers[leftPos] < numbers[rightPos])
        {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else
        {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j)
    {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k)
    {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k)
{
    int j;

    if (i < k)
    {
        j = (i + k) / 2; // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

int Partition(string numbers[], int i, int k)
{
    int l;
    int h;
    int midpoint;
    string pivot = "";
    string temp = "";
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    done = false;
    l = i;
    h = k;

    while (!done)
    {

        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot)
        {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h])
        {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h)
        {
            done = true;
        }
        else
        {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

void Quicksort(string numbers[], int i, int k)
{
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k)
    {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    Quicksort(numbers, i, j);
    Quicksort(numbers, j + 1, k);
}

void outputTest(int num[], int size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << num[i] << " ";
        }
        cout << endl;
    }
}

void outputTest(string str[], int size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << str[i] << " ";
        }
        cout << endl;
    }
}

void removeRepeats(int final[], int &finalSize)
{
    int temp[20000];
    int tempSize = 1;
    temp[0] = final[0];
    for (int i = 1; i < finalSize; i++)
    {
        if (final[i] != final[i - 1])
        {
            temp[tempSize] = final[i];
            tempSize++;
        }
    }
    for (int i = 0; i < tempSize; i++)
    {
        final[i] = temp[i];
    }
    finalSize = tempSize;
}

void removeRepeats(string final[], int &finalSize)
{
    string temp[20000];
    int tempSize = 1;
    temp[0] = final[0];
    for (int i = 1; i < finalSize; i++)
    {
        if (final[i] != final[i - 1])
        {
            temp[tempSize] = final[i];
            tempSize++;
        }
    }
    for (int i = 0; i < tempSize; i++)
    {
        final[i] = temp[i];
    }
    finalSize = tempSize;
}

void findShared(int final[], int &finalSize, int num1[], int size1, int num2[], int size2)
{
    int pos1 = 0;
    int pos2 = 0;
    while (pos1 < size1 && pos2 < size2)
    {
        if (num1[pos1] == num2[pos2])
        {
            final[finalSize] = num1[pos1];
            finalSize++;
            pos1++;
            pos2++;
        }
        else if (num1[pos1] < num2[pos2])
        {
            pos1++;
        }
        else
        {
            pos2++;
        }
    }
    if(finalSize>0){
        removeRepeats(final, finalSize);
    }
}

void findShared(string final[], int &finalSize, string num1[], int size1, string num2[], int size2)
{
    int pos1 = 0;
    int pos2 = 0;
    while (pos1 < size1 && pos2 < size2)
    {
        if (num1[pos1] == num2[pos2])
        {
            final[finalSize] = num1[pos1];
            finalSize++;
            pos1++;
            pos2++;
        }
        else if (num1[pos1] < num2[pos2])
        {
            pos1++;
        }
        else
        {
            pos2++;
        }
    }
    if (finalSize >0)
    {
        removeRepeats(final, finalSize);
    }

}

void outputFinal(int num[], int size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << num[i] << endl;
        }
    }
}

void outputFinal(string num[], int size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << num[i] << endl;
        }
    }
}

void readAndFill(string str[], int num[], int &size, string input, bool useString)
{
    ifstream inFS;
    inFS.open(input);
    if (!inFS.is_open())
    {
        cout << "Could not open input file: " << input << endl;
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
            if (useString)
            {
                str[size] = nextString;
            }
            else
            {
                num[size] = stoi(nextString);
            }
            size++;
        }
        inFS.close();
    }
}

int main(int argc, char *argv[])
{
    string is = argv[1];
    string input = argv[2];
    string input2 = argv[3];
    ifstream inFS;

    string strings1[40000];
    int numbers1[40000];
    string strings2[20000];
    int numbers2[20000];

    int size1 = 0;
    int size2 = 0;

    
    if (is == "i")
    {
        //read first input and fill strings1
        readAndFill(strings1, numbers1, size1, input, false);
        //read second input and fill strings1
        readAndFill(strings2, numbers2, size2, input2, false);

        // sorts each array
        MergeSort(numbers1, 0, size1 - 1);
        MergeSort(numbers2, 0, size2 - 1);
        // outputTest(numbers1, size1);
        // outputTest(numbers2, size2);

        int final[20000];
        int finalSize = 0;
        //goes through strings1 and strings2 and adds shared to final, deleting repeats
        findShared(final, finalSize, numbers1, size1, numbers2, size2);

        //outputs each item of final on its own line; foreach(cout<<item<<endl;)
        outputFinal(final, finalSize);
    }
    else if (is == "s")
    {
        //read first input and fill strings1
        readAndFill(strings1, numbers1, size1, input, true);
        //read next input and fill strings2
        readAndFill(strings2, numbers2, size2, input2, true);

        // sorts each array
        Quicksort(strings1, 0, size1 - 1);
        Quicksort(strings2, 0, size2 - 1);

        // outputTest(strings1, size1);
        // outputTest(strings2, size2);

        string final[20000];
        int finalSize = 0;
        //goes through strings1 and strings2 and adds shared to final, deleting repeats
        findShared(final, finalSize, strings1, size1, strings2, size2);

        outputFinal(final, finalSize);
    }
    else
    {
        cout << "Error, invalid second argument" << endl;
    }
}