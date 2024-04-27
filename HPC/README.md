To run the code, we need -fopenmp flag


```bash
# Compile
g++ -fopenmp -o <output> <input>.cpp

# Run
./<output>
```


To run cuda code, we need nvcc compiler
```bash
nvcc -o <output> <input>.cu
./<output>
```

INSTALL CUDA
https://www.youtube.com/watch?v=8i3BiWa5AZ4
```