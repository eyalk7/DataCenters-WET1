#include "AVL.h"

AVL::AVL() {

}

AVL::~AVL() {

}

TreeIterator AVL::find(KeyType key) {
    // if doesn't exist - return end()
    // find HELP!
}

AVLResult AVL::insert(KeyType key, DataType& data) {
    // parameter checks -> invalid input

    // insert HELP!
    // if you find it SUCCESS
    // if you dont find it add:
        // balance tree for each node in the recursive return
}

AVLResult AVL::remove(KeyType key) {
    // if not exist -> FAILURE

    // if leaf -> remove
    // if one son -> change the one son for grandson
    // if two sons -> ...
}

TreeIterator AVL::begin() {
    // dummy -> left
}

TreeIterator AVL::end() {
    // dummy
}

// static AVL functions

static void AVL::BalanceSubTree(TreeNode* subTreeRoot) {
    // calculate balance factor and check [-1,1]
    // use rotateRight or rotateLeft accordingly
}

static void AVL::rotateRight(TreeNode* subTreeRoot) {

}

static void AVL::rotateLeft(TreeNode* subTreeRoot) {
    // left on the left son =>  right on the left son
}

// TreeIterator class implementation
DataType& TreeIterator::operator*() const {

}

TreeIterator& TreeIterator::operator++() {

}

bool TreeIterator::operator<(const TreeIterator& other) const {
    // compare keys with key's operator <
}

bool TreeIterator::operator==(const TreeIterator& other) const {
    // compare keys with key's operator ==
}
