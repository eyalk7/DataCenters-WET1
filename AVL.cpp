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

AVLResult AVL::insert(KeyType key, DataType data) {
    TreeNode* last = dummyRoot;
    TreeNode* ptr = dummyRoot->left;

    // find where the new node should be placed
    while (ptr != nullptr) {
        last = ptr;
        if (key == ptr->key) {
            // key is already in the tree
            return AVL_SUCCESS;
        } else if (key < ptr->key) {
            ptr = ptr ->left;
        } else {
            ptr = ptr->right;
        }
    }

    // Add the new node:
    ptr = new TreeNode(key, data, last);
    size++;
    if (key < last->key) {
        last->left = ptr;
    } else {
        last->right = ptr;
    }

    // balance the tree
    ptr = ptr->parent;
    while (ptr != dummyRoot) {
        BalanceSubTree(ptr);
        ptr = ptr->parent;
    }

    return AVL_SUCCESS;
}

AVLResult AVL::remove(KeyType key) {
    TreeNode* last = dummyRoot;
    TreeNode* ptr = dummyRoot->left;

    // look for the node
    while (key != ptr->key) {
        last = ptr;
        if (key < ptr->key) {
            ptr = ptr ->left;
        } else {
            ptr = ptr->right;
        }
        if (ptr == nullptr) {
            // the node doesn't exist in the tree
            return AVL_SUCCESS;
        }
    }

    // if leaf -> remove
    if (ptr->isLeaf()) {
        ptr = ptr->parent;
        delete ptr->left;
        ptr->left = nullptr;
    }
    // if one son -> change the one son for grandson
    // if two sons -> ...
    // balance tree

    size--;
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

static void AVL::BalanceSubTree(TreeNode* root) {
    if (subTreeRoot == nullptr || subTreeRoot == dummyRoot)
        return;

    int BF = subTreeRoot->getBalanceFactor();
    if (BF == 2) {
        int BF_left = root->left->getBalanceFactor();
        if (BF_left >= 0) {
            // LL
            rotateRight(root);
        } else if (BF_left == -1) {
            // LR
            rotateLeft(root->left);
            rotateRight(root);
        }
    } else if (BF == -2) {
        int BF_right = root->right->getBalanceFactor();
        if (BF_right <= 0) {
            // RR
            rotateLeft(root);
        } else if (BF_right == 1) {
            // RL
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
}

static void AVL::rotateRight(TreeNode* root) {
    if (subTreeRoot == nullptr || subTreeRoot == dummyRoot)
        return;

}

static void AVL::rotateLeft(TreeNode* root) {
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

//-------------------------TREE NODE FUNCTIONS-------------------------
int AVL::TreeNode::getBalanceFactor() const {
    return (left->height - right->height);
}

bool AVL::TreeNode::isLeaf() const {
    return (left == nullptr && right == nullptr);
}