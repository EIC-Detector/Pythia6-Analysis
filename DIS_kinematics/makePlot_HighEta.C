int makePlot_HighEta(
		     const TString infile = "/direct/phenix+u/tkrahul/EIC_tkrahulik_work/Pythia_studies/files/pythia.ep.250x010.10000000events.seed505211968_Subset10000.root",
		     )

{
  tkStyle->SetOptStat(kFALSE);

  TFile *f_pyth = new TFile( infile, "OPEN");
  TTree* T_pyth = (TTree*)f_pyth->Get("T");
  T_pyth->Print();

  TCut eta_cut_n3n2 = "TMath::ASinH(particles.fPz/sqrt((particles.fPx)**2 + (particles.fPy)**2)) > -3 && TMath::ASinH(particles.fPz/sqrt((particles.fPx)**2 + (particles.fPy)**2)) < -2";
  TCut eta_cut_4 = "TMath::ASinH(particles.fPz/sqrt((particles.fPx)**2 + (particles.fPy)**2)) > 4";

  TCut photon_cut = "particles.fPdgCode == 22";

  TH1F* h_eta =new TH1F("h_eta", "", 60, 0, 30);
  TCanvas *c_eta = new TCanvas("c_eta");
  T_pyth->Draw("sqrt(particles.fPx**2 + particles.fPy**2 + particles.fPz**2)>>h_eta", eta_cut_4 && photon_cut ,"goff" );
  h_eta->Draw();

  return 0;
}
