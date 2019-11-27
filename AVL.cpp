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
    TreeNode* last = dummyRoot;
    TreeNode* ptr = dummyRoot->left;

    // if doesn't exist - return end()
    TreeIterator iter = end();
    while (ptr != nullptr) {
        last = ptr;
        if (key == ptr->key) {
            iter.curr = ptr;
            iter.last = ptr->parent;
        } else if (key < ptr->key {
            ptr = ptr ->left;
        } else {
            ptr = ptr->right;
        }
    }

    return iter;
}

DataType* AVL::get(KeyType key) {
    if (!find(key))
        return nullptr;


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
    // go all the way left
    // curr = dummyRoot->left
    TreeIterator iter;
    iter.curr = dummyRoot->left;

    while (iter->curr->left != nullptr) {
        iter.curr = iter->curr->left;
    }
    last = curr->parent;

    return iter;
}

TreeIterator AVL::end() {
    // dummy
    TreeIterator iter;
    iter.curr = dummyRoot;
    return iter;
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

TreeIterator& TreeIterator::operator++() {
    // check if reached end before ++
    if (curr == dummyRoot)
        return *this;

    // doSomething(curr) was done

    // if a right subtree exists
    if (curr->right != nullptr) {
        last = curr;
        curr = curr->right; // go right

        // and then go left as much as possible
        while (curr->left != nullptr) {
            last = curr;
            curr = curr->left;
        }
    }
    else {
        // no right subtree exists
        last = curr;
        curr = curr->parent; // go up

        // if you came back from a right subtree
        // keep rising until you come back from a left subtree
        while (last == curr->right) {
            last = curr;
            curr = curr->parent;
        }
    }

    return *this;   // doSomething(curr) will be done
}

bool TreeIterator::operator<(const TreeIterator& other) const {
    // compare keys with key's operator <
    return (curr.key < other.curr.key);
}

bool TreeIterator::operator==(const TreeIterator& other) const {
    // compare keys with key's operator ==
    return (curr.key == other.curr.key);
}
