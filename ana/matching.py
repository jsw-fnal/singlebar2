#!/usr/bin/env python

# scan trials with different matching materials between PWO and SiPM

# note python2 is assumed b/c we're using CMS releases
from __future__ import print_function
import ROOT as r
import os, sys
r.gROOT.SetBatch(True)

GEANTDIR='/store/hirosky/GeantFiles'
PWOAIR=GEANTDIR+'/PWO/air_gap/el_10GeV.root'
PWOOG=GEANTDIR+'/PWO/og_gap/el_10GeV.root'
PWOSI=GEANTDIR+'/PWO/si_gap/el_10GeV.root'

fAIR=r.TFile(PWOAIR)
fOG=r.TFile(PWOOG)
fSI=r.TFile(PWOSI)

tAIR=fAIR.Get("tree")
tOG=fOG.Get("tree")
tSI=fSI.Get("tree")


def GetMean(tree,branch):
    tree.Draw(branch)
    mean=r.gROOT.FindObject('htemp').GetMean()
    return mean

# photons entering SiPM windows
NCAIR=GetMean(tAIR,"SDCdetected_r_C")
NSAIR=GetMean(tAIR,"SDSdetected_r_S")
NCOG=GetMean(tOG,"SDCdetected_r_C")
NSOG=GetMean(tOG,"SDSdetected_r_S")
NCSI=GetMean(tSI,"SDCdetected_r_C")
NSSI=GetMean(tSI,"SDSdetected_r_S")

print('NCAIR: ',NCAIR)
print('NCOG: ',NCOG)
print('NCSI: ',NCSI)

print('NSAIR: ',NSAIR)
print('NSOG: ',NSOG)
print('NSSI: ',NSSI)

print('Repeat with optically perfect surface')
PWOSI_OP=GEANTDIR+'/PWO/si_gap_OP/el_10GeV.root'
fSI_OP=r.TFile(PWOSI_OP)
tSI_OP=fSI_OP.Get("tree")
NCSI_OP=GetMean(tSI_OP,"SDCdetected_r_C")
NSSI_OP=GetMean(tSI_OP,"SDSdetected_r_S")
print('NCSI_OP: ',NCSI_OP)
print('NSSI_OP: ',NSSI_OP)

print('Hit return to exit')
#sys.stdout.flush() 
#raw_input('')
