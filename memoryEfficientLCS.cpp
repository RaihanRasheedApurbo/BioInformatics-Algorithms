#include<bits/stdc++.h>
using namespace std;
int main()
{
    // input string a,b
    string a,b;
    a = "ATCTGAT";
    b = "TGCATA";
    //  e T G C A T A
    //e 0 0 0 0 0 0 0 
    //A 0 0 0 0 1 1 1 
    //T 0 1 1 1 1 2 2 
    //C 0 1 1 2 2 2 2 
    //T 0 1 1 2 2 3 3 
    //G 0 1 2 2 2 3 3 
    //A 0 1 2 2 3 3 4 
    //T 0 1 2 2 3 4 4 

    vector<int> prev(b.size()+1);
    vector<int> next(b.size()+1);
    for(int i=0;i<b.size()+1;i++)
    {
        prev[i] = 0;
    }
    for(int i=1;i<a.size()+1;i++)
    {
        for(int j=0;j<b.size()+1;j++)
        {
            if(j==0)
            {
                next[j] = 0;
                continue;
            }

            if(a[i-1]==b[j-1])
            {
                next[j] = prev[j-1] + 1;
            }
            else if(next[j-1]>prev[j])
            {
                next[j] = next[j-1];
            }
            else
            {
                next[j] = prev[j];
            }
        }
        prev = next;
    }
    cout<<next[b.size()]<<endl;
}