#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>

#define MIN_FREQ 10
#define SAFE 5

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

        static void alert(map<char, int> m1, map<char, int> avg, int size) {
            vector<char> restock;

            for (auto it1 = m1.begin(), it2 = avg.begin(); it1 != m1.end(), it2 != avg.end(); it1++, it2++) {
                if (((it1->second - it2->second) <= 0) || ((it1->second - it2->second) <= MIN_FREQ)) {
                    restock.push_back(it1->first);
                }
            }

            cout << "The following elements need to be restocked!" << "\n";

            for (int i= 0; i < restock.size(); i++) {
                cout << restock[i] << "\n";
            }

            cout << "Would you like to restock them right now?" << "\n" << "Answer 1 if yes, 0 if no." << "\n";
            int temp;
            cin >> temp;

            if (temp == 1) {
                Huffmancoding::restock(m1, avg, size);
            }

            else {
                cout << "Thankyou" << "\n";
            }
        }

        static void restock(map<char, int> m1, map<char, int> avg, int size) {
            for (auto it1 = m1.begin(), it2 = avg.begin(); it1 != m1.end(), it2 != avg.end(); it1++, it2++) {
                if (((it1->second - it2->second) <= 0) || ((it1->second - it2->second) <= MIN_FREQ)) {
                    it1->second = it1->second + (MIN_FREQ*SAFE);
                }
            }

            Huffmancoding::Codes(m1, size);
        }
};

map<char, string> Huffmancoding::codes = {}; //Initialise the map for the codes of the characters

int main() {

    map<char, int> dataset; //Frequency table that is represented as a map.
    map<char, int> avgdata; //Frequency table of average usage of all the elements that exist in the actual dataset.

    
    int size; //Size of frequency table (no. of rows)
    cout << "Enter size of frequency table: " << "\n";
    cin >> size;

    cout << "Enter details of the main frequency table" << "\n";

    for (int i= 0; i < size; i++) {
        char temp;
        int temp2;
        cout << "Enter name and frequency of element " << i+1 << "\n";
        cin >> temp >> temp2;

        dataset.insert({temp, temp2});
    }

    cout << "Enter average usage of each element" << "\n";

    for (auto it = dataset.begin(); it != dataset.end(); it++) {
        int temp;
        cout << "Enter avg usage of " << it->first << "\n";
        cin >> temp;

        avgdata.insert({it->first, temp});
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

    cout << "Would you like to check if the current stocks are enough?" << "\n" << "Answer 1 if yes, 0 if no." << "\n";
    int ip;
    cin >> ip;

    if (ip == 1) {
        Huffmancoding::alert(dataset, avgdata, size);
    }

    else cout << "Thankyou" << "\n";

    return 0;
}