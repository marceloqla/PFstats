#ifndef PDBRESIDUES_H
#define PDBRESIDUES_H

#include "pdbatom.h";

using namespace std;

class PdbResidues
{
private:
    vector<PdbAtom*> atoms;

public:
    PdbResidues();
    void addAtom(PdbAtom* atom);
    vector<PdbAtom*> getAtoms();
    string getResname();
};

#endif // PDBRESIDUES_H
