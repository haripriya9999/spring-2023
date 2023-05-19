I used CPP programming in implementation 

# Minimum Spanning Tree

This program generates a random undirected complete graph and implements two algorithms to find the minimum spanning tree (MST): Prim's algorithm and Kruskal's algorithm.


## How to Compile

To compile the program, open a terminal in the directory where the source code files are located, and type the following command:

make
in the terminal

This will compile the program and produce an executable file named mst.

## How to Run

To run the program, open a terminal in the directory where the executable file is located, and type the following command:

```
./proj4
```

This will generate a random undirected complete graph with a random number of vertices between 5 and 10, and then run both Prim's algorithm and Kruskal's algorithm to find the minimum spanning tree. The program will print the adjacency matrix of the graph and the edges of the minimum spanning tree found by each algorithm.
select algorithm either prim or kruskal
if you select other than these 2 then error is occurred.

## How to Clean Up

To clean up the generated files, open a terminal in the directory where the source code files are located, and type the following command:

```
make clean
```

This will remove the object files and the executable file from the directory.