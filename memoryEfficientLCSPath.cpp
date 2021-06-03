#include<bits/stdc++.h>
using namespace std;
enum direction{RIGHT,BOTTOM,DIAGONAL};
int lcsForTrivial(string a, string b)
{
    vector<vector<int>> s(a.size()+1);
    vector<vector<int>> p(a.size()+1);
    for(int i=0;i<s.size();i++)
    {
        vector<int> t(b.size()+1);
        for(int j=0;j<t.size();j++)
        {
            t[j] = -5;
        }
        
        s[i] = t;
        p[i] = t;
    }
    // initializing first row and first
    // column with boundary condition which
    // is in this case 0
    for(int i=0;i<s.size();i++)
    {
        s[i][0] = 0;
    }
    for(int i=0;i<s[0].size();i++)
    {
        s[0][i] = 0;
    }

    for(int i=1;i<s.size();i++)
    {
        for(int j=1;j<s[0].size();j++)
        {
            if(a[i-1]==b[j-1])
            {
                s[i][j] = s[i-1][j-1] + 1;
                p[i][j] = DIAGONAL; 
            }
            else if(s[i-1][j]>s[i][j-1])
            {
                s[i][j] = s[i-1][j];
                p[i][j] = BOTTOM; 
            }
            else
            {
                s[i][j] = s[i][j-1];
                p[i][j] = RIGHT;
            }
        }
    }
    //acquiring reverse of the lcs by
    //traversing the path table backwards
    int ci = a.size();
    int cj = b.size();
    string reverseLcs = "";
    while(p[ci][cj] != -5)
    {
        if(p[ci][cj] == BOTTOM)
        {
            ci -= 1;
        }
        else if(p[ci][cj] == RIGHT)
        {
            cj -= 1;
        }
        else if(p[ci][cj] == DIAGONAL)
        {
            reverseLcs += a[ci-1];
            ci -= 1;
            cj -= 1;
        }


    }



    // generating reverse string of reverseLcs
    // which is our desired lcs
    string lcs = "";
    for(int i=reverseLcs.size()-1;i>=0;i--)
    {
        lcs += reverseLcs[i];
    }
    //printing both
    // cout<<reverseLcs<<endl;
    cout<<lcs;
}


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

    if(abs(leftB-rightB)<=2)
    {
        string rowString = a.substr(leftA,rightA-leftA+1);
        string colString = b.substr(leftB,rightB-leftB+1);
        lcsForTrivial(rowString,colString);
        return;
        // int maxLCS = -1;
        // int maxIndex = -1;
        // for(int i=1;i<a.size()+1;i++)
        // {
            
        //     int t = lcsLengthMemoryEfficient(rowString,colString);
        //     if(t>=maxLCS)
        //     {
        //         maxIndex = i;
        //     } 
        // }
        // cout<<maxIndex<<","<<left<<endl;
        return;
    }
    int maxLCS = -1;
    int maxIndex = -1;
    int midColumn = (leftB+rightB)/2;
    for(int i=1;i<=rightA-leftA+1;i++)
    {
        string rowString = a.substr(leftA,i);
        string colString = b.substr(leftB,midColumn-leftB+1);
        //cout<<rowString<<" "<<colString<<endl;
        int t1 = lcsLengthMemoryEfficient(rowString,colString);
        //cout<<t1<<endl;
        
        rowString = a.substr(leftA+i,rightA-leftA-i+1);
        colString = b.substr(midColumn+1,rightB-midColumn-1+1);
        int t2 = lcsLengthMemoryEfficient(rowString,colString);
        //cout<<t2<<endl;
        //cout<<t1+t2<<endl;
        if(maxLCS<=t1+t2)
        {
            maxLCS = t1+t2;
            maxIndex = leftA+i-1;
        }
    }
    
    lcsPathMemoryEfficient(a,b,leftA,maxIndex,leftB,midColumn);
    //cout<<maxIndex<<","<<midColumn<<endl;
    lcsPathMemoryEfficient(a,b,maxIndex+1,rightA,midColumn+1,rightB);
    
}

int main()
{
    string a = "ATCTGATATCTGAT";
    string b = "TGCATATGCATA";
    cout<<"lcs trivial"<<endl;
    lcsForTrivial(a,b);
    cout<<endl;
    cout<<"lcs memory efficient"<<endl;
    lcsPathMemoryEfficient(a,b,0,a.size()-1,0,b.size()-1);
    cout<<endl;
    // cout<<a.substr(3,7);

    
}