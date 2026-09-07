//
// Created by PC-XX on 6/4/2025.
//

#include "AVL.h"

//Recursive helper to insert a new node in the AVL tree
TreeNode* AVL::insertHelper(TreeNode* node, string name, string id, bool &success) {
    if (node == nullptr) {
        success = true;
        return new TreeNode(name, id);
    }
    if (id == node->id) {
        success = false;
        return node;
    }
    else if (id < node->id)
        node->left = insertHelper(node->left, name, id, success);
    else
        node->right = insertHelper(node->right, name, id, success);
    //Update height and balance:
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);
    //Balance the tree using AVL rotations
    if (balance < -1) {
        if (id < node->right->id) {
            node->right = rotateRight(node->right); //Right-Left case
            return rotateLeft(node);
        }
        else {
            return rotateLeft(node); //Right-Right case
        }
    }
    if (balance > 1) {
        if (id > node->left->id) {
            node->left = rotateLeft(node->left); //Left-Right case
            return rotateRight(node);
        }
        else {
            return rotateRight(node); //Left-Left case
        }
    }
    return node;
}

//Recursive helper to remove a node by ID
TreeNode* AVL::removeHelper(TreeNode* node, string id, bool& success) {
    if (node == nullptr) {
        success = false;
        return nullptr;
    }
    if (id < node->id)
        node->left = removeHelper(node->left, id, success);
    else if (id > node->id)
        node->right = removeHelper(node->right, id, success);
    else {
        success = true;
        //Node has 1 or 0 child
        if (node->left == nullptr || node->right == nullptr) {
            TreeNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        else { //Node has 2 children
            TreeNode* temp = minValue(node->right);
            node->id = temp->id;
            node->name = temp->name;
            node->right = removeHelper(node->right, node->id, success);
        }
    }
    //Update height and balance
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);
    if (balance < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        else {
            return rotateLeft(node);
        }
    }
    if (balance > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else {
            return rotateRight(node);
        }
    }
    return node;
}

//Binary search by ID
TreeNode* AVL::searchIDHelper(TreeNode *node, string id) {
    if (node == nullptr)
        return nullptr;
    if (id == node->id)
        return node;
    else if (id < node->id)
        return searchIDHelper(node->left, id);
    else
        return searchIDHelper(node->right, id);
}

//search name using preorder traversal
void AVL::searchNameHelper(TreeNode* node, const string& name, vector<string>& result) {
    if (node == nullptr)
        return;
    if (name == node->name)
        result.push_back(node->id);
    searchNameHelper(node->left, name, result);
    searchNameHelper(node->right, name, result);
}

//helper for removing the Nth node using inorder traversal (0-based)
TreeNode* AVL::removeInorderHelper(TreeNode *node, int& index, int target, bool& success) {
    if (node == nullptr)
        return nullptr;
    node->left = removeInorderHelper(node->left, index, target, success);
    if (success)
        return node;
    if (index == target) {
        success = true;
        return removeHelper(node, node->id, success);
    }
    index++;
    node->right = removeInorderHelper(node->right, index, target, success);
    if (success) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);
        if (balance < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            else {
                return rotateLeft(node);
            }
        }
        if (balance > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            else {
                return rotateRight(node);
            }
        }
    }
    return node;
}

//inorder traversal helper
void AVL::inorderHelper(TreeNode* node, vector<string>& names) {
    if (node == nullptr)
        return;
    else {
        inorderHelper(node->left, names);
        names.push_back(node->name);
        inorderHelper(node->right, names);
    }
}

//preorder traversal
void AVL::preorderHelper(TreeNode* node, vector<string>& names) {
    if (node == nullptr)
        return;
    else {
        names.push_back(node->name);
        preorderHelper(node->left, names);
        preorderHelper(node->right, names);
    }
}

//postorder traversal
void AVL::postorderHelper(TreeNode* node, vector<string>& names) {
    if (node == nullptr)
        return;
    else {
        postorderHelper(node->left, names);
        postorderHelper(node->right, names);
        names.push_back(node->name);
    }
}

//Returns height of node
int AVL::getHeight(TreeNode* node) {
    if (node == nullptr)
        return -1;
    else
        return node->height;
}

//Returns balance factor of the node
int AVL::getBalanceFactor(TreeNode* node) {
    if (node == nullptr)
        return 0;
    else {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return leftHeight - rightHeight;
    }
}

//left rotation
TreeNode* AVL::rotateLeft(TreeNode* node) {
    TreeNode* grandchild = node->right->left;
    TreeNode* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));
    return newParent;
}

//right rotation
TreeNode* AVL::rotateRight(TreeNode* node) {
    TreeNode* grandchild = node->left->right;
    TreeNode* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));
    return newParent;
}

//helper to traverse to the minimum value node of the tree
TreeNode* AVL::minValue(TreeNode* node) {
    TreeNode* temp = node;
    while (temp && temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

//helper that validates if a name is correctly input (only letters and spaces are accepted)
bool AVL::isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

//helper that validates if an ID is correctly input (they can only be of length 8 and they can only contain digits)
bool AVL::isValidID(const string& id) {
    if (id.length() != 8) {
        return false;
    }
    for (char c : id) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

//Checks if ID is present in the tree
bool AVL::idExists(TreeNode* node, const string& id) {
    if (node == nullptr)
        return false;
    if (id == node->id)
        return true;
    if (id < node->id)
        return idExists(node->left, id);
    else
        return idExists(node->right, id);
}

//deletes tree, this is a helper for the destructor.
void AVL::deleteTree(TreeNode *node) {
    if (node == nullptr)
        return;
    else {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

//Public insert method
bool AVL::insert(string name, string id) {
    bool success = false;
    if (!isValidID(id) || !isValidName(name)) {
        return false;
    }
    root = insertHelper(root, name, id, success);
    return success;
}

//Public remove method
bool AVL::remove(string id) {
    bool success = false;
    if (!isValidID(id)) {
        return false;
    }
    root = removeHelper(root, id, success);
    return success;
}

//Public search ID method.
string AVL::search(string id) {
    TreeNode* found = searchIDHelper(root, id);
    if (found == nullptr)
        return "unsuccessful";
    return found->name;
}

//Public search by name
vector<string> AVL::search(string name, bool isName) {
    vector<string> result;
    if (!isName) {
        TreeNode* found = searchIDHelper(root, name);
        if (found != nullptr)
            result.push_back(found->name);
    }
    else {
        if (!isValidName(name))
            return {"unsuccessful"};
        searchNameHelper(root, name, result);
        if (result.empty())
            result.push_back("unsuccessful");
    }
    return result;
}

//public inorder traversal
vector<string> AVL::printInorder() {
    vector<string> result;
    inorderHelper(root, result);
    return result;
}

//public preorder traversal
vector<string> AVL::printPreorder() {
    vector<string> result;
    preorderHelper(root, result);
    return result;
}

//public postorder traversal
vector<string> AVL::printPostorder() {
    vector<string> result;
    postorderHelper(root, result);
    return result;
}

//public level count
int AVL::printLevelCount() {
    if (root == nullptr)
        return 0;
    else
        return getHeight(root)+1;
}

//public remove using inorder traversal of the Nth node.
bool AVL::removeInorder(int n) {
    int index = 0;
    bool success = false;
    root = removeInorderHelper(root, index, n, success);
    return success;
}

//destructor
AVL::~AVL() {
    deleteTree(root);
}











