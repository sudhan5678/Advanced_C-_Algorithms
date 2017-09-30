/*1
4
GEEKS FOR QUIZ GO
3 3
G I Z U E K Q S E*/


#include<iostream>
#include<unordered_set>
#include<string>
#include<functional>
#include <set>

using namespace std;
typedef pair<int, int> position;

namespace std {
	template<>
	struct hash<position>
	{
		int operator() (const position &pair) const
		{
			return (hash<int>()(pair.first) + hash<int>()(pair.second));
		}
	};
}

void word_game(unordered_set<string> &dictionary, position pos, vector<vector<char>> &board,
				set<string> &result)
{
	static vector<int> offsets = { -1,0,1 };
	unordered_set<position>  visited;
	string temp;

	//Define lambda function
	std::function<void(position)> word_game_dfs = [&](position pos) {
		for (auto &i : offsets)
		{
			for (auto &j : offsets)
			{
				position next_pos = { pos.first + i,pos.second + j };
				if ((next_pos.first >= 0 && next_pos.first < static_cast<int>(board.size()))
					&& (next_pos.second >= 0 && next_pos.second < static_cast<int>(board[next_pos.first].size()))) {
					if (visited.find(next_pos) == visited.end())
					{
						visited.insert(next_pos);
						temp = temp + board[pos.first + i][pos.second + j];
						if (dictionary.find(temp) != dictionary.end() && result.find(temp) == result.end())
						{
							result.insert(temp);
						}

						word_game_dfs(next_pos);
						//Remove last char after its iteration
						visited.erase(visited.find(next_pos));
						temp.resize(temp.length() - 1);
					}
				}
			}
		}
	};

	word_game_dfs(pos);

}

void boggle(unordered_set<string> &dictionary, vector<vector<char>> &board, set<string> &result)
{
	for (unsigned row = 0; row < board.size(); ++row)
	{
		for (unsigned col = 0; col < board[row].size(); ++col)
		{
			word_game(dictionary, { row,col }, board,result);
		}
	}
}

int main()
{
	int no_Of_test_cases;
	cin >> no_Of_test_cases;
	int temp = no_Of_test_cases;
	//Read the input
	vector<set<string>> result;
	while (no_Of_test_cases--)
	{
		unordered_set<string> dictionary;
		int words_in_dictionary;
		int rows, column;
		vector<vector<char>> board;
		set<string> temp_res;
		cin >> words_in_dictionary;
		for (int i = 0; i < words_in_dictionary; ++i)
		{
			string temp;
			cin >> temp;
			dictionary.insert(temp);
		}
		cin >> rows >> column;
		for (int i = 0; i < rows; ++i)
		{
			vector<char> temp_vec;
			for (int j = 0; j < column; ++j)
			{
				char temp;
				cin >> temp;				
				temp_vec.push_back(temp);
			}
			board.push_back(temp_vec);
		}
		boggle(dictionary, board, temp_res);
		result.push_back(temp_res);
	}

	for (int i = 0; i < temp; ++i)
	{
		for (auto &str : result[i])
		{
			cout << str << " ";
		}
		cout << endl;
	}
	
	return 0;
}