# Build
`mkdir build && cd build && cmake ..`

Inside build folder:

`make`: compile all programs

`make <programname>`: compile specific programs, including:

```
make run
make run2
make caching
make system_call
make fast
make fast_mmap
```

`make && cd .. && g++ runbenchmark.cpp rdwr.c -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o runbenchmark`: compile runbenchmark

# Programs
`./run <filename> [-r|-w] <block_size> <block_count>`

`./run2 <filename> <block_size>`

`./caching`

`./system_call`

`./fast <filename>`

`./fast_mmap`

`./runbenchmark`