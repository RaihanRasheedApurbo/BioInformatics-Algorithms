#include<bits/stdc++.h>
using namespace std;
enum direction{RIGHT,BOTTOM,DIAGONAL};
int main()
{
    // input string a,b
    string a,b;
    a = "ATCTGAT";
    b = "TGCATA";

    // s table represents lcs length
    // p table represents lcs path
    // initializing tables with -5
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
    //printing input strings and length of lcs
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<s[a.size()][b.size()]<<endl;

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
    cout<<reverseLcs<<endl;
    cout<<lcs<<endl;

    //printing lcs length table s
    for(int i=0;i<s.size();i++)
    {
        for(int j=0;j<s[0].size();j++)
        {
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    
}