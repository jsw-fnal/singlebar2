source /cvmfs/sft.cern.ch/lcg/views/LCG_101/x86_64-centos8-gcc11-opt/setup.sh
source $ROOTSYS/bin/thisroot.sh
export LIBRARY_PATH=./fakelib:$LIBRARY_PATH
export LD_LIBRARY_PATH=./fakelib:$LD_LIBRARY_PATH

# setup first build with
# cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/10.05.p01-76df0/x86_64-centos7-gcc8-opt/lib64/Geant4-10.5.1

