#!/usr/bin/env python

# plot distribution of photons to rear SiPMs

# note python2 is assumed b/c we're using CMS releases
from __future__ import print_function
import ROOT as r
import os, sys
#r.gROOT.SetBatch(True)

E="10GeV"
GEANTDIR='/store/hirosky/GeantFiles/PWO/si_gap'

tfel=r.TFile(GEANTDIR + "/el_%s.root"%E)
tfmu=r.TFile(GEANTDIR + "/mu_%s.root"%E)
tfpi=r.TFile(GEANTDIR + "/pi_%s.root"%E)

tc=r.TCanvas()
tc.Divide(2,3)

#mystyle = r.TStyle("mystyle","Better Style");
#mystyle.SetLabelSize(0.08,"xy")
#mystyle.SetTitleSize(0.08,"xy")
#r.gROOT.SetStyle("mystyle")
#tc.UseCurrentStyle()

tc.cd(1)
tfel.Get("tree").Draw("SDSdetected_r_S>>h1(100,0,5e4)")
r.gROOT.FindObject('h1').SetTitle("# Scint to 6x6 SIPM PWO/10GeV Electrons;N#gamma")
tc.cd(2)
tfel.Get("tree").Draw("SDCdetected_r_C>>h2(100,0,6000)")
r.gROOT.FindObject('h2').SetTitle("# ScintCeren to 6x6 SIPM PWO/10GeV Electrons;N#gamma")

tc.cd(3)
tfmu.Get("tree").Draw("SDSdetected_r_S>>h3(100,0,5e4)")
r.gROOT.FindObject('h3').SetTitle("# Scint to 6x6 SIPM PWO/10GeV Muons;N#gamma")
tc.cd(4)
tfmu.Get("tree").Draw("SDCdetected_r_C>>h4(100,0,6000)")
r.gROOT.FindObject('h4').SetTitle("# ScintCeren to 6x6 SIPM PWO/10GeV Muons;N#gamma")

tc.cd(5)
tfpi.Get("tree").Draw("SDSdetected_r_S>>h5(100,0,5e4)")
r.gROOT.FindObject('h5').SetTitle("# Scint to 6x6 SIPM PWO/30GeV Pions;N#gamma")
tc.cd(6)
tfpi.Get("tree").Draw("SDCdetected_r_C>>h6(100,0,6000)")
r.gROOT.FindObject('h6').SetTitle("# ScintCeren to 6x6 SIPM PWO/10GeV Pions;N#gamma")

tc.Update()
tc.cd()
tc.Print("photon_dists.pdf")

print('Hit return to exit')
sys.stdout.flush() 
if sys.version_info.major==2:
    raw_input('')
else:
    input()
