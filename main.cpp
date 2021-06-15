
#include <iostream>
#include <cstring>

using namespace std;
int *arr ;

void failure(char *pat) //function to get failure links "prefix table" for the pattern given which is will be used in kmp function.
{
    int x= strlen(pat);

    arr[0]=-1;   //set the first index to -1 and move the iterator after it
    int j = -1;
    for(int i=0 ; i<x ;) //for loop to iterate over the pattern length
    {
        if (j == -1 || pat[i] == pat[j]) //check if the 2 characters is similar to each other or j==-1 which means
                                          // its locations on the first of the array and doesn't move yet.
        {
            j++; //j goes to the next index if the match happened between characters of the pattern.
            i++; //i goes to the next index if the match happened between characters of the pattern.
            arr[i] = j;  // set the failure link of index i equal to the value of j ,ex: of j=0,i=1 the failure link of the first index= 0
        }
        else  // if the characters of the pattern don't match each other and j is greater than -1
        {
            j = arr[j];  // will set the value of j equal to the value of the failure link which the j iterator stopped at
            // in the last iteration to return to the index which the failure link equal to ,ex: if the j finally stopped at j=0 and the characters
            //of the pattern didn't match each other so the new value of j will be arr[0] which is always equal -1 so the new value of j will be -1.
        }
        if(j==x)  // if j comes to the end of the pattern length it will break.
        {
            break;
        }
    }
    cout<<"faliure links for this pattern:";
      for(int k=1 ; k< x+1 ;k++ )  //loop to print the failure link array.
      {
          cout<< arr[k] << " ";
      }
      cout<<endl;
}
void KMP(char *word, char *patt)
{
    failure(patt);  //construct failure table to the pattern given.
    int  j = 0; // iterator to iterate allover the pattern characters.
    for (int i = 0; i < strlen(word);)  //  for loop to iterate on the word
    {
        if (word[i] == patt[j]) // check if the characters of the pattern and the word are matching
                                 // if yes so increment i,j to go to the next characters along the word and the pattern.
        {
            i++;
            j++;

            if (j == strlen(patt)) //check if the j which is iterating on the pattern comes to the end of the pattern
                           //if yes it will print the indeces of word & pattern in which they matched and the index in which they matched in the word.
                {
                cout <<"word("<<i-1 << ") , Pattern(" << j-1 << ")"<<endl;
                cout <<"The pattern is found in the word at index :"<< i - j << endl;
                j = arr[j]; // will set the value of j equal to the value of the failure link which the j iterator stopped at
                      // in the last iteration to return to the index which the failure link equal to .
            }
        }
        else if(word[i] != patt[j] ) // if the characters doesn't match each other
        {
            if (j <= 0) //check about the value of j if it equals to -1 as it can't compare pattern[0] "which is equal to -1"
                // to word[i] as it will be out of bounds.
            {
                i++;    //increment i to go to the next char in the word.
                j = 0;  // make j=0 so it can compare the 2 characters from the word and the pattern correctly.
            } else
                {
                j = arr[j];  //will set the value of j equal to the value of the failure link which the j iterator stopped at
                    // in the last iteration to return to the index which the failure link equal to .
            }
        }
    }
}

int main()
{
    char *word = "AGAGAAGAGGAGAAGAGAAGAGA";  //testcase
    char *p = "AGAAGAG";
    arr = new int[strlen(p)]; // integer array to store the length of the pattern character array.
    KMP(word, p);
    return 0;

}

