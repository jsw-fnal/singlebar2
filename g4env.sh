source /cvmfs/sft.cern.ch/lcg/views/LCG_96rc1/x86_64-centos7-gcc8-opt/setup.sh
export CXX=`which g++`
export CC=`which gcc`

source $ROOTSYS/bin/thisroot.sh
export LIBRARY_PATH=./fakelib:$LIBRARY_PATH
export LD_LIBRARY_PATH=./fakelib:$LD_LIBRARY_PATH

