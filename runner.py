#! /usr/bin/python

from __future__ import print_function
import fileinput
import argparse
import sys
import subprocess

def update_param(file,tp):
    #print(file)
    for line in fileinput.input(file, inplace=True):
        # inside this loop the STDOUT will be redirected to the file
        # the comma after each print statement is needed to avoid 
        # double line breaks
        #print line.replace("100", "helloworld"),
        if line.startswith(tp[0]):
            print(tp[0],tp[1])
        else: print (line.strip()),
            

import tempfile, shutil, os
def make_tmpfiles(f_run,f_cfg):
    tmp_run = tempfile.mkstemp()[1]
    tmp_cfg = tempfile.mkstemp()[1]
    shutil.copy2(f_run, tmp_run)
    shutil.copy2(f_cfg, tmp_cfg)
    return tmp_run,tmp_cfg

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='GEANT Runner Script')
    parser.add_argument("-G", "--GeV", default=-1, type=float,
                        help="Particle energy in GeV"
    )
    parser.add_argument("-M", "--MeV", default=-1, type=float,
                        help="Particle energy in MeV"
    )
    parser.add_argument("-n", "--nevent", type=int, default=100,
                        help="Number of events to run"
    )
    parser.add_argument("-b", "--beam", default="e-",
                        help="Beam particle type"
    )
    parser.add_argument("-o", "--output", default="test",
                        help="Output file name[.root]"
    )
    args = parser.parse_args()
    
    if args.GeV>0: 
        E=args.GeV
        Eunit="GeV"
    elif args.MeV>0:
        E=args.MeV
        Eunit="MeV"
    else:
        print("Invalid particle energy, use -G or -M flag")
        sys.exit(1)
    beam=args.beam
    outfile=args.output
    if outfile.endswith(".root"): outfile=outfile[:-5]

    print("Simulating",args.beam,"beam at",E,Eunit)
    print("Output:",outfile+".root");
    

    run_mac,temp_cfg = make_tmpfiles('run.mac','template.cfg')
    #print(run_mac,temp_cfg)
    update_param(run_mac,['/run/beamOn',args.nevent])
    update_param(run_mac,['/gps/energy',str(E)+" "+Eunit])
    update_param(run_mac,['/gps/particle',args.beam])
    
    # ./CEPC_CaloTiming -c template.cfg -m run.mac -o test 
    command = "./CEPC_CaloTiming -m "+run_mac+" -c "+temp_cfg+" -o "+outfile
    #print(command,command.split())
    # use subprocess.run for python3
    subprocess.call(command.split())
