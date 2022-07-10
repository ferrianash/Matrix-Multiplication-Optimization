# UCAS Assembly Final Assignment 

# - Optimization of matrix multiplication

付国 2019K8009922008

ferrianash, 2022.07.10

### Files Info

```shell
evaluate.c		# test the correctness of the matrix-mul file and report the elapsed time
matrix.S		# the optimized file
matrix.c		# C file before optimization
```

### Test & Evaluation

```sh
# get the elapsed time before optimization with gcc -O2 level as standard
gcc -O2 evaluate.c matrix.c -o matrix
./matrix

# get the elapsed time after optmization
gcc evaluate.c matrix.S -o matrix1
./matrix1
```

### Report

The report is under the directory `report/`.