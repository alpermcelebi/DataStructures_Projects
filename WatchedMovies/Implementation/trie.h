#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.

    

    
    void deleteTrieNode(TrieNode* node) {
        if (node == NULL) {
            return;
        }

        for (int k = 0; k < 128; k++) {
            deleteTrieNode(node->children[k]);
        }

        
        delete node->data;
        delete node;
    }
    
    void fsw_rec_helper(TrieNode* node, const std::string& temp_key, std::vector<T*> &results) {
        if(node == NULL) return;
        else if(node->isEndOfKey) results.push_back(node->data);
        int i = 0;
        while(i < 128) {
            if(node->children[i]) fsw_rec_helper(node->children[i], temp_key + (char) i, results);
            i++;
        }
        return;
    }
    
    
    void wildcard_helper(TrieNode* node, const std::string &wildcardKey, const std::string &currentKey, size_t wildcard_index, std::vector<T*> &results) {
        if (!node) {
            return;
        }
    
        if (wildcard_index == wildcardKey.size()) {
            if (node->isEndOfKey) {
                results.push_back(node->data);
            }
            return;
        }
    
        char currentChar = wildcardKey[wildcard_index];
    
        if (currentChar == '*') {
            
            wildcard_helper(node, wildcardKey, currentKey, wildcard_index + 1, results);
    
            for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    wildcard_helper(node->children[i], wildcardKey, currentKey + (char) i, wildcard_index, results);
                }
            }
        } else if (currentChar == '?') {
            
            for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    wildcard_helper(node->children[i], wildcardKey, currentKey + (char) i, wildcard_index + 1, results);
                }
            }
        } else {
           
            int index = (int) currentChar;
            if (node->children[index]) {
                wildcard_helper(node->children[index], wildcardKey, currentKey + currentChar, wildcard_index + 1, results);
            }
        }
    }





    
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    deleteTrieNode(root);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {

    TrieNode* temp = root;
   

    for (int i = 0; i < key.length(); ++i) {
        char c = key[i];
        int ind = (int) c;
        if (temp->children[ind] == NULL) {
            temp->children[ind] = new TrieNode(c);
        }
        
        temp = temp->children[ind];
    }
    
    
    temp->isEndOfKey = true;
    temp->data = new T(key);
    
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    int check = 1;
    for(int i = 0; i < 128; i++) {
        if(root->children[i] != NULL){
            check = 0;
            break;
        } 
    }
    if(check == 0){
        TrieNode* temp = root;
    
        for (int i = 0; i < username.length(); ++i) {
            char c = username[i];
            int ind = (int) c;
            if (!temp->children[ind]) {
                return NULL;
            }
            temp = temp->children[ind];
        }
    
        if (temp->isEndOfKey) {
            return temp->data;
        }
    }
    return NULL;
   
}

template <class T>
void Trie<T>::remove(std::string username) {
    TrieNode* temp = root;

    for (int i = 0; i < username.length(); ++i) {
        char c = username[i];
        int ind = (int) c;
        if (!temp->children[ind]) {
            return;
        }
        temp = temp->children[ind];
    }

    if (temp->isEndOfKey) {
        temp->isEndOfKey = false;
    }
}


template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
    TrieNode* temp = root;
    for(int i = 0; i < prefix.length(); i++) {
        char c = prefix[i];
        int ind = (int) c;
        if(temp->children[ind] == NULL) return;
        temp = temp->children[ind];
    }
    
    
    fsw_rec_helper(temp, prefix, results);

    
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    
    wildcard_helper(root, wildcardKey, "", 0, results);
    
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + (char) i);
        }
    }
}

