// BST FUNCTIONS (prototypes inside plate.h) //

/* PA3 A License Plate and Name Database with Binary Search Tree Written in C */
// NAME: Linnea P. Castro
// DATE: 14 FEB 2023
// COURSE: CSE 222
// ASSIGNMENT: PA3
// SYNOPSIS:
/*
All functions used by main program, plate, are contained below together with more detailed 
descriptions underneath function heading.  The following functions work together to create
a binary search tree, search the tree, traverse the tree in three orders (LNR, NLR, and LRN), 
determine the height and balance of the tree, delete from the tree, and finally, free all
memory when the program exits.
*/

#include "plate.h"


// NODE ADD FUNCTION //
/*
The main program uses the add function to read in a database, where each line of the database ends up
becoming a new node in the binary search tree, with the first line read becoming the tree's root node.
The node add function accepts a Node stucture, and character pointers to plate, first name, and last 
name field as input.  Memory for character fields are dynamically allocated based on the character
size of the fields.  The final part of creating a new node involves creating left and right node branches, 
and setting their fields to NULL.  The function returns the new root of the tree to the main program.

Once the root node is in place, subsequent nodes are added to the tree with recursive calls to the add
function.  Placement is determined throuh strcmp, which evaluates incoming node in comparison to the root
node, with larger nodes being added to the right of the root, and smaller nodes being added to the left of root,
giving deliberate instruction for placement of nodes as the tree grows.     
*/
Node add(Node root, char *plate, char *first, char *last)
{
  if (root == NULL){ // If we are adding to a completely empty tree and neet to make a new node for root 
    struct node *new=malloc(sizeof(struct node)); // Adding a new node and mallocing memory for it
    
    new->plate=malloc((strlen(plate)+1)*sizeof(char)); // Need to be able to store the null character, hence +1
    strcpy(new->plate, plate); // Use strcpy to add plate to new->plate, new plate node just created

    new->first=malloc((strlen(first)+1)*sizeof(char)); // Mallocing space for first name in new node
    strcpy(new->first, first); // Strcpying firstname into new node

    new->last=malloc((strlen(last)+1)*sizeof(char)); // Mallocing space for last name in new node
    strcpy(new->last, last); // Strcpying lastname into new node

    new->left = NULL; // Each node has a L and R child, empty by default, populated as new nodes are added.
    new->right = NULL;
    return(new); // This is THE root of the tree, very 1st plate added
  }

  if (0 < strcmp(plate, root->plate)){ // New plate being added in is GREATER than root, strcmp returns greater than 0, add to RIGHT
    root->right = add(root->right, plate, first, last);
    return(root);
  }

  else{  // New plate is SMALLER than root, add to LEFT
    root->left = add(root->left, plate, first, last);
    return(root);
  } 
}


// LNR FUNCTION //
/*
The LNR function is a recursive way to print the entire contents of the tree.  The way it traverses the tree 
results in the entire tree being printed from smallest plate values to largest tree values, because it 
prints the left side of the root first, starting from the very bottom, and working its way up toward the root 
and then over to the right side.  This print method is known as "depth first" because it starts with the smallest
values and works its way up to the largest values.  This works because of the original way the BST was structured
in the add statement, with strcmp determining placement of new nodes, either L or R. 
*/
void LNR(Node root)
{
  if (root == NULL){ // Base case, return to main program if tree is completely empty
    return;
  }
  LNR(root->left); // Recursive call to L side of root
  printf("Plate: <%s> Name: %s, %s\n", root->plate, root->last, root->first);
  LNR(root->right); // Recursive call to R side of root
}


// NLR FUNCTION //
/*
The NLR function is another recursive function, very similar to LNR, which prints the contents of the tree.
The difference for NLR is the order in which tree contents are printed.  NLR begins by printing the root,
travelling the left side of the tree, and then the right side of the tree.  This order is useful for 
identifying the root of the tree, as it will be the first line printed. 
*/
void NLR(Node root)
{
  if (root == NULL){ // Base case
    return;
  } 
  printf("Plate: <%s> Name: %s, %s\n", root->plate, root->last, root->first); // Print root, followed by L, then R
  NLR(root->left);
  NLR(root->right);
}


// LRN FUNCTION //
/*
LRN function is the final traversal order for printing contents of the tree.  Like LNR, and NLR, it is recursive.
LRN starts at the bottom of the left side of the tree, and works its way up, reaching the root (not printing it),
and then printing starting at the bottom of the right side of the tree, printing the root last. 
*/
void LRN(Node root)
{
  if (root == NULL){ // Base case
    return;
  }
  LRN(root->left); // L side first, then R, then root
  LRN(root->right);
  printf("Plate: <%s> Name: %s, %s\n", root->plate, root->last, root->first);
}
 

// SEARCH FUNCTION //
/*
The main program treats all data entry beyond specific *DUMP and *DELETE commands as searches, and in addition
the search function is a precursor to the using the delete function (plate must exist to be deleted).  Search is 
implemented recursively to travel through the tree.  Strcmp is used to evaluate whether plate entered matches a
node's plate field.  If a match is found, strcpy returns the first and last name to the main program, and returns 
1 to main program.  Based on evaluation of strcmp (is plate being searched for to R or L of root?), search 
will operate on either the left or right side of tree to continue recursively searching for a match.  No match
returns a 0 to the main program. 
*/
int search(Node root, char *plate, char *first, char *last)
{
  if (root == NULL){ // Base case for recursive function
    return(0);
  }
  if (0 == strcmp(plate, root->plate)){
    strcpy(first, root->first); // Distribute temp->first to first
    strcpy(last, root->last); // Distribute temp->last to last
    return(1);
  }
  if (0 < strcmp(plate, root->plate)){ // New plate being searched for is GREATER than root, strcmp returns greater than 0, search RIGHT
    return(search(root->right, plate, first, last));
  }
  else{ // If plate being searched for is not greater than root, it is less than root: search LEFT side of tree
    return(search(root->left, plate, first, last));
  } 
}


// HEIGHT FUNCTION //
/*
Called within the *DUMP command, as a precursor to determining tree balance.  The height function assigns 
integer variables to recursively calculate the right and left heights of the tree
independently.  If the height of the left is larger than the right, the function returns left height +1
to account for the root. If right and left sides are equal, the function returns left height +1 (but it could
just as well be right height).  If neither of the two "if" statements are satisfied, an else statement
determines that the right tree must be the largest one, and returns height of right +1 to the main function.
The height function is also used in the balance function.
*/
int height(Node root)
{
  if (root == NULL){ // Base case, an empty tree has height -1
    return(-1);
  }
  int hl = height(root->left); // recursive calls to find height of L and R subtrees and store as int variables
  int hr = height(root->right);
  if ( hl > hr ){ // If LEFT tree is bigger than right
    return(1+hl);
  }
  if ( hl == hr ){ // If L and R heights are equal
    return (1+hl);
  }
  else{ // R tree is biggest
    return(1+hr);
  }
}


// BALANCED FUNCTION //
/*
The balanced function is called within *DUMP command, called after height function. Balanced uses two recursive
calls to itself to determine whether the left and right subtrees are balanced, as well as two calls to the
height fuction to find L and R tree heights.  Balance depends on three factors, evaluated inside an if 
statement: L side must be balanced, R side must be balanced, AND abs val of L height - R height must be 
<=1.  If all 3 conditions are met, tree is balanced and function returns 1 to main program.  If these 
conditions are not met, tree is not balanced, 0 returned to main program.   
*/
int balanced(Node root)
{
  if (root == NULL){
    return(1); // Base case, an empty tree is balanced, return 1
  }
  int leftisbal = balanced(root->left); // Used to determine balance in if statement below
  int rightisbal = balanced(root->right);  
  int leftheight = height(root->left);
  int rightheight = height(root->right);

  if (abs(leftheight - rightheight) <= 1 && leftisbal == 1 && rightisbal == 1){ // All must be met for tree to be balanced
    return(1);
  }
  else{
    return(0); // Tree is not balanced, return 0
  }
}


// DELETE FUNCTION //
/*
The delete function handles plate deletion and is broken down into 3 parts:
1. Deleting from an empty tree
2. Recursive delete calls
3. When the root is the plate we want to delete (handled itself in 3 edge cases)

The main program passes the plate user wants to delete to the search function.  If plate is found, it can be deleted and
plate gets passed to delete function. The main challenge of the delete function is deleting a desired node
while still preserving the underlying structure of the tree and the parameters outlined in the add function in
terms of node placement, number of children, etc.

To delete the root I used an algorithm given in class to handle three possibilities:
CASE 3: Root has no left child. Uses pointer newroot to make root's right child the new root.  Memory from original 
root is freed.
CASE 2: Root has left child, and that node only has a left child.  I used a pointer called biggest to make root's left 
child the new root, and adopt root's right node as biggest's right child.  Memory from original root is then freed.
CASE 1: Root has a left child, called biggest, and biggest has right child/ren.  In this instance, we need to travel
the node, finding the largest, right most node in the left subtree.  Using pointers biggest and parent inside a while loop, 
the tree is traversed until biggest is found (its right child = NULL). At that point, we prepare biggest to become the new root,
parent adopts biggest's left child, biggest becomes the new root, taking on the root's left and right children as its own, and 
then freeing memory from the original root after pointers are in place.   

Delete function returns the new root to the main program.
*/
Node delete(Node root, char *plate)
{
  // DELETING FROM EMPTY TREE
  if (root == NULL){ // If the tree is completely empty, just return the empty tree
    return(NULL);
  }
  
  // RECURSIVE DELETE
  if (0 > strcmp(plate, root->plate)){ // Plate being deleted is SMALLER than root, strcmp returns less than 0, del from LEFT subtree
    root->left=delete(root->left, plate);
    return(root);
  }

  if (0 < strcmp(plate, root->plate)){ // Plate being deleted is LARGER than root, strcmp returns less than 0, del from RIGHT subtree
    root->right=delete(root->right, plate);
    return(root);
  }

  // EDGE CASES WHEN DELETING ROOT
  if (0 == strcmp(plate, root->plate)){ // Plate searched for matches root's plate, leading to CASE 3 deletion

    // CASE 3 - ROOT HAS NO LEFT CHILD
    if (root->left == NULL){ // CASE 3, we want to delete the root, root has no left child, only right child/ren.
      Node newroot; // Pointer to newroot, using what we typedef'd
      newroot=root->right; // Save new root in new variable before we delete old root
      free(root->plate); // Deleting old root
      free(root->first);
      free(root->last);
      free(root);
      return(newroot); // Returning newroot as the new root of the tree
    }

    // Pointers for edge cases when deleting root
    Node biggest;
    Node parent;

    biggest=root->left;

    // CASE 2, BIGGEST (ROOT->LEFT) HAS NO RIGHT CHILD
    if (biggest->right == NULL){ // CASE 2, want to delete root, root->left exists (calling it biggest), biggest has no right child
      biggest->right=root->right; // biggest will adopt root->right as its right child/ren
      free(root->plate); // Freeing root's memory
      free(root->first);
      free(root->last);
      free(root);
      return(biggest); // Returning biggest as new root
    }
    
    parent=biggest; // Parent and biggest are same to start

    // CASE 3, BIGGEST HAS RIGHT CHILD, NEED TO FIND NEW ROOT/BIGGEST THING
    while(biggest->right != NULL){ // CASE 3, where biggest (root->left) has a right child and we have to find actual biggest on left subtree
      parent=biggest;
      biggest=biggest->right;
    }

    parent->right=biggest->left; // Parent will adopt biggest's left child
    biggest->left=root->left; // biggest becoming new root, what's on left of biggest will be left of root
    biggest->right=root->right; // biggest adopting root's right subtree as its own right subtree
    
    free(root->plate);
    free(root->first);
    free(root->last);
    free(root);
    return(biggest); // Return biggest as new root
   
  }
}

// TREEFREE FUNCTION //
/*
The treeFree function is called when the user CTRL-D's to exit from the program.  It recursively deletes
from the left subtree, right subtree, and frees each data field (plate, first name, and last name), before 
finally freeing the root.  TreeFree has no return value.
*/
void treeFree(Node root)
{
  if (root!=NULL){ // Carries out the following as long as tree is not empty:
    treeFree(root->left);
    treeFree(root->right);
    free(root->plate);
    free(root->first);
    free(root->last);
    free(root);
  }
}




