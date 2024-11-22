#include "main.h"
#define ll long long

int MAXSIZE = 0;
class HUFFMAN_TREE;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class ADMIN; //

class HUFFMAN_TREE
{
    class Node;

private:
    Node *root = nullptr;

public:
    ~HUFFMAN_TREE()
    {
        DELETE(root);
    }
    void DELETE(Node *node)
    {
        if (node)
        {
            DELETE(node->left);
            DELETE(node->right);
            delete node;
        }
    }
    bool compare1(pair<char, int> a, pair<char, int> b)
    {
        // So sánh theo giảm dần của giá trị thứ hai (second)
        if (a.second != b.second)
        {
            return a.second > b.second;
        }

        if (a.first >= 'a' && b.first >= 'a')
        {
            return a.first > b.first;
        }
        else if (a.first < 'a' && b.first < 'a')
        {
            return a.first > b.first;
        }
        else
        {
            return a.first < 'a';
        }
    }

    char caesarCipherEncrypt(char ch, int &shift)
    {
        int base;
        if (ch >= 97 && ch <= 122)
        {
            base = 97;
        }
        else if (ch >= 65 && ch <= 90)
        {
            base = 65;
        }
        else
        {
            return ch;
        }

        return static_cast<char>((ch - base + shift) % 26 + base);
    }

    void encodeWithCaesarCipher(vector<pair<char, int>> &freq_prev, string &name)
    {
        for (char &c : name)
        {
            for (pair<char, int> i : freq_prev)
            {
                if (i.first == c)
                {
                    c = caesarCipherEncrypt(c, i.second);
                    break;
                }
            }
        }
        for (pair<char, int> &i : freq_prev)
        {
            i.first = caesarCipherEncrypt(i.first, i.second);
        }
    }

    vector<pair<char, int>> accumulateFrequency(vector<pair<char, int>> &freq_prev)
    {
        map<char, int> freq_map;

        // Tích hợp tần suất của các ký tự giống nhau
        for (const auto &c : freq_prev)
        {
            freq_map[c.first] += c.second;
        }

        // Cập nhật freq_prev dựa trên tần suất mới tính toán
        freq_prev.clear();
        for (const auto &c : freq_map)
        {
            freq_prev.emplace_back(c.first, c.second);
        }
        return freq_prev;
    }
    int partition(vector<pair<char, int>> &freq, int low, int high)
    {
        pair<char, int> pivot = freq[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (compare1(freq[j], pivot))
            {
                i++;
                swap(freq[i], freq[j]);
            }
        }

        swap(freq[i + 1], freq[high]);
        return i + 1;
    }

    void quickSort(vector<pair<char, int>> &freq, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(freq, low, high);

            quickSort(freq, low, pi - 1);
            quickSort(freq, pi + 1, high);
        }
    }

    void sortCaesar(vector<pair<char, int>> &freq)
    {
        int n = freq.size();
        quickSort(freq, 0, n - 1);
    }
    vector<pair<char, int>> stringName_Customer(string &name)
    {
        // 1
        unordered_map<char, int> frequent_map;
        for (char i : name)
        {
            frequent_map[i]++;
        }
        vector<pair<char, int>> freq_prev(frequent_map.begin(), frequent_map.end());
        if (freq_prev.size() < 3)
            return {

            };
        // 2
        encodeWithCaesarCipher(freq_prev, name);
        // 3 tich hop tan so
        vector<pair<char, int>> freq;
        freq = accumulateFrequency(freq_prev);
        // 4 sort
        sortCaesar(freq);
        return freq;
    }

    int getHeightRec(Node *&root)
    {
        if (!root)
            return 0;

        int leftHeight = getHeightRec(root->left);
        int rightHeight = getHeightRec(root->right);

        if (leftHeight > rightHeight)
            return 1 + leftHeight;
        else
            return 1 + rightHeight;
    }

    int getBalance(Node *&root)
    {
        if (!root)
            return 0;
        return getHeightRec(root->left) - getHeightRec(root->right);
    }
    Node *rotateLeft(Node *&root)
    {
        if (!root)
            return nullptr;
        Node *newRoot = root->right;
        Node *newRootLeftSubTree = newRoot->left;
        newRoot->left = root;
        root->right = newRootLeftSubTree;
        return newRoot;
    }
    Node *rotateRight(Node *&root)
    {
        if (!root)
            return nullptr;
        Node *newRoot = root->left;
        Node *newRootRightSubTree = newRoot->right;
        newRoot->right = root;
        root->left = newRootRightSubTree;
        return newRoot;
    }
    bool balanceNode(Node *&root, int &count)
    {
        if (!root)
        {
            return false;
        }

        int balance = getBalance(root);

        if (balance > 1)
        {
            if (getBalance(root->left) >= 0)
            {
                count++;
                root = rotateRight(root);
                return true;
            }
            else
            {
                root->left = rotateLeft(root->left);
                count++;
                if (count >= 4)
                {
                    return true;
                }
                root = rotateRight(root);
                return true;
            }
        }
        else if (balance < -1)
        {
            if (getBalance(root->right) <= 0)
            {
                count++;
                root = rotateLeft(root);
                return true;
            }
            else
            {
                root->right = rotateRight(root->right);
                count++;
                if (count >= 4)
                {
                    return true;
                }
                root = rotateLeft(root);
                return true;
            }
        }

        return false;
    }

    Node *balanceTree(Node *node, int count = 0)
    {
        if (node == nullptr)
            return node;
        if (count == 1)
            return node;
        bool balanced = false;
        do
        {
            balanced = balanceNode(node, count);
        } while (balanced);
        node->left = balanceTree(node->left, count);
        node->right = balanceTree(node->right, count);
        return node;
    }

    Node *mergeNodes(vector<Node *> &build)
    {
        Node *newNode = nullptr;

        Node *smallest = build[build.size() - 1];
        Node *secondSmallest = build[build.size() - 2];
        // DELETE the last two elements
        build.pop_back();
        build.pop_back();
        newNode = new Node(smallest->weight + secondSmallest->weight, '\0', smallest, secondSmallest);
        newNode = balanceTree(newNode);
        newNode = balanceTree(newNode);
        newNode = balanceTree(newNode);

        return newNode;
    }

    Node *buildHuff(vector<pair<char, int>> freq)
    {
        vector<Node *> build;
        for (pair<char, int> c : freq)
        {
            build.push_back(new Node((char)c.second, (int)c.first));
        }
        Node *newNode = nullptr;
        while (build.size() > 1)
        {
            newNode = mergeNodes(build);
            int index = 0;
            while (index < (int)build.size())
            {
                if (build[index]->weight <= newNode->weight)
                    break;
                index++;
            }
            build.insert(build.begin() + index, newNode);
        }
        return build[0];
    }

    void helpEncodingHuffman(vector<string> &encoding, Node *&root, string s = "")
    {
        if (root->isChar())
        {
            encoding[root->c] = s;
            return;
        }

        if (root->left)
            helpEncodingHuffman(encoding, root->left, s + "0");
        if (root->right)
            helpEncodingHuffman(encoding, root->right, s + "1");
    }

    int encodeBinaryToDecimal(string binary) // For encode hufffman3
    {
        int result = 0;
        for (int i = 0; i < (int)binary.size(); ++i)
        {
            if (i >= 10)
                break;
            result = (result << 1) | (binary[i] - '0');
        }
        return result;
    }
    void reverseString(string &str)
    {
        int start = 0;
        int end = str.size() - 1;

        while (start < end)
        {
            swap(str[start], str[end]);
            ++start;
            --end;
        }
    }
    int encodingHuffman(Node *root, string nameCaesar)
    {
        if (!root->left && !root->right)
            return 0;

        vector<string> enCode(256, "");
        helpEncodingHuffman(enCode, root);

        //  binary off HuffmanTree
        string binaryString = "";
        for (char c : nameCaesar)
        {
            binaryString = binaryString + enCode[c];
        }
        reverseString(binaryString);

        //  Mã hóa binary->decimal (10 bits đầu phải sang trái)
        int result = 0;
        result = encodeBinaryToDecimal(binaryString);
        return result;
    }

    int encode(string name)
    {
        vector<pair<char, int>> freq = this->stringName_Customer(name);
        if (freq.size() == 0)
            return -1;
        this->DELETE(root);
        root = this->buildHuff(freq);
        if (!root->left && !root->right)
            return 0;
        int result = this->encodingHuffman(root, name);
        return result;
    }

    void helpPrint(Node *node)
    {
        if (!node)
            return;
        helpPrint(node->left);
        if (node->c == '\0')
            solution << node->weight << "\n";
        else
            solution << node->c << "\n";
        helpPrint(node->right);
    }
    void helpHAND_print()
    {
        helpPrint(root);
    }

private:
    class Node
    {
    public:
        int weight;
        char c;
        Node *left;
        Node *right;
        friend class HUFFMAN_TREE;

    public:
        Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
        bool isChar() const { return c != '\0'; } // ktra ký tự
    };
};
class RESTAURANT_Gojo
{
    class BinarySearchTree;

private:
    vector<BinarySearchTree> AREA;

public:
    RESTAURANT_Gojo() : AREA(MAXSIZE + 1) {}
    void insertAREA(int result)
    {
        int ID = result % MAXSIZE + 1;
        AREA[ID].insert(result);
    }
    void DELETE_KOKUSEN()
    {

        for (int i = 1; i <= MAXSIZE; ++i)
            AREA[i].DELETE();
    }

    void helpLIMITLESS(int number)
    {
        if (number <= 0 || number > MAXSIZE)
            return;
        AREA[number].print();
    }

private:
    class BinarySearchTree
    {
        class Node;

    private:
        Node *root;
        queue<int> QUEUE;

    public:
        BinarySearchTree()
        {
            this->root = nullptr;
        }
        ~BinarySearchTree()
        {
            while (!QUEUE.empty())
            {
                int qFront = QUEUE.front();
                QUEUE.pop();
                root = helpDELETE(root, qFront);
            }
        }
        int size()
        {
            return QUEUE.size();
        }
        Node *helpInsert(Node *node, int result)
        {
            if (!node)
            {
                QUEUE.push(result);
                return new Node(result);
            }
            if (result < node->result)
                node->left = helpInsert(node->left, result);
            else
                node->right = helpInsert(node->right, result);
            return node;
        }
        void insert(int result)
        {
            root = helpInsert(root, result);
        }

        Node *helpDELETE(Node *node, int result)
        {
            if (!node)
                return nullptr;
            else if (result < node->result)
                node->left = helpDELETE(node->left, result);
            else if (result > node->result)
                node->right = helpDELETE(node->right, result);
            else
            {
                if (!node->left && !node->right)
                {
                    delete node;
                    return nullptr;
                }
                else if (!node->left)
                {
                    Node *tmp = node->right;
                    delete node;
                    return tmp;
                }
                else if (!node->right)
                {
                    Node *tmp = node->left;
                    delete node;
                    return tmp;
                }
                else
                {
                    Node *tmp = node->right;
                    while (true)
                    {
                        if (!tmp->left)
                            break;
                        tmp = tmp->left;
                    }
                    swap(node->result, tmp->result);
                    node->right = helpDELETE(node->right, tmp->result);
                }
            }
            return node;
        }
        int CountNode(Node *root)
        {
            if (!root)
            {
                return 0;
            }

            int count = 0;
            stack<Node *> nodeStack;
            nodeStack.push(root);

            while (!nodeStack.empty())
            {
                Node *current = nodeStack.top();
                nodeStack.pop();
                ++count;

                if (current->right)
                {
                    nodeStack.push(current->right);
                }

                if (current->left)
                {
                    nodeStack.push(current->left);
                }
            }

            return count;
        }
        unsigned ll combination(int r, int n)
        {
            if (r > n)
            {
                return 0;
            }
            vector<vector<unsigned ll>> pascal(n + 1, vector<unsigned ll>(n + 1, 0));
            for (int i = 0; i <= n; ++i)
            {
                pascal[i][0] = 1;
                for (int j = 1; j <= i; ++j)
                {
                    pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
                }
            }

            return pascal[n][r] % MAXSIZE;
        }
        unsigned ll DFS(Node *node)
        {
            if (!node)
                return 1;
            unsigned ll left = CountNode(node->left);
            unsigned ll right = CountNode(node->right);
            return (combination(left, left + right) * DFS(node->left) * DFS(node->right)) % MAXSIZE;
        }
        void DELETE()
        {
            if (QUEUE.empty())
                return;

            unsigned ll n = DFS(root) % MAXSIZE;

            while (!QUEUE.empty())
            {
                if (n == 0)
                    break;
                int qFront = QUEUE.front();
                QUEUE.pop();
                root = helpDELETE(root, qFront);
                n--;
            }
        }
        void helpPrint(Node *node)
        {
            if (node)
            {
                helpPrint(node->left);
                solution << node->result << "\n";
                helpPrint(node->right);
            }
        }
        void print()
        {
            helpPrint(root);
        }

    private:
        class Node
        {
        private:
            int result;
            Node *left;
            Node *right;
            friend class BinarySearchTree;

        public:
            Node(int result) : result(result), left(nullptr), right(nullptr) {}
        };
    };
};

class RESTAURANT_Sukuna
{
    class Node;

private:
    vector<Node *> AREA;
    list<Node *> LRU;

private:
    bool Compare(int index1, int index2)
    {
        auto it1 = find(LRU.begin(), LRU.end(), AREA[index1]);
        auto it2 = find(LRU.begin(), LRU.end(), AREA[index2]);

        int order1 = -1;
        int order2 = -1;

        if (it1 != LRU.end())
        {
            order1 = distance(LRU.begin(), it1);
        }

        if (it2 != LRU.end())
        {
            order2 = distance(LRU.begin(), it2);
        }

        return (order1 < order2);
    }
    void reHeapDown(int index)
    {

        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        int sizeArea = AREA.size();
        // Compare left child with current smallest
        if (left < sizeArea)
        {
            if (AREA[left]->sizeList() < AREA[smallest]->sizeList())
            {
                smallest = left;
            }
            else if (AREA[left]->sizeList() == AREA[smallest]->sizeList())
            {
                if (Compare(smallest, left))
                {
                    smallest = left;
                }
            }
        }

        // Compare right child with current smallest
        if (right < sizeArea)
        {
            if (AREA[right]->sizeList() < AREA[smallest]->sizeList())
            {
                smallest = right;
            }
            else if (AREA[right]->sizeList() == AREA[smallest]->sizeList())
            {
                if (Compare(smallest, right))
                {
                    smallest = right;
                }
            }
        }

        // If the smallest is not the current index, swap and continue reheapify
        if (smallest != index)
        {
            swap(AREA[smallest], AREA[index]);
            reHeapDown(smallest);
        }
    }

    void reHeapUp(int index)
    {

        while (true)
        {
            if (index <= 0)
                break;
            int parent = (index - 1) / 2;
            if (AREA[parent]->sizeList() > AREA[index]->sizeList())
            {
                swap(AREA[parent], AREA[index]);
                index = parent;
            }
            else
                break;
        }
    }
    void moveToTop(Node *node)
    {
        auto it = LRU.begin();
        while (it != LRU.end() && *it != node)
        {
            if (*it == node)
                break;
            ++it;
        }
        if (it != LRU.end())
        {
            LRU.erase(it);
        }

        LRU.push_front(node);
    }
    void DELETENode(Node *node)
    {
        auto it = LRU.begin();
        while (it != LRU.end())
        {
            if (*it == node)
                break;
            ++it;
        }
        LRU.erase(it);
    }

public:
    RESTAURANT_Sukuna() {}
    ~RESTAURANT_Sukuna()
    {

        for (int i = 0; i < (int)AREA.size(); i++)
        {
            delete AREA[i];
        }
    }

    void insertAREA(int result)
    {
        int ID = result % MAXSIZE + 1;
        int index = -1;
        int size = AREA.size();
        for (int i = 0; i < size; ++i)
        {
            if (index == -1 && ID == AREA[i]->ID)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            AREA.push_back(new Node(ID));

            index = AREA.size() - 1;
            AREA[index]->insert(result);
            this->moveToTop(AREA[index]);
            this->reHeapUp(index);
        }
        else
        {
            AREA[index]->insert(result);
            this->moveToTop(AREA[index]);
            this->reHeapDown(index);
        }
    }
    void DELETE_KEITEIKEN(int number)
    {
        if (AREA.size() <= 0)
            return;
        vector<Node *> AREANew(AREA.begin(), AREA.end());
        queue<Node *> LIST_DELETE;
        for (int i = 0; i < number; ++i)
        {
            if (!AREA.size())
                break;
            Node *nodeDelete = AREA[0];
            swap(AREA[0], AREA[AREA.size() - 1]);
            AREA.pop_back();
            this->reHeapDown(0);
            LIST_DELETE.push(nodeDelete);
        }
        AREA = AREANew;
        while (LIST_DELETE.size())
        {
            Node *nodeDelete = LIST_DELETE.front();
            LIST_DELETE.pop();

            nodeDelete->DELETE(number);

            int index = 0;
            while (AREA[index] != nodeDelete)
                index++;
            if (nodeDelete->sizeList() == 0)
            {
                swap(AREA[index], AREA[AREA.size() - 1]);
                // delete in dslk
                this->DELETENode(AREA[AREA.size() - 1]);
                delete AREA[AREA.size() - 1];
                // delete in heap
                AREA.pop_back();
            }
            this->reHeapDown(index);
        }
    }

    void preOrder(int index, int number)
    {
        if (index >= (int)AREA.size() || number <= 0)
            return;
        this->AREA[index]->print(number);
        preOrder(index * 2 + 1, number);
        preOrder(index * 2 + 2, number);
    }
    void helpLIMITLESS(int number)
    {
        preOrder(0, number);
    }

private:
    class Node
    {
    private:
        int ID;
        list<int> head;
        friend class RESTAURANT_Sukuna;

    public:
        Node(int ID) : ID(ID) {}
        int sizeList() const
        {
            return head.size();
        }
        void insert(int result)
        {
            head.push_front(result);
        }
        void DELETE(int number)
        {
            while (!head.empty())
            {
                if (number == 0)
                    break;
                solution << head.back() << "-" << ID << "\n";
                head.pop_back();
                number--;
            }
        }
        void print(int number)
        {
            for (const auto &value : head)
            {
                if (number <= 0)
                {
                    break;
                }
                solution << ID << "-" << value << "\n";
                --number;
            }
        }
    };
};

class ADMIN
{
private:
    HUFFMAN_TREE customer;
    RESTAURANT_Gojo hashGOJO;
    RESTAURANT_Sukuna heapSUKUNA;

public:
    void LAPSE(string name)
    {
        if (name[0] >= '0' && name[0] <= '9') //! BỎ lúc nộp
        {
            int result = stoi(name);
            if (result % 2 == 1)
                hashGOJO.insertAREA(result);
            else
                heapSUKUNA.insertAREA(result);
            return;
        }
        int res = customer.encode(name);
        if (res == -1)
            return;

        if (res % 2 == 0)
            heapSUKUNA.insertAREA(res);
        else
            hashGOJO.insertAREA(res);
    }

    // HUFFMAN TREE
    void HAND()
    {
        customer.helpHAND_print();
    }
    // gojo
    void KOKUSEN()
    {
        hashGOJO.DELETE_KOKUSEN();
    }
    void LIMITLESS(int NUM)
    {
        hashGOJO.helpLIMITLESS(NUM);
    }

    // sukuna
    void KEITEIKEN(int NUM)
    {
        heapSUKUNA.DELETE_KEITEIKEN(NUM);
    }
    void CLEAVE(int NUM)
    {
        heapSUKUNA.helpLIMITLESS(NUM);
    }
};

void simulate(string filename)
{

    ifstream file(filename);
    string nameFunc;
    string nameCustomer;
    int NUM;

    file >> nameFunc;
    file >> MAXSIZE;

    ADMIN *FUNCTION = new ADMIN();
    while (file >> nameFunc)
    {
        if (nameFunc == "LAPSE") // LAPSE <NAME>
        {
            file >> nameCustomer;
            FUNCTION->LAPSE(nameCustomer);
        }
        else if (nameFunc == "KOKUSEN") // KOKUSEN
        {
            FUNCTION->KOKUSEN();
        }
        else if (nameFunc == "KEITEIKEN") // KEITEIKEN <NUM>
        {
            file >> NUM;
            FUNCTION->KEITEIKEN(NUM);
        }
        else if (nameFunc == "HAND") // HAND
        {
            FUNCTION->HAND();
        }
        else if (nameFunc == "LIMITLESS") // LIMITLESS <NUM>
        {
            file >> NUM;
            FUNCTION->LIMITLESS(NUM);
        }
        else if (nameFunc == "CLEAVE") // CLEAVE <NUM>
        {
            file >> NUM;
            FUNCTION->CLEAVE(NUM);
        }
    }
    delete FUNCTION;
}
