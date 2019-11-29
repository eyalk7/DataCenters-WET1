#include "AVL.h"

template <class KeyType, class DataType>
AVL<KeyType, DataType>::AVL() : size(0) {
    // create dummy
    KeyType dummyKey;
    DataType dummyData;
    dummyRoot = new TreeNode<KeyType, DataType>(dummyKey, dummyData);
}

template <class KeyType, class DataType>
AVL<KeyType, DataType>::~AVL() {
    if (size != 0) {
        TreeIterator iter = begin();
        auto ptr = iter.curr;
        TreeNode<KeyType, DataType>* last = nullptr;

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

            last = ptr->parent;
            if (ptr->isLeftSubtree()) {
                last->left = nullptr;
            }
            else {
                last->right = nullptr;
            }
            delete ptr;

            ptr = last;
        }
    }

    delete dummyRoot;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::find(const KeyType& key) const {
    auto ptr = dummyRoot->left;

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
AVLResult AVL<KeyType, DataType>::insert(const KeyType& key, const DataType& data) {
    if (size != 0) {
        auto last = dummyRoot;
        auto ptr = dummyRoot->left;

        // find where the new node should be placed
        while (ptr != nullptr) {
            last = ptr;
            if (key == ptr->key) {
                return AVL_SUCCESS;    // key is already in the tree
            } else if (key < ptr->key) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }

        // Add the new node:
        ptr = new TreeNode<KeyType, DataType>(key, data, last);
        if (key < last->key) {
            last->left = ptr;
        } else {
            last->right = ptr;
        }

        // fix the tree
        fixTree(ptr->parent);
    }
    else
    {
        // tree is empty
        dummyRoot->left = new TreeNode<KeyType, DataType>(key, data, dummyRoot);
        dummyRoot->left->parent = dummyRoot;
    }

    size++;
    return AVL_SUCCESS;
}

template <class KeyType, class DataType>
AVLResult AVL<KeyType, DataType>::remove(const KeyType& key) {
    if (size == 0)
        return AVL_SUCCESS;

    auto ptr = dummyRoot->left;

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

    auto to_delete = ptr;
    if (to_delete->hasTwoSons()) {
        // get next node in the inorder traversal
        TreeIterator iter;
        iter.curr = to_delete;
        iter.last = to_delete->left;
        iter++;
        auto next = iter.curr;

        // swap the two nodes
        TreeNode<KeyType, DataType>::swap(*to_delete, *next);

        to_delete = next; // update pointer of node to be removed
    }

    TreeNode<KeyType, DataType>* son = nullptr;
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

    auto to_fix = to_delete->parent;
    delete to_delete;
    fixTree(to_fix);

    size--; // update tree size

    return AVL_SUCCESS;
}

template <class KeyType, class DataType>
typename AVL<KeyType, DataType>::TreeIterator AVL<KeyType, DataType>::begin() const {
    // go all the way left
    // curr = dummyRoot->left
    TreeIterator iter;
    iter.curr = dummyRoot;

    while (iter.curr->left != nullptr) {
        iter.curr = iter.curr->left;
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
void AVL<KeyType, DataType>::fixTree(TreeNode<KeyType, DataType>* root) {
    while (root != dummyRoot) {
        root->updateHeight();
        BalanceSubTree(root);
        root = root->parent;
    }
}

template <class KeyType, class DataType>
void AVL<KeyType, DataType>::BalanceSubTree(TreeNode<KeyType, DataType>* root) {
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
            root->left->updateHeight();
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
            root->right->updateHeight();
            rotateLeft(root);
        }
    }

    root->updateHeight();
}

template <class KeyType, class DataType>
void AVL<KeyType, DataType>::rotateRight(TreeNode<KeyType, DataType>* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    // save relevant pointers
    auto parent = root->parent;
    auto B = root;
    auto A = root->left;
    auto A_R = A->right;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = A;
    }
    else {
        parent->right = A;
    }
    A->parent = parent;

    B->left = A_R;
    if (A_R != nullptr)
        A_R->parent = B;

    A->right = B;
    B->parent = A;
}

template <class KeyType, class DataType>
void AVL<KeyType, DataType>::rotateLeft(TreeNode<KeyType, DataType>* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    // get relevant pointers
    auto parent = root->parent;
    auto A = root;
    auto B = root->right;
    auto B_L = B->left;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = B;
    }
    else {
        parent->right = B;
    }
    B->parent = parent;

    A->right = B_L;
    if (B_L != nullptr)
        B_L->parent = A;

    B->left = A;
    A->parent = B;
}

//-------------------------TREE ITERATOR FUNCTIONS-------------------------
template <class KeyType, class DataType>
DataType& AVL<KeyType, DataType>::TreeIterator::operator*() const {
    // assert(curr->parent != nullptr); // can't dereference the dummy
    return (curr->data);
}

template <class KeyType, class DataType>
const typename AVL<KeyType, DataType>::TreeIterator& AVL<KeyType, DataType>::TreeIterator::operator++(int) {
    // check if reached end (dummyNode) before ++
    if (curr->parent == nullptr)
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
    return (curr->key < other.curr->key);
}

template <class KeyType, class DataType>
bool AVL<KeyType, DataType>::TreeIterator::operator==(const TreeIterator& other) const {
    return (curr == other.curr);
}

//-------------------------TREE NODE FUNCTIONS-------------------------
template <class KeyType, class DataType>
int TreeNode<KeyType, DataType>::getBalanceFactor() const {
    int left_height = -1, right_height = -1;

    if (left != nullptr) {
        left_height = left->height;
    }
    if (right != nullptr) {
        right_height = right->height;
    }

    return (left_height - right_height);
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

template<class KeyType, class DataType>
void TreeNode<KeyType, DataType>::updateHeight() {
    if (isLeaf()) {
        height = 0;
        return;
    }

    int left_height = -1, right_height = -1;

    if (left != nullptr) {
        left_height = left->height;
    }
    if (right != nullptr) {
        right_height = right->height;
    }

    height = (left_height > right_height) ? left_height : right_height;
    height++;
}

template<class KeyType, class DataType>
void TreeNode<KeyType, DataType>::swap(TreeNode<KeyType, DataType>& A, TreeNode<KeyType, DataType>& B) {
    KeyType temp_key = A.key;
    DataType temp_data = A.data;

    A.key = B.key;
    A.data = B.data;

    B.key = temp_key;
    B.data = temp_data;
}
