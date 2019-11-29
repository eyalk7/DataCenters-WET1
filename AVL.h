#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

enum AVLResult { AVL_SUCCESS, AVL_FAILURE, AVL_INVALID_INPUT };

template <class KeyType, class DataType>
struct TreeNode {
    KeyType key;
    DataType data;
    TreeNode* parent, * left, * right;
    int height;

    TreeNode(KeyType key,
             DataType data,
             TreeNode* parent = nullptr) :
            key(key), data(data),
            parent(parent), left(nullptr), right(nullptr),
            height(0) {};

    int getBalanceFactor() const;
    bool isLeftSubtree() const;
    bool isLeaf() const;
    bool hasSingleSon() const;
    bool hasTwoSons() const;
    void updateHeight();

    static void swap(TreeNode& A, TreeNode& B);
};

template <class KeyType, class DataType>
class AVL {
public:
    class TreeIterator {
    public:
        TreeIterator() : curr(nullptr), last(nullptr) {};
        DataType& operator*() const;
        const TreeIterator& operator++(int);
        bool operator<(const TreeIterator& other) const;
        bool operator==(const TreeIterator& other) const;


        friend AVL;

    private:
        TreeNode<KeyType, DataType>* curr, * last;
    };

    AVL();
    ~AVL();
    TreeIterator find(const KeyType& key) const;
    AVLResult insert(const KeyType& key, const DataType& data);
    AVLResult remove(const KeyType& key);
    TreeIterator begin() const;
    TreeIterator end() const;
    int getSize() const;



private:
    // the actual tree is the dummy's left subtree
    TreeNode<KeyType, DataType>* dummyRoot;
    int size;

    void fixTree(TreeNode<KeyType, DataType>* root);
    void BalanceSubTree(TreeNode<KeyType, DataType>* root);
    void rotateRight(TreeNode<KeyType, DataType>* root);
    void rotateLeft(TreeNode<KeyType, DataType>* root);
};

#endif //DATACENTERS_WET1_AVL_H
