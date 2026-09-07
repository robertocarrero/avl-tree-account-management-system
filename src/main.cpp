#include <iostream>
#include <string>
#include <regex>
#include "AVL.h"

using namespace std;

int main(){
	AVL tree;
	int n;
	cin >> n;
	cin.ignore();
	regex insertRegex("^insert\\s+\"([A-Za-z\\s]+)\"\\s+([0-9]{8,8})$");
	regex removeRegex("^remove\\s+([0-9]{8,8})$");
	regex searchIDRegex("^search\\s+([0-9]{8,8})$");
	regex searchNameRegex("^search\\s+\"([A-Za-z\\s]+)\"$");
	regex removeInorderRegex("^removeInorder\\s+([0-9]+)$");

	for (int i = 0; i < n; i++) {
		string line;
		getline(cin, line);
		smatch match;
		if (regex_match(line, match, insertRegex)) {
			string name = match[1];
			string id = match[2];
			cout << (tree.insert(name, id) ? "successful" : "unsuccessful") << endl;
		}
		else if (regex_match(line, match, removeRegex)) {
			string id = match[1];
			cout << (tree.remove(id) ? "successful" : "unsuccessful") << endl;
		}
		else if (regex_match(line, match, searchIDRegex)) {
			string id = match[1];
			string result = tree.search(id);
			if (result == "unsuccessful") {
				cout << "unsuccessful" << endl;
			}
			else {
				cout << result << endl;
			}
		}
		else if (regex_match(line, match, searchNameRegex)) {
			string name = match[1];
			vector<string> result = tree.search(name, true);
			if (result.size() == 1 && result[0] == "unsuccessful") {
				cout << "unsuccessful" << endl;
			}
			else {
				for (const string& id : result) {
					cout << id << endl;
				}
			}
		}
		else if (line == "printPreorder") {
			vector<string> result = tree.printPreorder();
			for (int j = 0; j < result.size(); j++) {
				cout << result[j];
				if (j != result.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else if (line == "printInorder") {
			vector<string> result = tree.printInorder();
			for (int j = 0; j < result.size(); j++) {
				cout << result[j];
				if (j != result.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else if (line == "printPostorder") {
			vector<string> result = tree.printPostorder();
			for (int j = 0; j < result.size(); j++) {
				cout << result[j];
				if (j != result.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else if (line == "printLevelCount") {
			cout << tree.printLevelCount() << endl;
		}
		else if (regex_match(line, match, removeInorderRegex)) {
			int index = stoi(match[1]);
			cout << (tree.removeInorder(index) ? "successful" : "unsuccessful") << endl;
		}
		else {
			cout << "unsuccessful" << endl;
		}
	}
	return 0;
}
