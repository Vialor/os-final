#include <stdlib.h>
#include <iostream>
#include <benchmark/benchmark.h>
#include "rdwr.h"
using namespace std;

char file_name[] = "./test/4G.txt";

// static void BM_block_read(benchmark::State& state) {
//   for (auto _: state){
//     state.PauseTiming();
//     int block_size = state.range(0);
//     int block_count = (1<<30) / block_size * 4;
//     state.ResumeTiming();
//     block_read(file_name, block_size, block_count);
//   }
// }
// BENCHMARK(BM_block_read)->RangeMultiplier(2)->Range(1<<9, 1<<11);

static void BM_read_and_write(benchmark::State& state) {
  for (auto _: state){
    state.PauseTiming();
    char buf[BUFSIZ];
    int block_size = state.range(0);
    int block_count = (1<<30) / block_size * 4;
    snprintf(buf, sizeof(buf),
      "./build/run ./test/test.iso -r %d %d && ./build/run ./test/test3.iso -w %d %d",
      block_size, block_count, block_size, block_count);
    state.ResumeTiming();
    system(buf);
  }
}
BENCHMARK(BM_read_and_write)->RangeMultiplier(2)->Range(1<<9, 1<<12);

static void BM_dd(benchmark::State& state) {
  for (auto _: state){
    state.PauseTiming();
    char buf[BUFSIZ];
    int block_size = state.range(0);
    int block_count = (1<<30) / block_size * 4;
    snprintf(buf, sizeof(buf),
      "dd if=test/test.iso of=test/test2.iso bs=%d count=%d status=none",
      block_size, block_count);
    state.ResumeTiming();
    system(buf);
  }
}
BENCHMARK(BM_dd)->RangeMultiplier(2)->Range(1<<9, 1<<12);

BENCHMARK_MAIN();