int makePlot_LoI_Ext_Mom()
{
  TChain EICTree("EICTree");
  //TString str("...basename..");
  // str += integer
  // str += ".root"
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_1.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_2.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_3.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_4.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_5.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_6.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_7.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_8.root");
  EICTree.Add("/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_9.root");

  /*
  char *file[20];

  for(int i=0; i<10; i++)
    {
           sprintf(file, "/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_%d\n", i);
	   std::cout << file << endl;
           //EICTree.Add(file);
           //cout << "/gpfs/mnt/gpfs02/phenix/spin3/nfeege/eic/pythiaeRHIC_setting1/pythia_ep_10_250_run_[i].root" << endl;
    }
  */

  EICTree->Print();
  EICTree->Scan("nTracks");

  const int NPARTMAX = 1000;

  Double_t x, Q2, y, W2, nu;
  Int_t nTracks;
  Int_t PdgCode[NPARTMAX];
  //  Int_t KS[NPARTMAX];
  Double_t px[NPARTMAX];
  Double_t py[NPARTMAX];
  Double_t pz[NPARTMAX];
  Double_t p[NPARTMAX];
  Double_t E[NPARTMAX];
  Double_t eta[NPARTMAX];

  TBranch *b_x;
  TBranch *b_Q2;
  TBranch *b_y;
  TBranch *b_W2;
  TBranch *b_nu;
  TBranch *b_nTracks;
  TBranch *b_PdgCode;
  TBranch *b_px;
  TBranch *b_py;
  TBranch *b_pz;
  TBranch *b_p;
  TBranch *b_E;
  TBranch *b_eta;

  EICTree.SetBranchAddress("x", &x, &b_x);
  EICTree.SetBranchAddress("QSquared", &Q2, &b_Q2);
  EICTree.SetBranchAddress("y", &y, &b_y);
  EICTree.SetBranchAddress("WSquared", &W2, &b_W2);
  EICTree.SetBranchAddress("nu", &nu, &b_nu);
  EICTree.SetBranchAddress("nTracks", &nTracks, &b_nTracks);
  EICTree.SetBranchAddress("particles.id", &PdgCode, &b_PdgCode);
  EICTree.SetBranchAddress("particles.px", &px, &b_px);
  EICTree.SetBranchAddress("particles.py", &py, &b_py);
  EICTree.SetBranchAddress("particles.pz", &pz, &b_pz);
  EICTree.SetBranchAddress("particles.p", &p, &b_p);
  EICTree.SetBranchAddress("particles.E", &E, &b_E);
  EICTree.SetBranchAddress("particles.eta", &eta, &b_eta);

  TH2F *h_peta_e = new TH2F("h_peta_e", "", 100, -4, 3, 100, 0, 50 ); //250x015 10M

  //  EICTree->Draw("sqrt(particles.px**2 + particles.py**2 + particles.pz**2):eta>>h_peta_e", "particles.id == 11", "colz");

  Int_t nEv = 10;
    // int( EICTree.GetEntries() );
  printf("nEntries to process = %d\n",nEv);

  for(Int_t iEv = 0; iEv < nEv; iEv++)
    {

      EICTree.GetEntry(iEv);
      std::cout << "Run Event:" << iEv << endl;
      std::cout << "NPart:" << nTracks << endl;

      for(int ip = 0 ; ip < nTracks; ip++)
	{
	  std::cout << "NPart:" << ip << endl;

	  if(PdgCode[ip] == 11)
	    {
	      //std::cout << eta[ip] << endl;
	      Double_t eta_fill = eta[ip];
	      Double_t p_fill = TMath::sqrt(px[ip]**2 + py[ip]**2 + pz[ip]**2);
	      h_peta_e->Fill(eta_fill, p_fill);
	    }
	}
    }

  //  h_peta_e->Fill(x, Q2, 1.);
  //  h_peta_e->Draw();

  TCanvas *c_peta_e = new TCanvas( "c_peta_e" );
  c_peta_e->SetLogz();

  h_peta_e->Draw("colz");
  //  EICTree->Draw("sqrt(px**2 + py**2 + pz**2):eta>>h_peta_e", "PdgCode == 11", "colz");
  //  EICTree->Draw("sqrt((particles.fPx)**2 + (particles.fPy)**2 + (particles.fPz)**2 ):TMath::ASinH(particles.fPz/sqrt((particles.fPx)**2 + (particles.fPy)**2))>>h_peta_e", electron_cut && mother_cut && "Q2 > 1", "colz");

  h_peta_e->GetXaxis()->SetTitle("Pseudorapidity #eta");
  h_peta_e->GetYaxis()->SetTitle("Electron Momentum p_{e-} [GeV]");

  return 0;
}
