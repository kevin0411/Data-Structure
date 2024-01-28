/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
int AVLTree<K, V>::findHeight(const Node* node) const{
    if(node==NULL)return -1;
    return 1+ std::max(findHeight(node->left), findHeight(node->right));
}

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    Node* next = t->right;
    t->right = t-> right ->left;
    next->left = t;
    t = next;
    t->height = findHeight(t);
    temp->height = findHeight(temp);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    Node* next = t->left;
    t->left = t->left->right;
    next->right = t;
    t = next;
    t->height = findHeight(t);
    temp->height = findHeight(temp);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==NULL)return;
    int diff = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if(diff >= 2){  // left unbalanced
        int left_diff = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
        if(left_diff == 1){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    else if(diff <= -2){  // left unbalanced
        int right_diff = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
        if(right_diff == -1){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    subtree->height = findHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==NULL){
        Node* create = new Node(key, value);
        subtree = create;
        return;
    }
    else if(key>subtree->key)insert(subtree->right, key, value);
    else{
        insert(subtree->left, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* it = subtree->left;
            while(it->right!=NULL){
                it=it->right;
            }
            swap(subtree,it);
            remove(subtree->left, key);
            return;
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right==NULL){
                Node* temp = subtree->left;
                *subtree = *temp;
                delete temp;
                temp = NULL;
            }
            else{
                Node* temp = subtree->right;
                *subtree = *temp;
                delete temp;
                temp = NULL;
            }
        }
        // your code here
        rebalance(subtree);
    }
}