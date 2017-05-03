# Sparse_Matrices
### The task №2:
Determine the maximum modulo element of the matrix and perform the dividing all elements <br/>
of the column in which it is on this element, if quantity of such elements is more than one,<br/>
then make the dividing with next-to-last column containing such an element.
### Algorithm:
Realize these actions: 
  * Read the matrix from file
  * Print in internal representation inputted matrix
  * Print in external representation inputted matrix
  * Perform the task 
  * Print in internal representation gotten matrix
  * Print in external representation gotten matrix
### Matrix representation   
Two cells correspond to a nonzero element: 
contains the column number, the second contains the value of the element. A zero in the <br/>
first cell indicates the end of the line, and the second cell in this case contains the <br/>
number of the next stored line. Zeros in both cells are a sign of the end of the list of <br/> 
non-zero elements 
### Testing 
...
