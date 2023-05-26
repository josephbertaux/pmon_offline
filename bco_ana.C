std::string text_file = "hitrate_vs_delay.txt";
std::string root_file = "hitrate_vs_delay.root";

std::string file_path = "/home/phnxrc/INTT/commissioning_5_23/hit_files/";
std::map<int, int> runs =
{
    //{8002, 54},
    //{8005, 20},
    {8006, 54},
    {8007, 52},
    {8008, 56},
    {8009, 50},
    {8010, 58},
    {8011, 48},
    {8012, 60},
    //{8013, 46},
    {8014, 62},
    {8015, 44},
    {8016, 64},
    {8017, 100},
};

void bco_ana()
{
    FILE* fptr = fopen(text_file.c_str(), "w+");
    TTree* bco_tree = new TTree("bco_tree", "bco_tree");
    int delay = 0;
    double hitrate = 0;
    bco_tree->Branch("delay", &delay);
    bco_tree->Branch("hitrate", &hitrate);

    int felix_server = 0;
    int felix_module = 0;

    int prev_evt = -1;
    int evt = 0;

    Long64_t tot_evts = 0;
    Long64_t tot_hits = 0;

    std::string filename;

    for(std::map<int, int>::const_iterator itr = runs.begin(); itr != runs.end(); ++itr)
    {
        filename = file_path + Form("run_%08d.root", itr->first);

        TFile* file = TFile::Open(filename.c_str(), "READ");
        if(!file)continue;
        TTree* tree = (TTree*)file->Get("tree");
        if(!tree)continue;

        printf("Reading file:\n\t%s\n", filename.c_str());

        tree->SetBranchAddress("felix_server", &felix_server);
        tree->SetBranchAddress("felix_module", &felix_module);
        tree->SetBranchAddress("evt", &evt);

        prev_evt = -1;
        evt = 0;
        tot_hits = 0;
        tot_evts = 0;
        for(Long64_t n = 0; n < tree->GetEntriesFast(); ++n)
        {
            tree->GetEntry(n);

            if(felix_server != 2)continue;
            if(!(0 <= felix_module && felix_module < 7))continue;

            if(evt != prev_evt)
            {
                prev_evt = evt;
                ++tot_evts;
            }

            ++tot_hits;
        }

        printf("tot_hits: %lld\tnum_evt: %lld\tdelay: %d\n", tot_hits, tot_evts, itr->second);

        delay = itr->second;
        hitrate = (double)tot_hits / (double)tot_evts;
        fprintf(fptr, "%12d\t%16.4lf\n", delay, hitrate);
        bco_tree->Fill();

        file->Close();
        delete file;
    }

    TCanvas* cnvs = new TCanvas("hitrate_v_delay", "hitrate_v_delay");
    cnvs->cd();

    bco_tree->SetMarkerStyle(20);
    bco_tree->SetMarkerSize(2);
    bco_tree->Draw("hitrate:delay");

    cnvs->SaveAs("hitrate_v_delay.png");
    delete cnvs;

    TFile* file = TFile::Open(root_file.c_str(), "RECREATE");
    file->cd();
    bco_tree->Write();
    file->Write();
    file->Close();

    fclose(fptr);
}
