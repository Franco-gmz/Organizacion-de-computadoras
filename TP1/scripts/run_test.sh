#!/bin/bash
./compile_c.sh 
./pbm_files_c.sh 
./compile_s.sh 
./pbm_files_s.sh
./compile_pbm_test.sh
./../bin/pbm_test

