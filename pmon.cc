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

    values = (struct InttOnline_s){};

    return 0;
}

int process_event(Event* e)
{
    if(!e)return 0;

    Packet* p = e->getPacket(values.felix_server + 3001);
    if(!p)return 0;

    values.num_hits = p->iValue(0, "NR_HITS");
    values.full_bco = p->lValue(0, "BCO");

    //values.evt = (uint32_t)(p->iValue(0, "DATAWORD"));
    //values.evt = (values.evt & 0xffff0000) >> 0x10;// + (values.evt & 0x0000ffff) << 0x10;

    for(int n = 0; n < values.num_hits; ++n)
    {
        values.felix_module = p->iValue(n, "FEE");

        values.bco = p->iValue(n, "FPHX_BCO");
        values.chp = p->iValue(n, "CHIP_ID") % 26;
        values.chn = p->iValue(n, "CHANNEL_ID");
        values.adc = p->iValue(n, "ADC");
        values.amp = p->iValue(n, "AMPLITUDE");

        tree->Fill();
    }

    values.tot_hits += values.num_hits;
    ++values.evt;
    //tree->Fill();

    delete p;

    return 0;
}
