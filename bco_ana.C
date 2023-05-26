std::string text_file = "hitrate_vs_params.txt";
std::string root_file = "hitrate_vs_params.root";

std::string file_path = "/home/phnxrc/INTT/commissioning_5_23/hit_files/";

struct RunParams_s
{
    int delay = -1;
    int n_cols = -1;
    int open_time = -1;
};
std::map<int, struct RunParams_s> runs =
{
    //{8002, (struct RunParams_s){.delay = 54, .n_cols = 127}},
    //{8005, (struct RunParams_s){.delay = 20, .n_cols = 127}},

    //{8006, (struct RunParams_s){.delay = 54, .n_cols = 2}},
    //{8007, (struct RunParams_s){.delay = 52, .n_cols = 2}},
    //{8008, (struct RunParams_s){.delay = 56, .n_cols = 2}},
    //{8009, (struct RunParams_s){.delay = 50, .n_cols = 2}},
    //{8010, (struct RunParams_s){.delay = 58, .n_cols = 2}},
    //{8011, (struct RunParams_s){.delay = 48, .n_cols = 2}},
    //{8012, (struct RunParams_s){.delay = 60, .n_cols = 2}},
    ////{8013, (struct RunParams_s){.delay = 46, .n_cols = 2}},
    //{8014, (struct RunParams_s){.delay = 62, .n_cols = 2}},
    //{8015, (struct RunParams_s){.delay = 44, .n_cols = 2}},
    //{8016, (struct RunParams_s){.delay = 64, .n_cols = 2}},
    //{8017, (struct RunParams_s){.delay = 100, .n_cols = 2}},

    {8020, (struct RunParams_s){.delay =    0,      .n_cols =   127,    .open_time = 120}},

    {8021, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 80}},
    {8023, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 75}},
    {8024, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 70}},
    {8025, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 65}},
    {8026, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 60}},
    {8027, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 50}},
    {8028, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 40}},
    {8030, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 30}},
    {8031, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 20}},
    {8032, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 10}},
    {8033, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 15}},
    {8034, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 17}},
    {8035, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 19}},
    {8036, (struct RunParams_s){.delay =    20,     .n_cols =   127,    .open_time = 12}},

    {8037, (struct RunParams_s){.delay =    25,     .n_cols =   127,    .open_time = 25}},
    {8038, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 25}},
    {8039, (struct RunParams_s){.delay =    25,     .n_cols =   127,    .open_time = 25}},
    {8040, (struct RunParams_s){.delay =    25,     .n_cols =   110,    .open_time = 25}},
    {8041, (struct RunParams_s){.delay =    25,     .n_cols =   90,     .open_time = 25}},
    {8042, (struct RunParams_s){.delay =    25,     .n_cols =   30,     .open_time = 25}},
    {8043, (struct RunParams_s){.delay =    25,     .n_cols =   50,     .open_time = 25}},
    {8044, (struct RunParams_s){.delay =    25,     .n_cols =   70,     .open_time = 25}},
    {8045, (struct RunParams_s){.delay =    25,     .n_cols =   60,     .open_time = 25}},
    {8046, (struct RunParams_s){.delay =    25,     .n_cols =   55,     .open_time = 25}},
    {8047, (struct RunParams_s){.delay =    25,     .n_cols =   52,     .open_time = 25}},
    {8048, (struct RunParams_s){.delay =    25,     .n_cols =   53,     .open_time = 25}},
    {8049, (struct RunParams_s){.delay =    25,     .n_cols =   54,     .open_time = 25}},

    {8050, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8051, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8052, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8053, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8054, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8056, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8057, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8058, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
    {8059, (struct RunParams_s){.delay =    25,     .n_cols =   120,    .open_time = 35}},
};

void bco_ana()
{
    FILE* fptr = fopen(text_file.c_str(), "w+");
    fprintf(fptr, "%16s\t%12s\n", "hitrate", "delay");

    TTree* bco_tree = new TTree("bco_tree", "bco_tree");

    double hitrate = 0;
    bco_tree->Branch("hitrate", &hitrate);

    struct RunParams_s params;
    bco_tree->Branch("delay", &params.delay);
    bco_tree->Branch("n_cols", &params.n_cols);
    bco_tree->Branch("open_time", &params.open_time);

    int felix_server = 0;
    int felix_module = 0;

    int prev_evt = -1;
    int evt = 0;

    Long64_t tot_evts = 0;
    Long64_t tot_hits = 0;

    std::string filename;
    for(std::map<int, struct RunParams_s>::const_iterator itr = runs.begin(); itr != runs.end(); ++itr)
    {
        filename = file_path + Form("run_%08d.root", itr->first);

        TFile* file = TFile::Open(filename.c_str(), "READ");
        if(!file)continue;
        TTree* tree = (TTree*)file->Get("tree");
        if(!tree)continue;

        printf("\n");
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
            //if(!(0 <= felix_module && felix_module < 7))continue;
            if(felix_module != 0)continue;

            if(evt != prev_evt)
            {
                prev_evt = evt;
                ++tot_evts;
            }

            ++tot_hits;
        }

        hitrate = (double)tot_hits / (double)tot_evts;
        params.delay = itr->second.delay;
        params.n_cols = itr->second.n_cols;
        params.open_time = itr->second.open_time;

        printf("%16s\t%12s\n", "hitrate", "delay");
        printf("%16.4lf\t%12d\n", hitrate, params.delay);
        printf("\n");

        fprintf(fptr, "%16.4lf\t%12d\n", hitrate, params.delay);
        bco_tree->Fill();

        file->Close();
        delete file;
    }


    bco_tree->SetMarkerStyle(20);
    bco_tree->SetMarkerSize(2);

    TCanvas* delay_cnvs = new TCanvas("hitrate_vs_delay", "hitrate_vs_delay");
    delay_cnvs->cd();
    bco_tree->Draw("hitrate:delay");
    delay_cnvs->SaveAs("hitrate_vs_delay.png");

    TCanvas* n_cols_cnvs = new TCanvas("hitrate_vs_n_cols", "hitrate_vs_n_cols");
    n_cols_cnvs->cd();
    bco_tree->Draw("hitrate:n_cols");
    n_cols_cnvs->SaveAs("hitrate_vs_n_cols.png");

    TCanvas* open_time_cnvs = new TCanvas("hitrate_vs_open_time", "hitrate_vs_open_time");
    open_time_cnvs->cd();
    bco_tree->Draw("hitrate:open_time");
    open_time_cnvs->SaveAs("hitrate_vs_open_time.png");

    TFile* file = TFile::Open(root_file.c_str(), "RECREATE");
    file->cd();
    bco_tree->Write();
    file->Write();
    file->Close();

    fclose(fptr);
}
