#include "AVL.h"

AVL::AVL() : size(0) {
    // create dummy
    KeyType* dummyKey = nullptr;
    DataType* dummyData = nullptr;
    dummyRoot = new TreeNode(dummyKey, dummyData);

}

AVL::~AVL() {
    if (size != 0) {

    }

    delete dummyRoot;
}

TreeIterator AVL::find(KeyType key) {
    // if doesn't exist - return end()
    // find HELP!
}

AVLResult AVL::insert(KeyType key, DataType* data) {
    if (data == nullptr) // || key == nullptr)
        return AVL_INVALID_INPUT;

    // insert HELP!
    // if you find it SUCCESS
    // size doesn't change

    // if you dont find it add:
        // balance tree for each node in the recursive return
        // SUCCESS
        // size++;
}

AVLResult AVL::remove(KeyType key) {
    // if not exist -> FAILURE (size doesn't change)

    // if leaf -> remove
    // if one son -> change the one son for grandson
    // if two sons -> ...
    // size--
}

TreeIterator AVL::begin() {
    // dummy -> left
}

TreeIterator AVL::end() {
    // dummy
}

// static AVL functions

static void AVL::BalanceSubTree(TreeNode* subTreeRoot) {
    if (subTreeRoot == nullptr || subTreeRoot == dummyRoot)
        return;

    // calculate balance factor and check [-1,1]
    // use rotateRight or rotateLeft accordingly
}

static void AVL::rotateRight(TreeNode* subTreeRoot) {
    if (subTreeRoot == nullptr || subTreeRoot == dummyRoot)
        return;

}

static void AVL::rotateLeft(TreeNode* subTreeRoot) {
    if (subTreeRoot == nullptr || subTreeRoot == dummyRoot)
        return;

    // left on the left son =>  right on the left son
}

//-------------------------TREE ITERATOR FUNCTIONS-------------------------
DataType& TreeIterator::operator*() const {
    // assert(curr->parent != nullptr); // can't dereference the dummy

    return (this->curr->data);
}

DataType* TreeIterator::operator->() {
    return &(curr->data);
}

TreeIterator& TreeIterator::operator++() {
    // check if reached end before ++

//    if (curr->parent == last) {
//        // if can go left, go left
//        if (curr->left != nullptr) {
//            last = curr;
//            curr = curr->left;
//        }
//        else if (curr->right != nullptr) {
//            last = curr;
//            curr = curr->right;
//        } else { // else go back to parent
//
//        }
//
//    }

    return *this;
}

bool TreeIterator::operator<(const TreeIterator& other) const {
    // compare keys with key's operator <

}

bool TreeIterator::operator==(const TreeIterator& other) const {
    // compare keys with key's operator ==

}
