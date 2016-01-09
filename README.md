#Burrows-Wheeler Transform using V-order(V-BWT)

This project is an implementation of Burrows-Wheeler Transform using V-order(V-BWT) in C++. It is developed as an assignment for Bioinformatics class on Faculty of Electrical Engineering and Computing (FER) in Zagreb.

For computing V-BWT we, firstly, factorize input string (given in FASTA format) into V-words. We process these V-words in reverse order(from right to left) grouping them into groups of V-words with the same maximal letter. Each V-word in a group has to have the same number of V-letters as the longest V-word in group, so we homogenize them. For each V-word we then create conjugacy class which contains every rotation of that V-word. Finaly, we merge every conjugacy class of one group into one matrix and sort it using merge sort. The last column of these matrices (one matrix for each group) is V-BWT.

##Usage
```
make all
./bin/all

make clean
```

##References
1. J.W. Daykin, W.F. Smyth, A bijective variant of the Burrows-Wheeler Transform using V-order, Theoret. Comput. Sci. 531 (2014) 77-89
2. D.E. Daykin, J.W. Daykin, W.F. Smyth, A linear partitioning algorithm for Hybrid Lyndons using V-order, Theoret. Comput. Sci. 483 (2013) 149-161
