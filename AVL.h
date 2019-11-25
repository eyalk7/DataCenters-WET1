#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

enum AVLResult {SUCCESS, FAILURE};

template <class KeyType, class DataType>
class AVL {
public:
    AVL();
    ~AVL();
    TreeIterator find(KeyType key);
    AVLResult insert(KeyType key, DataType& data);
    AVLResult remove(KeyType key);
    TreeIterator begin();
    TreeIterator end();

    class TreeIterator {
    public:
        TreeIterator() : curr( nullptr ), last( nullptr );
        DataType& operator*() const;
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
        DataType& data;
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

    void BalanceSubTree(TreeNode* subTreeRoot);
    void rotateRight(TreeNode* subTreeRoot);
    void rotateLeft(TreeNode* subTreeRoot);
};

#endif //DATACENTERS_WET1_AVL_H
