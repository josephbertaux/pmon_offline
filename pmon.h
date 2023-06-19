#ifndef PMON_H
#define PMON_H

#include <pmonitor/pmonitor.h>
#include <Event/Event.h>
#include <Event/EventTypes.h>

#include <cstdio>
#include <cstdint>

#include <TTree.h>

struct InttOnline_s
{
    Long64_t full_bco = 0;
    int bco = 0;
    int felix_server = 0;
    int felix_module = 0;
    int chp = 0;
    int chn = 0;
    int adc = 0;
    int amp = 0;
    int num_hits = 0;
    int evt = 0;
    int run = 0;
    Long64_t tot_hits = 0;
};

extern struct InttOnline_s values;
extern TTree* tree;

int pinit();
int process_event(Event*);

#endif//PMON_H
