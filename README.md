# Single Bar

GEANT4-based simulation of a single bar for DualReadout purpose.

## Installing

The following works on the UVa NAS1 server:
```bash
source g4env.sh
cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/10.05.p01-76df0/x86_64-centos7-gcc8-opt/lib64/Geant4-10.5.1
cmake --build .
or
make
```

## Single event running
For the interactive runing:

Check the geometry through a detector viewing window
```bash
./CV_Testbeam -c template.cfg -u Qt  
```
Run the events defined in run.mac
```bash
./CV_Testbeam -c template.cfg -m run.mac -o test
# -c config file
# -m particle source
# -o output file
```

Use the runner script
```bash
python runner.py -b <beam> -G <E in GeV> of -M <E in MeV> -n <events> -o<outputfile>
use standard GEANT particle names:  [e-,pi+,mu-,gamma,etc]
example: python runner.py -bpi+ -G10 -n10 -opi_test
```


## Template to access and build the examples
```
ls $G4EXAMPLES
cd /tmp; mkdir geant-test; cd geant-test
cmake $G4EXAMPLES/basic/B5
make
./exampleB5
```


## Bulk running
use the generate_temp.sh in `./template`
```bash
cd template 
source generate_temp.sh
```




