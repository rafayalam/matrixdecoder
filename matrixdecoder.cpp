#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

void print(string label, ofstream& myotherfile, vector<string>& str, vector<string>& labels);

char spiralPrint(int x, int y, vector<vector<char> >& matrix, vector<string>& str);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage:  \"input=<file>;output=<file>\"" << std::endl;
        return -1;
    }
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");

    ofstream output;
    output.open(outfilename);
    ifstream input;
    input.open(infilename);

    ifstream myfile;
    ofstream myotherfile;

    myfile.open(infilename.c_str()); //infilename.c_str()
    myotherfile.open(outfilename.c_str()); //outfilename.c_str()

    vector<string> str;
    vector<string> labels;
    string label;
    string line;
    string rows;
    string columns;
    char size;
    int x;
    int y;

    while (myfile >> label)
    {
        labels.push_back(label);
        getline(myfile, line, ',');
        stringstream sa(line);
        sa >> x;
        getline(myfile, line);
        stringstream sb(line);
        sb >> y;

        vector<vector<char> > matrix;
        for (int i = 0; i < x; i++)
        {
            vector<char>temp;
            for (int j = 0; j < y; j++)
            {
                myfile >> size;
                temp.push_back(size);
            }
            matrix.push_back(temp);
        }
        spiralPrint(x, y, matrix, str);
        cout << endl;
    }

    print("finish", myotherfile, str, labels);

    myfile.close();
    myotherfile.close();
    return 0;
}

void print(string label, ofstream& myotherfile, vector<string>& str, vector<string>& labels)
{
    for (int i = 0; i < labels.size(); i++)
    {
        if (label == "start")
        {
            return;
        }
        if (label == str[i])
        {
            label = labels[i];
            myotherfile << labels[i] << endl;
            //cout << ": " << labels[i] << endl;
        }
    }
    print(label, myotherfile, str, labels);
}

//Code from https://www.youtube.com/watch?v=SV5ao_ITBjI
char spiralPrint(int x, int y, vector<vector<char> >& matrix, vector<string>& str)
{
    stringstream ss;
    string word;
    int bottom = x - 1;
    int right = y - 1;
    int top = 0;
    int left = 0;

    while (1)
    {
        if (left > right)
        {
            break;
        }
        for (int i = left; i <= right; i++)
        {
            ss << matrix[top][i];
        }
        top++;

        if (top > bottom)
        {
            break;
        }
        for (int i = top; i <= bottom; i++)
        {
            ss << matrix[i][right];
        }
        right--;

        if (left > right)
        {
            break;
        }
        for (int i = right; i >= left; i--)
        {
            ss << matrix[bottom][i];
        }
        bottom--;

        if (top > bottom)
        {
            break;
        }
        for (int i = bottom; i >= top; i--)
        {
            ss << matrix[i][left];
        }
        left++;
    }
    word = ss.str();
    str.push_back(word);
    return 0;
}