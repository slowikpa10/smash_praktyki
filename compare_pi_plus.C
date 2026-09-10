#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

using namespace std;

void compare_pi_plus() {

    vector<string> energie = {"5.12","6.12","7.62","8.77","11.9","16.8"};
    vector<TH1D*> histogramy;

    for (int i=0; i<6; i++) {
        ifstream file("wyniki/" + energie[i] + "/particle_lists.oscar");
        TH1D *a1 = new TH1D(("a1_"+energie[i]).c_str(),"#bar{#Lambda};y;dN/dy",50,-5,5);

        string tekst;

        while (getline(file,tekst)) {

            if (tekst.empty() || tekst[0]=='#')
                continue;

            stringstream dane(tekst);

            double t,x,y_pos,z,mass;
            double E,px,py,pz;
            int pdg,id,charge;

            dane >> t >> x >> y_pos >> z >> mass
                 >> E >> px >> py >> pz
                 >> pdg >> id >> charge;

           if (pdg == -3122) {

    double rapidity = 0.5 * log((E + pz) / (E - pz));

    a1->Fill(rapidity);
} 
        }

        double N_events = 100.0;
        double bin_width = a1->GetBinWidth(1);

        a1->Scale(1.0/(N_events*bin_width));

        histogramy.push_back(a1);//zapisuje histogram na koncu
    }
    TCanvas *c = new TCanvas("c","antylambda pospiesznosc",800,600);
    TLegend *leg = new TLegend(0.7,0.65,0.88,0.88);

    for (int i=0; i<6; i++) {

        histogramy[i]->SetLineColor(i+1); //dodaje kolor do kazdego histogramu
        histogramy[i]->SetLineWidth(2);

        if (i==0)
            histogramy[i]->Draw("HIST");
        else
            histogramy[i]->Draw("HIST SAME");
string opis = energie[i] + " GeV";
    leg->AddEntry(histogramy[i],opis.c_str(),"l");
}
    leg->Draw();

    c->SaveAs("pi_alambda_energie.pdf");
}
