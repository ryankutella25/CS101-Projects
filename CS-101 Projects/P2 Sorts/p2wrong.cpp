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

void combineArray(string (&str1)[40000], string str2[20000], int &size1, int size2)
{
   for (int i = size1; i < size1 + size2; i++)
   {
      str1[i] = str2[i];
      cout << str2[i]<< endl;
   }
   size1 = size1 + size2;
}

void combineArray(int (&num1)[40000], int num2[20000], int &size1, int size2)
{
   for (int i = size1; i < size1 + size2; i++)
   {
      num1[i] = num2[i];
      cout << num2[i]<< endl;
   }
   size1 = size1 + size2;
}

void outputToFileTest(string fileName, int num[], int size)
{
   ofstream outFS;
   outFS.open(fileName);
   if (!outFS.is_open())
   {
      cout << "Could not open output file: " << fileName << endl;
   }
   else
   {
      // print all items on new line
      for (int i = 0; i < size; i++)
      {
         outFS << num[i] << endl;
      }
      // blank line
      outFS << endl;
      outFS.close();
   }
}

void outputToFileTest(string fileName, string str[], int size)
{
   ofstream outFS;
   outFS.open(fileName);
   if (!outFS.is_open())
   {
      cout << "Could not open output file: " << fileName << endl;
   }
   else
   {
      // print all items on new line
      for (int i = 0; i < size; i++)
      {
         outFS << str[i] << endl;
      }
      // blank line
      outFS << endl;
      outFS.close();
   }
}

void findRepeats(int (&final)[20000], int &finalSize, int num[], int size)
{
   for (int i = 1; i < size; i++)
   {
      if (num[i - 1] == num[i])
      {
         bool exists = false;
         for (int l = 0; l < finalSize; l++)
         {
            if (num[i] == final[l])
            {
               exists = true;
               break;
            }
         }
         if (!exists)
         {
            final[finalSize] = num[i];
            finalSize++;
         }
      }
   }
}

void findRepeats(string (&final)[20000], int &finalSize, string str[], int size)
{
   for (int i = 1; i < size; i++)
   {
      if (str[i - 1] == str[i])
      {
         bool exists = false;
         for (int l = 0; l < finalSize; l++)
         {
            if (str[i] == final[l])
            {
               exists = true;
               break;
            }
         }
         if (!exists)
         {
            final[finalSize] = str[i];
            finalSize++;
         }
      }
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

   int raySizeUsed = 0;
   int raySizeUsed1 = 0;

   inFS.open(input);
   if (!inFS.is_open())
   {
      cout << "Could not open input file: " << input << endl;
      return 0;
   }

   // fills numbers1[] and numbers2[] and makes raySizedUsed and raySizedUsed1 the right values
   // the else if fills string[] and strings2[] and makes raySizedUsed and raySizedUsed1 the right values
   if (is == "i")
   {
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
         numbers1[raySizeUsed] = stoi(fullLine);
         raySizeUsed++;
      }
      inFS.close();
      // start next input
      inFS.open(input2);
      if (!inFS.is_open())
      {
         cout << "Could not open input file: " << input << endl;
         return 0;
      }
      tf = true;
      while (tf)
      {
         string fullLine = "";
         getline(inFS, fullLine);
         if (fullLine == "")
         {
            tf = false;
            break;
         }
         numbers2[raySizeUsed1] = stoi(fullLine);
         raySizeUsed1++;
      }
   }
   else if (is == "s")
   {
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
         strings1[raySizeUsed] = fullLine;
         raySizeUsed++;
      }
      inFS.close();
      // start next input
      inFS.open(input2);
      if (!inFS.is_open())
      {
         cout << "Could not open input file: " << input << endl;
         return 0;
      }
      tf = true;
      while (tf)
      {
         string fullLine = "";
         getline(inFS, fullLine);
         if (fullLine == "")
         {
            tf = false;
            break;
         }
         strings2[raySizeUsed1] = fullLine;
         raySizeUsed1++;
      }
   }
   else
   {
      cout << "Error, invalid second argument" << endl;
   }
   inFS.close();

   // starting output
   if (is == "i")
   {
      int finalNumbers[20000];
      int finalSize = 0;
      // combine makes numbers1 the combined array and makes raySizeUsed the combined sizes
      combineArray(numbers1, numbers2, raySizeUsed, raySizeUsed1);
      outputToFileTest("out.txt",numbers1,raySizeUsed);
      outputTest(numbers2,raySizeUsed1);
      cout << raySizeUsed << endl;

      MergeSort(numbers1, 0, raySizeUsed);

      // finds all repeats, checks they aren't already in finalNumbers, and puts the imto finalNumbers
      // also sets final size to the right size
      findRepeats(finalNumbers, finalSize, numbers1, raySizeUsed);

      for (int i = 0; i < finalSize; i++)
      {
         cout << finalNumbers[i] << " ";
      }
      cout << endl;
   }
   else if (is == "s")
   {
      string finalNumbers[20000];
      int finalSize = 0;
      // combine makes numbers1 the combined array and makes raySizeUsed the combined sizes
      combineArray(strings1, strings2, raySizeUsed, raySizeUsed1);

      Quicksort(strings1, 0, raySizeUsed - 1);

      // finds all repeats, checks they aren't already in finalNumbers, and puts the imto finalNumbers
      // also sets final size to the right size
      findRepeats(finalNumbers, finalSize, strings1, raySizeUsed);

      for (int i = 0; i < finalSize; i++)
      {
         cout << finalNumbers[i] << " ";
      }
      cout << endl;
   }

   return 0;
}