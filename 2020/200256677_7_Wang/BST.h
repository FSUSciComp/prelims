template<class T>
class BST {

    public:
        BST(); // default constructor
        ~BST(); // destructor
        void insert(T data); // insert a new number
        bool search(T query); // search for a given number
        T* output(); // return sorted array
        int getSize(); // return number of elements in the tree
    
    private:
        
        struct Node {
            public:
                Node(const T num);
                T data;
                Node* left;
                Node* right;
        };
        
        Node* root; // root node of the tree (first number inserted)
        int size; // keep track of number of elements in the tree, to make outputting a sorted array easier
        void insert(T data, Node* node); // recursively navigate tree and insert new node/number
        void empty(Node* node); // recursively deallocate nodes 
        int output(Node* node, int pos, T* array); // helper function, recursively build sorted array
        bool search(T query, Node* node); // helper function, recursively search for query

};

// Node constructor
template<class T>
BST<T>::Node::Node(const T num) : left(nullptr), right(nullptr), data(num) {}

// default constructor
template<class T>
BST<T>::BST() : root(nullptr), size(0) {}

// destructor
template<class T>
BST<T>::~BST() {

    empty(root);

}

// getter for size
template<class T>
int BST<T>::getSize() {
    return size;
}

// helper function -- recursively deallocate nodes
template<class T>
void BST<T>::empty(Node* node) {
    if(node != nullptr) {
        empty(node->left);
        empty(node->right);
    }
    return;
}

// publicly accessible -- insert new number into the tree
template<class T>
void BST<T>::insert(T num) {
    size++;
    insert(num, root);
}

// insert number into tree (recursive navigation)
template<class T>
void BST<T>::insert(T num, Node* node) { 

    // handle case of first node in binary tree
    if(node == nullptr) {
        root = new Node(num);
    }
    // navigate down left branch
    else if(num <= node->data && node->left != nullptr) {
        insert(num, node->left);
    }
    // navigate down right branch
    else if(num > node-> data && node->right != nullptr) {
        insert(num, node->right);
    }
    // we've reached the end, insert to the left
    else if(num <= node->data) {
        node->left = new Node(num);
    }
    // we've reached the end, insert to the right
    else if(num > node-> data) {
        node->right = new Node(num);
    }

    return;

}

// publicly accessible -- recursively search tree for number
template<class T>
bool BST<T>::search(T query) {
    return search(query, root);
}

// recursively search tree for number
template<class T>
bool BST<T>::search(T query, Node* node) {

    bool contains;
    
    // if we have reached the end of the line without finding it
    if(node == nullptr) {
        contains = false;
    }
    // if the query is less than current node, move left
    else if(query < node->data) {
        contains = search(query, node->left);
    }
    // if the query is greater, move right
    else if(query > node->data) {
        contains = search(query, node->right);
    }
    // otherwise, we have found the query
    else {
        contains = true;
    }

    return contains;

}

// publicly accessible -- call output as array function
template<class T>
T* BST<T>::output() {
    T* array = new T[size];
    output(root, 0, array);
    return array;
}

// output as array (recursive navigation)
template<class T>
int BST<T>::output(Node* node, int pos, T* array) {

    if(node->left != nullptr) {
        pos = output(node->left, pos, array);
    }
    
    // std::cout << pos << std::endl;
    array[pos] = node->data;
    pos++;
    
    if(node->right != nullptr) {
        pos = output(node->right, pos, array);
    }

    return pos;

}