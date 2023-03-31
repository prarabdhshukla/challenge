#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

char g_counter = '0';

struct Path
{
    int row, col;
    int length;
    static bool Compare(Path first, Path second)
    {
        return first.length < second.length;
    }
};

const vector<int> k_dir_row = {0, -1, 0, 1, 0};
const vector<int> k_dir_col = {0, 0, -1, 0, 1};

bool IsOutOfBounds(const vector<string>& matrix, const int row, const int col)
{
    return row < 0 || col < 0 || row >= matrix.size() || col >= matrix[0].length();
}

void DepthFirstSearch(const int row, const int col, vector<string>& matrix, vector<vector<bool>>& visited)
{
    for(int i = 0; i < k_dir_row.size(); i++)
    {
        int temp_row = row + k_dir_row[i], temp_col = col + k_dir_col[i];
        if(IsOutOfBounds(matrix, temp_row, temp_col))
            continue;

        if (matrix[temp_row][temp_col] == '.' && !visited[temp_row][temp_col])
        {
            visited[temp_row][temp_col] = true;
            matrix[temp_row][temp_col] = g_counter;
            g_counter++;
            DepthFirstSearch(temp_row, temp_col, matrix, visited);
        }
    }
}

void BreadthFirstSearch(const vector<string>& matrix, vector<Path>& paths)
{
    int rows = matrix.size(), cols = matrix[0].length();
    vector<vector<bool>> visited(matrix.size(), vector<bool>(cols, false));

    queue<pair<int,int>> queue;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(matrix[i][j] == '#' || visited[i][j])
                continue;
            queue.push(make_pair(i,j));
            visited[i][j] = true;
            int length = 0;

            while(!queue.empty())
            {
                pair<int,int> top = queue.front();
                queue.pop();
                length++;

                for(int k = 0; k < k_dir_row.size(); k++)
                {
                    int temp_row = top.first + k_dir_row[k], temp_col = top.second + k_dir_col[k];
                    if(IsOutOfBounds(matrix, temp_row, temp_col))
                        continue;
                    if(matrix[temp_row][temp_col] == '#' || visited[temp_row][temp_col])
                        continue;

                    visited[temp_row][temp_col] = true;
                    queue.push(make_pair(temp_row,temp_col));
                }
            }
            paths.push_back(Path({i,j,length}));
        }
    }
}

Path GetLongestPath(const vector<string>& matrix)
{
    vector<Path> paths;
    BreadthFirstSearch(matrix, paths);
    sort(paths.begin(), paths.end(), Path::Compare);
    return paths.back();
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);
    string line;
    vector<string> matrix;
    while(getline(file, line))
        matrix.push_back(line);

    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].length(), false));
    Path longest_path = GetLongestPath(matrix);
    cout << longest_path.length << endl;

    DepthFirstSearch(longest_path.row, longest_path.col, matrix, visited);
    ofstream file2("output.txt",ios::out);
    if(!file2.is_open()){
        cout<<"Error occured while trying to open file"<<endl;
        return 1;
    }
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++)
            file2<<matrix[i][j];
        file2<<"\n";
    }
    file2.close();

    return 0;
}
