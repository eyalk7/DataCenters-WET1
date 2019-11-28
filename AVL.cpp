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
        TreeIterator iter = begin();
        TreeNode* ptr = iter.curr;
        TreeNode* parent = ptr->parent;

        // PostOrder Traversal to delete all nodes
        while (ptr != dummyRoot) {
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }

            while (ptr->right != nullptr) {
                ptr = ptr->right;

                while (ptr->left != nullptr) {
                    ptr = ptr->left;
                }
            }

            parent = ptr->parent;
            if (ptr->isLeftSubTree()) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            delete ptr;

            ptr = parent;
        }
    }

    delete dummyRoot;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::find(KeyType key) const {
    TreeNode* ptr = dummyRoot->left;

    auto iter = end(); // if doesn't exist - return end()

    while (ptr != nullptr) {
        if (key == ptr->key) {
            iter.last = ptr->parent;
            iter.curr = ptr;
        }
        else if (key < ptr->key) {
            ptr = ptr->left;
        }
        else {
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
        }
        else if (key < ptr->key) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    // Add the new node:
    ptr = new TreeNode(key, data, last);
    size++;
    if (key < last->key) {
        last->left = ptr;
    }
    else {
        last->right = ptr;
    }

    // fix the tree
    fixTree(ptr->parent);

    return AVL_SUCCESS;
}

template <class KeyType, class DataType>
AVLResult AVL<KeyType, DataType>::remove(KeyType key) {
    TreeNode* ptr = dummyRoot->left;

    // look for the node
    while (key != ptr->key) {
        if (key < ptr->key) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }

        if (ptr == nullptr) {
            // the node doesn't exist in the tree
            return AVL_SUCCESS;
        }
    }

    TreeNode* to_delete = ptr;
    if (to_delete->hasTwoSons()) {
        // get next node in the inorder traversal
        TreeIterator iter;
        iter.curr = to_delete;
        iter.last = to_delete->left;
        iter++;
        TreeNode* next = iter.curr;

        // swap the two nodes {
        TreeNode* next_R = next->right; // the next node doesn't have a left son
        TreeNode* next_P = next->parent;

        next->right = to_delete->right;
        to_delete->right->parent = next;

        next->left = to_delete->left;
        to_delete->left->parent = next;

        next->parent = to_delete->parent;
        if (to_delete->isLeftSubtree()) {
            to_delete->parent->left = next;
        }
        else {
            to_delete->parent->right = next;
        }

        to_delete->left = nullptr; // the next node doesn't have a left son
        to_delete->right = next_R;
        to_delete->parent = next_P;

        next_R->parent = to_delete;
        next_P->parent = to_delete;
        //}
    }

    TreeNode* son = nullptr;
    if (to_delete->hasSingleSon()) {
        // find which is the single son
        son = to_delete->left;
        if (son == nullptr) {
            son = to_delete->right;
        }

        // set the son's parent to be the removed node's parent
        son->parent = to_delete->parent;
    }

    // set parent's son (if it's leaf son = nullptr)
    if (to_delete->isLeftSubtree()) {
        to_delete->parent->left = son;
    }
    else {
        to_delete->parent->right = son;
    }

    TreeNode* to_fix = to_delete->parent;
    delete to_delete;
    fixTree(to_fix);

    size--; // update tree size
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::begin() const {
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
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::end() const {
    // dummy
    TreeIterator iter;
    iter.curr = dummyRoot;
    return iter;
}

template <class KeyType, class DataType>
int AVL<KeyType, DataType>::getSize() const {
    return size;
}

//-------------------------PRIVATE AVL FUNCTIONS-------------------------

template <class KeyType, class DataType>
static void AVL<KeyType, DataType>::fixTree(TreeNode<KeyType, DataType>* root) {
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
        }
        else if (BF_left == -1) {
            // LR
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    else if (BF == -2) {
        int BF_right = root->right->getBalanceFactor();
        if (BF_right <= 0) {
            // RR
            rotateLeft(root);
        }
        else if (BF_right == 1) {
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

    // save relevant pointers
    TreeNode* parent = root->parent;
    TreeNode* B = root;
    TreeNode* A = root->left;
    TreeNode* A_R = A->right;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = A;
    }
    else {
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

    // get relevant pointers
    TreeNode* parent = root->parent;
    TreeNode* A = root;
    TreeNode* B = root->right;
    TreeNode* B_L = B->left;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = B;
    }
    else {
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
bool TreeNode<KeyType, DataType>::isLeftSubtree() const {
    return (parent->left == this);
}

template <class KeyType, class DataType>
bool TreeNode<KeyType, DataType>::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

template <class KeyType, class DataType>
bool TreeNode<KeyType, DataType>::hasTwoSons() const {
    return (left != nullptr && right != nullptr);
}

template <class KeyType, class DataType>
bool TreeNode<KeyType, DataType>::hasSingleSon() const {
    return (!isLeaf() && !hasTwoSons());
}