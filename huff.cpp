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


priority_queue<MHnode*, vector<MHnode*>, decltype(cmp)*> MinHeap(cmp); // creation of priority queue for sorting
                                                                        // elements based on frequency

class Huffmancoding {
    public:
        static map<char, string> codes;

        //function creates a binary tree from the frequency table
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

        //function prints codes of the elements
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

        //function stores the binary tree encode of the elements
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
        cout << "Enter name and frequency of element" << i+1 << "\n";
        cin >> temp >> temp2;

        dataset.insert({temp, temp2});

    }
    
    /*
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    */

    // binary tree formation of the given data
    Huffmancoding::Codes(dataset, size);

    cout << "Original Frequency Table: " << "\n";

    //printing the original frequency table. auto is a variable type
    //that can take any datatype
    
    for (auto it3 = dataset.begin(); it3 != dataset.end(); it3++) {
        cout << it3->first << ": " << it3->second << "\n";
    }

    cout << "Encoded Frequency Table: " << "\n";

    for (auto it2 = Huffmancoding::codes.begin(); it2 != Huffmancoding::codes.end(); it2++) {
        cout << it2->first << ": " << it2->second << "\n";
    }

    return 0;
}
