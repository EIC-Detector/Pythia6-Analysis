


int makePlot_EtaDistribution(
			     const TString infile = // /path/to/input/file
			     )
{
  tkStyle->SetOptStat(kFALSE);

  TFile *f_pyth = new TFile( infile, "OPEN");
  TTree* T_pyth = (TTree*)f_pyth->Get("T");
  T->Print();

  TCut electron_cut = "particles.fPdgCode == 11";
  TCut Pion_cut = "abs(particles.fPdgCode) == 211 || particles.fPdgCode == 111";

  TH1F *h_eta = new TH1F("h_eta", "", 60, -6, 6);
  TH1F *h_eta_e = (TH1F*)h_eta->Clone();
  TCanvas *c_eta = new TCanvas("c_eta");

  T->Draw("TMath::ASinH(particles.fPz/sqrt(((particles.fPx)**2 + (particles.fPy)**2)))>>h_eta", Pion_cut);
  h_eta->SetLineStyle(2);
  T->Draw("TMath::ASinH(particles.fPz/sqrt(((particles.fPx)**2 + (particles.fPy)**2)))>>h_eta_e", electron_cut && "particles.fMother[][0] == 1", "same");

  h_eta->GetXaxis()->SetTitle("Pseudorapidity #eta");
  h_eta->GetYaxis()->SetTitle("dN/d#eta");

  TLegend* leg_eta = new TLegend( 0.25, 0.70, 0.45, 0.90);
  leg_eta->AddEntry(h_eta, "Pions", "L");
  leg_eta->AddEntry(h_eta_e, "Electrons", "L");
  leg_eta->Draw();

  c_eta->Print("EtaDistributions.png");

  return 0;
}
