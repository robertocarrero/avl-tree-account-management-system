
#ifndef AVL_H
#define AVL_H


#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;
class TreeNode {
  public:
    string name;
    string id;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(const string& n, const string& i) : name(n), id(i), left(nullptr), right(nullptr), height(0) {}
};

class AVL {
    TreeNode* root;
    TreeNode* insertHelper(TreeNode* node, string name, string id, bool& success);
    TreeNode* removeHelper(TreeNode* node, string id, bool& success);
    TreeNode* searchIDHelper(TreeNode* node, string id);
    void searchNameHelper(TreeNode* node, const string& name, vector<string>& result);
    TreeNode* removeInorderHelper(TreeNode* node, int& index, int target, bool& success);
    void inorderHelper(TreeNode* node, vector<string>& names);
    void preorderHelper(TreeNode* node, vector<string>& names);
    void postorderHelper(TreeNode* node, vector<string>& names);
    int getHeight(TreeNode* node);
    int getBalanceFactor(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* minValue(TreeNode* node);
    bool isValidName(const string& name);
    bool isValidID (const string& id);
    bool idExists(TreeNode* node, const string& id);
    void deleteTree(TreeNode* node);



  public:
    AVL() : root(nullptr) {}
    ~AVL();

    bool insert(string name, string id);
    bool remove(string id);
    string search(string id);
    vector<string> search(string name, bool isName);
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();
    int printLevelCount();
    bool removeInorder(int n);
};
#endif //AVL_H
