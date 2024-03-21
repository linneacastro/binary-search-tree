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

#include "plate.h"

void main(int argc, char **argv) 
{ 
  char temp[1000]; // Char array for user input w fgets to be passed to sscanf 
  char command[120]; // Variable to store command for menu interface and fget/sscanf
  char *databasename; // Variable to store database name, which is file we must open

  char plate[40]; // Next 3 variable lines for sscanf (memory is dynamically allocated otherwise)
  char first[40]; 
  char last[40];

  char deletethisplate[300];

// CHECKING COMMAND LINE ARGUMENTS AND READING IN DATABASE 
  if (argc ==1){
    printf("Error: Did not speficy database to open\n");
    return;
  }

  if (argc == 2){ // 2 command line arguments given, latter is database name
    databasename=argv[1]; // whatever is in the command line argument is the database we're going to open
  }

  Node root = NULL; // Representing initial empty tree, Node has been typedef'd in plate.h

// READING IN DATABASE 
  FILE *fp;  // Preparing to open file, declaring file pointer
  fp = fopen(databasename, "r"); // Opeing file stored as database
  if (fp == NULL){ // If file opens and returns NULL, print error message
    printf("Error: database cannot be read\n"); // Error message
    return;
  }
  while(NULL != fgets(temp,1000,fp)){ // While loop to read database line by line
    temp[strlen(temp)-1]='\0'; // Remove trailing newline
    sscanf(temp, "%s %s %s", plate, first, last);
    root=add(root, plate, first, last); // Calling root function to read lines in to be added to tree
  }
  fclose(fp); // Close the database we opened, important to prevent memory leak

// USER MENU INTERFACE
    printf("Enter plate or command: ");
    while(NULL != fgets(command, 120, stdin)){ // Beginning of while loop... using this and continue statements instead of infinite loop
      command[strlen(command)-1]='\0'; // Remove newline from what fgets stored
     
       // DUMP COMMAND 
       if(0==strcmp(command, "*DUMP")){ // If command matches *DUMP, we want to do the following
         //CALL HEIGHT FUNCTION
         int heightofthetree=height(root);
         printf("TREE HEIGHT: %d\n", heightofthetree);
         
         // CALL BALANCED FUNCTION
         int isthetreebalanced=balanced(root);
         if (isthetreebalanced == 0){ // Balanced function returned 0, tree is NOT balanced
           printf("BALANCED: NO\n");
         }
         else{ // Balanced function returned 1, tree IS balanced
           printf("BALANCED: YES\n");
         }
         
         printf("\n");
  
         // CALL LNR FUNCTION
         printf("LNR TRAVERSAL:\n");
         LNR(root);

         printf("\n");

         // CALL NLR FUNCTION
         printf("NLR TRAVERSAL:\n");
         NLR(root);
 
         printf("\n");

         // CALL LRN FUNCTION
         printf("LRN TRAVERSAL:\n");
         LRN(root);

         printf("\n");
        
         printf("Enter plate or command: ");
         continue; // Back to top of while loop
       }

       if (1==sscanf(command, "*DELETE %s", deletethisplate)){ // Pattern match was found, there is a cell to delete
         int wastheplatefound=search(root, deletethisplate, first, last); // Call search function to see if plate exists inside tree

         if (wastheplatefound==0){ // Plate not found, can't delete it
           printf("PLATE NOT FOUND\n");
           printf("Enter plate or command: ");
           continue; // Back to top
         }

         if (wastheplatefound==1){ // Plate WAS found, proceed to call delete function
           root=delete(root, deletethisplate); // Important to assign output of delete function to be root, as it returns new root of tree
           printf("SUCCESS\n");
           printf("Enter plate or command: ");
           continue;
         }
       }

       // TREAT DATA ENTRY NOT MATCHING COMMANDS AS PLATE SEARCH
       else{ // One of the above commands was NOT entered, search for plate
         char searchforthisplate[300]; // Character array for storing plate we're seraching for
         sscanf(command, "%s", searchforthisplate); // Using sscanf to store plate to search binary tree for
         int searchresult=search(root, searchforthisplate, first, last); // Call search function
         if(searchresult==0){ // Plate was not found
           printf("Plate not found.\n");
           printf("Enter plate or command: ");
           continue; // Plate not found, go back to while loop
         }
         else{ // Plate match was found
           printf("Found: first=%s, last=%s\n", first, last); // Print matching first and last name passed back 
           printf("Enter plate or command: ");
           continue; // Go back to while loop
         } 
       }
    printf("Enter plate or command: ");
    }
  treeFree(root); // Call treeFree function to release all memory associated with BST 

}

