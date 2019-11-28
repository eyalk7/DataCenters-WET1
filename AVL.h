#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

enum AVLResult { AVL_SUCCESS, AVL_FAILURE, AVL_INVALID_INPUT };

template <class KeyType, class DataType>
class TreeNode {
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
    bool isLeaf() const;
};

template <class KeyType, class DataType>
class AVL {
public:
    class TreeIterator {
    public:
        TreeIterator() : curr(nullptr), last(nullptr) {};
        DataType& operator*() const;
        TreeIterator& operator++(int);
        bool operator<(const TreeIterator& other) const;
        bool operator==(const TreeIterator& other) const;


        friend AVL;

    private:
        TreeNode<KeyType, DataType>* curr, * last;
    };

    AVL();
    ~AVL();
    TreeIterator find(KeyType key);
    AVLResult insert(KeyType key, DataType data);
    AVLResult remove(KeyType key);
    TreeIterator begin();
    TreeIterator end();
    int getSize() const;

private:
    // the actual tree is the dummy's left subtree
    TreeNode<KeyType, DataType>* dummyRoot;
    int size;

    static void fixTree(TreeNode<KeyType, DataType>* root);
    static void BalanceSubTree(TreeNode<KeyType, DataType>* root);
    static void rotateRight(TreeNode<KeyType, DataType>* root);
    static void rotateLeft(TreeNode<KeyType, DataType>* root);
};

#endif //DATACENTERS_WET1_AVL_H
