#include "AVL.h"

template <class KeyType, class DataType>
AVL<KeyType, DataType>::AVL() : size(0) {
    // create dummy
    KeyType* dummyKey = nullptr;
    DataType* dummyData = nullptr;
    dummyRoot = new TreeNode(dummyKey, dummyData);
}

template <class KeyType, class DataType>
AVL<KeyType, DataType>::~AVL() {
    if (size != 0) {

    }

    delete dummyRoot;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::find(KeyType key) {
    TreeNode* ptr = dummyRoot->left;

    auto iter = end(); // if doesn't exist - return end()

    while (ptr != nullptr) {
        if (key == ptr->key) {
            iter.last = ptr->parent;
            iter.curr = ptr;
        } else if (key < ptr->key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    return iter;
}

template <class KeyType, class DataType>
AVLResult AVL<KeyType, DataType>::insert(KeyType key, DataType data) {
    TreeNode* last = dummyRoot;
    TreeNode* ptr = dummyRoot->left;

    // find where the new node should be placed
    while (ptr != nullptr) {
        last = ptr;
        if (key == ptr->key) {
            return AVL_SUCCESS;	// key is already in the tree
        } else if (key < ptr->key) {
            ptr = ptr->left;
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

    // fix the tree
    fixTree(ptr->parent);

    return AVL_SUCCESS;
}

template <class KeyType, class DataType>
AVLResult AVL<KeyType, DataType>::remove(KeyType key) {
    TreeNode* last = dummyRoot;
    TreeNode* ptr = dummyRoot->left;

    // look for the node
    while (key != ptr->key) {
        last = ptr;
        if (key < ptr->key) {
            ptr = ptr->left;
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



    fixTree(ptr);
    // if one son -> change the one son for grandson
    // if two sons -> ...
    // balance tree

    size--;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::begin() {
    // go all the way left
    // curr = dummyRoot->left
    TreeIterator iter;
    iter.curr = dummyRoot->left;

    while (iter->curr->left != nullptr) {
        iter.curr = iter->curr->left;
    }
    iter.last = iter.curr->parent;

    return iter;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::end() {
    // dummy
    TreeIterator iter;
    iter.curr = dummyRoot;
    return iter;
}

template <class KeyType, class DataType>
int AVL<KeyType, DataType>::getSize() const {
    return size;
}

//-------------------------PRIVATE (STATIC) AVL FUNCTIONS-------------------------

template <class KeyType, class DataType>
static void fixTree(TreeNode<KeyType, DataType>* root) {
    while (root != dummyRoot) {
        BalanceSubTree(root);
        root = root->parent;
    }
}

template <class KeyType, class DataType>
static void AVL<KeyType, DataType>::BalanceSubTree(TreeNode<KeyType, DataType>* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    int BF = root->getBalanceFactor();
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

template <class KeyType, class DataType>
static void AVL<KeyType, DataType>::rotateRight(TreeNode<KeyType, DataType>* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    TreeNode* parent = root->parent; // save subtree's parent

    // set a flag for whether this is a left or right subtree
    bool isLeftSubtree = false;
    if (parent->left == root) {
        isLeftSubtree = true;
    } else {
        isLeftSubtree = false;
    }

    // save relevant pointers
    TreeNode* B = root;
    TreeNode* A = root->left;
    TreeNode* A_R = A->right;

    // change pointers accordingly
    if (isLeftSubtree) {
        parent->left = A;
    } else {
        parent->right = A;
    }
    A->parent = parent;

    B->left = A_R;
    A_R->parent = B;

    A->right = B;
    B->parent = A;
}

template <class KeyType, class DataType>
static void AVL<KeyType, DataType>::rotateLeft(TreeNode<KeyType, DataType>* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    TreeNode* parent = root->parent; // save subtree's parent

    // set a flag for whether this is a left or right subtree
    bool isLeftSubtree = false;
    if (parent->left == root) {
        isLeftSubtree = true;
    } else {
        isLeftSubtree = false;
    }

    // get relevant pointers
    TreeNode* A = root;
    TreeNode* B = root->right;
    TreeNode* B_L = B->left;

    // change pointers accordingly
    if (isLeftSubtree) {
        parent->left = B;
    } else {
        parent->right = B;
    }
    B->parent = parent;

    A->right = B_L;
    B_L->parent = A;

    B->left = A;
    A->parent = B;
}

//-------------------------TREE ITERATOR FUNCTIONS-------------------------
template <class KeyType, class DataType>
DataType& AVL<KeyType, DataType>::TreeIterator::operator*() const {
    // assert(curr->parent != nullptr); // can't dereference the dummy
    return (this->curr->data);
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator& AVL<KeyType, DataType>::TreeIterator::operator++(int) {
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
    } else {
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

template <class KeyType, class DataType>
bool AVL<KeyType, DataType>::TreeIterator::operator<(const TreeIterator& other) const {
    // compare keys with key's operator <
    return (curr.key < other.curr.key);
}

template <class KeyType, class DataType>
bool AVL<KeyType, DataType>::TreeIterator::operator==(const TreeIterator& other) const {
    // compare keys with key's operator ==
    return (curr.key == other.curr.key);
}

//-------------------------TREE NODE FUNCTIONS-------------------------
template <class KeyType, class DataType>
int TreeNode<KeyType, DataType>::getBalanceFactor() const {
    return (left->height - right->height);
}
template <class KeyType, class DataType>
bool TreeNode<KeyType, DataType>::isLeaf() const {
    return (left == nullptr && right == nullptr);
}