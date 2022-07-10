#!/usr/bin/env python

# note python2 is assumed b/c we're using CMS releases
from __future__ import print_function
import ROOT as r
import os, sys


GEANTDIR=os.environ['HOME']+'/single_bar2'
PWOFILE=GEANTDIR+'/PWO/air_gap/mu_10GeV.root'
BGOFILE=GEANTDIR+'/BGO/air_gap/mu_10GeV.root'

fPWO=r.TFile(PWOFILE)
fBGO=r.TFile(BGOFILE)

hPWO_C=fPWO.Get("h_phot_lambda_ECAL_f_produce_Ceren")
hPWO_S=fPWO.Get("h_phot_lambda_ECAL_f_produce_Scin")
hBGO_C=fBGO.Get("h_phot_lambda_ECAL_f_produce_Ceren")
hBGO_S=fBGO.Get("h_phot_lambda_ECAL_f_produce_Scin")

hPWO_C.Scale(1/hPWO_C.Integral())
hPWO_S.Scale(1/hPWO_S.Integral())
hBGO_C.Scale(1/hBGO_C.Integral())
hBGO_S.Scale(1/hBGO_S.Integral())


hPWO_C.SetLineColor(r.kMagenta)
hBGO_C.SetLineColor(r.kMagenta)
hPWO_S.SetLineColor(r.kBlue)
hBGO_S.SetLineColor(r.kBlue)

hPWO_S.SetTitle("Optial photon spectrum for 10 GeV muon in PWO;lambda [nm];Arbitrary units")
hBGO_S.SetTitle("Optial photon spectrum for 10 GeV muon in BGO;lambda [nm];Arbitrary units")


r.gStyle.SetOptStat(0)

tc=r.TCanvas()
tc.Divide(1,2)
pad=tc.cd(1)
hPWO_S.Draw('c')
hPWO_C.Draw('samec')
pad.BuildLegend()

pad=tc.cd(2)
hBGO_S.Draw('c')
hBGO_C.Draw('samec')
pad.BuildLegend()

tc.Print("spectrum.pdf")

print('Hit return to exit')
sys.stdout.flush() 
raw_input('')
