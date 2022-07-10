#!/usr/bin/env python

# scan trials with different particles,E and plot light entering SiPM

# note python2 is assumed b/c we're using CMS releases
from __future__ import print_function
import ROOT as r
import os, sys
#r.gROOT.SetBatch(True)

def GetMean(tree,branch):
    tree.Draw(branch)
    mean=r.gROOT.FindObject('htemp').GetMean()
    return mean

GEANTDIR=os.environ['HOME']+'/single_bar2/PWO/si_gap'

Egen=['300MeV','1GeV','3GeV','10GeV','30GeV']
part=['el','mu','pi']


tgC={}
tgS={}

tcE=r.TCanvas()

for p in part:
    tgC[p]=r.TGraph()
    tgS[p]=r.TGraph()
    tgC[p].SetLineWidth(2)
    tgS[p].SetLineWidth(2)
    pm=20
    col=2
    title="electron"
    if p=="mu": 
        pm=21
        col=3
        title="muon"
    elif p=="pi": 
        pm=22
        col=4
        title="pion"
    tgC[p].SetMarkerStyle(pm)
    tgS[p].SetMarkerStyle(pm)
    tgC[p].SetLineColor(col)
    tgS[p].SetLineColor(col)
    tgC[p].SetMarkerColor(col)
    tgS[p].SetMarkerColor(col)
    tgC[p].SetTitle(title)
    tgS[p].SetTitle(title)

    for E in Egen:
        file=GEANTDIR + "/%s_%s.root"%(p,E)
        tf=r.TFile(file)
        e=float(E[:E.find("eV")-1])
        if e==300
        if 'M' in E : e=e/1000
        n=GetMean(tf.Get("tree"),"SDCdetected_r_C")
        tgC[p].SetPoint(tgC[p].GetN(),e,n)
        n=GetMean(tf.Get("tree"),"SDSdetected_r_S")
        tgS[p].SetPoint(tgS[p].GetN(),e,n)

tcS=r.TCanvas()
tmS=r.TMultiGraph()
tmS.SetTitle("Scintillation photons to 6x6 SiPM (PWO,Silicone);E (GeV);<N> photons")
for g in tgS:
    tmS.Add(tgS[g])

tmS.Draw("APL")
tcS.cd().BuildLegend()    
tcS.Print("ScintLight.pdf")


tcC=r.TCanvas()
tmC=r.TMultiGraph()
tmC.SetTitle("Cherenkov photons to 6x6 SiPM (PWO,Silicone);E (GeV);<N> photons")
for g in tgC:
    tmC.Add(tgC[g])

tmC.Draw("APL")
tcC.cd().BuildLegend()    
tcC.Print("CerenLight.pdf")






print('Hit return to exit')
sys.stdout.flush() 
raw_input('')
