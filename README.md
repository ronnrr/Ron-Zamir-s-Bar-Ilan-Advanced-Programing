# ex1-Ron Zamir
My ex1 submision on github.
I used a struct made out of a 2d dynamic array of floats, and two integers indicating the height and width of the array.
Now, I shall expand upon my implementation of every function:
Firstly, create matrix - we inititate the dynamic arrays according to the height and width variables given. Same goes for the height and width variables of the matrix itself.
Secondly, copy matrix - we begin by allocating memory for our values array, and then we set everything as needed.
Thirdly, the delete function - we delete the values arrays and then the matrix itself.
Now, the get width function - we return the value of the width variable.
On to the get height function - we return the value of the height variable.
Fourthly, the get var - we return the values array in position col row.
As for the set var - we put the value given in the col row slot.
Add function - we check if sizes are correct, and if so we add all the values in every slot together after initiating a new array.
On to the multiply function - we check for dimention validity and then multiply as needed.
Finally, as for the multiply by scalar - we go through the slots and multiply them.
Now, as a disclaimer, before initiating any action, I check if inputs are fine and if not, return an error message. 