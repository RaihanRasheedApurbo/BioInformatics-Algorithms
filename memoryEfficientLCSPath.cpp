#include<bits/stdc++.h>
using namespace std;

int lcsLengthMemoryEfficient(string a, string b)
{
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
    return next[b.size()];
}

void lcsPathMemoryEfficient(string a, string b, int leftA, int rightA, int leftB, int rightB)
{ 
    //e 0 0 0 0 0 0 0 
    //A 0 0 0 0 1 1 1 
    //T 0 1 1 1 1 2 2 
    //C 0 1 1 2 2 2 2 
    //T 0 1 1 2 2 3 3 
    //G 0 1 2 2 2 3 3 
    //A 0 1 2 2 3 3 4 
    //T 0 1 2 2 3 4 4 



    //  7,6 <- 7,5 <- 6,4 <- 5,3 <- 5,2 <- 4,1 <- 3,0
    //    0 1 2 3 4 5 6     //    0 1 2 3 4 5 6
    //    e T G C A T A     //    e T G C A T A
    //0 e n n n n n n n     //0 e 0 0 0 0 0 0 0
    //1 A n R R R D R D     //1 A 0 0 0 0 1 1 1 
    //2 T n D R R R D R     //2 T 0 1 1 1 1 2 2
    //3 C n B R D R R R     //3 C 0 1 1 2 2 2 2
    //4 T n D R B R D R     //4 T 0 1 1 2 2 3 3
    //5 G n B D R R B R     //5 G 0 1 2 2 2 3 3 
    //6 A n B B R D R D     //6 A 0 1 2 2 3 3 4
    //7 T n D B R B D R     //7 T 0 1 2 2 3 4 4

    if(leftB==rightB)
    {
        int maxLCS = -1;
        int maxIndex = -1;
        for(int i=1;i<a.size()+1;i++)
        {
            string rowString = a.substr(0,i);
            string colString = b.substr(left,left+1);
            int t = lcsLengthMemoryEfficient(rowString,colString);
            if(t>=maxLCS)
            {
                maxIndex = i;
            } 
        }
        cout<<maxIndex<<","<<left<<endl;
        return;
    }
    int maxLCS = -1;
    int maxIndex = -1;
    int midColumn = (leftB+rightB)/2;
    for(int i=leftA+1;i<rightA+2;i++)
    {
        string rowString = a.substr(leftA,i);
        string colString = b.substr(leftB,midColumn);
        //cout<<rowString<<" "<<colString<<endl;
        int t1 = lcsLengthMemoryEfficient(rowString,colString);
        //cout<<t1<<endl;
        
        rowString = a.substr(i,rightA+1);
        colString = b.substr(midColumn,rightB+1);
        int t2 = lcsLengthMemoryEfficient(rowString,colString);
        //cout<<t2<<endl;
        //cout<<t1+t2<<endl;
        if(maxLCS<=t1+t2)
        {
            maxLCS = t1+t2;
            maxIndex = i;
        }
    }
    
    lcsPathMemoryEfficient(a,b,leftA,maxIndex,leftB,midColumn);
    //cout<<maxIndex<<","<<midColumn<<endl;
    lcsPathMemoryEfficient(a,b,maxIndex+1,rightA,midColumn+1,rightB);
    
}

int main()
{
    string a = "ATCTGAT";
    string b = "TGCATA";
    lcsPathMemoryEfficient(a,b,0,b.size());
    
}