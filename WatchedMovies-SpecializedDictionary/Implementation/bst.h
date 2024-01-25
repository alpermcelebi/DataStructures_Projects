#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.

    
    void delete_nodes(TreeNode* node) {
        if (node != NULL) {
            delete_nodes(node->left);
            delete_nodes(node->right);

            delete node;
        }
    }

    void remove(TreeNode *& current, std::string value) {
        if (current == NULL) return;
        int comparison = current->key.compare(value);
        if(comparison < 0) {
            remove(current->right, value);
        }
        else if(comparison > 0) {
            remove(current->left, value);
        }
        else{
            if(current->left != NULL && current->right != NULL) {
                current->key = getMin(current->right);
                remove(current->right, current->key);
            }
            else {
                TreeNode* oldnode = current;
                current = (current->left != NULL) ? current->left : current->right;
                delete oldnode;
            }
        }
    }
    
    std::string getMin(TreeNode* r){
        if(r->left == NULL) return r->key;
        return getMin(r->left);
    }
    

    void tree2vector(TreeNode* node, vector<TreeNode>& result) {
        if(node != NULL) {
            tree2vector(node->left, result);
            result.push_back(*node);
            tree2vector(node->right, result);
        }
        return;
    }

    vector<TreeNode> mergeVectors(const vector<TreeNode>& vector1, const vector<TreeNode>& vector2) {
        vector<TreeNode> mergedVector;
        size_t i = 0, j = 0;

        while (i < vector1.size() && j < vector2.size()) {
            if (vector1[i].key < vector2[j].key) {
                mergedVector.push_back(vector1[i]);
                ++i;
            } else {
                mergedVector.push_back(vector2[j]);
                ++j;
            }
        }

        
        while (i < vector1.size()) {
            mergedVector.push_back(vector1[i]);
            ++i;
        }

        while (j < vector2.size()) {
            mergedVector.push_back(vector2[j]);
            ++j;
        }

        return mergedVector;
    }

    vector<TreeNode> find_intersection(const vector<TreeNode>& vector1, const vector<TreeNode>& vector2) {
        vector<TreeNode> intersected;
        size_t i = 0, j = 0;

        while (i < vector1.size() && j < vector2.size()) {
            int comparison = (vector1[i].key).compare(vector2[j].key);
            if (comparison == 0) {
                intersected.push_back(vector1[i]);
                ++i;
                ++j;
            } 
            else if (comparison < 0) {
                ++i;
            } 
            else {
                ++j;
            }
        }

        return intersected;
    }

};

    
    template <class T>
    BST<T>::BST() : root(NULL) {}

    
    template <class T>
    BST<T>::~BST() {
        delete_nodes(root);
    }

    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
        TreeNode* newNode = new TreeNode(key, value);

        if (root == NULL) {
            root = newNode;
            return *this;
        }

        TreeNode* current = root;
        TreeNode* parent = NULL;

        while (current != NULL) {
            parent = current;

            int comparison = current->key.compare(key);

            if (comparison < 0) {
                current = current->right;
            } else if (comparison > 0) {
                current = current->left;
            } else {
                delete newNode; 
                return *this;
            }
        }

        
        int comparison = parent->key.compare(key);
        if (comparison < 0) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }

        return *this;
    }

    
    
    template <class T>
    bool BST<T>::search(std::string value) const {
        TreeNode* current = root;

        if(current == NULL) return false;
        
        while(current != NULL) {
            int comparison = current->key.compare(value);

            if (comparison == 0) return true;
            else if(comparison < 0 && current != NULL) current = current->right;
            else if(comparison > 0 && current != NULL) current = current->left;
        }

        return false;
        
    }

    
    
    
    template <class T>
    void BST<T>::remove(std::string key) {
        remove(root, key);
    }   
    
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(root,result);
        return result;
    }
    
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
        BST<T>* ret_bst = new BST<T>();

        
        vector<TreeNode> vector1 = tree2vector(root);
        vector<TreeNode> vector2 = bst->tree2vector(bst->getRoot());

        std::vector<TreeNode> mergedVector = mergeVectors(vector1, vector2);

        for (size_t k = 0; k < mergedVector.size(); ++k) {
            const TreeNode& node = mergedVector[k];
            ret_bst->insert(node.key, node.data);
        }

        return ret_bst;
        
    }
        
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
        BST<T>* ret_bst = new BST<T>();

        vector<TreeNode> vector1 = tree2vector(root);
        vector<TreeNode> vector2 = bst->tree2vector(bst->getRoot());

        vector<TreeNode> intersected = find_intersection(vector1, vector2);

        for (int k = 0; k < intersected.size(); k++) {
            const TreeNode& node = intersected[k];
            ret_bst->insert(node.key, node.data);
        }

        return ret_bst;
    }

    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }


