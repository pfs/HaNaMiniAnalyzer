{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Nov 28 23:41:09 2016) by ROOT version5.34/19
   TCanvas *c1 = new TCanvas("c1", "c1",13,36,700,502);
   c1->Range(10,1.925,70,11.975);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(8);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,20,3.6);
   graph->SetPoint(1,25,4.4);
   graph->SetPoint(2,30,5.5);
   graph->SetPoint(3,35,6.5);
   graph->SetPoint(4,40,7.2);
   graph->SetPoint(5,45,8.1);
   graph->SetPoint(6,50,9.5);
   graph->SetPoint(7,59.9137934,10.27879752);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,16,64);
   Graph_Graph1->SetMinimum(2.93);
   Graph_Graph1->SetMaximum(10.97);
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
   
   
   TF1 *PrevFitTMP = new TF1("PrevFitTMP","pol1",16,64);
   PrevFitTMP->SetFillColor(19);
   PrevFitTMP->SetFillStyle(0);
   PrevFitTMP->SetLineColor(2);
   PrevFitTMP->SetLineWidth(2);
   PrevFitTMP->SetChisquare(0.5392152);
   PrevFitTMP->SetNDF(6);
   PrevFitTMP->GetXaxis()->SetLabelFont(42);
   PrevFitTMP->GetXaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetXaxis()->SetTitleFont(42);
   PrevFitTMP->GetYaxis()->SetLabelFont(42);
   PrevFitTMP->GetYaxis()->SetLabelSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleSize(0.035);
   PrevFitTMP->GetYaxis()->SetTitleFont(42);
   PrevFitTMP->SetParameter(0,0.1838361);
   PrevFitTMP->SetParError(0,0.3409611);
   PrevFitTMP->SetParLimits(0,0,0);
   PrevFitTMP->SetParameter(1,0.175814);
   PrevFitTMP->SetParError(1,0.008502578);
   PrevFitTMP->SetParLimits(1,0,0);
   graph->GetListOfFunctions()->Add(PrevFitTMP);
   graph->Draw("ap");
   
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
