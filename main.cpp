//Stephen Ngai
//March 12th, 2017
//Problem 3

/*This program demonstrates how to form a binary search tree and display it. This file
uses a text file with integers as the input. Each integer has a frequency counter,
 which is incremented whenever the same integer is found. 
 
 After creating the binary search tree, the tree is traversed and the output, which
 is the frequency of each integer read in was  placed into a file called 
 integer.out */


// stdio provides access to file processing and console processing
#include <stdio.h>
// stdlib provides malloc and free dynamic memory allocations
#include <stdlib.h>
// stdbool defines "bool", "true" and "false"
// it is used whenever a boolean is being produced, used, or passed back to a caller
#include <stdbool.h>

// <<< you need to describe what each of these is and how it is used in the solution

#define INFILENAME "integers.in"
//Sets the name of the file that will be read in.
#define OUTFILENAME "integerFreq.out"
//Sets the name of the file that will be read out.

// <<< you need to describe what each of these is and how they are used in the solution
typedef struct {
    int data;
    int frequency;
}NodeData, *Node_Ptr;
/*A struct containing the data stored in a node. In this program, data is an 
 int type. The frequency int is used to count the number of times this node has
 been called.*/
typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right, *parent;
} TreeNode, *TreeNodePtr;
/*A struct which is a node of a tree. The data is contained in a struct, to make 
 it more generalized and easier to substitute other data types. There are also
 three separate TreeNodPtrs to the left, right, and parent nodes.*/



TreeNodePtr Head_Tree_Node = NULL;
//Global variable that contains a TreeNodePtr that will be the root node.


int allocationCount = 0;



TreeNodePtr  newNodeData(int data);
/*Dynamically allocates new memory, filling in the user data and clearing 
 the left, right, and parent nodes. Also sets the frequency to zero.*/

void        inOrder             (FILE *, TreeNodePtr);
// inOrder does a traversal of the Head_Tree_Node that will write a file
// with the traversal results.

TreeNodePtr buildTree           (TreeNodePtr current, Node_Ptr data);
/* Builds a tree from the Head_Tree_Node and data read in from the file. It ensures
 that Head_Tree_Node isn't NULL, if it is, it sets it calls the newNodeData and
 sets the Head_Tree_Node to the return value. It also increments frequency. If 
 the Head_Tree_Node is already defined, the program will compare the data in the node
 to the data from the file. If the data to insert is less than the node's data 
 the left side will be traversed, else it will attempt to traverse the right nodes.
 The next case is whether the left or right child nodes exist. If they don't, they
 will be created and the data will be inserted into the nodes. If the node already
 exist the function will traverse to it. If the data in the node and the file are
 equal, then the frequency for the node is incremented, and the node is returned*/

void        DeleteTree         (TreeNodePtr nodeToDelete);
/*Uses the postOrder order to cycle through the binary tree. When a pointer has
 gone through the left and right, visited those then it's parent has the node 
 pointing towards the nodeToDElete set to NULL, delinking the node from the list.
 The nodeToDelete is freed. memoryAllocation is decremented. */

//main
/*
 1. Sets pointers to the in and out files. If the files are not opened, a statement
 will be printed out and the program will exit. 
 2. Reads in the file by checking for the end of file marker and will store
the information in the Binary Search Tree.
 3. The frequency amounts is exported to the out file via the inOrder function
 4. The Tree is deleted.
 5. Inorder was attempted to be called again, but nothing would print since 
 * the BST is set to NULL.
 6. File is closed*/
int main()
{
    // open the input file and exit if it does not open
    FILE * in = fopen( INFILENAME, "r");
    if (in == NULL) {
        printf ("Unable to open file %s... exiting", INFILENAME);
        exit (0);
    }

    // the input file opened, so open the output file.
    // it it does notm open, close the input file and exit
    FILE * out = fopen( OUTFILENAME, "w");
    if (out == NULL)
    {
        printf ("Unable to open file %s for output... exiting", OUTFILENAME);
        fclose (in);
        exit(0);
    }

    
    printf("Allocation count before building the Binary Search Tree is: %i\n", allocationCount);
    
    
    //reads in the file while the eof marker isn't read in. IF it is read in,
    //the loop will break. The data from the file is stored in an integer address
    //which is then put into insert.data. The buildTree function builds
    //the tree with the inserData Node_Ptr..
    while (1)
    {
         if(feof (in))
        {
            break;
        }
        int intHolder = 0;
        
        NodeData insert;
        Node_Ptr insertData = &insert;
        
        fscanf(in, "%i", &intHolder);
        insert.data = intHolder;
        
        //Call to the buildTree
        buildTree(Head_Tree_Node, insertData);
        


    }
    
    printf("After Building the tree, the allocationCount is: %i\n", allocationCount);
    

    
    // The file has been processed.  Write out the results by using
    // an in-order traversal and writing as the "visit"
    fprintf(out, "\nWords        Frequency\n\n");
    inOrder(out, Head_Tree_Node);
    fprintf(out, "\n\n");

    
     DeleteTree(Head_Tree_Node);
    //Deletes the tree and prints out the nodes as they are deleted
    
    printf("After the tree has been deleted, the allocationCount is: %i\n", allocationCount);
    
    
    printf("inOrder is called again: nothing should print");
    inOrder(out, Head_Tree_Node);
    
    
 
    // close both files and return.  We're done!!
    fclose(in);
    fclose(out);
    return 0;
} // end main


//


// inOrder does a go left, visit, go right traversal through recursively
// calling itself.  Instead of calling on a "visit", it accomplishes it
// by writing out the user data word and occurrence count to the file
// provided

void inOrder(FILE * out, TreeNodePtr node)
{
    // if we are not NULL we cannot go further in the tree
    if (node!= NULL) {
        // go left
        inOrder(out, node -> left);
        // "visit" by printing the user information
        fprintf(out, "\n%-15d %2d\n", node -> data.data, node -> data.frequency);
        // go right
        inOrder(out, node -> right);
    }
    return;
} //end inOrder

// newNodeData is a utility that builds a NodeData structure from
// the user data fields it receives as input.  In this case, it is an integer
// and an initial frequency of occurrence


TreeNodePtr  newNodeData(int data)
{
    TreeNodePtr newPointer;
    newPointer = (TreeNodePtr) malloc(sizeof(TreeNode));
    //Sets the node's data
    newPointer->data.data = data;
    //Pointers for the lft, right, parent are set to NULL.
    newPointer->left = NULL;
    newPointer->right = NULL;
    newPointer->parent = NULL;
    newPointer->data.frequency = 0;
    allocationCount++;
    
    return newPointer;
}

/* Input: 
 * current - TreeNodePtr at the node that currently being traversed.
 * data - Node_Ptr that will be inserted into the node.
 * 
 * Output: Returns a TreeNodePtr towards the newly allocated node
 * Process:
 * Builds a tree from the Head_Tree_Node and data read in from the file. It ensures
 that Head_Tree_Node isn't NULL, if it is, it sets it calls the newNodeData and
 sets the Head_Tree_Node to the return value. It also increments frequency. If 
 the Head_Tree_Node is already defined, the program will compare the data in the node
 to the data from the file. If the data to insert is less than the node's data 
 the left side will be traversed, else it will attempt to traverse the right nodes.
 The next case is whether the left or right child nodes exist. If they don't, they
 will be created and the data will be inserted into the nodes. If the node already
 exist the function will traverse to it. If the data in the node and the file are
 equal, then the frequency for the node is incremented, and the node is returned*/
TreeNodePtr buildTree (TreeNodePtr current, Node_Ptr data)
{
   //Executes if Head Tree Node is Node, making sure there is a Binary Tree
    if (Head_Tree_Node == NULL)
    {
        int info = data->data;
        
        Head_Tree_Node = newNodeData(info);
        Head_Tree_Node->data.frequency++;
        return Head_Tree_Node;
    }
    //Head_Tree_Node should be initialized
    TreeNodePtr newNode;
    if(data->data < current->data.data)
    //Checks to see if the data that is being inserted, is less than the 
    //data inside of the node.
    {
    //If the node doesn't exist, the node is created.
        if(current->left ==NULL)
        {
            //sets the data and parent pointers.
            newNode = newNodeData(data->data);
            newNode->parent = current;
            //increases frequency
            newNode->data.frequency++;
            //the left node is set to the newly created node.
            current->left = newNode;
            return newNode;
        }
    //if the node to the left does exist, then the current pointer is set to 
    //traverse to the left child node.
        else if(current->left != NULL)
        {
            buildTree(current->left, data);
        }
    }
    if(data->data > current->data.data)
    {
        if(current->right == NULL)
        //Creates node towards the right ptr if it is NULL
        {
            //sets the newNode's data and parent ptr.
            newNode = newNodeData(data->data);
            newNode->parent = current;
            //Frequency is increased.
            newNode->data.frequency++;
            //Points the right node of the parent node to the new node.
            current->right = newNode;
            return newNode;
        }
        else if(current->right != NULL)
            //Recursively calls the current right node if the node exists.
        {
            buildTree(current->right, data);
        }
    }
    if(data->data == current->data.data)
    //Increases the frequency counter if the data from the file matches the data
    //input from the file
    {
        current->data.frequency++;
        return current;
    }
}
//DeleteTree
/*
 Inputs: 
 * nodeToDelete - Node that will be deleted
 Outputs: None
 Process: Checks to see if the ptr is set to NULL. Next, checks for a left child,
 and if one is found, DeleteTree is called recursively towards the left ptr. The
 same is done to the right ptr. The Parent ptr is set towards the nodeToDelete
 parent ptr. If the Parent ptr doesn't exist, then the current ptr is the root
 node and it will delete itself. The Parent treeNodePtr will set its left or right
 child node to NULL, unlinking the nodeToDelete from the list. The nodeToDelete's
 data is printed, and then freed. The memory Allocation is decremented.*/
void DeleteTree (TreeNodePtr nodeToDelete)
{
    if( nodeToDelete != NULL)
    //Checks if the node exists
    {
        if(nodeToDelete->left != NULL)
        //if the pointer to the left child exist, then the function is called 
        //recursively, with the left child as the input.
        {
            DeleteTree(nodeToDelete->left);
        }
        if(nodeToDelete->right != NULL)
        /*If the the right pointer exists, then the function is called 
         recursively, with the right child as the input.*/
        {
            DeleteTree(nodeToDelete->right);
        }

        TreeNodePtr Parent = nodeToDelete->parent;
        //Creates a pointer towards the parent node.
        if(Parent != NULL)
        /*If the parent does not exist, then the nodeToDelete is the root node
        and then the following code isn't executed. */
        {

            if(Parent->left == nodeToDelete)
            //Case where the nodeToDelete is the parent's left node. This will 
            //set the parent's left ptr to NULL, unlinking it from the list.
            {
                Parent->left = NULL;
            }
            else if (Parent->right == nodeToDelete)
            //If the nodeToDelete is the address of the parent's right child, then
            //the parent's right child ptr is set to node, unlinking the nodeToDelete.
            {
                Parent->right = NULL;
            }
        }
        else
        {
            Head_Tree_Node = NULL;
        }
        

        printf("Deleted and Freed %i\n", nodeToDelete->data);
        //Prints a message indicating which node was deleted.

        free(nodeToDelete);
        //Frees the node.
        allocationCount--;
        //Global variable memoryAllocation is decremented.
    }
}