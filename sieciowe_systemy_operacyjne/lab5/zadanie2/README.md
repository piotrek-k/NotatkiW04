Program można przetestować komendą

```
./run_parallel.sh "./build/shared_mem.out 0" "./build/shared_mem.out 1" "./build/shared_mem.out 2" "./build/shared_mem.out 3" "./build/shared_mem.out 4"
```

Żeby wyłączyć rozwiązanie zakleszczenia należy ustawić stałą `SWITCH_FORK_ORDER_FOR_FIRST_PHILOSOPHER` na wartość `0`.