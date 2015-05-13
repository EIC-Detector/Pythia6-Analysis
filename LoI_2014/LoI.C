const int NPARTMAX = 1000;

hadron()
// Hadron yield
{
  TFile* f = new TFile("pythia/tmp/pythia.ep.10x100_q1.1Mevents.root");
  // for 5x100: for Q^2>1 xsec=5.4e-4 mb => 1M events corresponds to 2pb
  //  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/Q2-CUT/pythia.ep.5x100.1Mevents.RadCor=0.Q2-0.1.root");
  // for 5x100: for Q^2>0.1 xsec=3e-3 mb => 1M events corresponds to 0.3pb

  TTree* treeDIS  = (TTree*)f->Get("EICTree");

  TH1F* hn = new TH1F("hn","log10(nu)",30,0,3);
  TH1F* hn_id = new TH1F("hn_id","log10(nu)",30,0,3);

  TH2F* hpeta = new TH2F("hpeta","",80,-4,4,50,0,50);

  //  EICTree->Draw("nu>>hn","inelasticity>0.01&&inelasticity<0.95&&QSquaredTrue>1&&QSquaredTrue<10&&KS<10&&id==211&&eta>-1&&eta<4","goff");
  //  hpi->Draw();
  //  return;

  Float_t Q2, y, nu;
  Int_t npart;
  Int_t id[NPARTMAX];
  Int_t parpid[NPARTMAX];
  Int_t orig[NPARTMAX];
  Int_t KS[NPARTMAX];
  Float_t eta[NPARTMAX];
  Float_t px[NPARTMAX];
  Float_t py[NPARTMAX];
  Float_t pz[NPARTMAX];
  Float_t E[NPARTMAX];
  Float_t pp[NPARTMAX];

  treeDIS->SetBranchAddress("QSquaredTrue",&Q2);
  treeDIS->SetBranchAddress("inelasticity",&y);
  treeDIS->SetBranchAddress("nu",&nu);

  treeDIS->SetBranchAddress("NumParticles",&npart);
  treeDIS->SetBranchAddress("KS",&KS);
  treeDIS->SetBranchAddress("orig",&orig);
  treeDIS->SetBranchAddress("eta",&eta);
  treeDIS->SetBranchAddress("id",&id);
  treeDIS->SetBranchAddress("px",&px);
  treeDIS->SetBranchAddress("py",&py);
  treeDIS->SetBranchAddress("pz",&pz);
  treeDIS->SetBranchAddress("E",&E);
  treeDIS->SetBranchAddress("p",&pp);

  int nEv = int(treeDIS->GetEntries());
  printf("nEntries to process = %d\n",nEv);

  float z;

  for( int ien=0; ien<nEv; ien++ ) {

    if( ien%10000 == 0 ) printf("nEvent = %d\n",ien);
    treeDIS->GetEvent(ien);

    if( y>0.01 && y<0.95 && Q2>2 && Q2<4 ) {
    //    if( y>0.01 && y<0.95 && Q2>100 && Q2<200 ) {

      for( int ip=0; ip<npart; ip++ ) {

	// pion+/-: id=+/-211
	// kaons+/-: id=+/-321
	// (anti)proton: id=-/+2212

	if( KS[ip]==1 && eta[ip]>-1 && eta[ip]<4 && id[ip]==321 ) { // K
	//	if( KS[ip]==1 && eta[ip]>-1 && eta[ip]<4 && id[ip]==2212 ) { // p
	  // z = (p*p_h)/(pq)
	  // Beam proton: ip=1
	  // Virtual photon: ip=2
	  z = (E[1]*E[ip]-px[1]*px[ip]-py[1]*py[ip]-pz[1]*pz[ip])/(E[1]*E[2]-px[1]*px[2]-py[1]*py[2]-pz[1]*pz[2]);

	  //	  hz->Fill(z);
	  //	  hn->Fill(nu);
	  if( z>0.4 && z<0.7 ) {
	    hn->Fill(log10(nu));
	    if( (fabs(eta[ip])<1&&pp[ip]<4) || (eta[ip]>1&&eta[ip]<2&&pp[ip]<15) || (eta[ip]>1&&eta[ip]<4&&pp[ip]>15&&pp[ip]<60) ) hn_id->Fill(log10(nu));
	    else hpeta->Fill(eta[ip],pp[ip]);
	  }

	}

      }
      
    } // if( Q2

  } // for( int ien=0

  hn->Draw();
  hn_id->SetLineColor(2);  
  hn_id->Draw("same");  
    
  //  hpeta->Draw("colz");
}


nu_Q2()
{
  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/Q2-CUT/pythia.ep.5x100.1Mevents.RadCor=0.Q2-0.1.root");
  
  const float xmin = 0; // Means 10**(-5)
  const float xmax = 3.5;
  const int xnbin = 35;
  Float_t xbins[xnbin+1];
  for( int i=0; i<xnbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/xnbin);

  const float qmin = 0;
  const float qmax = 3; // Means 10**(3)
  const int qnbin = 60;
  Float_t qbins[qnbin+1];
  for( int i=0; i<qnbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/qnbin);

  TH2F* hqnu = new TH2F("hqnu","#nu vs Q2",qnbin,qbins,xnbin,xbins);

  EICTree->Draw("nu:QSquaredTrue>>hqnu","inelasticity>0.01&&inelasticity<0.95","goff");

  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,500,550);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->SetLogx();
  pad1->SetLogy();

  pad1->cd();
  hqnu->Draw("colz");
}


xq2_pol()
// See xq2_pol.C
{
}


kin()
// Q2x and Ee vs eta
{
  float Ecut = 2; // energy cut for eID

  //  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/Q2-CUT/pythia.ep.5x100.5Mevents.RadCor=0.Q2-0.1.root");
  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/Q2-CUT/pythia.ep.10x250.1Mevents.RadCor=0.Q2-0.1.root");
  //  TFile* f = new TFile("/phenix/spin/data77/phnxsp01/shura/dis/pythia/tmp/pythia.ep.5x250_q10.1Mevents.root");

  printf("!!! Don't forget to put correct value for electron beam energy in: QSquaredTrue/2./10./(1-cos(3.1415926-theta))\n Now it is 10 GeV\n");

  const float xmin = -4; // Means 10**(-5)
  const float xmax =  0;
  const int xnbin = 40;
  Float_t xbins[xnbin+1];
  for( int i=0; i<xnbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/xnbin);

  const float qmin = 0;
  const float qmax = 3; // Means 10**(3)
  const int qnbin = 60;
  Float_t qbins[qnbin+1];
  for( int i=0; i<qnbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/qnbin);

  char* cond0 = "QSquaredTrue>1&&inelasticity<0.95&&inelasticity>0.01";
  char cond[256];

  TH2F* hqr = new TH2F("hqr","log_{10}(Q2) vs #eta",50,-4,1,60,0,3);
  EICTree->Draw("log10(QSquaredTrue):-log(tan(theta/2.))>>hqr",cond0,"goff");
  TH2F* hxr = new TH2F("hxr","log_{10}(x) vs #eta",50,-4,1,50,-5,0);
  EICTree->Draw("log10(x):-log(tan(theta/2.))>>hxr",cond0,"goff");

  TH2F* hqx = new TH2F("hqx","Q2 vs x",xnbin,xbins,qnbin,qbins);
  EICTree->Draw("QSquaredTrue:x>>hqx",cond0,"goff");

  TH2F* hqx_ecut = new TH2F("hqx_ecut","Q2 vs x",xnbin,xbins,qnbin,qbins);
  sprintf(cond,"%s&&QSquaredTrue/2./10./(1-cos(3.1415926-theta))>%f",cond0,Ecut);
  EICTree->Draw("QSquaredTrue:x>>hqx_ecut",cond,"goff");

  //  TH2F* hqx_forw = new TH2F("hqx_forw","log_{10}(Q2) vs log_{10}(x)",50,-5,0,60,0,3);
  //  EICTree->Draw("log10(QSquaredTrue):log10(x)>>hqx_forw","QSquaredTrue>1&&-log(tan(theta/2.))<-1","goff");
  sprintf(cond,"%s&&-log(tan(theta/2.))<-1",cond0);
  TH2F* hqx_forw = new TH2F("hqx_forw","Q2 vs x",xnbin,xbins,qnbin,qbins);
  EICTree->Draw("QSquaredTrue:x>>hqx_forw",cond,"goff");

  //  TH2F* hqx_cent = new TH2F("hqx_cent","log_{10}(Q2) vs log_{10}(x)",50,-5,0,60,0,3);
  //  EICTree->Draw("log10(QSquaredTrue):log10(x)>>hqx_cent","QSquaredTrue>1&&abs(-log(tan(theta/2.)))<1","goff");
  sprintf(cond,"%s&&abs(-log(tan(theta/2.)))<1",cond0);
  TH2F* hqx_cent = new TH2F("hqx_cent","Q2 vs x",xnbin,xbins,qnbin,qbins);
  EICTree->Draw("QSquaredTrue:x>>hqx_cent",cond,"goff");

  TH2F* her = new TH2F("her","Ee vs eta",70,-3.5,3.5,60,0,30);
  EICTree->Draw("QSquaredTrue/2./10./(1-cos(3.1415926-theta)):-log(tan(theta/2.))>>her",cond0,"goff");

  TH1F* he_cent = new TH1F("he_cent","Ee, |#eta|<1",120,0,30);
  sprintf(cond,"%s&&abs(-log(tan(theta/2.)))<1",cond0);
  EICTree->Draw("QSquaredTrue/2./10./(1-cos(3.1415926-theta))>>he_cent",cond,"goff");

  TH1F* he_forw = new TH1F("he_forw","Ee, #eta<-1",120,0,30);
  sprintf(cond,"%s&&-log(tan(theta/2.))<-1",cond0);
  EICTree->Draw("QSquaredTrue/2./10./(1-cos(3.1415926-theta))>>he_forw",cond,"goff");
  
  TFile* ff = new TFile("kin.root","RECREATE");
  hqr->Write();
  hxr->Write();
  hqx->Write();
  hqx_cent->Write();
  hqx_forw->Write();
  he_cent->Write();
  he_forw->Write();
  ff->Close();

  gStyle->SetTitleFontSize(0.08);


  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,600,350);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,0.5,1.0);
  pad2 = new TPad("pad2","This is pad2",0.5,0.0,1.0,1.0);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLogx();
  pad1->SetLogy();
  float zmax  = hqx_forw->GetMaximum();
  hqx_forw->SetTitle("");
  hqx_forw->SetXTitle("x");
  hqx_forw->SetYTitle("Q^{2} (GeV^{2})");
  hqx_forw->Draw("col2");

  pad2->cd();
  pad2->SetLogx();
  pad2->SetLogy();
  hqx_cent->SetMaximum(zmax);
  hqx_cent->SetTitle("");
  hqx_cent->SetXTitle("x");
  hqx_cent->SetYTitle("Q^{2} (GeV^{2})");
  hqx_cent->Draw("col2");

  c2 = new TCanvas("c2","The Ntuple canvas",100,100,600,550);
  c2->Range(0,0,1,1);
  pad21 = new TPad("pad31","This is pad1",0.0,0.0,1.0,1.0);
  pad21->Draw();
  pad21->SetLogx();
  pad21->SetLogy();

  pad21->cd();
  hqx_ecut->Divide(hqx);
  hqx_ecut->SetTitle("");
  hqx_ecut->SetXTitle("x");
  hqx_ecut->SetYTitle("Q^{2} (GeV^{2})");
  hqx_ecut->Draw("colz");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.04);
  tex->DrawLatex(0.20,0.82,"ePHENIX e+p 10 GeV #times 250 GeV");
  tex->DrawLatex(0.20,0.76,"PYTHIA DIS 0.01<y<0.95");
  tex->DrawLatex(0.20,0.70,"Z-axis: fraction of events with E_{e}>2 GeV");


  gStyle->SetOptStat(0);
  c3 = new TCanvas("c3","The Ntuple canvas",200,200,600,550);
  c3->Range(0,0,1,1);
  pad31 = new TPad("pad31","This is pad1",0.0,0.0,1.0,1.0);
  pad31->Draw();

  pad31->cd();
  her->SetTitle("");
  her->SetXTitle("#eta");
  her->SetYTitle("E (GeV)");
  her->Draw("col2");
}

spectra_purity()
// Electron ID purity
{
  TFile* f = new TFile("spectra_eta23.root"); // Produced from LoI_study.C::bkgr()
  TH1F* he = (TH1F*)f->Get("he0");
  TH1F* hh = (TH1F*)f->Get("hph");
  TH1F* hh2 = (TH1F*)f->Get("hph_emc2");
  TH1F* hh23 = (TH1F*)f->Get("hph_emc23");

  TH1F* hs = (TH1F*)he->Clone();
  TH1F* hr0 = (TH1F*)he->Clone();
  hs->Add(hh);
  hr0->Divide(hs);

  TH1F* hs2 = (TH1F*)he->Clone();
  TH1F* hr2 = (TH1F*)he->Clone();
  hs2->Add(hh23);
  hr2->Divide(hs2);

  TH1F* hr0_eta23 = (TH1F*)hr0->Clone();
  TH1F* hr2_eta23 = (TH1F*)hr2->Clone();

  TFile* f = new TFile("spectra_eta12.root"); // Produced from LoI_study.C::bkgr()
  TH1F* he = (TH1F*)f->Get("he0");
  TH1F* hh = (TH1F*)f->Get("hph");
  TH1F* hh2 = (TH1F*)f->Get("hph_emc2");
  TH1F* hh23 = (TH1F*)f->Get("hph_emc23");

  TH1F* hs = (TH1F*)he->Clone();
  TH1F* hr0 = (TH1F*)he->Clone();
  hs->Add(hh);
  hr0->Divide(hs);

  TH1F* hs2 = (TH1F*)he->Clone();
  TH1F* hr2 = (TH1F*)he->Clone();
  hs2->Add(hh23);
  hr2->Divide(hs2);

  TH1F* hr0_eta12 = hr0->Clone();
  TH1F* hr2_eta12 = hr2->Clone();

  TFile* f = new TFile("spectra_eta01.root"); // Produced from LoI_study.C::bkgr()
  TH1F* he = (TH1F*)f->Get("he0");
  TH1F* hh = (TH1F*)f->Get("hph");
  TH1F* hh2 = (TH1F*)f->Get("hph_emc2");
  TH1F* hh23 = (TH1F*)f->Get("hph_emc23");

  TH1F* hs = (TH1F*)he->Clone();
  TH1F* hr0 = (TH1F*)he->Clone();
  hs->Add(hh);
  hr0->Divide(hs);

  TH1F* hs2 = (TH1F*)he->Clone();
  TH1F* hr2 = (TH1F*)he->Clone();
  hs2->Add(hh2); // Different one for barrel!!!
  hr2->Divide(hs2);

  TH1F* hr0_eta01 = hr0->Clone();
  TH1F* hr2_eta01 = hr2->Clone();

  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,700,300);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.00,0.0,0.35,1.0);
  pad2 = new TPad("pad2","This is pad2",0.35,0.0,0.65,1.0);
  pad3 = new TPad("pad3","This is pad3",0.65,0.0,1.00,1.0);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  pad1->SetLeftMargin(0.15);
  pad1->SetRightMargin(0);
  pad2->SetLeftMargin(0.0);
  pad2->SetRightMargin(0);
  pad3->SetLeftMargin(0.0);
  pad3->SetRightMargin(0.15);

  pad1->cd();
  hr0_eta23->SetTitle("");
  hr0_eta23->SetYTitle("Electron purity");
  hr0_eta23->SetXTitle("p (GeV/c)");
  hr0_eta23->SetTitleSize(0.07,"X");
  hr0_eta23->SetTitleSize(0.07,"Y");
  hr0_eta23->SetMinimum(0);
  hr0_eta23->SetMaximum(1.1);
  hr0_eta23->SetLineStyle(2);
  hr0_eta23->GetXaxis()->SetLimits(0,14.99);
  hr0_eta23->Draw();
  hr2_eta23->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.4,0.2,"-3<#eta<-2");

  pad2->cd();
  hr0_eta12->SetTitle("");
  hr0_eta12->SetYTitle("");
  hr0_eta12->SetXTitle("p (GeV/c)");
  hr0_eta12->SetTitleSize(0.075,"X");
  hr0_eta12->SetMinimum(0);
  hr0_eta12->SetMaximum(1.1);
  hr0_eta12->SetLineStyle(2);
  hr0_eta12->GetXaxis()->SetLimits(0,14.99);
  hr0_eta12->Draw();
  hr2_eta12->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.085);
  tex->DrawLatex(0.3,0.2,"-2<#eta<-1");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.065);
  tex->DrawLatex(0.15,0.45,"e+p 10 GeV #times 250 GeV");
  tex->DrawLatex(0.15,0.37,"PYTHIA DIS");

  pad3->cd();

  TH1F* htmp = hr0_eta01->Clone();
  htmp->SetTitle("");
  htmp->SetXTitle("p (GeV/c)");
  htmp->SetYTitle("");
  htmp->SetTitleSize(0.07,"X");
  htmp->SetMinimum(0.);
  htmp->SetMaximum(1.1);
  htmp->SetLineStyle(2);
  htmp->GetXaxis()->SetLimits(0,14.99);
  htmp->Draw();

  hr0_eta01->SetTitle("");
  hr0_eta01->SetYTitle("");
  hr0_eta01->SetXTitle("p (GeV/c)");
  hr0_eta01->SetTitleSize(0.07,"X");
  hr0_eta01->SetMinimum(0);
  hr0_eta01->SetMaximum(1.1);
  hr0_eta01->SetLineStyle(2);
  hr0_eta01->Draw("same");
  hr2_eta01->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.3,0.2,"-1<#eta<0");

  TLegend* lg = new TLegend(0.25,0.35,0.81,0.50);
  hr0_eta01->SetTitle("From mom. spectra");
  hr2_eta01->SetTitle("After EMCal PID");
  lg->AddEntry(hr0_eta01,"","L");
  lg->AddEntry(hr2_eta01,"","L");
  lg->SetTextSize(0.05);
  lg->Draw();

}

spectra()
{
  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/pythia.ep.10x250.1Mevents.RadCor=0.root");
  TTree* treeDIS  = (TTree*)f->Get("EICTree");

  const int nbin = 30;
  const float pmax = 14.99;

  TH1F* hp_e_m3m2 = new TH1F("hp_e_m3m2","dN/dp vs p, -3<#eta<-2",nbin,0,pmax);
  TH1F* hp_p_m3m2 = new TH1F("hp_p_m3m2","dN/dp vs p, -3<#eta<-2",nbin,0,pmax);
  TH1F* hp_h_m3m2 = new TH1F("hp_h_m3m2","dN/dp vs p, -3<#eta<-2",nbin,0,pmax);

  treeDIS->Draw("p>>hp_e_m3m2","QSquaredTrue>0.01&&KS==1&&id==11&&orig==3&&-log(tan(theta/2.))>-3&&-log(tan(theta/2.))<-2","goff");
  treeDIS->Draw("p>>hp_h_m3m2","QSquaredTrue>0.01&&KS<10&&(id==211||id==-211)&&eta>-3&&eta<-2","goff");
  treeDIS->Draw("p>>hp_p_m3m2","QSquaredTrue>0.01&&KS<10&&id==22&&eta>-3&&eta<-2","goff");

  TH1F* hp_e_m2m1 = new TH1F("hp_e_m2m1","dN/dp vs p, -2<#eta<-1",nbin,0,pmax);
  TH1F* hp_p_m2m1 = new TH1F("hp_p_m2m1","dN/dp vs p, -2<#eta<-1",nbin,0,pmax);
  TH1F* hp_h_m2m1 = new TH1F("hp_h_m2m1","dN/dp vs p, -2<#eta<-1",nbin,0,pmax);

  treeDIS->Draw("p>>hp_e_m2m1","QSquaredTrue>0.01&&KS==1&&id==11&&orig==3&&-log(tan(theta/2.))>-2&&-log(tan(theta/2.))<-1","goff");
  treeDIS->Draw("p>>hp_h_m2m1","QSquaredTrue>0.01&&KS<10&&(id==211||id==-211)&&eta>-2&&eta<-1","goff");
  treeDIS->Draw("p>>hp_p_m2m1","QSquaredTrue>0.01&&KS<10&&id==22&&eta>-2&&eta<-1","goff");

  TH1F* hp_e_m1m0 = new TH1F("hp_e_m1m0","dN/dp vs p, -1<#eta<0",nbin,0,pmax);
  TH1F* hp_p_m1m0 = new TH1F("hp_p_m1m0","dN/dp vs p, -1<#eta<0",nbin,0,pmax);
  TH1F* hp_h_m1m0 = new TH1F("hp_h_m1m0","dN/dp vs p, -1<#eta<0",nbin,0,pmax);

  treeDIS->Draw("p>>hp_e_m1m0","QSquaredTrue>0.01&&KS==1&&id==11&&orig==3&&-log(tan(theta/2.))>-1&&-log(tan(theta/2.))<0","goff");
  treeDIS->Draw("p>>hp_h_m1m0","QSquaredTrue>0.01&&KS<10&&(id==211||id==-211)&&eta>-1&&eta<0","goff");
  treeDIS->Draw("p>>hp_p_m1m0","QSquaredTrue>0.01&&KS<10&&id==22&&eta>-1&&eta<0","goff");

  float ymin = 0.6;
  float ymax = 0.99e5;

  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,700,300);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.00,0.0,0.35,1.0);
  pad2 = new TPad("pad2","This is pad2",0.35,0.0,0.65,1.0);
  pad3 = new TPad("pad3","This is pad3",0.65,0.0,1.00,1.0);
  pad1->SetLogy();
  pad2->SetLogy();
  pad3->SetLogy();
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  pad1->SetLeftMargin(0.15);
  pad1->SetRightMargin(0);
  pad2->SetLeftMargin(0.01);
  pad2->SetRightMargin(0);
  pad3->SetLeftMargin(0.01);
  pad3->SetRightMargin(0.15);

  pad1->cd();
  hp_h_m3m2->SetLineStyle(2);
  hp_p_m3m2->SetLineStyle(3);
  hp_h_m3m2->SetTitle("");
  hp_h_m3m2->SetYTitle("dN/dp");
  hp_h_m3m2->SetXTitle("p (GeV/c)");
  hp_h_m3m2->SetTitleSize(0.07,"X");
  hp_h_m3m2->SetTitleSize(0.07,"Y");
  hp_h_m3m2->SetLineWidth(2);
  hp_h_m3m2->SetLineColor(1);
  hp_h_m3m2->SetMinimum(ymin);
  hp_h_m3m2->SetMaximum(ymax);
  hp_h_m3m2->Draw();
  hp_p_m3m2->SetLineWidth(2);
  hp_p_m3m2->SetLineColor(4);
  hp_p_m3m2->Draw("same");
  hp_e_m3m2->SetLineWidth(2);
  hp_e_m3m2->SetLineColor(2);
  hp_e_m3m2->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.3,0.8,"-3<#eta<-2");

  pad2->cd();
  hp_h_m2m1->SetLineStyle(2);
  hp_p_m2m1->SetLineStyle(3);
  hp_h_m2m1->SetTitle("");
  hp_h_m2m1->SetYTitle("");
  hp_h_m2m1->SetXTitle("p (GeV/c)");
  hp_h_m2m1->SetTitleSize(0.075,"X");
  hp_h_m2m1->SetLineWidth(2);
  hp_h_m2m1->SetLineColor(1);
  hp_h_m2m1->SetMinimum(ymin);
  hp_h_m2m1->SetMaximum(ymax);
  hp_h_m2m1->Draw();
  hp_p_m2m1->SetLineWidth(2);
  hp_p_m2m1->SetLineColor(4);
  hp_p_m2m1->Draw("same");
  hp_e_m2m1->SetLineWidth(2);
  hp_e_m2m1->SetLineColor(2);
  hp_e_m2m1->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.085);
  tex->DrawLatex(0.2,0.8,"-2<#eta<-1");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.07);
  tex->DrawLatex(0.25,0.65,"e+p 10 GeV #times 250 GeV");
  tex->DrawLatex(0.25,0.57,"PYTHIA DIS");

  pad3->cd();

  TH1F* htmp = hp_h_m1m0->Clone();
  htmp->SetTitle("");
  htmp->SetXTitle("p (GeV/c)");
  htmp->SetYTitle("");
  htmp->SetTitleSize(0.07,"X");
  htmp->SetMinimum(ymin);
  htmp->SetMaximum(ymax);
  htmp->SetLineStyle(2);
  htmp->Draw();

  hp_h_m1m0->SetLineStyle(2);
  hp_p_m1m0->SetLineStyle(3);
  hp_h_m1m0->SetLineWidth(2);
  hp_h_m1m0->SetLineColor(1);
  hp_h_m1m0->Draw("same");
  hp_p_m1m0->SetLineWidth(2);
  hp_p_m1m0->SetLineColor(4);
  hp_p_m1m0->Draw("same");
  hp_e_m1m0->SetLineWidth(2);
  hp_e_m1m0->SetLineColor(2);
  hp_e_m1m0->Draw("same");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.2,0.8,"-1<#eta<0");

  TLegend* lg = new TLegend(0.25,0.45,0.70,0.70);
  hp_e_m1m0->SetTitle("DIS electron");
  hp_h_m1m0->SetTitle("#pi#pm");
  hp_p_m1m0->SetTitle("Photons");
  lg->AddEntry(hp_e_m1m0,"","L");
  lg->AddEntry(hp_h_m1m0,"","L");
  lg->AddEntry(hp_p_m1m0,"","L");
  lg->SetTextSize(0.06);
  lg->Draw();

}


res()
{
  float Ee = 10; // Electron energy
  float Ep = 250; // Proton energy
  float sTheta = 0.003; // 3 mrad from 3mm pos. res. of EMCal

  float ss = 4.*Ee*Ep;

  TF1* fin = new TF1("fin","[0]*x+[1]*x*x");
  fin->SetParameters(1.86,-1.06);

  float ymin = 0.01;
  //  float ymax = 0.95;
  float ymax = 1.0;

  const float xmin = -4; // Means 10**(-5)
  const float xmax =  0;
  const int xnbin = 100;
  //  const int xnbin = 25;
  Float_t xbins[xnbin+1];
  for( int i=0; i<xnbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/xnbin);

  const float qmin = 0;
  const float qmax = 3; // Means 10**(3)
  const int qnbin = 120;
  //  const int qnbin = 15;
  Float_t qbins[qnbin+1];
  for( int i=0; i<qnbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/qnbin);

  TH2F* hq = new TH2F("hq","Q2 vs x",xnbin,xbins,qnbin,qbins);
  TH2F* hx = new TH2F("hx","Q2 vs x",xnbin,xbins,qnbin,qbins);
  TH2F* hy = new TH2F("hy","Q2 vs x",xnbin,xbins,qnbin,qbins);
  TH2F* he = new TH2F("he","Q2 vs x",xnbin,xbins,qnbin,qbins);

  TH2F* hin = new TH2F("hin","hin",xnbin,xbins,qnbin,qbins);

  TAxis *xaxis = hx->GetXaxis();
  TAxis *yaxis = hx->GetYaxis();

  float rq_log, rx_log;
  float rq, rx, ry, re, rre, rrt, rrq, rrx, rin, rin1, ww, wq, wx;
  float rre_emc, rre_mom;
  float tgT2, Theta, eta;

  //  TH1F* he = new TH1F("he","he",100,0,20);

  //  printf("Number of bins: %d %d\n",nx,ny);
  for( int iy=1; iy<=qnbin; iy++ ) {
  for( int ix=1; ix<=xnbin; ix++ ) {
    rx = xaxis->GetBinCenter(ix);
    rq = yaxis->GetBinCenter(iy);
    ry = rq/rx/ss;
    
    if( ry>ymin && ry<ymax ) {
      re = Ee*(1.-ry+rq/4./Ee/Ee);
      //	he->Fill(re,ww);
      tgT2 = sqrt(rq/4./Ee/Ee/(1-ry));
      Theta = 2.*atan(tgT2);
      eta = log(tgT2);

      rre_emc = sqrt(0.12*0.12/re+0.01*0.01); // Barrel
      rre_mom = 0.004*re+0.01; // Jin's e-mail from 6/18/13 12:34 PM

      rrt = 0; // no effect of angle resoltuion at mid-rapidity
      if( eta<-1 ) { // Backward
	rre_emc = sqrt(0.015*0.015/re+0.01*0.01);
	rre_mom = 0.01*re+0.01; // Jin's e-mail from 6/18/13 11:26 PM
	//	rrt = 2.*sTheta/Theta; // as Q^2~sin^2(Theta/2)~Theta^2
	rrt = (sTheta/sqrt(re))*2./Theta; // From EMCal pos. res.
	//	rrt = 2.*sTheta/Theta; // as Q^2~sin^2(Theta/2)~Theta^2
      }

      rrt = 0; // No angle resolution

      //      rre_emc=rre_mom;

      if( eta<1 ) {
	rre = rre_emc;
	if( rre>rre_mom ) rre=rre_mom;
	//      rre = rre_mom; // If only tracking
	
	rrq = rre;
	rrq = sqrt(rrq*rrq+rrt*rrt);
	rrx = rrq/ry; // Assume no effect of Theta resolution on y
	//	wq = log10(1.+rrq);
	//	wx = log10(1.+rrx);
	he->Fill(rx,rq,re);
	hy->Fill(rx,rq,ry);
	hq->Fill(rx,rq,rrq);
	hx->Fill(rx,rq,rrx);

	rin = fin->Eval(1.);
	if(rrx<1) rin=fin->Eval(rrx);
	rin1 = fin->Eval(1.);
	if(rrq<1) rin1=fin->Eval(rrq);

	hin->Fill(rx,rq,1.-rin-rin1);

	//      hq_cent->Fill(rx_log,rq_log,wq);
	//      hx_cent->Fill(rx_log,rq_log,wx);
	//      printf("q2= %e x= %e y= %f\n",rq,rx,ry);
      } // if( eta
    } // if( ry
  }
  }


  //  he->Draw();

  gStyle->SetTitleFontSize(0.06);
  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,600,350);
  c1->Range(0,0,1,1);
  pad11 = new TPad("pad11","This is pad1",0.00,0.0,0.50,1.0);
  pad12 = new TPad("pad12","This is pad2",0.50,0.0,1.00,1.0);
  pad11->Draw();
  pad12->Draw();
  pad11->SetLogz();
  pad12->SetLogz();
  pad11->SetRightMargin(0.15);
  pad12->SetRightMargin(0.15);

  pad11->cd();
  pad11->SetLogx();
  pad11->SetLogy();
  //  hq->SetTitle("#sigma_{Q^{2}}/Q^{2} vs Q^{2}&x");
  hq->SetTitle("");
  hq->SetXTitle("x");
  hq->SetYTitle("Q^{2} (GeV^{2})");
  hq->SetLabelSize(0.05,"Z");
  hq->SetMinimum(1e-3);
  hq->SetMaximum(1.);
  hq->Draw("colz");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.05);
  tex->DrawLatex(0.18,0.80,"Z-axis: #sigma_{Q^{2}}/Q^{2}");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.04);
  tex->DrawLatex(0.18,0.70,"ePHENIX e+p 10 GeV #times 250 GeV");
  tex->DrawLatex(0.18,0.64,"PYTHIA DIS 0.01<y<0.95");


  pad12->cd();
  pad12->SetLogx();
  pad12->SetLogy();
  //  hx->SetTitle("#sigma_{x}/x vs Q^{2}&x");
  hx->SetTitle("");
  hx->SetXTitle("x");
  hx->SetYTitle("Q^{2} (GeV^{2})");
  hx->SetLabelSize(0.05,"Z");
  hx->SetMinimum(1e-3);
  hx->SetMaximum(1.);
  hx->Draw("colz");

  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.05);
  tex->DrawLatex(0.18,0.80,"Z-axis: #sigma_{x}/x");

  //  return;

  c2 = new TCanvas("c2","The Ntuple canvas",100,100,500,550);
  c2->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->SetLogx();
  pad1->SetLogy();

  pad1->cd();
  hin->SetTitle("Bin survival prob. vs Q^{2}&x");
  hin->SetXTitle("x");
  hin->SetYTitle("Q^{2} (GeV^{2})");
  hin->Draw("colz");
  //  return;

  hy->SetTitle("y vs Q2&x");
  hy->SetMaximum(1.0);
  hy->Draw("colz");
  
  c3 = new TCanvas("c3","The Ntuple canvas",200,200,500,550);
  c3->Range(0,0,1,1);
  pad31 = new TPad("pad31","This is pad1",0.0,0.0,1.0,1.0);
  pad31->Draw();
  pad31->SetLogx();
  pad31->SetLogy();

  pad31->cd();
  he->SetTitle("Ee vs Q2&x");
  he->SetMinimum(1.e-2);
  he->SetMaximum(30.0);
  he->Draw("colz");
  
}

res2()
// For bin migration
{
  float Ee = 10; // Electron energy
  float Ep = 250; // Proton energy
  float sTheta = 0.003; // 3 mrad from 3mm pos. res. of EMCal

  float s = 4.*Ee*Ep;


  /*
  const int nn=7;
  float res[nn] = {0.02, 0.05, 0.1,  0.2,  0.3,  0.5,  1.0};
  float out[nn] = {0.03, 0.08, 0.15, 0.35, 0.48, 0.65, 0.8};
  TGraph* gr = new TGraph(nn,res,out);
  gr->SetMarkerStyle(20);
  gr->Draw("APL");
  TF1* ff = new TF1("ff","[0]*x+[1]*x*x");
  gr->Fit(ff);
  return;
  */
  TRandom* rnd = new TRandom();

  const int nxbin = 20;
  const float xmin = -4;
  const float xmax =  0;
  Float_t xbins[nxbin+1];
  for( int i=0; i<nxbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/nxbin);

  const int nqbin = 15;
  const float qmin = 0;
  const float qmax = 3;
  Float_t qbins[nqbin+1];
  for( int i=0; i<nqbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/nqbin);

  float ymin = 0.01;
  float ymax = 0.95;

  TF1* fxsec = new TF1("fxsec","1");

  TH2F* h0 = new TH2F("h0","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hall = new TH2F("hall","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hin = new TH2F("hin","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hout = new TH2F("hout","hin",nxbin,xbins,nqbin,qbins);

  float q, ql, qr, qrl, ww;
  float x, xl, xr, xrl, yr;
  float y, Eout, tgT2, Theta, eta;
  float semc, smom, ss, er, tr;
  int ibx0, ibx, ibq0, ibq;

  for( int i=0; i<1000000; i++ ) {

    ql = rnd->Rndm()*(qmax-qmin)+qmin;
    q = pow(10.,ql);
    xl = rnd->Rndm()*(xmax-xmin)+xmin;
    x = pow(10.,xl);

    y = q/s/x;

    if( y>ymin && y<ymax ) {

      Eout = Ee*(1.-y+q/4./Ee/Ee);
      tgT2 = sqrt(q/4./Ee/Ee/(1-y));
      Theta = 2.*atan(tgT2);
      eta = log(tgT2);

      semc = sqrt(0.12*0.12/Eout+0.01*0.01); // Barrel
      smom = 0.004*Eout+0.01; // Jin's e-mail from 6/18/13 12:34 PM

      if( eta<-1 ) { // Backward
	semc = sqrt(0.015*0.015/Eout+0.01*0.01);
	smom = 0.01*Eout+0.01; // Jin's e-mail from 6/18/13 11:26 PM
      }

      ss = semc;
      if( ss>smom ) ss = smom;

      er = rnd->Gaus(Eout,ss*Eout);
      if( er<=0 ) er=1e-10;
      tr = rnd->Gaus(Theta,sTheta/sqrt(Eout));

      //      er = Eout; // No smearing
      tr = Theta; // No smearing

      qr = 2.*Ee*er*(1.-cos(tr));
      yr = 1.-er/Ee*(1.+cos(tr))/2.;
      if( yr>0.9999 ) yr = 0.9999;
      if( yr<0.0001 ) yr = 0.0001;
      xr = qr/yr/s;

      //      printf("%f (%f) %f (%f)\n",q,qr,x,xr);
      qrl = log10(qr);
      xrl = log10(xr);

      ibx0 = (xl-xmin)/(xmax-xmin)*nxbin;
      ibq0 = (ql-qmin)/(qmax-qmin)*nqbin;

      ibx  = (xrl-xmin)/(xmax-xmin)*nxbin;
      ibq  = (qrl-qmin)/(qmax-qmin)*nqbin;

      //      ww = fxsec->Eval(q);
      ww = 1.;

      //      printf("%f (%f) %f (%f)\n",xl,xrl,ql,qrl);

      h0->Fill(x,q,ww);
      hall->Fill(xr,qr,ww);
      if( ibx==ibx0 && ibq==ibq0 ) hin->Fill(xr,qr,ww);
      else hout->Fill(xr,qr,ww);

    }
  }

  //  h0->Draw();
  //  hall->SetLineColor(2);
  //  hall->Draw("same");
  hin->Divide(h0);
  hout->Divide(h0);

  gStyle->SetOptStat(0);
  c2 = new TCanvas("c2","The Ntuple canvas",10,10,500,450);
  c2->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->SetLogx();
  pad1->SetLogy();

  pad1->cd();
  hin->SetTitle("");
  hin->SetTitleSize(0.06,"X");
  hin->SetTitleSize(0.06,"Y");
  hin->SetXTitle("x");
  hin->SetYTitle("Q^{2} (GeV^{2})");
  hin->Draw("colz");

  TF1* f1 = new TF1("f1","10000*0.1*x");
  f1->SetLineColor(1);
  f1->Draw("same");
  TF1* f2 = new TF1("f2","10000*0.3*x");
  f2->SetLineColor(1);
  f2->Draw("same");

  TLatex *tex = new TLatex(0.0017,2,"y=0.1");
  tex->SetTextAngle(50);
  tex->SetTextSize(0.035);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.0005,2,"y=0.3");
  tex->SetTextAngle(50);
  tex->SetTextSize(0.035);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,500,"ePHENIX e+p 10 GeV #times 250 GeV");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,250,"PYTHIA DIS 0.01<y<0.95");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,125,"Stat. survival prob. in a bin");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();
}

res2_pythia()
// For bin migration, from PYTHIA generated file
{
  TFile* f = new TFile("/eic/data/PYTHIA/ep/TREES/Q2-CUT/pythia.ep.10x250.1Mevents.RadCor=0.Q2-0.1.root");

  float Ee = 10; // Electron energy
  float Ep = 250; // Proton energy
  float sTheta = 0.003; // 3 mrad from 3mm pos. res. of EMCal

  float s = 4.*Ee*Ep;

  TTree* treeDIS  = (TTree*)f->Get("EICTree");

  Float_t Q2, y, nu;
  treeDIS->SetBranchAddress("QSquaredTrue",&Q2);
  treeDIS->SetBranchAddress("inelasticity",&y);

  TRandom* rnd = new TRandom();

  const int nxbin = 20;
  const float xmin = -4;
  const float xmax =  0;
  Float_t xbins[nxbin+1];
  for( int i=0; i<nxbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/nxbin);

  const int nqbin = 15;
  const float qmin = 0;
  const float qmax = 3;
  Float_t qbins[nqbin+1];
  for( int i=0; i<nqbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/nqbin);

  float ymin = 0.01;
  float ymax = 0.95;

  TF1* fxsec = new TF1("fxsec","1");

  TH2F* h0 = new TH2F("h0","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hall = new TH2F("hall","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hin = new TH2F("hin","hin",nxbin,xbins,nqbin,qbins);
  TH2F* hout = new TH2F("hout","hin",nxbin,xbins,nqbin,qbins);

  float q, ql, qr, qrl, ww;
  float x, xl, xr, xrl, yr;
  float Eout, tgT2, Theta, eta;
  float semc, smom, ss, er, tr;
  int ibx0, ibx, ibq0, ibq;

  int nEv = int(treeDIS->GetEntries());
  printf("nEntries to process = %d\n",nEv);
  //  nEv = 100000;

  for( int ien=0; ien<nEv; ien++ ) {

    if( ien%10000 == 0 ) printf("nEvent = %d\n",ien);
    treeDIS->GetEvent(ien);
    /*
    ql = rnd->Rndm()*(qmax-qmin)+qmin;
    q = pow(10.,ql);
    xl = rnd->Rndm()*(xmax-xmin)+xmin;
    x = pow(10.,xl);
    y = q/s/x;
    */
    q = Q2;
    x = q/s/y;
    ql = log10(q);
    xl = log10(x);

    if( y>ymin && y<ymax ) {

      Eout = Ee*(1.-y+q/4./Ee/Ee);
      tgT2 = sqrt(q/4./Ee/Ee/(1-y));
      Theta = 2.*atan(tgT2);
      eta = log(tgT2);

      semc = sqrt(0.12*0.12/Eout+0.01*0.01); // Barrel
      smom = 0.004*Eout+0.01; // Jin's e-mail from 6/18/13 12:34 PM

      if( eta<-1 ) { // Backward
	semc = sqrt(0.015*0.015/Eout+0.01*0.01);
	smom = 0.01*Eout+0.01; // Jin's e-mail from 6/18/13 11:26 PM
      }

      ss = semc;
      if( ss>smom ) ss = smom;

      er = rnd->Gaus(Eout,ss*Eout);
      if( er<=0 ) er=1e-10;
      tr = rnd->Gaus(Theta,sTheta/sqrt(Eout));

      //      er = Eout; // No smearing
      tr = Theta; // No smearing

      qr = 2.*Ee*er*(1.-cos(tr));
      yr = 1.-er/Ee*(1.+cos(tr))/2.;
      if( yr>0.9999 ) yr = 0.9999;
      if( yr<0.0001 ) yr = 0.0001;
      xr = qr/yr/s;

      //      printf("%f (%f) %f (%f)\n",q,qr,x,xr);
      qrl = log10(qr);
      xrl = log10(xr);

      ibx0 = (xl-xmin)/(xmax-xmin)*nxbin;
      ibq0 = (ql-qmin)/(qmax-qmin)*nqbin;

      ibx  = (xrl-xmin)/(xmax-xmin)*nxbin;
      ibq  = (qrl-qmin)/(qmax-qmin)*nqbin;

      //      ww = fxsec->Eval(q);
      ww = 1.;

      //      printf("%f (%f) %f (%f)\n",xl,xrl,ql,qrl);

      h0->Fill(x,q,ww);
      hall->Fill(xr,qr,ww);
      if( ibx==ibx0 && ibq==ibq0 ) hin->Fill(xr,qr,ww);
      else hout->Fill(xr,qr,ww);

    }
  }

  //  hin->Draw();
  //  hall->SetLineColor(2);
  //  hall->Draw("same");
  hin->Divide(h0);
  hout->Divide(h0);
  //  return;

  gStyle->SetOptStat(0);
  c2 = new TCanvas("c2","The Ntuple canvas",10,10,500,450);
  c2->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->SetLogx();
  pad1->SetLogy();

  pad1->cd();
  hin->SetTitle("");
  hin->SetTitleSize(0.06,"X");
  hin->SetTitleSize(0.06,"Y");
  hin->SetXTitle("x");
  hin->SetYTitle("Q^{2} (GeV^{2})");
  hin->Draw("colz");

  TF1* f1 = new TF1("f1","10000*0.1*x");
  f1->SetLineColor(1);
  f1->Draw("same");
  TF1* f2 = new TF1("f2","10000*0.3*x");
  f2->SetLineColor(1);
  f2->Draw("same");

  TLatex *tex = new TLatex(0.0017,2,"y=0.1");
  tex->SetTextAngle(50);
  tex->SetTextSize(0.035);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.0005,2,"y=0.3");
  tex->SetTextAngle(50);
  tex->SetTextSize(0.035);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,500,"ePHENIX e+p 10 GeV #times 250 GeV");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,250,"PYTHIA DIS 0.01<y<0.95");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();

  TLatex *tex = new TLatex(0.00014,125,"Stat. survival prob. in a bin");
  tex->SetTextSize(0.040);
  tex->SetTextColor(1);
  tex->Draw();
}



dvcs_eeta()
// Plots DVCS photon energy vs eta
{
  TFile* f = new TFile("milou/dvcs_10x250_xwide_4M.root");
  //  TFile* f = new TFile("milou/BH_5x250.root");

  TH1F* he_cent = new TH1F("he_cent","dN/dEg",100,0,20);
  TH1F* he_forw = new TH1F("he_forw","dN/dEg",100,0,20);
  TH1F* he_back = new TH1F("he_back","dN/dEg",100,0,20);
  TH2F* heeta = new TH2F("heeta","Eg vs eta",80,-4,4,60,0,30);

  TH1F* hdiff = new TH1F("hdiff","Angl Diff",80,0,1);

  h1->Draw("prglab[3]>>he_cent","abs(-log(tan(acos(prglab[2]/prglab[3])/2.)))<1","goff");
  h1->Draw("prglab[3]>>he_forw","-log(tan(acos(prglab[2]/prglab[3])/2.))>1","goff");
  h1->Draw("prglab[3]>>he_back","-log(tan(acos(prglab[2]/prglab[3])/2.))<-1","goff");
  h1->Draw("prglab[3]:-log(tan(acos(prglab[2]/prglab[3])/2.))>>heeta","","goff");

  h1->Draw("acos((prglab[0]*plolab[0]+prglab[1]*plolab[1]+prglab[2]*plolab[2])/sqrt(prglab[0]*prglab[0]+prglab[1]*prglab[1]+prglab[2]*prglab[2])/sqrt(plolab[0]*plolab[0]+plolab[1]*plolab[1]+plolab[2]*plolab[2]))>>hdiff","","goff");

  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",10,10,700,350);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.0,0.0,0.5,1.0);
  pad2 = new TPad("pad2","This is pad2",0.5,0.0,1.0,1.0);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  heeta->SetTitle("");
  heeta->SetYTitle("E_{#gamma} (GeV)");
  heeta->SetXTitle("#eta_{#gamma}");
  heeta->Draw("col2");

  pad2->cd();
  hdiff->Draw();
  hdiff->SetTitle("");
  hdiff->SetXTitle("e-#gamma angle (rad)");
  //  hdiff->SetYTitle("dN/dE");
  /*
  he_cent->SetTitle("");
  he_cent->SetXTitle("E (GeV)");
  he_cent->SetYTitle("dN/dE");
  he_cent->SetLineWidth(2);
  he_cent->SetLineColor(2);
  he_cent->Draw();
  he_forw->SetLineWidth(2);
  he_forw->SetLineColor(1);
  he_forw->Draw("same");
  he_back->SetLineWidth(2);
  he_back->SetLineColor(4);
  he_back->Draw("same");
  */

  gStyle->SetOptStat(0);
  c2 = new TCanvas("c2","The Ntuple canvas",100,100,500,550);
  c2->Range(0,0,1,1);
  pad21 = new TPad("pad21","This is pad1",0.0,0.0,1.0,1.0);
  pad21->Draw();

  pad21->cd();
  heeta->SetTitle("");
  heeta->SetYTitle("E_{#gamma} (GeV)");
  heeta->SetXTitle("#eta_{#gamma}");
  heeta->Draw("col2");
}


dvcs_q2x()
// Plots DVCS Q2 vs x
{
  //  TFile* f = new TFile("milou/dvcs_10x250_xwide.root");
  TFile* f = new TFile("milou/dvcs_10x250_xwide_4M.root");
  //  TFile* f = new TFile("milou/t.root");

  TTree* treeDIS  = (TTree*)f->Get("h1");

  const float xmin = -3.999; // Means 10**(-5)
  const float xmax =  0;
  const int xnbin = 40;
  Float_t xbins[xnbin+1];
  for( int i=0; i<xnbin+1; i++ ) xbins[i]=pow(10,xmin+(xmax-xmin)*i/xnbin);

  const float qmin = 0;
  const float qmax = 2; // Means 10**(3)
  const int qnbin = 40;
  Float_t qbins[qnbin+1];
  for( int i=0; i<qnbin+1; i++ ) qbins[i]=pow(10,qmin+(qmax-qmin)*i/qnbin);

  TH2F* hqx = new TH2F("hqx","Q2 vs x",xnbin,xbins,qnbin,qbins);
  treeDIS->Draw("qntp:xntp>>hqx","","goff");
  TH2F* hqx_cent = new TH2F("hqx_cent","Q2 vs x",xnbin,xbins,qnbin,qbins);
  treeDIS->Draw("qntp:xntp>>hqx_cent","abs(-log(tan(acos(prglab[2]/prglab[3])/2.)))<1","goff");
  TH2F* hqx_forw = new TH2F("hqx_forw","Q2 vs x",xnbin,xbins,qnbin,qbins);
  treeDIS->Draw("qntp:xntp>>hqx_forw","-log(tan(acos(prglab[2]/prglab[3])/2.))>1","goff");
  TH2F* hqx_back = new TH2F("hqx_back","Q2 vs x",xnbin,xbins,qnbin,qbins);
  treeDIS->Draw("qntp:xntp>>hqx_back","-log(tan(acos(prglab[2]/prglab[3])/2.))<-1","goff");

  gStyle->SetOptStat(0);
  c1 = new TCanvas("c1","The Ntuple canvas",100,100,900,350);
  c1->Range(0,0,1,1);
  pad1 = new TPad("pad1","This is pad1",0.00,0.0,0.35,1.0);
  pad2 = new TPad("pad2","This is pad2",0.35,0.0,0.65,1.0);
  pad3 = new TPad("pad3","This is pad2",0.65,0.0,1.00,1.0);
  pad1->SetLeftMargin(0.15);
  pad1->Draw();
  pad1->SetRightMargin(0);
  pad2->SetLeftMargin(0);
  pad2->SetRightMargin(0);
  pad2->Draw();
  pad3->SetLeftMargin(0);
  pad3->Draw();
  pad3->SetRightMargin(0.15);

  float zmax = hqx->GetMaximum();

  pad1->cd();
  pad1->SetLogx();
  pad1->SetLogy();
  hqx_back->SetTitle("");
  hqx_back->SetXTitle("x");
  hqx_back->SetYTitle("Q^{2} (GeV^{2})");
  hqx_back->SetTitleSize(0.07,"X");
  hqx_back->SetTitleSize(0.07,"Y");
  hqx_back->SetMaximum(zmax);
  hqx_back->Draw("col2");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.2,0.8,"#eta<-1");

  TLatex *tex = new TLatex();
  tex->SetTextSize(0.05);
  tex->DrawLatex(0.004,8,"e+p 10 GeV #times 250 GeV");
  tex->DrawLatex(0.004,5,"MILOU DVCS photons");
  //  tex->DrawLatex(0.004,3,"Q^{2}>1 GeV^{2}");


  pad2->cd();
  pad2->SetLogx();
  pad2->SetLogy();
  hqx_cent->SetTitle("");
  hqx_cent->SetXTitle("x");
  hqx_cent->SetYTitle("");
  hqx_cent->SetTitleSize(0.07,"X");
  hqx_cent->SetMaximum(zmax);
  hqx_cent->Draw("col2");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.1,0.8,"|#eta|<1");

  pad3->cd();
  pad3->SetLogx();
  pad3->SetLogy();
  hqx_forw->SetTitle("");
  hqx_forw->SetXTitle("x");
  hqx_forw->SetYTitle("");
  hqx_back->SetTitleSize(0.07,"X");
  hqx_back->SetMaximum(zmax);
  hqx_forw->Draw("colz");
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.08);
  tex->DrawLatex(0.1,0.8,"#eta>1");
}

diffr()
{
  // See diffr.C::rapgap()
}
