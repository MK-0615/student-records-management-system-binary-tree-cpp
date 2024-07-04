#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

//Main-functions

//(2)	Print deepest nodes
bool BST::deepestNodes() {

	//Check if tree is empty
	if (empty()) return false;

	//Output
	cout << "\n\n\t\t\tDeepest node: ";
	deepestNodesHelper(root);
	cout << endl;

	return true;
}

//(3)	Display student
bool BST::display(int order, int source) {

	//Declaration
	ofstream outfile;

	//Check if tree is empty
	if (empty()) return false;

	system("cls");

	//source = 1: Display to screen
	//source = 2: Write in file
	switch (source) {
	case 1:
		display2(order, cout);
		break;
	case 2:
		outfile.open("student-info.txt");
		display2(order, outfile);
		outfile.close();
		break;
	default:
		cout << "\n\n\t\t < < < < < < < < < < < < INVALID INPUT. PLEASE TRY AGAIN. > > > > > > > > > > >\n\n";
	}
	return true;
}

//(4)	Clone Subtree
bool BST::CloneSubtree(BST t1, type item) {

	//Declaration
	bool found = false;

	//Find the item in tree
	FindItem(item, t1.root, found);

	//Check if the  main tree is empty or if the item is in the tree
	if (t1.empty() || !found) return false;

	//Clear nodes in subtree if it is not empty
	if (!empty()) EmptyList();

	//Clone the subtree from main tree
	Clone1(t1, item, t1.root);
	return true;
}

//(5)	Print Level Nodes
bool BST::printLevelNodes() {

	//Declarations
	int levels[10][10] = { 0 };
	int n = 0;

	//Check if the tree is empty
	if (empty()) return false;

	//Store the ids in 2d array according to their levels
	levels[0][0] = root->item.id;
	printLevel(root,levels, n);

	//Output
	for (int i = 0; i < 10; i++) {
		if(levels[i][0] != 0) {
			cout << "\t\t\tLevel " << i + 1 << " nodes: ";
			for (int j = 0; j < 10; j++) {
				if (levels[i][j] != 0)
					cout << levels[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return true;
}

//(6)	Print Path
bool BST::printPath() {

	//Declarations
	int path[20] = { 0 };

	//Check if tree is empty
	if (empty()) return false;

	//Output
	cout << "\t\t\t\tBelow are all the external paths for the tree:\n\n";
	paths(root, path);
	return true;
}

//Sub-functions

//(2-1)	Print deepest nodes
void BST::deepestNodesHelper(BTNode*cur) {
	
	if (cur == NULL) return; 
	
	//Print the id if it has no sons (deepest)
	if (cur->left == NULL && cur->right == NULL) {
		cout << cur->item.id << " ";
		return;
	}
	deepestNodesHelper(cur->left);
	deepestNodesHelper(cur->right);
}

//(3-1)	Display student
void BST::display2(int order, ostream& out) {

	//order = 1: Ascending
	//order = 2: Descending
	switch (order) {
	case 1:
		ascendingOrderPrint(root, out);
		break;
	case 2:
		descendingOrderPrint(root, out);
		break;
	default:
		cout << "\n\n\t\t < < < < < < < < < < < < INVALID INPUT. PLEASE TRY AGAIN. > > > > > > > > > > >\n\n";
	}
}

//(3-2)	Display student
void BST::ascendingOrderPrint(BTNode* cur,ostream& out) {

	if (cur == NULL) return;
	ascendingOrderPrint(cur->left, out);
	cur->item.print(out);
	ascendingOrderPrint(cur->right, out);
}

//(3-3)	Display student
void BST::descendingOrderPrint(BTNode* cur, ostream& out) {

	if (cur == NULL) return;
	descendingOrderPrint(cur->right, out);
	cur->item.print(out);
	descendingOrderPrint(cur->left, out);
}

//(4-1)	Clone Subtree
void BST::EmptyList() {
	while (!empty()) remove(root->item);
}

//(4-2)	Clone Subtree
void BST::FindItem(type item, BTNode* cur, bool &found) {

	if (cur == NULL) return;
	FindItem(item, cur->left, found);
	if (cur->item.compare3(item.id)){
		found = true;
		return;
	}
	FindItem(item, cur->right, found);
}

//(4-3)	Clone Subtree
void BST::Clone1(BST t1, type item, BTNode* cur) {

	if (cur == NULL) return;
	Clone1(t1,item, cur->left);
	if(cur->item.compare3(item.id)){
		insert(cur->item);
		Clone2(t1, item, cur);
		return;
	}
	Clone1(t1,item, cur->right);
}

//(4-4)	Clone Subtree
void BST::Clone2(BST t1, type item, BTNode *cur) {

	if (cur == NULL) return;
	if (cur->item.id != item.id) insert(cur->item);
	Clone2(t1, item, cur->left);
	Clone2(t1, item, cur->right);
}

//(5-1)	Print Level Nodes
void BST::printLevel(BTNode*cur, int array[][10], int n) {

	if (cur == NULL) {
		n -= 1;
		return;
	}
	printLevel(cur->left,array,n+1);
	for (int i = 0; i < 10; i++) {
		bool exist = false;
		for (int j = 0; j < 10; j++) {
			if (array[i][j] == cur->item.id){
				exist = true;
				break;
			}
		}
		if (exist) break;

		if (array[n][i] == 0) {
			array[n][i] = cur->item.id;
			break;
		}
	}
	printLevel(cur->right,array,n+1);
	n -= 1;
}

//(6-1)	Print Path
void BST::paths(BTNode* cur,int array[]) {

	if (cur == NULL) return;
	for (int i = 0; i < 20; i++) {
		if (array[i] == 0){
			array[i] = cur->item.id;
			break;
		}
	}
	paths(cur->left, array);
	paths(cur->right, array);
	if (cur->left == NULL && cur->right == NULL) {
		cout << "\t\t\t\t";
		for (int i = 0; i < 20; i++)
			if (array[i] != 0)
				cout << array[i] << " ";
		cout << endl;
	}
	removeLastNode(array);
}

//(6-2)	Print Path
void BST::removeLastNode(int array[]) {

	if (array[0] == 0) return;
	for (int i = 0; i < 20; i++) {
		if (array[i] == 0){
			array[i - 1] = 0;
			break;
		}
	}
}
