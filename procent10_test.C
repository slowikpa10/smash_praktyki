 #include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

using namespace std;

void procent10_test() {

    ifstream file("wyniki/16.8p_100/particle_lists.oscar");

    TH1D *f = new TH1D( "y_f1","Rozklad pospiesznosci K+ dla sqrt(sNN) = 16.8 GeV;y;dN/dy",50, -5, 5);

    string tekst;

    while (getline(file, tekst)) {

        if (tekst.empty() || tekst[0] == '#')
            continue;

        stringstream dane(tekst);

        double t, x, y_pos, z, mass;
        double E, px, py, pz;
        int pdg, id, charge;

        dane >> t >> x >> y_pos >> z >> mass
             >> E >> px >> py >> pz
             >> pdg >> id >> charge;

        if (pdg == 321) {

            double rapidity =
                0.5 * log((E + pz) / (E - pz));

            f->Fill(rapidity);
        }
    }
    double N_events = 100.0;
    double bin_width = f->GetBinWidth(1);

    f->Scale(1.0 / (N_events * bin_width));
    f->GetXaxis()->SetTitle("y");
    f->GetYaxis()->SetTitle("dN/dy");

TFile *tf = TFile::Open("Dane_na61/K_plus/HEPData-ins2692441-v1-Figure_26_k_pos_at_150.root");
TDirectory *dir = (TDirectory*)tf->Get("Figure 26 k_pos at 150");
TGraphAsymmErrors *data = (TGraphAsymmErrors*)dir->Get("Graph1D_y1");
    TCanvas *c = new TCanvas( "c","SMASH vs NA61",800,600);
    f->Draw("HIST");

    // dane NA61
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1.0);
    data->Draw("P SAME");

    TLegend *leg =new TLegend(0.65, 0.75, 0.88, 0.88);
    leg->AddEntry(f, "Wygenerowane dane w SMASH", "l");
    leg->AddEntry(data, "Dane z publikacji", "p");
    leg->Draw();

    c->SaveAs("k_plus_16.8p100_SMASH_vs_NA61.pdf");
}
