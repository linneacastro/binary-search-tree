// MAIN PROGRAM //

/* PA3 A License Plate and Name Database using Binary Trees Written in C */
// NAME: Linnea P. Castro
// DATE: 11 FEB 2023
// COURSE: CSE 222
// ASSIGNMENT: PA3
// SYNOPSIS:
/*
This program implements a license plate and name database using a binary tree
to store information.  The main program reads in a database file of plate and name
combinations.  Line-by-line, this information becomes the binary tree.  The first
name read in becomes the root of the tree, and all following nodes get stored by plate,
in reference to how the plate evaluates numerically via string compare, to the root
and available nodes in the tree.  

With the main program being largely similar to that of PA2, the main theme explored in 
this assignment were familiarization with binary trees (how to build one, search within one,
and delete information, while keeping integrity of tree stucture intact), and the use
of recursive functions.

The main program accepts two direct commands from the user.  *DUMP  displays 
tree height, balance, and full traversal in three orders, LNR, NLR, and LRN.  *DELETE
followed by a plate searches the tree for a specified plate and deletes it, adjusting 
pointers and freeing memory as necessary to ensure all nodes are "adopted" to locations 
that correspond logically to the way the tree is built (smaller number to left, larger to 
right).  Anything other than *DUMP or *DELETE is treated as a plate lookup by the main 
program, and results of the search are produced. 

More detailed information on all functions used by the main program can be found in
the bst.c file.  

Skills practiced in PA3 include: Using recursive functions, the importance of establishing
a "base case" and when returning the root back to the main program, the need to assign
root= to the function call.  Understanding how a binary search tree is built, and also, how
one can be deconstructed via the algorithm we walked through in class.  Before coding, being able to 
visually represent/diagram what was happening when a node was being deleted from the tree 
ensured  children of deleted nodes (root specifically) were adopted in an appropriate
location. 
*/
