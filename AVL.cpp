#include "AVL.h"

AVL::AVL() {

}

AVL::~AVL() {

}

TreeIterator AVL::find(KeyType key) {
    // if doesn't exist - return end()

}

AVLResult AVL::insert(KeyType key, DataType& data) {

}

AVLResult AVL::remove(KeyType key) {

}

TreeIterator AVL::begin() {

}

TreeIterator AVL::end() {

}

// static AVL functions

static void AVL::BalanceSubTree(TreeNode* subTreeRoot) {

}

static void AVL::rotateRight(TreeNode* subTreeRoot) {

}

static void AVL::rotateLeft(TreeNode* subTreeRoot) {

}

// TreeIterator class implementation
DataType& TreeIterator::operator*() const {

}

TreeIterator& TreeIterator::operator++() {

}

bool TreeIterator::operator<(const TreeIterator& other) const {

}

bool TreeIterator::operator==(const TreeIterator& other) const {

}
