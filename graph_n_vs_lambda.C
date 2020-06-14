/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Apr 3 17:30:57 2018 +0200                                        *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

Double_t fitf(Double_t *x, Double_t *par);
void drawGraphs();

Double_t *parA = new Double_t[2];
Double_t *parB = new Double_t[2];

Double_t lam_min = 200;
Double_t lam_max = 800;
const Int_t nnMax = 10000;

void graph_n_vs_lambda(){
  TGraphErrors *gr_n_A = new TGraphErrors("n_A_Lam.dat");
  TGraphErrors *gr_n_B = new TGraphErrors("n_B_Lam.dat");
  gr_n_A->SetName("parabola");
  gr_n_A->SetTitle("parabola");
  TF1 *func = new TF1("fitf",fitf,lam_min,lam_max,2);
  func->SetParameters(0.09,83.29);
  func->SetParNames("A0","Lambda0");
  gr_n_A->SetMinimum(1.044);
  gr_n_A->Fit(func,"r",0);
  func->GetParameters(parA);
  gr_n_B->Fit(func,"r",0);
  func->GetParameters(parB);
  //----------------------------------------------------------------//
  //Not modified data before : Tue Jun  5 19:15:56 JST 2018         //
  //----------------------------------------------------------------//
  //Type A (upstream aerogel)   Aerogel1                            //
  //   NAME         VALUE         ERROR                             //
  //1  A0           9.04445e-02   3.19192e-04                       //
  //2  Lambda0      8.60104e+01   4.57665e+00                       //
  //Type B (downstream aerogel) Aerogel2                            //
  //1  A0           1.08692e-01   3.22418e-04                       //
  //2  Lambda0      8.45600e+01   3.91939e+00                       //
  //----------------------------------------------------------------//
  //Modified data to much 1.045 (for type A) and 1.055 (for type B) //
  //  Date : Tue Jun  5 19:18:13 JST 2018                           //
  //Type A (upstream aerogel)   Aerogel1                            //
  //   NAME         VALUE         ERROR                             //
  //1  A0           8.77337e-02   3.18295e-04                       //
  //2  Lambda0      8.71909e+01   4.63483e+00                       //
  //Type B (downstream aerogel) Aerogel2                            //
  //1  A0           1.08061e-01   3.22254e-04                       //
  //2  Lambda0      8.47807e+01   3.92907e+00                       //
  //----------------------------------------------------------------//
  drawGraphs();
}

Double_t fitf(Double_t *x, Double_t *par){
  Double_t fitval = 1 + par[0]*x[0]*x[0]/(x[0]*x[0]-par[1]*par[1]);
   if(fitval<0.0)
     return 0;
   return TMath::Sqrt(fitval);
}

void drawGraphs(){
  //
  TGraphErrors *gr_n_A = new TGraphErrors("n_A_Lam.dat");
  TGraphErrors *gr_n_B = new TGraphErrors("n_B_Lam.dat");
  //
  gr_n_A->SetName("gr_n_A");
  gr_n_A->SetTitle("n vs lambda");
  gr_n_A->SetMarkerStyle(21);
  gr_n_A->SetMarkerSize(1.5);
  gr_n_A->SetMarkerColor(kBlack);
  gr_n_A->SetLineColor(kBlack);
  gr_n_A->SetLineWidth(3);
  //
  gr_n_B->SetName("gr_n_B");
  gr_n_B->SetTitle("n vs lambda");
  gr_n_B->SetMarkerStyle(21);
  gr_n_B->SetMarkerSize(1.5);
  gr_n_B->SetMarkerColor(kRed);
  gr_n_B->SetLineColor(kRed);
  gr_n_B->SetLineWidth(3);
  //
  TF1 *funcA = new TF1("fitf",fitf,lam_min,lam_max,2);
  TF1 *funcB = new TF1("fitf",fitf,lam_min,lam_max,2);
  funcA->SetParameters(parA);
  funcB->SetParameters(parB);
  //
  Int_t i = 0;
  Double_t n_A[nnMax];
  Double_t n_B[nnMax];
  Double_t lam[nnMax];
  Double_t lamVal = 0.0;
  //
  for(i = 0 ; i<nnMax ; i++){
    lam[i] = lam_min + (lam_max - lam_min)/(nnMax-1)*i;
    lamVal = lam[i];
    n_A[i] = funcA->Eval(lamVal);
    n_B[i] = funcB->Eval(lamVal);
  }
  //  
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  //
  TCanvas *c1 = new TCanvas("c1","plots",10,10,800,800);
  c1->Clear();
  c1->SetFillColor(kWhite);
  c1->GetPad(0)->SetLeftMargin(0.12);
  c1->GetPad(0)->SetRightMargin(0.02);
  c1->GetPad(0)->SetTopMargin(0.07);
  c1->GetPad(0)->SetBottomMargin(0.2);
  //
  TGraph *grA = new TGraph(nnMax,lam,n_A);
  grA->SetName("grA");
  grA->SetTitle("n vs lambda");
  grA->SetMarkerStyle(6);
  grA->SetMarkerColor(kBlack);
  grA->SetLineColor(kBlack);
  grA->SetLineWidth(3);
  TGraph *grB = new TGraph(nnMax,lam,n_B);
  grB->SetName("grB");
  grB->SetTitle("n vs lambda");
  grB->SetMarkerStyle(6);
  grB->SetMarkerColor(kRed);
  grB->SetLineColor(kRed);
  grB->SetLineWidth(3);
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_n_A);
  mg->Add(gr_n_B);
  mg->Add(grA);
  mg->Add(grB);
  mg->SetMinimum(1.040);
  mg->SetMaximum(1.070);
  mg->Draw("AP");
  //
  mg->GetXaxis()->SetTitle("#lambda, nm");
  mg->GetYaxis()->SetTitle("Aerogel refractive index");  
  //
  //gr_n_A->Draw("APL");
  TF1 *f1 = new TF1("f1","1239.84/x",1.54980,6.19920);
  TGaxis *axis = new TGaxis( 200.0, 1.036, 800.0, 1.036, "f1", 510, "L+", 2);
  //axis->SetLabelColor(kRed);
  axis->SetTitle("h#nu, eV");
  axis->SetLabelSize(0.025);
  axis->Draw("same");
  //axis->SetTitleSize(0.01);
  //
  //gr_n_A->Draw("AP");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_n_A, "Data (Up stream)","p");
  leg->AddEntry(gr_n_B, "Data (Down stream)","p");
  leg->AddEntry(grA, "Sellmeier formula","lp");
  leg->AddEntry(grB, "Sellmeier formula","lp");
  leg->Draw();

}
