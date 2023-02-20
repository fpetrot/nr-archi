#!/bin/bash
gcc -O3 -c matmult-helpers.c
COND=0
SIZE=1536
PERFEVENTS=instructions,L1-icache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-dcache-load-misses,LLC-loads,LLC-load-misses,LLC-stores,power/energy-cores/,power/energy-ram/
# gcc sans optimisation
gcc -DCOND=$COND -DMSIZE=$SIZE -O0 matmult-helpers.o matmult-naive.c -o n
gcc -DCOND=$COND -DMSIZE=$SIZE -O0 matmult-helpers.o matmult-transpose.c -o t
gcc -DCOND=$COND -DMSIZE=$SIZE -O0 matmult-helpers.o matmult-cache.c -o c
echo "Perf pour naive O0"
perf stat -a -e $PERFEVENTS ./n
echo "Perf pour transpose O0"
perf stat -a -e $PERFEVENTS ./t
echo "Perf pour cache O0"
perf stat -a -e $PERFEVENTS ./c

# gcc avec optimisations max génériques
gcc -DCOND=$COND -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-naive.c -o n
gcc -DCOND=$COND -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-transpose.c -o t
gcc -DCOND=$COND -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-cache.c -o c
echo "Perf pour naive O3"
perf stat -a -e $PERFEVENTS ./n
echo "Perf pour transpose O3"
perf stat -a -e $PERFEVENTS ./t
echo "Perf pour cache O3"
perf stat -a -e $PERFEVENTS ./c

# gcc avec optimisations max génériques sans volatile
gcc -DCOND=$COND -Dvolatile="" -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-naive.c -o n
gcc -DCOND=$COND -Dvolatile="" -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-transpose.c -o t
gcc -DCOND=$COND -Dvolatile="" -DMSIZE=$SIZE -O3 matmult-helpers.o matmult-cache.c -o c
echo "Perf pour naive O3 sans volatile"
perf stat -a -e $PERFEVENTS ./n
echo "Perf pour transpose O3 sans volatile"
perf stat -a -e $PERFEVENTS ./t
echo "Perf pour cache O3 sans volatile"
perf stat -a -e $PERFEVENTS ./c
