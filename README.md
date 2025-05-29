# Game of life
 The Game of Life is a "game" that demonstrates how, through a set of simple rules, complex behaviors can be generated. It is not actually a game, but a cellular automaton, meaning a mathematical model that describes the functioning of computing systems (hardware or software). It was created by mathematician John Conway.

 # The rules of the game
 The Game of Life takes place on a grid of square cells, where each cell can have two states: alive or dead. Cells interact from one moment in time to another (called generations) with the 8 neighboring cells according to the following rules:
  1. Any live cell with fewer than two live neighbors dies (underpopulation). 
  2. Any live cell with two or three live neighbors continues to live. 
  3. Any live cell with more than three live neighbors dies (overpopulation). 
  4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
  For more details about the project, you can visit the website: <https://site-pa.netlify.app/proiecte/game_of_life/>

# How to use
In order to complete the project, it is necessary to install the package for the operation of the checker from this website <https://gitlab.cs.pub.ro/paaa/project-data/-/tree/main/gameoflife> and to download the input, output, and reference data to have a basis for testing the code.
The checker maintains the order of the project, signaling the emergence of problems, whether they are related to memory, style, or the output created.

# Main
The first step was to open the file from which I needed to get the information about the project: the task number(T), to see which case I was in, the number of rows(N) and columns(M) of the matrix, the generation number(K), and then reading the matrix.

# Task 1
To solve the first task, I created a function that retains in a matrix the number of neighbors of each element in the initial matrix(numar_vecini_vii). For each live element, I used the value 1, and for dead elements, I used the value 0, then summed the neighbors for each element. I handled the cases separately, since there are 3 possibilities for the number of neighbors: the element can have 3 neighbors (if it is located at the corner of the matrix), the element can have 5 neighbors (if it is on the edge of the matrix but not in the corner), and the element can have 8 neighbors (if it is in the middle of the matrix).
After analyzing the number of living neighbors, I set the necessary conditions for moving to the next generation in the 'implementare_reguli' function, and at the end, I added the specific generation of the read number (K) into the file.

# Task 2
For the second task, I used the same 'numar_vecini_vii' function to navigate between generations, and at each generation, I added to a list the row and column numbers of the elements that were modified in order to create the requested stack of lists. For the second task, I used the same 'neighbors' function to move between generations, and at each generation, I added to a list the row and column numbers of the elements that were modified to create the required stack of lists. I built the stack through the 'creare_lista' function. Another way to create the stack was to use the matrix only for the first list, while the creation of the subsequent lists required the use of the previous list, which accounted for the changes made one generation before. I approached this method in the function 'alt_mod'.
Another requirement found in task 2 was to determine the initial generation based on the already created stack and the matrix of the last generation. I addressed this case in the 'mers_invers' function after separately reading the stack and the matrix in the main.

# Task 3
The third case involves applying the two rules and creating a tree of lists with the elements that have changed at each generation based on them. I handled the two cases in the 'celula' function, creating the lists I needed and gradually building the tree. I printed the tree to a file using the 'preordine' function.

# Task 4
The fourth task involves finding the longest Hamiltonian chain for each node of the tree, displaying for each node for which the display is made and the coordinates of the cells (line and column). I traversed the tree in depth (DFS) and placed the conditions in the 'lant_hamiltonian' function.

# Important functions in the project
In addition to those already described in the 4 tasks, there are also other essential functions for the program to operate: 'sterge_arbore'(delete the tree), 'sterge_stiva'(delete the stack), 'sterge_lista'(delete the list), 'copie_matrice'(matrix copy function), 'adauga_la_inceput'(for adding the first element to the list), 'adauga_la_sfarsit'(to add to the list of the other elements).
