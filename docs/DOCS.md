<<<<<<< HEAD
# 1 Basics

We create **rdwr.c** including functions **block_read** and **block_write**. Both of them have 3 parameters: **file_name**,  **block_size**, **block_count**. In **block_read**, we read buf sized **block_size** **block_count** times from the file named **file_name**. And so on in **block_write**.

In **run.c**, we parse the parameters and choose to use **block_read** or **block_write**. We record the start time and the end time to get the runtime.



# 2 Measurement

Firstly, we parse the parameters to get the **file_name** and **block_size**.

Then, we start with **block_count=1**. In each loop, we double **block_count** and run

```c
block_read(file_name, block_size, block_count);
```

We record the runtime and quit the loop when **runtime>5** (second)

Finally, we print **block_size*block_count=1**  as the **file_size**



# 3 Raw Performance







# 4 Caching

We read the file twice. Record their runtime and compare them.

Then we clear the cache and run again.



Extra Credit: Explain `sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"`

The following comes from the documentation of Linux:

>To free pagecache:
>
>   echo 1 > /proc/sys/vm/drop_caches
>
>To free reclaimable slab objects (includes dentries and inodes):
>
>   echo 2 > /proc/sys/vm/drop_caches
>
>To free slab objects and pagecache:
>
>   echo 3 > /proc/sys/vm/drop_caches

Using 3 remove both the slab objects and pagecache. Slab is a memory management mechanism used in the Linux for commonly used objects. Page cache is part of the VM system. It is a cache of pages in RAM.



# 5 System Calls
- Measure performance MiB/s when using block size of 1 byte

3.680185 MiB/s

- Measure performance in B/s. This is how many system calls you can do per second.

3858954 B/s, or 3858954 systemcalls per second

- Try with other system calls that arguably do even less real work (e.g. lseek)

We have compared system calls read and lseek(system_call.c), here's the printing result:

Number of read per second: 3844769.056968

Number of lseek per second: 10240425.108437

# 6 Raw Performance

In this part we use multiple threads. We choose 16 as the number of threads.

We use the block_size 4096.

For the thread numbered **i**, we open a **fd** and read the blocks

**i, i+num\_threads, ... , i+k*num\_threads**

Use **lseek()** to jump to the right place. After reading, we **XOR** them byte by byte.

Finally, we output the total runtime (This runtime includes the time to calculate **XOR**) and the result of **XOR**
