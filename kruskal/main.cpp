#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
#define min 0;


string i2s(int a) {
	string tmp;
	if (a == 0) {
		tmp = "0";
	}
	else {
		while (a > 0) {
			tmp += a % 10 + '0';
			a /= 10;
		}
	}
	return tmp;
}

void ini_paths(map<int, int>& input2RC,map<int,int>&RC2input, vector<vector<double>>& paths, set<string>& F) {
	
	int lines;
	int RCcount=0;
	cin >> lines;
	for (int i = 0; i < lines; i++)
	{
		int node1, node2;

		double prob;
		cin >> node1 >> node2 >> prob;
		F.insert(i2s(node1));
		F.insert(i2s(node2));
		if (input2RC.find(node1) == input2RC.end()) {
			input2RC.insert(pair<int, int>(node1, RCcount++));
		}
		if (input2RC.find(node2) == input2RC.end()) {
			input2RC.insert(pair<int, int>(node2, RCcount++));
		}
		if (paths.size() < RCcount) {
			paths.resize(RCcount);
		}
		if (paths[input2RC.find(node1)->second].size() < RCcount) {
			for (int i = 0; i < paths.size(); i++)
			{
				paths[i].resize(RCcount);
			}
		}
		paths[input2RC.find(node1)->second][input2RC.find(node2)->second] = prob;
	}

	for (auto i = input2RC.begin(); i != input2RC.end(); i++)
	{
		RC2input.insert(pair<int, int>(i->second, i->first));
	}

}

bool comp(pair<string, double> a, pair<string, double> b) {
	bool c = min;
	if (!c) {
		return a.second > b.second;
	}
	else {
		return a.second < b.second;
	}

}

void ini_priQ(vector<pair<string, double>>& vec, vector < vector<double>  > paths) {
	map<string, double> pri_Q;
	for (int i = 0; i < paths.size(); i++)
	{
		for (int j = 0; j < paths[i].size(); j++)
		{
			if (paths[i][j] != 0) {
				pri_Q.insert(pair<string, double>(i2s(i + 1) + ' ' + i2s(j + 1), paths[i][j]));
			}
		}
	}

	for (auto it = pri_Q.begin(); it != pri_Q.end(); it++)
	{
		vec.push_back(pair<string, double>(it->first, it->second));
	}
	sort(vec.begin(), vec.end(), comp);

}

void spanning(vector<pair<string, double>>& priQ, set<string>& F, set<string>& MST) {
	string FirstWord, SecondWord;
	FirstWord = priQ[0].first.substr(0, priQ[0].first.find(" "));
	SecondWord = priQ[0].first.substr(priQ[0].first.find(" ") + 1);
	if (FirstWord == "" || SecondWord == "") {
		cout << "Err";
	}

	for (auto i = F.begin(); i != F.end() ; i++)
	{
		if ((*i).find(FirstWord) != -1 && (*i).find(SecondWord) != -1) {
			priQ.erase(priQ.begin());
			return;
		}
	}
	string tmp1;
	string tmp2;
	set<string>::iterator it1;
	set<string>::iterator it2;
	for (auto i = F.begin(); i != F.end(); i++)
	{

		if ((*i).find(FirstWord) != -1) {
			tmp1 = *i;
			it1 = i;
			continue;
		}
		if ((*i).find(SecondWord) != -1) {
			tmp2 = *i;
			it2 = i;
			continue;
		}

	}
	F.erase(it1);
	F.erase(it2);
	F.insert(tmp1 +" "+ tmp2);

	MST.insert(priQ[0].first);




}

double round(double a) {
	double b = a * 10000 + 0.5;
	return b / 10000;
}

string d2s(double a) {
	string res;
	int b = a * 10000;
	if (b == 0) {
		res = "0";
	}
	else {
		while (b > 0) {
			
			res += b % 10+'0';
			b /= 10;
		}
		reverse(res.begin(), res.end());
	}
	if (res.length() <= 4) {
		while (res.length() < 4) {
			res = "0" + res;
		}
		res = "0." + res;
	}
	else {
		res = res.substr(0, res.length() - 4) + "." + res.substr(res.length() - 4);
	}
	return res;
}

void compute_prob(set<string> MST, vector<pair<string, double>> priQ) {
	double cost = 1;
	for (auto i = MST.begin(); i != MST.end(); i++)
	{
		for (int j = 0; j < priQ.size(); j++)
		{
			if (priQ[j].first == (*i)) {
				cost *= priQ[j].second;
				break;
			}
		}
	}
	if (cost < 0.05) {
		cout << 0;
	}
	else {
		cost = round(cost);
		string result = d2s(cost);
		if (result == "0") {
			
		}
		else {
			int a = result.length() - 1;
			while (result[a] == '0'||result[a]=='.') {
				if (result[a] == '.') {
					result = result.substr(0, a);
					break;
				}
				result = result.substr(0, a--);
			}
		}
		cout << result;
	}
}

int main() {

	vector < vector<double>  > paths;
	map<int, int>input2RC;
	map<int, int>RC2input;
	set<string>F;
	set<string>MST;
	vector<pair<string, double>>priQ;
	ini_paths(input2RC,RC2input,paths, F);
	ini_priQ(priQ, paths);
	vector<pair<string, double>>probs(priQ);
	while (!priQ.empty()) {
		spanning(priQ, F, MST);
	}
	compute_prob(MST, probs);
	return 0;
}