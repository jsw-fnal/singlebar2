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
            
# using template cfg files, make files for this run
import tempfile, shutil, os
#def make_tmpfiles(f_run,f_cfg):
#    tmp_run = tempfile.mkstemp()[1]
#    tmp_cfg = tempfile.mkstemp()[1]
#    shutil.copy2(f_run, tmp_run)
#    shutil.copy2(f_cfg, tmp_cfg)
#    return tmp_run,tmp_cfg

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
                        help="Beam particle type (eg, pi-, mu-, e-)"
    )
    parser.add_argument("-d", "--outdir", default=".",
                        help="Output directory name [.]"
    )
    parser.add_argument("-o", "--output", default="test",
                        help="Output file name[.root]"
    )
    parser.add_argument("-f", "--force", default=None,
                        help="Force overwrite",
                        action="store_true"
    )
    parser.add_argument("-g", "--SiPMgapMaterial", default="1",
                        help="Material between xtal face and SiPM ([1 air], 2 optical grease, 5 silcone"
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
    if os.path.exists(outfile+".root"):
        if args.force:
            print("Replacing",outfile+".root")
        else:
            print(outfile+".root exists, exiting...")
            sys.exit(1)

    if not args.outdir==".":
        if not os.path.exists(args.outdir):
            os.makedirs(args.outdir)
        

    print("Simulating",args.beam,"beam at",E,Eunit)
    print("Output:",outfile+".root");
    

    run_mac = args.outdir+"/"+outfile+'.runmac'
    shutil.copy2('run.mac', run_mac)
    temp_cfg = args.outdir+"/"+outfile+'.cfg'
    shutil.copy2('template.cfg',temp_cfg)
    outfile=args.outdir+"/"+outfile
    logfile=outfile+".log"

    print(run_mac,temp_cfg)
    update_param(run_mac,['/run/beamOn',args.nevent])
    update_param(run_mac,['/gps/energy',str(E)+" "+Eunit])
    update_param(run_mac,['/gps/particle',args.beam])
    update_param(temp_cfg,['gap_material',' = '+args.SiPMgapMaterial])
    
    # ./CEPC_CaloTiming -c template.cfg -m run.mac -o test
    EXE=os.getcwd()+'/CV_Testbeam'
    
    command = EXE + ' -m ' + run_mac + ' -c ' + temp_cfg + ' -o ' + outfile +  ' > ' + logfile
    print(command,command.split())
    # use subprocess.run for python3
    #subprocess.call(command.split(), shell=True)
    subprocess.call(command, shell=True)
