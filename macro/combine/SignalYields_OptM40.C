{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Nov  6 12:13:13 2016) by ROOT version5.34/19
   TCanvas *c1 = new TCanvas("c1", "c1",13,36,700,500);
   c1->Range(10,-0.25,70,2.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(9);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetPoint(0,20,0.4175002743);
   graph->SetPoint(1,25,0.5894062188);
   graph->SetPoint(2,30,0.6820576966);
   graph->SetPoint(3,35,0.7873182337);
   graph->SetPoint(4,40,0.931308353);
   graph->SetPoint(5,45,1.066381359);
   graph->SetPoint(6,50,1.125357659);
   graph->SetPoint(7,55,0.9534972781);
   graph->SetPoint(8,60,0.7293421589);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,16,64);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(2);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   
   TF1 *PrevFitTMP = new TF1("PrevFitTMP","pol3",18.88,60.16);
   PrevFitTMP->SetFillColor(19);
   PrevFitTMP->SetFillStyle(0);
   PrevFitTMP->SetLineColor(2);
   PrevFitTMP->SetLineWidth(2);
   PrevFitTMP->SetChisquare(0.01002323);
   PrevFitTMP->SetNDF(5);
   PrevFitTMP->GetXaxis()->SetLabelFont(42);
   PrevFitTMP->GetXaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleFont(42);
   PrevFitTMP->GetYaxis()->SetLabelFont(42);
   PrevFitTMP->GetYaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleFont(42);
   PrevFitTMP->SetParameter(0,1.265976);
   PrevFitTMP->SetParError(0,0.5186312);
   PrevFitTMP->SetParLimits(0,0,0);
   PrevFitTMP->SetParameter(1,-0.1091047);
   PrevFitTMP->SetParError(1,0.04352519);
   PrevFitTMP->SetParLimits(1,0,0);
   PrevFitTMP->SetParameter(2,0.004279227);
   PrevFitTMP->SetParError(2,0.001142955);
   PrevFitTMP->SetParLimits(2,0,0);
   PrevFitTMP->SetParameter(3,-4.348363e-05);
   PrevFitTMP->SetParError(3,9.486587e-06);
   PrevFitTMP->SetParLimits(3,0,0);
   graph->GetListOfFunctions()->Add(PrevFitTMP);
   graph->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.4397126,0.9342405,0.5602874,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("Graph");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
