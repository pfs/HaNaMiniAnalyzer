{
int n = 3;
Double_t red[n]    = { 1.00, 1.00, 0.00};
Double_t green[n]  = { 0.00, 1.00, 0.00};
Double_t blue[n]   = { 0.00, 1.00, 1.00};
Double_t stops[n] = { 0.00, 0.50, 1.00 };
TColor::CreateGradientColorTable(n,stops,red,green,blue,50);
   gStyle->SetPaintTextFormat("4.1f");
}
