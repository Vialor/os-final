# 4 Caching

Extra Credit: Explain `sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"`

I copy this from the documentation of Linux:

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