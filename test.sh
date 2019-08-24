#!/bin/bash
cc -g $1/$1_test.c -o /tmp/kdb_test &&\
valgrind --leak-check=full --error-exitcode=1 /tmp/kdb_test
#rm -f a.out
