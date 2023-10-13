#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

//#define pqueue(T, cmp) priority_queue<T, vector<T>, decltype(cmp)>

//Definition of the node of the huffman tree.
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

//compare function for the priority minheap queue
bool cmp(MHnode* l, MHnode* r) {
    return (l->freq > r->freq);
}


priority_queue<MHnode*, vector<MHnode*>, decltype(cmp)*> MinHeap(cmp);

class Huffmancoding {
    public:
        static map<char, string> codes;

        static void Codes(map<char, int> m1 ,int size) {
            MHnode *left, *right, *top;

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

map<char, string> Huffmancoding::codes = {}; //Initialise the map for the codes of the characters

int main() {

    map<char, int> dataset; //Frequency table that is represented as a map.

    int size; //Size of frequency table (no. of rows)
    cout << "Enter size of frequency table: " << "\n";
    cin >> size;

    for (int i= 0; i < size; i++) {
        char temp;
        int temp2;
        cout << "Enter element " << i+1 << "\n";
        cin >> temp;
        cout << "Enter frequency of element " << i+1 << "\n";
        cin >> temp2;

        dataset.insert({temp, temp2});

    }


    Huffmancoding::Codes(dataset, size);

    cout << "Original Frequency Table: " << "\n";

    for (auto it3 = dataset.begin(); it3 != dataset.end(); it3++) {
        cout << it3->first << ": " << it3->second << "\n";
    }

    cout << "Encoded Frequency Table: " << "\n";

    for (auto it2 = Huffmancoding::codes.begin(); it2 != Huffmancoding::codes.end(); it2++) {
        cout << it2->first << ": " << it2->second << "\n";
    }

    return 0;
}