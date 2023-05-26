#include "pmon.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include <TFile.h>

std::string output_path = "/home/phnxrc/INTT/commissioning_5_23/hit_files/";

int main(int argc, char** argv)
{
    std::string filename;

    std::vector<std::string> replacements = {"_", "-", "."};
    std::size_t pos = std::string::npos;

    for(int c = 1; c < argc; ++c)
    {
        filename = argv[c];
        if(pfileopen(filename.c_str()))continue;

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

        prun();

        printf("Hits per event: %lf", (double)values.tot_hits / (double)values.evt);
    
        filename = output_path + Form("intt%d_run_%08d.root", values.felix_server, values.run);
        printf("\n\n");
        printf("Writing to file:\n\t%s\n", filename.c_str());
        printf("\n\n");
        TFile* file = TFile::Open(filename.c_str());
        tree->SetDirectory(file);
        tree->Write();
        file->Write();
        file->Close();
    }



    return 0;
}
