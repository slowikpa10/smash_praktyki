#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "TH1D.h"
#include "TFile.h"

using namespace std;

void zapisz_root() {

    ifstream file("data/8.77_procent10/particle_lists.oscar");

    TH1D *pi_plus= new TH1D("pi_plus","#pi+;y;dN/dy", 50, -5, 5);
    TH1D *pi_minus= new TH1D("pi_minus","#pi-;y;dN/dy", 50, -5, 5);
    TH1D *K_plus = new TH1D("K_plus","K+;y;dN/dy", 50, -5, 5);
    TH1D *K_minus= new TH1D("K_minus","K-;y;dN/dy", 50, -5, 5);
    TH1D *proton= new TH1D("proton","p;y;dN/dy", 50, -5, 5);
    TH1D *antiproton= new TH1D("antiproton","anti-p;y;dN/dy", 50, -5, 5);
    TH1D *Lambda= new TH1D("Lambda","#Lambda;y;dN/dy", 50, -5, 5);
    TH1D *antiLambda= new TH1D("antiLambda}","anti-Lambda;y;dN/dy", 50, -5, 5);
    TH1D *K0s= new TH1D("K0s","K0s;y;dN/dy", 50, -5, 5);

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

        double rapidity = 0.5 * log((E + pz) / (E - pz));

        if (pdg == 211)   pi_plus->Fill(rapidity);
        if (pdg == -211)  pi_minus->Fill(rapidity);

        if (pdg == 321)   K_plus->Fill(rapidity);
        if (pdg == -321)  K_minus->Fill(rapidity);

        if (pdg == 2212)  proton->Fill(rapidity);
        if (pdg == -2212) antiproton->Fill(rapidity);

        if (pdg == 3122)  Lambda->Fill(rapidity);
        if (pdg == -3122) antiLambda->Fill(rapidity);

        if (pdg == 311 || pdg == -311)
            K0s->Fill(rapidity, 0.5);
    }

    double N_events = 100.0;
    double bin_width = pi_plus->GetBinWidth(1);

    pi_plus->Scale(1.0/(N_events*bin_width));
    pi_minus->Scale(1.0/(N_events*bin_width));
    K_plus->Scale(1.0/(N_events*bin_width));
    K_minus->Scale(1.0/(N_events*bin_width));
    proton->Scale(1.0/(N_events*bin_width));
    antiproton->Scale(1.0/(N_events*bin_width));
    Lambda->Scale(1.0/(N_events*bin_width));
    antiLambda->Scale(1.0/(N_events*bin_width));
    K0s->Scale(1.0/(N_events*bin_width));

    TFile *out = new TFile("SMASH_ArSc_8.77.root", "RECREATE");

    pi_plus->Write();
    pi_minus->Write();
    K_plus->Write();
    K_minus->Write();
    proton->Write();
    antiproton->Write();
    Lambda->Write();
    antiLambda->Write();
    K0s->Write();

    out->Close();
}
