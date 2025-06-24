#!/bin/bash
# Check if load parameter is given
if [ $1 == "" ]
then
  echo Please run like ./run.sh 5000000
fi
# compile the source code
gcc load.c -o load1.x

# create copies of executable with different names. This can help to identify them in top.
cp load1.x load2.x
cp load1.x load3.x
cp load1.x load4.x
cp load1.x load5.x

# just to make the parameter verbose
export LOAD=$1

# launch all programs in parallel. Without the '&' they would be executed sequentially.
./load1.x 1 10 15 $LOAD &
./load2.x 2 10 15 $LOAD & 
./load3.x 3 10 15 $LOAD &
./load4.x 4 10 15 $LOAD &
./load5.x 5 10 15 $LOAD
