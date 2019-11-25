#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

enum AVLResult {AVL_SUCCESS, AVL_FAILURE};

template <class KeyType, class DataType>
class AVL {
public:
    AVL();
    ~AVL();
    TreeIterator find(KeyType key);
    DataType* get(KeyType key); // return nullptr if not exist
    AVLResult insert(KeyType key, DataType* data);
    AVLResult remove(KeyType key);
    TreeIterator begin();
    TreeIterator end();
    int size();

    class TreeIterator {
    public:
        TreeIterator() : curr( nullptr ), last( nullptr ) {};
        DataType& operator*();
        DataType* operator->();
        TreeIterator& operator++();
        bool operator<(const TreeIterator& other) const;
        bool operator==(const TreeIterator& other) const;


        friend AVL;

    private:
        TreeNode *curr, *last;
    };

private:
    class TreeNode {
        KeyType key;
        DataType* data;
        TreeNode *parent, *left, *right;
        int height;

        TreeNode(   KeyType key,
                    DataType& data,
                    TreeNode* parent = nullptr ) :
                key( key ), data( data ),
                parent( parent ), left( nullptr ), right( nullptr ),
                height( 0 ) {};

        friend AVL;
    };
    TreeNode *dummyRoot;
    int size;

    static void BalanceSubTree(TreeNode* subTreeRoot);
    static void rotateRight(TreeNode* subTreeRoot);
    static void rotateLeft(TreeNode* subTreeRoot);
};

#endif //DATACENTERS_WET1_AVL_H
