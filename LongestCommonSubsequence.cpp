#include <iostream>
#include <vector>

using namespace std;

std::vector<int> longest_common_subsequence(const std::vector<int> &s,
                                            const std::vector<int> &t)
{
    vector<vector<int>> memo(s.size() + 1, vector<int>(t.size() + 1, 0));
    for (auto i = 0; i < s.size() + 1; ++i)
    {
        for(auto j = 0; j < t.size() + 1;++j)
        {
            if(i==0 || j == 0) memo[i][j] = 0;
            else {
                memo[i][j] = (s[i-1] == t[j-1]) ? memo[i-1][j-1] +1 :
                                                    std::max(memo[i-1][j],memo[i][j-1]);
            }

        }
    }

    //Backtrack to find out the elements

    std::vector<int> lcs;
    auto length = memo[s.size()][t.size()]; // value in the last cell
    for(auto i = s.size(),j=t.size();i && j && length ; --length )
    {
        while(i && memo[i-1][j]==length) --i;
        while(j && memo[i][j-1]==length) --j;
        lcs.emplace(lcs.begin(),s[i-1]);
    }

    return lcs;
}

int main()
{
	return 0;
}
