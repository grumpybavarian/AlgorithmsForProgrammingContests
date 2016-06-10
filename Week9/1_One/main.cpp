//Code used from: https://gist.github.com/reterVision/8487831
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    char ch;
    map<char, Node*> children;
    bool isEnd;
};

class Trie {
public:
    Trie() { head.ch = -1; };
    ~Trie();
    
    void insert(string word);
    int countRenames();
    
protected:
    Node head;
    // Keep all newly created node in an array, for the ease of
    // memory release.
    vector<Node*> children;
};

Trie::~Trie() {
    for (int i=0; i<children.size(); ++i) {
        delete children[i];
    }
}


void Trie::insert(string word) {
    map<char, Node*> *current_tree = &head.children;
    map<char, Node*>::iterator it;
    
    for (int i=0; i<word.length(); ++i) {
        char ch = word.at(i);
        
        if ((it = current_tree->find(ch)) != current_tree->end()) {
            if (i == word.length()-1) {
                it->second->isEnd = true;
            }
            current_tree = &it->second->children;
            continue;
        }
        
        if (it == current_tree->end()) {
            // Display inserting position in the tree, for debug use
            //
            // cout << "Inserting " << ch << endl;
            // cout << "on layer " << endl;
            // map<char, Node*>::iterator temp = current_tree->begin();
            // for (; temp != current_tree->end(); ++temp)
            //   cout << temp->first << endl;
            
            Node* new_node = new Node();
            new_node->ch = ch;
            new_node->isEnd = (i == word.length()-1);
            (*current_tree)[ch] = new_node;
            
            // For continuous inserting a word.
            current_tree = &new_node->children;
            
            // For the ease of memory clean up.
            children.push_back(new_node);
        }
    }
}

int Trie::countRenames() {
    int toRename = 0;
    stack<Node*> s;
    s.push(&head);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        for (map<char, Node*>::iterator it=curr->children.begin(); it!=curr->children.end(); ++it) {
            s.push(it->second);
        }
        if (curr->isEnd && !curr->children.empty()) ++toRename;
    }
    
    return toRename;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
       	int n;
        cin >> n;
        vector<string> names(n);
        for (int i=0; i<n; ++i) {
            string s;
            cin >> names[i];
        }
        Trie trie;
        for (int i=0; i<n; ++i) {
            trie.insert(names[i]);
        }
        
        cout << "Case #" << ti << ": " << trie.countRenames()-1 << "\n";
    }
    return 0;
}

/*
 1
 7
 Bob
 Bobby
 Boba
 Charles
 Charly
 Julia
 Julian
 */
/*
 7
 4
 Bfugw
 Ksdb
 Ctg
 Bfug
 3
 Pgqh
 Mlvo
 Pgqhzot
 7
 Opmp
 Faokkia
 Fao
 Opmpn
 Qkqv
 Qewyu
 Faos
 3
 Ct
 Qxhu
 Qxhuzr
 8
 Olp
 Wafgmp
 Olpt
 Wafgm
 Olpv
 Wbgl
 Wbglhlq
 Waf
 4
 Alna
 Al
 Nl
 Mmybw
 8
 Wlyppv
 Etdtfz
 Wl
 Wly
 Etdtf
 Etdtfzu
 Spwaw
 Aogja
 */
/*
 b
 o
 b
 a
 b
 y
 c
 h
 a
 r
 l
 e
 s
 y
 j
 u
 l
 i
 a
 n
 */