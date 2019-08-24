#!/bin/bash
set -e

MODULES=(string entry list hash)

function test_module() {
	cc -g $1/$1_test.c -o /tmp/kdb_test &&\
		valgrind --leak-check=full --error-exitcode=1 /tmp/kdb_test
}

for i in "${MODULES[@]}"
do
	printf '=%.0s' {1..80}
	echo
	echo ${i^^}
	printf '=%.0s' {1..80}
	echo

	test_module $i
done
