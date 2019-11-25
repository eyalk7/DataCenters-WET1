#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

template <class KeyType, class DataType>
class AVL {

public:
    AVL();
    ~AVL();
    find();
    insert();
    remove();
    begin();
    end();

    class TreeNode {
        DataType& data;
        KeyType key;
        TreeNode *left, *right, *parent;
        int height;

        TreeNode(); //height = 0

        friend AVL;
    };

    class TreeIterator {
        TreeNode *curr, *last;

    public:
        TreeIterator();
        operator<();
        operator++();
        operator==();
        operator*();

        friend AVL;
    };

private:
    TreeNode *dummy_root;

    BalanceSubTree();
    rotateRight();
    rotateLeft();
};

#endif //DATACENTERS_WET1_AVL_H
