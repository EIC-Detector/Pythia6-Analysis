/**

 * \Brief Macro to reproduce Fig. 23 & 24 from HERA Physics (G. Wolf) Section 5.2
 * \Author: Thomas Krahulik <thomas.krahulik@stonybrook.edu>

 **/

int makePlot_HERA()
{

  /**

   * \Uses HERA Beam Energies of Ee = 26.7 GeV and Ep = 820 GeV

   **/

  /*----------------------------------*/
  /*-----------Lepton Angle-----------*/
  /*-----------HERA Fig. 23-----------*/
  /*----------------------------------*/

  /*----------Define Angles-----------*/

  TF1 *f_xQ2_0 = new TF1("f_xQ2_0" , " 2*[0]*[1]*x*(1 + cos([2])) / (1 + ((x*[1])/(2*[0]))*(1-cos([2])) - 0.5*(1- cos([2])))", 10e-6, 1);
  f_xQ2_0->SetParameter( 0 , 26.7);
  f_xQ2_0->SetParameter( 1 , 820.);
  f_xQ2_0->SetParameter( 2 , (0 * TMath::Pi())/180);
  TF1 *f_xQ2_30 = (TF1*)f_xQ2_0->Clone("f_xQ2_30");       //30 degrees 
  f_xQ2_30->SetParameter( 2 , (30 * TMath::Pi())/180);
  TF1 *f_xQ2_90 = (TF1*)f_xQ2_0->Clone("f_xQ2_90");       //90 degrees
  f_xQ2_90->SetParameter( 2 , (90 * TMath::Pi())/180);
  TF1 *f_xQ2_150 = (TF1*)f_xQ2_0->Clone("f_xQ2_150");     //150 degrees
  f_xQ2_150->SetParameter( 2 , (150 * TMath::Pi())/180);
  TF1 *f_xQ2_170 = (TF1*)f_xQ2_0->Clone("f_xQ2_170");     //170 degrees
  f_xQ2_170->SetParameter( 2 , (170 * TMath::Pi())/180);
  TF1 *f_xQ2_177 = (TF1*)f_xQ2_0->Clone("f_xQ2_177");     //177 degrees
  f_xQ2_177->SetParameter( 2 , (177 * TMath::Pi())/180);

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_LepA = new TCanvas();
  c_xQ2_LepA->SetLogx();
  c_xQ2_LepA->SetLogy();

  f_xQ2_0->Draw();
  f_xQ2_0->SetLineColor(1);
  f_xQ2_0->SetLineStyle(1);
  f_xQ2_0->SetTitle("");
  f_xQ2_0->GetXaxis()->SetTitle("x");
  f_xQ2_0->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_0->SetMinimum(1);
  f_xQ2_0->SetMaximum(10e4);

  f_xQ2_30->Draw("SAME");
  f_xQ2_30->SetLineColor(1);
  f_xQ2_30->SetLineStyle(3);
  f_xQ2_90->Draw("SAME");
  f_xQ2_90->SetLineColor(1);
  f_xQ2_90->SetLineStyle(5);
  f_xQ2_150->Draw("SAME");
  f_xQ2_150->SetLineColor(1);
  f_xQ2_150->SetLineStyle(7);
  f_xQ2_170->Draw("SAME");
  f_xQ2_170->SetLineColor(1);
  f_xQ2_170->SetLineStyle(9);
  f_xQ2_177->Draw("SAME");
  f_xQ2_177->SetLineColor(1);
  f_xQ2_177->SetLineStyle(2);

  TLegend* leg_xQ2_LepA = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_LepA->AddEntry(f_xQ2_0, "0^{o}", "L");
  leg_xQ2_LepA->AddEntry(f_xQ2_30, "30^{o}", "L");
  leg_xQ2_LepA->AddEntry(f_xQ2_90, "90^{o}", "L");
  leg_xQ2_LepA->AddEntry(f_xQ2_150, "150^{o}", "L");
  leg_xQ2_LepA->AddEntry(f_xQ2_170, "170^{o}", "L");
  leg_xQ2_LepA->AddEntry(f_xQ2_177, "177^{o}", "L");
  leg_xQ2_LepA->Draw();

  /*----------------------------------*/

  /*----------------------------------*/
  /*-----------Lepton Energy----------*/
  /*-----------HERA Fig. 23-----------*/
  /*----------------------------------*/

  /*----------Define Energies---------*/

  TF1 *f_xQ2_E0 = new TF1("f_xQ2_E0" , "2*[0]*[2]*( 1 + ((((x*[1]*([2]-[0]))/(x*[1]-[0])) - ([0] - (([0]*([2]-[0]))/(x*[1]-[0])))) / (((x*[1]*([2]-[0]))/(x*[1]-[0])) + ([0] - (([0]*([2]-[0]))/(x*[1]-[0]))))))", 10e-6, 1);
  f_xQ2_E0->SetParameter( 0 , 26.7);
  f_xQ2_E0->SetParameter( 1 , 820.);
  f_xQ2_E0->SetParameter( 2 , 0. );
  TF1 *f_xQ2_E10 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E10");  
  f_xQ2_E10->SetParameter( 2 , 10);
  TF1 *f_xQ2_E20 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E20");  
  f_xQ2_E20->SetParameter( 2 , 20);
  TF1 *f_xQ2_E25 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E25");  
  f_xQ2_E25->SetParameter( 2 , 25);
  TF1 *f_xQ2_E26_5 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E26_5");  
  f_xQ2_E26_5->SetParameter( 2 , 26.5);
  TF1 *f_xQ2_E26_9 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E26_9");  
  f_xQ2_E26_9->SetParameter( 2 , 26.9);
  TF1 *f_xQ2_E30 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E30");  
  f_xQ2_E30->SetParameter( 2 , 30);
  TF1 *f_xQ2_E50 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E50");  
  f_xQ2_E50->SetParameter( 2 , 50);
  TF1 *f_xQ2_E100 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E100");  
  f_xQ2_E100->SetParameter( 2 , 100);
  TF1 *f_xQ2_E200 = (TF1*)f_xQ2_E0->Clone("f_xQ2_E200");  
  f_xQ2_E200->SetParameter( 2 , 200);

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_LepE = new TCanvas();
  c_xQ2_LepE->SetLogx();
  c_xQ2_LepE->SetLogy();

  f_xQ2_E0->Draw();
  f_xQ2_E0->SetLineColor(1);
  f_xQ2_E0->SetLineStyle(1);
  f_xQ2_E0->SetTitle("");
  f_xQ2_E0->GetXaxis()->SetTitle("x");
  f_xQ2_E0->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_E0->SetMinimum(1);
  f_xQ2_E0->SetMaximum(10e4);

  f_xQ2_E10->Draw("SAME");
  f_xQ2_E10->SetLineColor(1);
  f_xQ2_E10->SetLineStyle(3);
  f_xQ2_E20->Draw("SAME");
  f_xQ2_E20->SetLineColor(1);
  f_xQ2_E20->SetLineStyle(5);
  f_xQ2_E25->Draw("SAME");
  f_xQ2_E25->SetLineColor(1);
  f_xQ2_E25->SetLineStyle(7);
  f_xQ2_E26_5->Draw("SAME");
  f_xQ2_E26_5->SetLineColor(1);
  f_xQ2_E26_5->SetLineStyle(9);
  f_xQ2_E26_9->Draw("SAME");
  f_xQ2_E26_9->SetLineColor(1);
  f_xQ2_E26_9->SetLineStyle(2);
  f_xQ2_E30->Draw("SAME");
  f_xQ2_E30->SetLineColor(1);
  f_xQ2_E30->SetLineStyle(4);
  f_xQ2_E50->Draw("SAME");
  f_xQ2_E50->SetLineColor(1);
  f_xQ2_E50->SetLineStyle(6);
  f_xQ2_E100->Draw("SAME");
  f_xQ2_E100->SetLineColor(1);
  f_xQ2_E100->SetLineStyle(8);
  f_xQ2_E200->Draw("SAME");
  f_xQ2_E200->SetLineColor(1);
  f_xQ2_E200->SetLineStyle(10);

  TLegend* leg_xQ2_LepE = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_LepE->AddEntry(f_xQ2_E0, "0 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E10, "10 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E20, "20 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E25, "25 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E26_5, "26.5 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E26_9, "26.9 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E30, "30 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E50, "50 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E100, "100 GeV", "L");
  leg_xQ2_LepE->AddEntry(f_xQ2_E200, "200 GeV", "L");
  leg_xQ2_LepE->Draw();
 
  /*----------------------------------*/

  /*----------------------------------*/
  /*-------------Jet Angle------------*/
  /*-----------HERA Fig. 23-----------*/
  /*----------------------------------*/

  /*-----------Define Angles----------*/

  TF1 *f_xQ2_JA180 = new TF1("f_xQ2_JA180" ,"(4 * (x**2)*([1]**2)*[0]*(1-cos([2]))) / (cos([2]) * ([0] -x*[1]) + [0] + x*[1])" , 10e-6, 1);
  f_xQ2_JA180->SetParameter( 0 , 26.7);
  f_xQ2_JA180->SetParameter( 1 , 820.);
  f_xQ2_JA180->SetParameter( 2 , (180 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA3 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA3");  
  f_xQ2_JA3->SetParameter( 2 , (3 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA5 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA5");  
  f_xQ2_JA5->SetParameter( 2 , (5 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA10 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA10");  
  f_xQ2_JA10->SetParameter( 2 , (10 * TMath::Pi())/180);
  TF1 *f_xQ2_JA30 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA30");  
  f_xQ2_JA30->SetParameter( 2 , (30 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA90 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA90");  
  f_xQ2_JA90->SetParameter( 2 , (90 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA150 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA150");  
  f_xQ2_JA150->SetParameter( 2 , (150 * TMath::Pi())/180 );
  TF1 *f_xQ2_JA170 = (TF1*)f_xQ2_JA180->Clone("f_xQ2_JA170");  
  f_xQ2_JA170->SetParameter( 2 , (170 * TMath::Pi())/180 );

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_JetA = new TCanvas();
  c_xQ2_JetA->SetLogx();
  c_xQ2_JetA->SetLogy();

  f_xQ2_JA180->Draw();
  f_xQ2_JA180->SetLineColor(1);
  f_xQ2_JA180->SetLineStyle(1);
  f_xQ2_JA180->SetTitle("");
  f_xQ2_JA180->GetXaxis()->SetTitle("x");
  f_xQ2_JA180->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_JA180->SetMinimum(1);
  f_xQ2_JA180->SetMaximum(10e4);

  f_xQ2_JA3->Draw("SAME");
  f_xQ2_JA3->SetLineColor(1);
  f_xQ2_JA3->SetLineStyle(3);
  f_xQ2_JA5->Draw("SAME");
  f_xQ2_JA5->SetLineColor(1);
  f_xQ2_JA5->SetLineStyle(5);
  f_xQ2_JA10->Draw("SAME");
  f_xQ2_JA10->SetLineColor(1);
  f_xQ2_JA10->SetLineStyle(7);
  f_xQ2_JA30->Draw("SAME");
  f_xQ2_JA30->SetLineColor(1);
  f_xQ2_JA30->SetLineStyle(9);
  f_xQ2_JA90->Draw("SAME");
  f_xQ2_JA90->SetLineColor(1);
  f_xQ2_JA90->SetLineStyle(2);
  f_xQ2_JA150->Draw("SAME");
  f_xQ2_JA150->SetLineColor(1);
  f_xQ2_JA150->SetLineStyle(4);
  f_xQ2_JA170->Draw("SAME");
  f_xQ2_JA170->SetLineColor(1);
  f_xQ2_JA170->SetLineStyle(6);

  TLegend* leg_xQ2_JetA = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_JetA->AddEntry(f_xQ2_JA3, "3^{o}", "L");
  leg_xQ2_JetA->AddEntry(f_xQ2_JA10, "10^{o}", "L");
  leg_xQ2_JetA->AddEntry(f_xQ2_JA30, "30^{o}", "L");
  leg_xQ2_JetA->AddEntry(f_xQ2_JA90, "90^{o}", "L");
  leg_xQ2_JetA->AddEntry(f_xQ2_JA150, "150^{o}", "L");
  leg_xQ2_JetA->AddEntry(f_xQ2_JA170, "170^{o}", "L");
  leg_xQ2_JetA->Draw();
 
  /*----------------------------------*/

  /*----------------------------------*/
  /*------------Jet Energy------------*/
  /*-----------HERA Fig. 23-----------*/
  /*----------------------------------*/

  /*----------Define Energies---------*/

  TF1 *f_xQ2_JE5 = new TF1("f_xQ2_JE5" , "(4*x*[0]*[1]*([2]-x*[1])) / ([0] - x*[1])", 10e-6, 1);
  f_xQ2_JE5->SetParameter( 0 , 26.7);
  f_xQ2_JE5->SetParameter( 1 , 820.);
  f_xQ2_JE5->SetParameter( 2 , 5. );
  TF1 *f_xQ2_JE10 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE10");  
  f_xQ2_JE10->SetParameter( 2 , 10);
  TF1 *f_xQ2_JE20 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE20");  
  f_xQ2_JE20->SetParameter( 2 , 20);
  TF1 *f_xQ2_JE26_7 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE26_7");
  f_xQ2_JE26_7->SetParameter( 2 , 26.7);
  TF1 *f_xQ2_JE100 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE100");  
  f_xQ2_JE100->SetParameter( 2 , 100);
  TF1 *f_xQ2_JE300 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE300");  
  f_xQ2_JE300->SetParameter( 2 , 300);
  TF1 *f_xQ2_JE500 = (TF1*)f_xQ2_JE5->Clone("f_xQ2_JE500");  
  f_xQ2_JE500->SetParameter( 2 , 500);

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_JetE = new TCanvas();
  c_xQ2_JetE->SetLogx();
  c_xQ2_JetE->SetLogy();

  f_xQ2_JE5->Draw();
  f_xQ2_JE5->SetLineColor(1);
  f_xQ2_JE5->SetLineStyle(4);
  f_xQ2_JE5->SetTitle("");
  f_xQ2_JE5->GetXaxis()->SetTitle("x");
  f_xQ2_JE5->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_JE5->SetMinimum(1);
  f_xQ2_JE5->SetMaximum(10e4);

  f_xQ2_JE10->Draw("SAME");
  f_xQ2_JE10->SetLineColor(1);
  f_xQ2_JE10->SetLineStyle(3);
  f_xQ2_JE20->Draw("SAME");
  f_xQ2_JE20->SetLineColor(1);
  f_xQ2_JE20->SetLineStyle(5);
  f_xQ2_JE26_7->Draw("SAME");
  f_xQ2_JE26_7->SetLineColor(1);
  f_xQ2_JE26_7->SetLineStyle(1);
  f_xQ2_JE100->Draw("SAME");
  f_xQ2_JE100->SetLineColor(1);
  f_xQ2_JE100->SetLineStyle(7);
  f_xQ2_JE300->Draw("SAME");
  f_xQ2_JE300->SetLineColor(1);
  f_xQ2_JE300->SetLineStyle(9);
  f_xQ2_JE500->Draw("SAME");
  f_xQ2_JE500->SetLineColor(1);
  f_xQ2_JE500->SetLineStyle(2);

  TLegend* leg_xQ2_JetE = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_JetE->AddEntry(f_xQ2_JE5, "5 GeV", "L");
  leg_xQ2_JetE->AddEntry(f_xQ2_JE10, "10 GeV", "L");
  leg_xQ2_JetE->AddEntry(f_xQ2_JE20, "20 GeV", "L");
  leg_xQ2_JetE->AddEntry(f_xQ2_JE100, "100 GeV", "L");
  leg_xQ2_JetE->AddEntry(f_xQ2_JE300, "300 GeV", "L");
  leg_xQ2_JetE->AddEntry(f_xQ2_JE500, "500 GeV", "L");
  leg_xQ2_JetE->Draw();
 
  /*----------------------------------*/

  /*----------------------------------*/
  /*-----------Inelasticity-----------*/
  /*-----------HERA Fig. 24-----------*/
  /*----------------------------------*/

  /*-------Define Inelasticities------*/

  TF1 *f_xQ2_yn0 = new TF1("f_xQ2_yn0" , "4*x*[0]*[1]*[2]", 10e-7, 1);
  f_xQ2_yn0->SetParameter( 0 , 26.7);
  f_xQ2_yn0->SetParameter( 1 , 820.);
  f_xQ2_yn0->SetParameter( 2 , 1. );
  TF1 *f_xQ2_yhalf = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yhalf");  
  f_xQ2_yhalf->SetParameter( 2 , 0.5);
  TF1 *f_xQ2_yn1 = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yn1");  
  f_xQ2_yn1->SetParameter( 2 , 0.1);
  TF1 *f_xQ2_yn2 = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yn2");  
  f_xQ2_yn2->SetParameter( 2 , 0.01);
  TF1 *f_xQ2_yn3 = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yn3");  
  f_xQ2_yn3->SetParameter( 2 , 0.001);
  TF1 *f_xQ2_yn4 = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yn4");  
  f_xQ2_yn4->SetParameter( 2 , 0.0001);
  TF1 *f_xQ2_yn5 = (TF1*)f_xQ2_yn0->Clone("f_xQ2_yn5");  
  f_xQ2_yn5->SetParameter( 2 , 0.00001);

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_y = new TCanvas();

  f_xQ2_yn0->Draw();
  f_xQ2_yn0->SetLineColor(1);
  f_xQ2_yn0->SetLineStyle(1);
  f_xQ2_yn0->SetTitle("");
  f_xQ2_yn0->GetXaxis()->SetTitle("x");
  f_xQ2_yn0->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_yn0->SetMinimum(1);
  f_xQ2_yn0->SetMaximum(10e4);

  f_xQ2_yhalf->Draw("SAME");
  f_xQ2_yhalf->SetLineColor(1);
  f_xQ2_yhalf->SetLineStyle(3);
  f_xQ2_yn1->Draw("SAME");
  f_xQ2_yn1->SetLineColor(1);
  f_xQ2_yn1->SetLineStyle(5);

  TLegend* leg_xQ2_y = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_y->AddEntry(f_xQ2_yn0, "y = 1", "L");
  leg_xQ2_y->AddEntry(f_xQ2_yhalf, "y = 0.5", "L");
  leg_xQ2_y->AddEntry(f_xQ2_yn1, "y = 0.1", "L");
  leg_xQ2_y->Draw();

  TCanvas *c_xQ2_ylog = new TCanvas();
  c_xQ2_ylog->SetLogx();
  c_xQ2_ylog->SetLogy();

  f_xQ2_yn0->Draw();
  f_xQ2_yn0->SetLineColor(1);
  f_xQ2_yn0->SetLineStyle(1);
  f_xQ2_yn0->SetTitle("");
  f_xQ2_yn0->GetXaxis()->SetTitle("x");
  f_xQ2_yn0->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_yn0->SetMinimum(10e-2);
  f_xQ2_yn0->SetMaximum(10e4);

  f_xQ2_yn1->Draw("SAME");
  f_xQ2_yn1->SetLineColor(1);
  f_xQ2_yn1->SetLineStyle(5);
  f_xQ2_yn2->Draw("SAME");
  f_xQ2_yn2->SetLineColor(1);
  f_xQ2_yn2->SetLineStyle(7);
  f_xQ2_yn3->Draw("SAME");
  f_xQ2_yn3->SetLineColor(1);
  f_xQ2_yn3->SetLineStyle(9);
  f_xQ2_yn4->Draw("SAME");
  f_xQ2_yn4->SetLineColor(1);
  f_xQ2_yn4->SetLineStyle(2);
  f_xQ2_yn5->Draw("SAME");
  f_xQ2_yn5->SetLineColor(1);
  f_xQ2_yn5->SetLineStyle(3);

  TLegend* leg_xQ2_ylog = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_ylog->AddEntry(f_xQ2_yn0, "y = 1", "L");
  leg_xQ2_ylog->AddEntry(f_xQ2_yn1, "y = 10^{-1}", "L");
  leg_xQ2_ylog->AddEntry(f_xQ2_yn2, "y = 10^{-2}", "L");
  leg_xQ2_ylog->AddEntry(f_xQ2_yn3, "y = 10^{-3}", "L");
  leg_xQ2_ylog->AddEntry(f_xQ2_yn4, "y = 10^{-4}", "L");
  leg_xQ2_ylog->AddEntry(f_xQ2_yn5, "y = 10^{-5}", "L");
  leg_xQ2_ylog->Draw();
 
  /*----------------------------------*/

  /*----------------------------------*/
  /*-------Hadronic System Mass-------*/
  /*-----------HERA Fig. 24-----------*/
  /*----------------------------------*/

  /*-----------Define Masses----------*/

  TF1 *f_xQ2_W3 = new TF1("f_xQ2_W3" , "([1] - [0]**2) / ((1/x) - 1)", 10e-7, 1);
  f_xQ2_W3->SetParameter( 0 , 0.938);
  f_xQ2_W3->SetParameter( 1 , (3)**2 );
  TF1 *f_xQ2_W10 = (TF1*)f_xQ2_W3->Clone("f_xQ2_W10");  
  f_xQ2_W10->SetParameter( 1 , (10)**2 );
  TF1 *f_xQ2_W50 = (TF1*)f_xQ2_W3->Clone("f_xQ2_W50");  
  f_xQ2_W50->SetParameter( 1 , (50)**2 );
  TF1 *f_xQ2_W100 = (TF1*)f_xQ2_W3->Clone("f_xQ2_W100");  
  f_xQ2_W100->SetParameter( 1 , (100)**2 );
  TF1 *f_xQ2_W150 = (TF1*)f_xQ2_W3->Clone("f_xQ2_W150");  
  f_xQ2_W150->SetParameter( 1 , (150)**2);
  TF1 *f_xQ2_W200 = (TF1*)f_xQ2_W3->Clone("f_xQ2_W200");  
  f_xQ2_W200->SetParameter( 1 , (200)**2);

  /*-----------Plot x-Q2--------------*/

  TCanvas *c_xQ2_W = new TCanvas();

  f_xQ2_W200->Draw();
  f_xQ2_W200->SetLineColor(1);
  f_xQ2_W200->SetLineStyle(1);
  f_xQ2_W200->SetTitle("");
  f_xQ2_W200->GetXaxis()->SetTitle("x");
  f_xQ2_W200->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_W200->SetMinimum(1);
  f_xQ2_W200->SetMaximum(10e4);

  f_xQ2_W150->Draw("SAME");
  f_xQ2_W150->SetLineColor(1);
  f_xQ2_W150->SetLineStyle(3);
  f_xQ2_W100->Draw("SAME");
  f_xQ2_W100->SetLineColor(1);
  f_xQ2_W100->SetLineStyle(5);
  f_xQ2_W50->Draw("SAME");
  f_xQ2_W50->SetLineColor(1);
  f_xQ2_W50->SetLineStyle(5);

  TLegend* leg_xQ2_W = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_W->AddEntry(f_xQ2_W50, "W = 50 GeV", "L");
  leg_xQ2_W->AddEntry(f_xQ2_W100, "W = 100 GeV", "L");
  leg_xQ2_W->AddEntry(f_xQ2_W150, "W = 150 GeV", "L");
  leg_xQ2_W->AddEntry(f_xQ2_W200, "W = 200 GeV", "L");
  leg_xQ2_W->Draw();

  TCanvas *c_xQ2_Wlog = new TCanvas();
  c_xQ2_Wlog->SetLogx();
  c_xQ2_Wlog->SetLogy();

  f_xQ2_W200->Draw();
  f_xQ2_W200->SetLineColor(1);
  f_xQ2_W200->SetLineStyle(1);
  f_xQ2_W200->SetTitle("");
  f_xQ2_W200->GetXaxis()->SetTitle("x");
  f_xQ2_W200->GetYaxis()->SetTitle("Q^{2} [GeV]");
  f_xQ2_W200->SetMinimum(10e-2);
  f_xQ2_W200->SetMaximum(10e4);

  f_xQ2_W100->Draw("SAME");
  f_xQ2_W100->SetLineColor(1);
  f_xQ2_W100->SetLineStyle(5);
  f_xQ2_W50->Draw("SAME");
  f_xQ2_W50->SetLineColor(1);
  f_xQ2_W50->SetLineStyle(7);
  f_xQ2_W10->Draw("SAME");
  f_xQ2_W10->SetLineColor(1);
  f_xQ2_W10->SetLineStyle(9);
  f_xQ2_W3->Draw("SAME");
  f_xQ2_W3->SetLineColor(1);
  f_xQ2_W3->SetLineStyle(2);

  TLegend* leg_xQ2_Wlog = new TLegend( 0.25, 0.65, 0.45, 0.85);
  leg_xQ2_Wlog->AddEntry(f_xQ2_W3, "W = 3 GeV", "L");
  leg_xQ2_Wlog->AddEntry(f_xQ2_W10, "W = 10 GeV", "L");
  leg_xQ2_Wlog->AddEntry(f_xQ2_W50, "W = 50 GeV", "L");
  leg_xQ2_Wlog->AddEntry(f_xQ2_W100, "W = 100 GeV", "L");
  leg_xQ2_Wlog->AddEntry(f_xQ2_W200, "W = 200 GeV", "L");
  leg_xQ2_Wlog->Draw();
 
  /*----------------------------------*/

  /*------------Make Files------------*/

  //  c_xQ2_LepA->Print("Plots/HERA/xQ2_HERA_LepA.eps");
  //  c_xQ2_LepA->Print("Plots/HERA/xQ2_HERA_LepA.png");
  //  c_xQ2_LepE->Print("Plots/HERA/xQ2_HERA_LepE.eps");
  //  c_xQ2_LepE->Print("Plots/HERA/xQ2_HERA_LepE.png");
  //  c_xQ2_JetA->Print("Plots/HERA/xQ2_HERA_JetA.eps");
  //  c_xQ2_JetA->Print("Plots/HERA/xQ2_HERA_JetA.png");
  //  c_xQ2_JetE->Print("Plots/HERA/xQ2_HERA_JetE.eps");
  //  c_xQ2_JetE->Print("Plots/HERA/xQ2_HERA_JetE.png");
  //  c_xQ2_y->Print("Plots/HERA/xQ2_HERA_y.eps");
  //  c_xQ2_y->Print("Plots/HERA/xQ2_HERA_y.png");
  //  c_xQ2_ylog->Print("Plots/HERA/xQ2_HERA_ylog.eps");
  //  c_xQ2_ylog->Print("Plots/HERA/xQ2_HERA_ylog.png");
  //  c_xQ2_W->Print("Plots/HERA/xQ2_HERA_W.eps");
  //  c_xQ2_W->Print("Plots/HERA/xQ2_HERA_W.png");
  //  c_xQ2_Wlog->Print("Plots/HERA/xQ2_HERA_Wlog.eps");
  //  c_xQ2_Wlog->Print("Plots/HERA/xQ2_HERA_Wlog.png");

  return 0;
}
