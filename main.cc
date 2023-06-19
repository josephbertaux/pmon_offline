#include "pmon.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include <TFile.h>

//std::string text_file = "/home/phnxrc/INTT/commissioning_5_23/HITS_PER_EVENT_BY_RUN.txt";
//std::string text_file = "/home/phnxrc/INTT/commissioning_5_30/HITS_PER_EVENT_BY_RUN.txt";
//std::string output_path = "/home/phnxrc/INTT/commissioning_5_23/hit_files/";
std::string output_path = "/bbox/commissioning/INTT/hit_files/";

int main(int argc, char** argv)
{
    FILE* fptr = nullptr;//fopen(text_file.c_str(), "a");
    std::string filename;

    std::vector<std::string> replacements = {"_", "-", "."};
    std::size_t pos = std::string::npos;

    for(int c = 1; c < argc; ++c)
    {
        filename = argv[c];
        pfileopen(filename.c_str());

        while(true)
        {
            pos = filename.find("/");
            if(pos == std::string::npos)break;
            filename = filename.substr(pos+1);
        }

        for(std::vector<std::string>::const_iterator itr = replacements.begin(); itr != replacements.end(); ++itr)
        {
            while(true)
            {
                pos = filename.find(*itr);
                if(pos == std::string::npos)break;
                filename.replace(pos, itr->size(), " ");
            }
        }

        sscanf(filename.c_str(), "%*s intt%d %d %*d %*s", &values.felix_server, &values.run);

        printf("\n\n");
        printf("Reading file:\n\t%s\n", argv[c]);
        printf("\tfelix server: %d\trun number: %d\n", values.felix_server, values.run);
        printf("\n\n");

        values.evt = 0;
        values.tot_hits = 0;
        prun();

        printf("Hits per event: %lf\n", (double)values.tot_hits / (double)values.evt);
        if(fptr)fprintf(fptr, "%d %08d %12ld %12ld\n", values.felix_server, values.run, values.tot_hits, values.evt);
    }

    filename = output_path + Form("run_%08d.root", values.run);
    printf("\n\n");
    printf("Writing to file:\n\t%s\n", filename.c_str());
    printf("\n\n");
    TFile* file = TFile::Open(filename.c_str(), "RECREATE");
    file->cd();
    tree->Write();
    file->Write();
    file->Close();

    if(fptr)fclose(fptr);

    return 0;
}
