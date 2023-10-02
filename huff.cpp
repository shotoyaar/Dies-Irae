#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

#define pqueue(T, cmp) priority_queue<T, vector<T>, decltype(cmp)*>

class MHnode {
    public:
        char data;
        unsigned freq;

        MHnode *left, *right;

        MHnode(char data, unsigned freq) {
            left = right = nullptr;
            this -> data = data;
            this -> freq = freq;
        }
};


auto cmp(MHnode* l, MHnode* r) {
    return (l->freq > r->freq);
}

/*
class Compare {
    public: 

        auto cmp(MHnode* l, MHnode* r) {
            return (l->freq > r->freq);
        }
};


struct compare {
    bool op(const MHnode& l, const MHnode& r) {
        return (l.freq > r.freq);
    }
};
*/

priority_queue<MHnode*, vector<MHnode*>, decltype(cmp)*> MinHeap(cmp);

class Huffmancoding {
    public:
        static map<char, string> codes;

        static void Codes(map<char, int> m1 ,int size) {
            MHnode *left, *right, *top;

            //pqueue(MHnode*, cmp) MinHeap(cmp);

            for (auto it = m1.begin(); it != m1.end(); it++) {
                MinHeap.push(new MHnode(it->first, it->second));
            }

            while (MinHeap.size() != 1) {
                left = MinHeap.top();
                MinHeap.pop();

                right = MinHeap.top();
                MinHeap.pop();

                auto temp = left->freq + right->freq;
                top = new MHnode('$', temp);

                top->left = left;
                top->right = right;
                MinHeap.push(top);
            }
            
            storecodes(MinHeap.top(), "");
        }

        static void printcodes(MHnode* root, string str) {

            if (!root) {
                return;
            }

            if (root->data != '$') {
                cout << root->data << ": " << str << "\n";
            }

            printcodes(root->left, str+"0");
            printcodes(root->right, str+"1");
        }

        static void storecodes(MHnode* root, string str) {

            if (root == NULL) {
                return;
            }
            
            if (root->data != '$') {
                Huffmancoding::codes[root->data] = str;
            }

            storecodes(root->left, str+"0");
            storecodes(root->right, str+"1");
        }

        static string decoding(MHnode* root, string s) {

            string ans = "";
            MHnode* curr = root;

            for (int i= 0; i < s.size(); i++) {
                if (s[i] == '0') {
                    curr = curr->left;
                }

                else {
                    curr = curr->right;
                }

                if (curr->left == NULL && curr->right == NULL) {
                    ans += curr->data;
                    curr = root; 
                }
            }

            return ans + '\0';
        }

        //static void Decoding(MHnode* root);
};

int main() {

    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {6, 8, 10, 21, 54, 75};

    map<char, int> dataset;

    int l1 = sizeof(data)/sizeof(data[0]);
    int l2 = sizeof(freq)/sizeof(freq[0]);

    if (l1 == l2) {
        for (int i= 0; i < l1; i++) {
            dataset[data[i]] = freq[i];
        }
    } 
    else {
        cout << "Invalid";
    }

    Huffmancoding::Codes(dataset, l1);

    cout << "Characters with their frequencies: " << "\n";

    for (auto it2 = Huffmancoding::codes.begin(); it2 != Huffmancoding::codes.end(); it2++) {
        cout << it2->first << ": " << it2->second << "\n";
    }

    return 0;
}