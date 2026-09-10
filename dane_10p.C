#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
           
#include "TH1D.h"
#include "TCanvas.h"   
using namespace std;
    
void dane_10p() {
    
    ifstream file("wyniki/16.8p/particle_lists.oscar");
         
    TH1D *a1 = new TH1D("y_a1","Rozklad pospiesznosci #pi+ dla sqrt(sNN) = 16.8 GeV;y;dN/dy",50, -5, 5);
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

      if (pdg == 211) {

    double rapidity = 0.5 * log((E + pz) / (E - pz));

    a1->Fill(rapidity);

        }
    }
    double N_events = 100.0;
    double bin_width = a1->GetBinWidth(1);

    a1->Scale(1.0 / (N_events * bin_width));
    a1->GetYaxis()->SetTitle("dN/dy");

    TCanvas *c = new TCanvas("c", "pi+ pospiesznosc", 800, 600);


    a1->Draw("HIST");
c->SaveAs("f1_10p.pdf");
}
