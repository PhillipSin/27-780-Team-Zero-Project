#pragma once
#include <vector>
#include <string>

using namespace std;
class printText
{
private:
	vector<string> text;
public:
	void add(string a) { text.push_back(a);};
	void remove() { text.erase(text.begin() + 0); };
};

