/*
By Ethan Larson
Started 4/10/2024, completed 4/18/2024*/

#include <iostream>
#include <fstream>
//#include "file.txt"
/*
I changed my mind I really don't want to deal with files right now
*/

using namespace std;

struct Node {
  int data;
  Node* parent = NULL;
  Node* lnode = NULL;
  Node* rnode = NULL;
};

void addNode(Node* &head);
void addUser(Node* &head, int data);
void checkData(Node* &pnode,  Node* &node);
void printTree(Node* node, int count);
int search(Node* node, int count, int num);
//literally all the delete functions
void deleteInit(Node* &head, int num);
Node* findNode (Node* node, int num);
void deleteFinal(Node* &head, Node* &node);
void shift(Node* &head, Node* pnode, Node* cnode);
Node* successor(Node* &node);

int intput = 0;
string input;

int main() {

  Node* head = NULL;
  cout << endl << "Begin Process" << endl;
  srand((unsigned) time(NULL));
  while (input != "quit") {
    cout << "Please type 'add', 'addNum', 'del', 'search', or 'print' to continue, or 'quit' to quit." << endl;
    cin >> input;
    if (input == "add") {
      cout << "What value should the node have?" << endl;
      cin >> intput;
      addUser(head, intput);
      cout << "Created." << endl;
    }
    else if (input == "addNum"){
      cout << "How many nodes to add?" << endl;
      cin >> intput;
      cout << "Making " << intput << " node(s)..." << endl;
      for (int i = 0; i < intput; i++) {
	addNode(head);
      }
      cout << "Created." << endl;
    }
    else if (input == "del"){
      cout << "Which Node to delete?" << endl;
      cin >> intput;
      cout << "Deleting Node with data: " << intput << "..." << endl;
      deleteInit(head, intput);
      cout << "Deleted." << endl;
    }
    else if (input == "print") {
      printTree(head, 0);
    }
    else if (input == "search") {
      cout << "Which number are we searching for?" << endl;
      cin >> intput;
      cout << "Searching for " << intput << "s..." << endl;
      cout << "There are " << search(head, 0, intput) << " " << intput << "s." << endl;
    }
    else if (input == "quit") {
      return 0;
    }
  }
  return 0;
}

void addUser(Node* &head, int data) {//like addNode but allows user to input data
  Node* cur = new Node();

  cur->data = data;
  if (head == NULL) {
    head = cur;
    return;
  }
  else {
    checkData(head, cur);
    return;
  }
}

void addNode(Node* &head) {//creates new node, puts it at top of tree, checks placement
  Node* cur = new Node();
  
  cur->data = (rand() % 999);
  if (head == NULL) {
    head = cur;
    return;
  }
  else {
    checkData(head, cur);
    return;
  }
}

void checkData(Node* &pnode, Node* &node) {//compares nodes, walks down tree
  if (pnode->data > node->data) {
    if (pnode->lnode == NULL) {
      pnode->lnode = node;
      node->parent = pnode;
      return;
    }
    else {
      checkData(pnode->lnode, node);
    }
  }
  else if (pnode->data < node->data) {
    if (pnode->rnode == NULL) {
      pnode->rnode = node;
      node->parent = pnode;
      return;
    }
    else {
      checkData(pnode->rnode, node);
    }
  }
  else {
    return;
  }
}

void printTree(Node* node, int count) {//prints tree (left->right root to leaf, up->down most to least)

  if (node->rnode != NULL) {
    printTree(node->rnode, count+1);
  }
  for (int i = 0; i < count; i++) {
    cout << '\t';

  }
  cout << node->data << endl;

   if (node->lnode != NULL) {
    printTree(node->lnode, count+1);
  }

}

int search(Node* node, int count, int num) {//walks down the tree, returns the number of times that node shows up
  if (node->rnode != NULL) {
    count += search(node->rnode, 0, num);
  }
  
  if (node->data == num) {
    count++;
  }

   if (node->lnode != NULL) {
     count += search(node->lnode, 0, num);
  }
   return count;
}

//DelInit and FindNode written by me, delFinal, successor, and shift based on psuedocode from Wikipedia, Binary_Search_Tree[10]:298

void deleteInit(Node* &head, int num) {//checks that input exists, then actually starts the chain reaction
  if (search(head, 0, num) > 0) {
    Node* node = findNode (head, num);
    deleteFinal(head, node);
  }
  else {
    cout << "Node doesn't exist." << endl;
    return;
  }
}
Node* findNode (Node* node, int num) {//Similar to search, but returns a node instead of a count
  if (node->data < num) {
    if (node->rnode != NULL) {
      findNode(node->rnode, num);
    }
  }
  else if (node->data == num) {
    return node;
  }
  else if (node->data > num) {
    if (node->lnode != NULL) {
      findNode(node->lnode, num);
    }
  }
  
}
void deleteFinal(Node* &head, Node* &node) {
  if (node->lnode == NULL) {
    shift(head, node, node->rnode);
  }
  else if (node->rnode == NULL) {
    shift(head, node, node->lnode);
  }
  else {
    Node* suc = successor(node);
    if (suc->parent != node) {
      shift(head, suc, suc->rnode);
      suc->rnode = node->rnode;
      suc->rnode->parent = suc;
    }
    shift(head, node, suc);
    suc->lnode = node->lnode;
    suc->lnode->parent = suc;
  }
}
void shift(Node* &head, Node* pnode, Node* cnode) {
  if (pnode->parent == NULL) {
    head = cnode;
  }
  else if (pnode == pnode->parent->lnode) {
    pnode->parent->lnode = cnode;
  }
  else {
    pnode->parent->rnode = cnode;
  }
  if (cnode != NULL) {
    cnode->parent = pnode->parent;
  }
}

       
Node* successor(Node* &node) {
  if (node->rnode != NULL) {
    while (node->lnode != NULL) {
      node = node->lnode;
    }
  }
  Node* suc = node->parent;
  while (suc != NULL && node == suc->rnode) {
    node = suc;
    suc = suc->parent;
  }
  return suc;
}


