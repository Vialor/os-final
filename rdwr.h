#ifndef RDWR_H
#define RDWR_H

void block_read(char* file_name, int block_size, int block_count);
void block_write(char* file_name, int block_size, int block_count);

#endif