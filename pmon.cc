#include <pmonitor/pmonitor.h>

#include "pmon.h"


struct InttOnline_s values = (struct InttOnline_s){};
TTree* tree = nullptr;

int pinit()
{
    if(!tree)
    {
        tree = new TTree("tree", "tree");

        tree->Branch("full_bco", &values.full_bco);
        tree->Branch("bco", &values.bco);
        tree->Branch("felix_server", &values.felix_server);
        tree->Branch("felix_module", &values.felix_module);
        tree->Branch("chp", &values.chp);
        tree->Branch("chn", &values.chn);
        tree->Branch("adc", &values.adc);
        tree->Branch("amp", &values.amp);
        tree->Branch("num_hits", &values.num_hits);
        tree->Branch("evt", &values.evt);
    }

    tree->Reset();
    values = (struct InttOnline_s){};

    return 0;
}

int process_event(Event* e)
{
    if(!e)return 1;

    Packet* p = e->getPacket(values.felix_server + 3001);
    if(!p)return 1;

    int N = p->iValue(0, "NR_HITS");
    if(!N)return 1;

    for(int n = 0; n < N; ++n)
    {
        values.full_bco = p->lValue(n, "BCO");
        values.bco = p->iValue(n, "FPHX_BCO");
        values.felix_module = p->iValue(n, "FEE");
        values.chp = p->iValue(n, "CHIP_ID") % 26;
        values.chn = p->iValue(n, "CHANNEL_ID");
        values.adc = p->iValue(n, "ADC");
        values.amp = p->iValue(n, "AMPLITUDE");
        values.num_hits = N;

        tree->Fill();
    }

    values.tot_hits += N;
    ++values.evt;

    return 0;
}
