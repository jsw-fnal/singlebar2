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

Note: each time you open a new terminal, you will need to source the g4env.sh script to set up you environment.  The first cmake command is only needed the fist time the code is built.  For subsequent changes it is only necessary to type 'make'.

## View the geometry / run interactively

```bash
./CV_Testbeam -c template.cfg -u Qt  
```
## Run the events defined in run.mac

```bash
./CV_Testbeam -c template.cfg -m run.mac -o test
# -c config file
# -m particle source
# -o output file
```

## Use the runner script

```bash
python runner.py -b <beam> -G <E in GeV> of -M <E in MeV> -n <events> -o<outputfile>
use standard GEANT particle names:  [e-,pi+,mu-,gamma,etc]
example: python runner.py -bpi+ -G10 -n10 -opi_test
```

## Bulk running
use the generate_temp.sh in `./template`
```bash
cd template 
source generate_temp.sh
```

## Root file

__Histograms__

lambda of photons produced: (f)ront/(rear) crystal, Cherenkov/Scintillation light
- h_phot_lambda_ECAL_f_produce_Ceren
- h_phot_lambda_ECAL_f_produce_Scin
- h_phot_lambda_ECAL_r_produce_Ceren
- h_phot_lambda_ECAL_r_produce_Scin

time of photon production (ns)
- h_phot_time_ECAL_f_produce_Ceren
- h_phot_time_ECAL_f_produce_Scin
- h_phot_time_ECAL_r_produce_Ceren
- h_phot_time_ECAL_r_produce_Scin

time of photon detected: SiPM(F) in front SiPM(C/S) in rear, Cherenkov/Scintillation light
- h_phot_time_SiPMF_Ceren
- h_phot_time_SiPMF_Scin
- h_phot_time_SiPMC_Ceren
- h_phot_time_SiPMC_Scin
- h_phot_time_SiPMS_Ceren
- h_phot_time_SiPMS_Scin

photons collected in front sipm
- h_phot_lambda_SiPMF_f_Ceren
- h_phot_lambda_SiPMF_f_Scin

photons collected in rear sipms
- h_phot_lambda_SiPMC_r_Ceren
- h_phot_lambda_SiPMC_r_Scin 
- h_phot_lambda_SiPMS_r_Ceren
- h_phot_lambda_SiPMS_r_Scin

__Branches in tree__ (partial list)

beam parameters
- Branch("inputMomentum", "vector<float>", &inputMomentum)  3-momentum, MeV
- Branch("primaryID", &this->primaryID, "primaryID/I") beam particle ID

energy deposited in MeV, total and by ionization only
- Branch("depositedEnergyECAL_f", &this->depositedEnergyECAL_f, "depositedEnergyECAL_f/F") 
- Branch("depositedEnergyECAL_r", &this->depositedEnergyECAL_r, "depositedEnergyECAL_r/F") 
- Branch("depositedIonEnergyTotal", &this->depositedIonEnergyTotal, "depositedIonEnergyTotal/F")
- Branch("depositedIonEnergyECAL_f", &this->depositedIonEnergyECAL_f, "depositedIonEnergyECAL_f/F")
- Branch("depositedIonEnergyECAL_r", &this->depositedIonEnergyECAL_r, "depositedIonEnergyECAL_r/F")
  
count of Scint and Cherenkov photons produced in crystal bars
- Branch("ECAL_f_total_S", &this->ECAL_f_total_S, "ECAL_f_total_S/I")
- Branch("ECAL_f_total_C", &this->ECAL_f_total_C, "ECAL_f_total_C/I")
- Branch("ECAL_r_total_S", &this->ECAL_r_total_S, "ECAL_r_total_S/I")
- Branch("ECAL_r_total_C", &this->ECAL_r_total_C, "ECAL_r_total_C/I")  

count of photons exiting front and rear crystals
- Branch("ECAL_f_exit_S", &this->ECAL_f_exit_S, "ECAL_f_exit_S/I")
- Branch("ECAL_f_exit_C", &this->ECAL_f_exit_C, "ECAL_f_exit_C/I")
- Branch("ECAL_r_exit_S", &this->ECAL_r_exit_S, "ECAL_r_exit_S/I")
- Branch("ECAL_r_exit_C", &this->ECAL_r_exit_C, "ECAL_r_exit_C/I")

count of photons detected in three SiPM detectors
- Branch("SDFdetected_f_S", &this->SDFdetected_f_S, "SDFdetected_f_S/I")
- Branch("SDFdetected_f_C", &this->SDFdetected_f_C, "SDFdetected_f_C/I")
- Branch("SDCdetected_r_S", &this->SDCdetected_r_S, "SDCdetected_r_S/I")
- Branch("SDCdetected_r_C", &this->SDCdetected_r_C, "SDCdetected_r_C/I")
- Branch("SDSdetected_r_S", &this->SDSdetected_r_S, "SDSdetected_r_S/I")
- Branch("SDSdetected_r_C", &this->SDSdetected_r_C, "SDSdetected_r_C/I")

## GEANT4 Resources
- [GEANT4 Homepage](https://geant4.web.cern.ch/)
- [GEANT4 Tutorials/Schools](https://geant4.web.cern.ch/past-events)
  - Example [beginner's course](https://indico.cern.ch/event/865808/timetable/)


## Template to access and build the examples
```
ls $G4EXAMPLES
cd /tmp; mkdir geant-test; cd geant-test
# build a specific example, eg
cmake $G4EXAMPLES/basic/B5
make
./exampleB5
```
