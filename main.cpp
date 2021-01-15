
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_OCCURRENCES = 9;
struct OrderMap
{
	bool operator()(const string& a, const string& b)const 
	{
		const char* aTest = a.c_str();
		const char* bTest = b.c_str();
		if (a == b)
		{
			return a < b;
		}
		else
			
			return _stricmp(aTest, bTest); 
			
	}
};

int main(int argc, char* argv[])
{
	map<string, map<int, int> /*OrderMap*/> reference;
	map<string, map<int, int> >::iterator itr; //iterator to access outer map
	map<int, int> ::iterator ptr; //iterator to access inner map
	vector<string> testVector;
	string str;
	string line;
	fstream textFile(argv[1]);
	int occurrences = 1;
	int lineNum = 1;
	if (argc < 2)
	{
		cout << "No file found. Using console input." << endl;
	}
	while (getline(textFile, line)) //read words from Strings.txt and add them to the container
	{
		int occurrences = 1;
		stringstream ss(line);
		while (ss >> str)
		{
			
			bool isValid = false;
			bool upperCase = false;
			if (isalpha(str[0])) //ensure the words begin with a letter
			{
				isValid = true;
				for (size_t i = 0; i < str.size(); i++)
				{
					if (isdigit(str[i])) //ensure no numerals are in the string
					{
						isValid = false;
						break;
					}
				}
				if (!isalpha(str[str.size() - 1])) // get rid of any symbols at the end of the string
				{
					while (!isalpha(str[str.size() - 1]))
					{
						str.pop_back();
					}
				}
			}
			if (isValid)
			{
				
				
				reference.insert(make_pair(str, map<int, int>()));
				reference[str].insert(make_pair(lineNum, occurrences));

				
				auto check = find(testVector.begin(), testVector.end(), str);
				if (check != testVector.end())
				{
					reference[str][lineNum]++;
				}
				testVector.push_back(str);
				
				
			}
			
		}
		testVector.clear();
		++lineNum;
	}
	for (itr = reference.begin(); itr != reference.end(); itr++) {
		cout << left;
		cout << setw(45) << itr->first;
		cout << ": ";
		int refCount = 0;
		for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
			if ( refCount > 0 and (refCount % MAX_OCCURRENCES) == 0)
			{
				cout << endl;
				cout << setw(45) << " " << ": ";
			}
			cout << ptr->first << ":";
			cout << ptr->second;
			if (next(ptr, 1) != itr->second.end())
			{
				cout << ", ";
			}
			++refCount;
		}
		cout << endl;
	}


	return 0;
}
void PrintTest(string word)
{
	cout << word << endl;
}

