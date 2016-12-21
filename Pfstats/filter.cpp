﻿#include "filter.h"

Filter::Filter()
{
    name = "Filtered Alignment";
    alphabet = "T20";
    type = 0;
    refSeq = "";
    taxon = "";
    minOcc = 0;
    minId = 0;
    maxId = 0;
    conservedPDBpath = "";
    commPDBPath = "";
    cons_min = 0.8;

    c = new Colors();
}

Filter::Filter(string name, string alphabet, int type){
    this->name = name;
    this->alphabet = alphabet;
    this->type = type;
    refSeq = "";
    taxon = "";
    minOcc = 0;
    minId = 0;
    maxId = 0;
    conservedPDBpath = "";
    cons_min = 0.8;
    corr_min_score = 0;
    corr_minssfraction = 0;
    corr_min_delta = 0;
    corr_refseq = 0;
    commPDBPath = "";

    c = new Colors();
}

Filter::~Filter(){
    this->clear();
}

void Filter::clear(){
    name.clear();
    name.shrink_to_fit();
    alphabet.clear();
    alphabet.shrink_to_fit();
    refSeq.clear();
    refSeq.shrink_to_fit();
    taxon.clear();
    taxon.shrink_to_fit();
    minOcc = 0;
    minId = 0;
    maxId = 0;
    cons_pdb.clear();
    cons_pdb.shrink_to_fit();
    cons_min = 0;
    corr_pdb.clear();
    corr_pdb.shrink_to_fit();
    corr_min_score = 0;
    corr_minssfraction = 0;
    corr_min_delta = 0;
    corr_refseq = 0;
    conservedPDBpath.clear();
    conservedPDBpath.shrink_to_fit();
    commPDBPath.clear();
    commPDBPath.shrink_to_fit();
    refseqs.clear();
    refseqs.shrink_to_fit();
    frequencies.clear();
    frequencies.shrink_to_fit();
    dG.clear();
    dG.shrink_to_fit();
    consDG.clear();
    consDG.shrink_to_fit();
    consvfreq.clear();
    consvfreq.shrink_to_fit();
    consfreqPerc.clear();
    consfreqPerc.shrink_to_fit();
    SortOrder.clear();
    SortOrder.shrink_to_fit();
    subsetfrequencies.clear();
    subsetfrequencies.shrink_to_fit();
    minssData.clear();
    minssData.shrink_to_fit();
    corrGraph.clear();
    corrGraph.shrink_to_fit();
    subalignmentseqs.clear();
    subalignmentseqs.shrink_to_fit();
    referencesequence = 0;
    referencevector.clear();
    referencevector.shrink_to_fit();
    comunidades.clear();
    comunidades.shrink_to_fit();
    residuesComm.clear();
    residuesComm.shrink_to_fit();
    residuesCommPs.clear();
    residuesCommPs.shrink_to_fit();
    communityX.clear();
    communityX.shrink_to_fit();
    communityXAll.clear();
    communityXAll.shrink_to_fit();
    communityXps.clear();
    communityXps.shrink_to_fit();
    selfcorrelationmatrix.clear();
    selfcorrelationmatrix.shrink_to_fit();
    Deltas.clear();
    Deltas.shrink_to_fit();
    weights.clear();
    weights.shrink_to_fit();
    uniprotMined.clear();
    uniprotMined.shrink_to_fit();
}

vector<string> Filter::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

unsigned int Filter::freqmatrixposition(char c){
    if((c=='a')||(c=='A')) return 1;
    if((c=='c')||(c=='C')) return 2;
    if((c=='d')||(c=='D')) return 3;
    if((c=='e')||(c=='E')) return 4;
    if((c=='f')||(c=='F')) return 5;
    if((c=='g')||(c=='G')) return 6;
    if((c=='h')||(c=='H')) return 7;
    if((c=='i')||(c=='I')) return 8;
    if((c=='k')||(c=='K')) return 9;
    if((c=='l')||(c=='L')) return 10;
    if((c=='m')||(c=='M')) return 11;
    if((c=='n')||(c=='N')) return 12;
    if((c=='p')||(c=='P')) return 13;
    if((c=='q')||(c=='Q')) return 14;
    if((c=='r')||(c=='R')) return 15;
    if((c=='s')||(c=='S')) return 16;
    if((c=='t')||(c=='T')) return 17;
    if((c=='v')||(c=='V')) return 18;
    if((c=='w')||(c=='W')) return 19;
    if((c=='y')||(c=='Y')) return 20;
    if((c=='x')||(c=='X')||(c=='.')||(c=='-')) return 0;
    return 0;
}

long double Filter::lnfact(int x){
    long double result=1.0;
    if ((x==0)||(x==1)) return(0.0);
    else for (int i=1;i<=x;i++) result=result*((long double)i);
    return (logl(result));
}

long double Filter::stirling(int x){
    if(x<=8) return(lnfact(x));
    return ((((long double)x)+0.5)*logl((long double)x)-x+0.918938533205);
}

long double Filter::lnbdf(int N, int nx, float px){
    if(N==nx) return ((long double)N*logl((long double)px));
    if(nx==0) return ((long double)N*logl((long double)(1.0-px)));
    return (stirling(N)-stirling(nx)-stirling(N-nx)+((long double)nx)*logl((long double)px)+((long double)(N-nx))*logl(1-(long double)(px)));
}

char Filter::num2aa(int n){
    if(n==1) return ('A');
    if(n==2) return ('C');
    if(n==3) return ('D');
    if(n==4) return ('E');
    if(n==5) return ('F');
    if(n==6) return ('G');
    if(n==7) return ('H');
    if(n==8) return ('I');
    if(n==9) return ('K');
    if(n==10) return ('L');
    if(n==11) return ('M');
    if(n==12) return ('N');
    if(n==13) return ('P');
    if(n==14) return ('Q');
    if(n==15) return ('R');
    if(n==16) return ('S');
    if(n==17) return ('T');
    if(n==18) return ('V');
    if(n==19) return ('W');
    if(n==20) return ('Y');
    return('-');
}

bool Filter::isaa(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y'))
         return true;
    else return false;
}

bool Filter::isaax(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
        (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y')||(c=='X'))
         return true;
    else return false;
}

vector<vector<int> > Filter::createBlankIntMatrix(int i1, int j1, int v){
    vector<vector<int> > matrix;

    for(int i = 0; i < i1; i++){
        vector<int> vec
                ;
        for(int j = 0; j < j1; j++){
            vec.push_back(v);
        }
        matrix.push_back(vec);
    }

    return matrix;
}

unsigned int Filter::AlignNumbering2Sequence2(int seqnumber, int position, vector<string> fullSequences){
    unsigned int c1;

    referencesequence=seqnumber;
    if(referencevector.size()>0) referencevector.clear();

    for(c1=0;c1<=fullSequences[0].size()-1;c1++)
        if(isaax(fullSequences[seqnumber-1][c1])) referencevector.push_back(c1);


    for(unsigned int c1=0;c1<=referencevector.size()-1;c1++)
        if (referencevector[c1]==position) return(c1+1);
    return 0;
}

unsigned int Filter::GetOffsetFromSeqName(string seqname){
    bool found=false;
    string offsetstr;
    unsigned int c1=0;

    while (c1<seqname.length()){
        if(seqname[c1]=='/'){
            found=true;
            c1++;
            break;
        }
        c1++;
    }

    if (!found) return 0;

    while (c1<seqname.length()){
        if(seqname[c1]=='-') break;
        else offsetstr+=seqname[c1];
        c1++;
    }

    return(atoi(offsetstr.c_str())-1);
}

int Filter::seqname2seqint2(string refseqcode, vector<string> fullAlignment){
    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        vector<string> vecSplit = this->split(fullAlignment[i],'/');
        if(vecSplit[0] == refseqcode) return i;
    }
    return 0;
}

vector<int> Filter::getRefSeqCodes(vector<string> fullAlignment){
    vector<int> codes;
    for(unsigned int i = 0; i < refseqs.size(); i++){
        codes.push_back(seqname2seqint2(refseqs[i],fullAlignment));
    }

    return codes;
}

long Filter::eto10(long double x){
    return (x/((long double)2.30258509299));
}

long double Filter::cbd_tietjen(int N, int n, float freq, bool right){
    long double a=pow(1-freq,N);

    if((!right)&&(n==0)) return a;
    if((right)&&(n==0)) return 1;

    long double sum=0;
    if(!right) sum=a;

    float u=freq/(1-freq);

    for(int i=2;i<=N+1;i++){
        a=a*u*((float)(N+2-i))/((float)(i-1));
        if(((!right)&&(i<=n+1))||((right)&&(i-1>=n)))
            sum+=a;
    }

    return sum;
}

int Filter::cbd(int N, int n, float freq, bool right){
    if(pow(1-freq,N)!=0) return ((int)ceil(log10(cbd_tietjen(N,n,freq,right))));
    float minP;
    float sum=0;
    float *Ps = new float [(N-n)+1];
    float *lPs = new float [n+1];

    if ((!Ps)||(!lPs)){
        QMessageBox::critical(NULL,"ERROR","Insuficient memory");
        return 1;
    }

    minP=(float)eto10(lnbdf(N,n,freq));
    if(right){
        for (int i=n;i<=N;i++){
            Ps[i-n]=(float)eto10(lnbdf(N,i,freq));
            if(Ps[i-n]>minP) minP=Ps[i-n];
        }

        for (int i=n;i<=N;i++){
            sum+=pow(10,Ps[i-n]-floor(minP));
        }
    }else{
        for (int i=0;i<=n;i++){
            lPs[i]=(float)eto10(lnbdf(N,i,freq));

            if(lPs[i]>minP) minP=lPs[i];
        }

            for (int i=0;i<=n;i++){
                sum+=pow(10,lPs[i]-floor(minP));
        }
    }
    delete Ps;
    delete lPs;

    printf("P<10^%i\n",int(floor(logl(sum))+floor(minP)));
    return(int(floor(logl(sum))+floor(minP)));
}

Feature* Filter::parseFeature(string feature){
    Feature *f = new Feature();

    if(feature[0] == ' ') feature = feature.substr(1);

    vector<string> vecFilter = split(feature,' ');

    f->setType("");
    if(vecFilter[0] == "ACT_SITE") f->setType("Active Site");
    else if(vecFilter[0] == "BINDING") f->setType("Binding Site");
    else if(vecFilter[0] == "CA_BIND") f->setType("Calcium Bind");
    else if(vecFilter[0] == "DNA_BIND") f->setType("DNA Bind");
    else if(vecFilter[0] == "METAL") f->setType("Metal Bind");
    else if(vecFilter[0] == "NP_BIND") f->setType("Nucleotide Bind");
    else if(vecFilter[0] == "SITE") f->setType("Site");
    else if(vecFilter[0] == "CROSSLNK") f->setType("Cross-Link");
    else if(vecFilter[0] == "DISULFID") f->setType("Disulfide Bond");
    else if(vecFilter[0] == "CARBOHYD") f->setType("Glycosylation");
    else if(vecFilter[0] == "LIPID") f->setType("Lipidation");
    else if(vecFilter[0] == "MOD_RES") f->setType("Modified Residue");

    if(f->getType() == "") return f;

    if(vecFilter[1] == vecFilter[2]) f->setPosition(atoi(vecFilter[2].c_str()));
    else{
        f->setBegin(atoi(vecFilter[1].c_str()));
        f->setEnd(atoi(vecFilter[2].c_str()));
    }

    string description = "";

    for(unsigned int i = 3; i < vecFilter.size(); i++)
        description += vecFilter[i] + " ";

    f->setDescription(description);

    return f;
}

int Filter::countAA(char aa, int col){
    if(col > sequences[0].size()) return 0;

    int count = 0;
    for(unsigned int i = 0; i < sequences.size(); i++){
        if(sequences[i][col] == aa) count ++;
    }

    return count;
}

string Filter::typeToString(){
    switch(type){
    case 9:
        return "Full Alignment";
    case 8:
        return "Full ALignment";
    case 0:
        return "HMM";
    case 1:
        return "Refseq";
    case 2:
        return "Henikof";
    }

    return "Full Alignment";
}

int Filter::blosum_indexes(char c){
    switch(c){
        case 'A': return 0;
        case 'R': return 1;
        case 'N': return 2;
        case 'D': return 3;
        case 'C': return 4;
        case 'Q': return 5;
        case 'E': return 6;
        case 'G': return 7;
        case 'H': return 8;
        case 'I': return 9;
        case 'L': return 10;
        case 'K': return 11;
        case 'M': return 12;
        case 'F': return 13;
        case 'P': return 14;
        case 'S': return 15;
        case 'T': return 16;
        case 'W': return 17;
        case 'Y': return 18;
        case 'V': return 19;
        default: return -1;
    }
}

int Filter::BLOSUM62(char c1, char c2){
    int matrix[20][20] = {
        { 4, -1, -2, -2,  0, -1, -1,  0, -2, -1, -1, -1, -1, -2, -1,  1,  0, -3, -2,  0},
        {-1,  5,  0, -2, -3,  1,  0, -2,  0, -3, -2,  2, -1, -3, -2, -1, -1, -3, -2, -3},
        {-2,  0,  6,  1, -3,  0,  0,  0,  1, -3, -3,  0, -2, -3, -2,  1,  0, -4, -2, -3},
        {-2, -2,  1,  6, -3,  0,  2, -1, -1, -3, -4, -1, -3, -3, -1,  0, -1, -4, -3, -3},
        { 0, -3, -3, -3,  9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1},
        {-1,  1,  0,  0, -3,  5,  2, -2,  0, -3, -2,  1,  0, -3, -1,  0, -1, -2, -1, -2},
        {-1,  0,  0,  2, -4,  2,  5, -2,  0, -3, -3,  1, -2, -3, -1,  0, -1, -3, -2, -2},
        { 0, -2,  0, -1, -3, -2, -2,  6, -2, -4, -4, -2, -3, -3, -2,  0, -2, -2, -3, -3},
        {-2,  0,  1, -1, -3,  0,  0, -2,  8, -3, -3, -1, -2, -1, -2, -1, -2, -2,  2, -3},
        {-1, -3, -3, -3, -1, -3, -3, -4, -3,  4,  2, -3,  1,  0, -3, -2, -1, -3, -1,  3},
        {-1, -2, -3, -4, -1, -2, -3, -4, -3,  2,  4, -2,  2,  0, -3, -2, -1, -2, -1,  1},
        {-1,  2,  0, -1, -3,  1,  1, -2, -1, -3, -2,  5, -1, -3, -1,  0, -1, -3, -2, -2},
        {-1, -1, -2, -3, -1,  0, -2, -3, -2,  1,  2, -1,  5,  0, -2, -1, -1, -1, -1,  1},
        {-2, -3, -3, -3, -2, -3, -3, -3, -1,  0,  0, -3,  0,  6, -4, -2, -2,  1,  3, -1},
        {-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4,  7, -1, -1, -4, -3, -2},
        { 1, -1,  1,  0, -1,  0,  0,  0, -1, -2, -2,  0, -1, -2, -1,  4,  1, -3, -2, -2},
        { 0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1,  1,  5, -2, -2,  0},
        {-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1,  1, -4, -3, -2, 11,  2, -3},
        {-2, -2, -2, -3, -2, -1, -2, -3,  2, -1, -1, -2, -1,  3, -3, -2, -2,  2,  7, -1},
        { 0, -3, -3, -3, -1, -2, -2, -3, -3,  3,  1, -2,  1, -1, -2, -2,  0, -3, -1,  4}
    };
    int x = blosum_indexes(c1);
    int y = blosum_indexes(c2);

    if(x == -1 || y == -1) return 0;
    else return matrix[x][y];
}

string Filter::getName(){
    return name;
}

void Filter::setName(string name){
    this->name = name;
}

string Filter::getAlphabet(){
    return alphabet;
}

void Filter::setAlphabet(string alp){
    this->alphabet = alp;
}

int Filter::getType(){
    return type;
}

void Filter::setType(int type){
    this->type = type;
}

string Filter::getRefSeq(){
    return refSeq;
}

void Filter::setRefSeq(string refSeq){
    this->refSeq = refSeq;
}

string Filter::getTaxon(){
    return taxon;
}

void Filter::setTaxon(string tax){
    this->taxon = tax;
}

float Filter::getMinOcc(){
    return minOcc;
}

void Filter::setMinOcc(float occ){
    this->minOcc = occ;
}

float Filter::getMaxId(){
    return maxId;
}

void Filter::setMaxId(float id){
    this->maxId = id;
}

float Filter::getMinId(){
    return minId;
}

void Filter::setMinId(float id){
    this->minId = id;
}

string Filter::getConsPDB(){
    return this->cons_pdb;
}

void Filter::setConsPDB(string pdb){
    this->cons_pdb = pdb;
}

float Filter::getConsMin(){
    return this->cons_min;
}

void Filter::setConsMin(float value){
    this->cons_min = value;
}

/*
int Filter::getConsRefseq(){
    return this->cons_refseq;
}

string Filter::getStrConsRefseq(){
    return this->sequencenames[cons_refseq];
}

void Filter::setConsRefseq(int seq){
    this->cons_refseq = seq;
}

void Filter::setConsRefseq(string seq){
    unsigned int i = 0;

    for(i = 0; i < sequencenames.size(); i++){
        if(seq == sequencenames[i]) break;
    }

    this->cons_refseq = i;
}
*/

string Filter::getCorrPDB(){
    return this->corr_pdb;
}

void Filter::setCorrPDB(string pdb){
    this->corr_pdb = pdb;
}

int Filter::getCorrMinScore(){
    return this->corr_min_score;
}

void Filter::setCorrMinScore(int value){
    this->corr_min_score = value;
}

float Filter::getCorrMinssFraction(){
    return this->corr_minssfraction;
}

void Filter::setCorrMinssFraction(float value){
    this->corr_minssfraction = value;
}

float Filter::getCorrMinDelta(){
    return this->corr_min_delta;
}

void Filter::setCorrMinDelta(float value){
    this->corr_min_delta = value;
}

void Filter::setCorrRefSeq(string seq){
    unsigned int i = 0;

    for(i = 0; i < sequencenames.size(); i++){
        if(sequencenames[i] == seq) break;
    }

    this->corr_refseq = i;
}

void Filter::setConsPDBPath(string path){
    this->conservedPDBpath = path;
}

string Filter::getConsPDBPath(){
    return this->conservedPDBpath;
}

void Filter::setCommPDBPath(string path){
    this->commPDBPath = path;
}

string Filter::getCommPDBPath(){
    return this->commPDBPath;
}

bool Filter::addSequences(vector<string> names, vector<string> seqs){
    if(names.size() != seqs.size()) return false;

    sequencenames = names;
    sequences = seqs;

    return true;
}

void Filter::addSequences(string protName, string protSequence){
    sequencenames.push_back(protName);
    sequences.push_back(protSequence);
}

vector<string> Filter::getSequences(){
    return this->sequences;
}

vector<string> Filter::getSequenceNames(){
    return this->sequencenames;
}

int Filter::getSequencesCount(){
    return sequencenames.size();
}

string Filter::getSequence(int i){
    return this->sequences[i];
}

string Filter::getSequenceName(int i){
    return this->sequencenames[i];
}

void Filter::addRefSeq(string seq){
    this->refseqs.push_back(seq);
}

string Filter::getRefSeq(int i){
    return refseqs[i];
}

void Filter::clearRefSeq(){
    this->refseqs.clear();
}

unsigned int Filter::getRefSeqsSize(){
    return refseqs.size();
}

void Filter::printRefSeqs(){
    for(unsigned int i = 0; i < refseqs.size(); i++){
        printf("%s\n",refseqs[i].c_str());
    }
}

void Filter::CalculateFrequencies(){
    long double partialresult;
    unsigned int c1,c2;

    frequencies.clear();

    // FREQUENCE MATRIX INITIALIZATION
    for(c1=0;c1<=sequences[0].size();c1++){ // total positions: sequencesize + 1 (positions + totals)
        frequencies.push_back( vector<int>(21) );
        for(c2=0; c2<=20; c2++)
            frequencies[c1].push_back(0);
    }

    // INSERT AMINO ACID FREQUENCES ON EACH POSITION OF THE ALIGNMENT
    for(c1=0;c1<=sequences.size()-1;c1++){
        for(c2=0;c2<=sequences[0].size()-1;c2++){
            frequencies[c2][freqmatrixposition(sequences[c1][c2])]++;
            frequencies[sequences[0].size()][freqmatrixposition(sequences[c1][c2])]++;
        }
    }

    for (c1=1;c1<=20;c1++){
        partialresult=(long double)(frequencies[sequences[0].size()][c1]);
        partialresult=partialresult/((long double)((sequences.size()*sequences[0].size())-frequencies[sequences[0].size()][0]));
        meanf[c1]=partialresult;
    }
}

string Filter::getAAList(string alphabet){
    if(alphabet == "T2"){
        return "PY";
    }else if(alphabet == "T5"){
        return "IFKGC";
    }else if(alphabet == "T6"){
        return "IFKDGT";
    }else if(alphabet == "3IMG"){
        return "IGD";
    }else if(alphabet == "5IMG"){
        return "GCEMF";
    }else if(alphabet == "11IMG"){
        return "AFCGSWYPDNH";
    }else if(alphabet == "Murphy15"){
        return "LCAGSTPFWEDNQKH";
    }else if(alphabet == "Murphy10"){
        return "LCAGSPFEKH";
    }else if(alphabet == "Murphy8"){
        return "LASPFEKH";
    }else if(alphabet == "Murphy4"){
        return "LAFE";
    }else if(alphabet == "Murphy2"){
        return "PE";
    }else if(alphabet == "Wang5"){
        return "IAGEK";
    }else if(alphabet == "Wang5v"){
        return "ILAEK";
    }else if(alphabet == "Wang3"){
        return "IAE";
    }else if(alphabet == "Wang2"){
        return "IA";
    }else if(alphabet == "Li10"){
        return "CYLVGPSNEK";
    }else if(alphabet == "Li5"){
        return "YIGSN";
    }else if(alphabet == "Li4"){
        return "YISE";
    }else if(alphabet == "Li3"){
        return "ISE";
    }

    return "ACDEFGHIKLMNPQRSTVWY";
}

//Carrijo

void Filter::dGCalculation(float alpha, float beta){
    vector<vector<char> > aa_types;
    vector<string> newsequences;

    QProgressDialog progress("Parsing sequences...(1/3)", "Abort", 0,sequences.size()+sequences[0].size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    //Adapta caracteres minusculos e gaps
    for(unsigned int i = 0; i < sequences.size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        string newseq = "";
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            char aa = sequences[i][j];
            if(aa == '.') newseq += '-';
            else newseq += toupper(aa);
        }
        newsequences.push_back(newseq);
    }

    //Obtem os tipos de aminoacidos presentes em cada posicao.
    set<char> types;
    for(unsigned int i = 0; i < newsequences[0].size(); i++){
        progress.setValue(i+sequences.size());
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        set<char> set_aa_types;
        for(unsigned int j = 0; j < newsequences.size(); j++){
            set_aa_types.insert(newsequences[j][i]);
            types.insert(newsequences[j][i]);
        }
        //printf("%s\n",newsequences[i].c_str());
        vector<char> vec_aa_types(set_aa_types.begin(),set_aa_types.end());
        aa_types.push_back(vec_aa_types);
        //typesCount.push_back(vec_aa_types.size());
    }

    progress.setLabelText("Calculating entropy...(2/3)");
    progress.setMaximum(aa_types.size()+newsequences[0].size());
    progress.setValue(0);

    //GET P
    float lambda_t = 1/log2(types.size());
    vector<float> entropies;
    string aalist = this->getAAList(this->alphabet);
    vector<float> max_entropy;
    for(unsigned int i = 0; i < aa_types.size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        map<char,float> pmap = {{'A',0.0},{'C',0.0},{'D',0.0},{'E',0.0},{'F',0.0},{'G',0.0},{'H',0.0},{'I',0.0},{'K',0.0},{'L',0.0},{'M',0.0},{'N',0.0},{'P',0.0},{'Q',0.0},{'R',0.0},{'S',0.0},{'T',0.0},{'V',0.0},{'W',0.0},{'Y',0.0},{'-',0.0}};
        bool gap = false;
        vector<char> aas = aa_types[i];
        for(unsigned int j = 0; j < aas.size(); j++){
            char aa = aas[j];
            float p = 0;
            for(unsigned int k = 0; k < newsequences.size(); k++){
                string seq = newsequences[k];
                if(seq[i] == aa){
                    p+= weights[k];
                    if(aa == '-') gap = true;
                }
            }
            pmap[aa] = p;
        }

        float entropy = 0;
        for(auto const& ent1 : pmap){
            float p = ent1.second;
            if(p > 0) entropy += (p*log2(p))*(-1);
        }
        entropies.push_back(lambda_t*entropy);

        float pgap = 0;
        if(gap)
            pgap = pmap['-'];

        //Aqui
        map<char,float> p;
        for(unsigned int i = 0; i < aalist.size(); i++){
            char t = aalist[i];
            p[t] = (1-pgap)/aalist.size();
        }

        entropy = 0;
        for(auto const& ent1 : p){
            entropy += (ent1.second*log2(ent1.second))*(-1);
        }
        float val = lambda_t*entropy;
        if(isnan(val))
            max_entropy.push_back(0);
        else
            max_entropy.push_back(lambda_t*entropy);
    }

    //get_corrected_entropy
    vector<float> corrected_entropy;
    float biggestMaxEntropy = *max_element(max_entropy.begin(),max_entropy.end());

    for(unsigned int i = 0; i < newsequences[0].size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        float delta_entropy = entropies[i]-max_entropy[i];
        corrected_entropy.push_back(delta_entropy + biggestMaxEntropy);
    }

    progress.setLabelText("Calculating sthereochemistry variety...(3/3)");
    progress.setMaximum(aalist.size()+aa_types.size()+newsequences[0].size());
    progress.setValue(0);

    //#Calcula diversidade estereoquimica para cada posicao.
    vector<float> sthereochemistry;
    map<char,vector<int> > matrix;
     set<int> m;
    for(unsigned int i = 0; i < aalist.size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        char aa1 = aalist[i];
        vector<int> temp;
        matrix[aa1] = temp;
       for(unsigned int j = 0; j < aalist.size(); j++){
           char aa2 = aalist[j];
           matrix[aa1].push_back(BLOSUM62(aa1,aa2));
       }
       if(aa1 != '-' && aa1 != 'X'){
           vector<int> matrixaa = matrix[aa1];
           for(unsigned int j = 0; j < matrixaa.size(); j++){
               m.insert(matrixaa[j]);
           }
       }
    }

    int m_max = *max_element(m.begin(),m.end());
    int m_min = *min_element(m.begin(),m.end());
    float lambda_r = (float)1/sqrt(20*pow((float)m_max-(float)m_min,2));

    for(unsigned int i = 0; i < aa_types.size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        vector<char> column = aa_types[i];
        vector<int> sum_x {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        vector<vector<int> > X;
        for(unsigned int j = 0; j < column.size(); j++){
            char aa = column[j];
            if(aa != '-' && aa != 'X'){
                vector<int> x = matrix[aa];
                X.push_back(x);
                std::transform (sum_x.begin(), sum_x.end(), x.begin(), sum_x.begin(), std::plus<int>());
            }
        }
        vector<float> mean_x;
        int sum_dist = 0;
        for(unsigned int j = 0; j < sum_x.size(); j++){
            mean_x.push_back((float)sum_x[j]/(float)column.size());
        }
        for(unsigned int j = 0; j < X.size(); j++){
            vector<float> dist_vector;
            for(unsigned int k = 0; k < mean_x.size(); k++)
                dist_vector.push_back(mean_x[k] - X[j][k]);
            int sqr_sum = 0;
            for(unsigned int k = 0; k < dist_vector.size(); k++){
                float d = dist_vector[k];
                sqr_sum += d*d;
            }
            sum_dist = sqrt(sqr_sum);
        }
        float mean_dist = (float)sum_dist/(float)column.size();
        sthereochemistry.push_back(lambda_r*mean_dist);
    }

    for(unsigned int i = 0; i < newsequences[0].size(); i++){
        progress.setValue(i);
        QApplication::processEvents();
        if(progress.wasCanceled()) return;

        dG.push_back((pow(1-corrected_entropy[i],alpha))*(pow(1-sthereochemistry[i],beta)));
    }

    progress.close();
}


//Lockless
void Filter::dGCalculation(){
    unsigned int c1,c2;
    long double partialresult;
    float max = -99999;
    float min = 99999;

    dG.clear();
    for(c1=0;c1<=sequences[0].size()-1;c1++){
        partialresult=0;
        for(c2=1; c2<=20; c2++){
            partialresult+=pow(lnbdf(sequences.size(),frequencies[c1][c2],meanf[c2])-lnbdf(sequences.size(),(int)(((long double)frequencies[sequences[0].size()][c2])/(long double)sequences[0].size()),meanf[c2]),2);
        }

        partialresult = sqrt(partialresult);

        if(partialresult > max) max = partialresult;
        if(partialresult < min) min = partialresult;

        dG.push_back(partialresult);
    }

    //NORMALIZA
    for(unsigned int i = 0; i < dG.size(); i++){
        float value = (dG[i] - min)/(max-min);
        dG[i] = value;
    }


}


void Filter::dGWrite(){
    consDG.clear();
    for(unsigned int i = 0; i<sequences[0].size();i++){//for(unsigned int i = 0; i<sequences[0].size()-1;i++){
        consDG.push_back((float)dG[i]);
        //consDG.push_back(float(dG[i]));
        //printf("%d - %f\n",i,consDG[i]);
    }
}

void Filter::FreqWrite(){
    consfreqPerc.clear();
    consvfreq.clear();
    for (unsigned int i=0;i<=sequences[0].size();i++){//-1 para não incluir o ALL
        vector<int> freqs;
        for (int j=0;j<=20;j++){
            freqs.push_back(frequencies[i][j]);
        }
        consvfreq.push_back(freqs);
    }

     for (unsigned int i=0;i<=sequences[0].size()-1;i++){
         vector<float> freqpercs;
         for (unsigned int j=1;j<=20;j++){
             if(frequencies[i][j]!=sequences.size()){
                freqpercs.push_back(100.0*(float)frequencies[i][j]/((float)sequences.size()));
             }else freqpercs.push_back(100.00);
         }
         consfreqPerc.push_back(freqpercs);
     }
}

vector<float> Filter::ShannonEntropy(int repetitions, int cores){
    vector<int> populatedpos;
    vector<float> outputVec;
    vector<vector<int> > subsetTemp;
    vector<float> blank;
    double partialsum=0;
    int tamanhoSeq = 0;
    int currentProgress = 0;
    int currentsize = sequences.size();

    int size = frequencies[0].size() + frequencies.size() + frequencies.size() + sequences.size() + subsetfrequencies.size() + 5;
    QProgressDialog progress("Pré-calculating...", "Abort", 0,size);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(unsigned int i = 0; i < frequencies[0].size(); i++){
        currentProgress++;
        progress.setValue(currentProgress);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        tamanhoSeq += frequencies[0][i];
    }

    //Filtro por GAP
    for(unsigned int i = 0; i < frequencies.size(); i++){
        currentProgress++;
        progress.setValue(currentProgress);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        populatedpos.push_back(i);
    }

    //Primeira Iteração
    for(unsigned int k = 0; k < populatedpos.size() -1; k++){
        currentProgress++;
        progress.setValue(currentProgress);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        for(unsigned int l = 0; l <= 20; l++){
            double subsetfreq = (double)frequencies[k][l]/(double)currentsize;
            if(subsetfreq > 0)
                partialsum += (subsetfreq* log(subsetfreq));
        }
    }
    partialsum = partialsum * -1;
    outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()))));

    //Cria sortOrder
    SortOrder.clear();
    for(unsigned int i = 0; i < sequences.size()-1; i++){
        currentProgress++;
        progress.setValue(currentProgress);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        SortOrder.push_back(i);
    }

    //Populaciona subsetlocal
    for(unsigned int i = 0; i < subsetfrequencies.size(); i++){
        vector<int> temp;
        currentProgress++;
        progress.setValue(currentProgress);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        for(unsigned int j = 0; j < subsetfrequencies[0].size(); j++){
            temp.push_back(0);
        }
        subsetTemp.push_back(temp);
    }

    progress.setLabelText("Calculating...");
    progress.setMaximum(110);
    progress.setMinimum(0);

    for(unsigned int i = 1; i < 100; i++){
        progress.setValue(i);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;

        partialsum = 0;
        currentsize=sequences.size()-((i*sequences.size())/(100));

        if (currentsize<=0) break;

        omp_set_num_threads(cores);
        #pragma omp parallel for firstprivate(subsetTemp) reduction (+:partialsum)
        //Teste sem filtro
        for(int j = 0; j < repetitions; j++){
            random_shuffle(SortOrder.begin(),SortOrder.end());
            //Calcula frequência do subalinhamento
            for (unsigned int i1 = 0; i1 < subsetTemp.size(); i1++)
                for(unsigned int j1 = 0; j1 < subsetTemp[0].size(); j1++)
                    subsetTemp[i1][j1]=0;

            for(int i1 = 0; i1 < currentsize; i1++){
                for(unsigned int j1 = 0; j1 < sequences[0].size(); j1++){
                    subsetTemp[j1][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                    subsetTemp[sequences[0].size()][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                }
            }

            for(unsigned int k = 0; k < populatedpos.size() - 1; k++){
                for(unsigned int l = 0; l <= 20; l++){
                    double subsetfreq = (double)subsetTemp[k][l]/(double)currentsize;
                    if(subsetfreq > 0){
                        if(subsetfreq* log(subsetfreq) < 0) partialsum += (subsetfreq* log(subsetfreq) * -1);
                        else partialsum += (subsetfreq* log(subsetfreq));
                    }
                }
            }

        }
        outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()*repetitions))));
    }

    minssData.clear();
    for(unsigned int i = 0; i < outputVec.size(); i++){
        progress.setValue(i+100);
        QApplication::processEvents();

        if(progress.wasCanceled()) return blank;
        //printf("%f\n",outputVec[i]);
        this->minssData.push_back(outputVec.at(i));
    }

    progress.close();

    return outputVec;
}

void Filter::alignment2UpperCase(){
    for(unsigned int i = 0; i < sequences.size(); i++){
        string sequenceI = sequences[i];
        std::transform(sequenceI.begin(),sequenceI.end(),sequenceI.begin(),::toupper);
        sequences[i] = sequenceI;
        //printf("%s - %s\n",sequenceI.c_str(),sequences[i].c_str());
    }
}

void Filter::SubAlignmentIndices(char aa, int pos){
    unsigned int c1;

    if(subalignmentseqs.size()>0) subalignmentseqs.clear();

    for (c1=0;c1<=sequences.size()-1;c1++)
        if(sequences[c1][pos]==aa)
            subalignmentseqs.push_back(c1);
}

vector<int> Filter::subalignmentIndicesW(char aa, int pos){
    vector<int> indices;

    for(unsigned int i = 0; i < sequences.size(); i++)
        if(sequences[i][pos] == aa)
            indices.push_back(i);

    return indices;
}

int Filter::Singlepvalue(char aa1, int pos1, char aa2, int pos2){
    unsigned int aa2pos2count=0;
    unsigned int c2;
    if(pos1==pos2) return 0;
    SubAlignmentIndices(aa1,pos1);

    if (subalignmentseqs.size()>0){
        for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
            if (sequences[subalignmentseqs[c2]][pos2]==aa2) aa2pos2count++;

        if ((((float)aa2pos2count)/((float)subalignmentseqs.size()))!=((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size()))){
            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())))
                return(-cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())),true));
            else
                return(cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())),false));
        }else return 0;
    }else return 0;
}

void Filter::SympvalueCalculation(int minlogp, float minssfraction, float mindeltafreq){
    int aa1,aa2,aa2pos2count,aa1pos1count;
    unsigned int c2,pos1,pos2;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();
    //FILE *temp;
    //temp = fopen("temppvalues.txt","w");

    QProgressDialog progress("Calculating correlations...(1/6)", "Abort", 0,sequences[0].size()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences[0].size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()){
            corrGraph.clear();
            return;
        }

        for (aa1=1;aa1<=20;aa1++){
            if(frequencies[pos1][aa1]>minssfraction*((float)sequences.size()))
                for(pos2=pos1+1;pos2<=sequences[0].size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        if(frequencies[pos2][aa2]>minssfraction*((float)sequences.size())){
                            QApplication::processEvents();

                            if(progress.wasCanceled()){
                                corrGraph.clear();
                                return;
                            }
                            SubAlignmentIndices(num2aa(aa1),pos1);
                            aa2pos2count=0;

                            for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                if (sequences[subalignmentseqs[c2]][pos2]==num2aa(aa2)) aa2pos2count++;

                            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][aa2])/(float(sequences.size()))){
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++){
                                        if (sequences[subalignmentseqs[c2]][pos1]==num2aa(aa1)) aa1pos1count++;
                                    }

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }else{
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())<(mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                        if (sequences[subalignmentseqs[c2]][pos1]==num2aa(aa1)) aa1pos1count++;

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }
                            if(mindeltafreqok){
                                pvalue1=Singlepvalue(num2aa(aa1),pos1,num2aa(aa2),pos2);
                                pvalue2=Singlepvalue(num2aa(aa2),pos2,num2aa(aa1),pos1);
                                //fprintf(temp,"%c%d %c%d \n",num2aa(aa1),pos1,num2aa(aa2),pos2);
                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    //printf ("%c%d %c%d %i\n",num2aa(aa1),pos1+1,num2aa(aa2),pos2+1,(pvalue1+pvalue2)/2);
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    //printf("%s %s %d\n",residue1.c_str(),residue2.c_str(),edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }

    progress.close();
}

void Filter::henikoffpvalueCalculation(int minlogp, float minssfraction, float mindeltafreq){
    int aa1,aa2;
    unsigned int c2,pos1,pos2;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();

    QProgressDialog progress("Calculating correlations...(1/6)", "Abort", 0,sequences[0].size()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences[0].size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()){
            corrGraph.clear();
            return;
        }

        for (aa1=1;aa1<=20;aa1++){
            vector<int> subalignmentseqs1 = subalignmentIndicesW(num2aa(aa1),pos1);
            float f0a1 = 0.0;

            for(unsigned int i = 0; i < subalignmentseqs1.size(); i++){
                f0a1 += weights[subalignmentseqs1[i]];
            }

            if(f0a1>minssfraction)
                for(pos2=pos1+1;pos2<=sequences[0].size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        QApplication::processEvents();

                        if(progress.wasCanceled()){
                            corrGraph.clear();
                            return;
                        }
                        vector<int> subalignmentseqs2 = subalignmentIndicesW(num2aa(aa2),pos2);
                        float f0a2 = 0.0;

                        for(unsigned int i = 0; i < subalignmentseqs2.size(); i++){
                            f0a2 += weights[subalignmentseqs2[i]];
                        }

                        if(f0a2>minssfraction){
                            float f1a2 = 0.0;

                            for(c2=0;c2<=subalignmentseqs1.size()-1;c2++)
                                if (sequences[subalignmentseqs1[c2]][pos2]==num2aa(aa2)) f1a2 += weights[subalignmentseqs1[c2]];

                            f1a2 = f1a2/(float)f0a1;

                            float f1a1 = 0.0;
                            if(f1a2 > f0a2){
                                if(f1a2 > (1.0-mindeltafreq)){
                                    for(c2=0;c2<=subalignmentseqs2.size()-1;c2++){
                                        if (sequences[subalignmentseqs2[c2]][pos1]==num2aa(aa1)) f1a1 += weights[subalignmentseqs2[c2]];
                                    }

                                    f1a1 = f1a1/(float)f0a2;

                                    if(f1a1 > (1.0-mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }else{
                                if(f1a2<(mindeltafreq)){
                                    for(c2=0;c2<=subalignmentseqs2.size()-1;c2++){
                                        if (sequences[subalignmentseqs2[c2]][pos1]==num2aa(aa1)) f1a1 += weights[subalignmentseqs2[c2]];
                                    }

                                    f1a1 = f1a1/(float)f0a2;

                                    if(f1a1<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }

                            if(mindeltafreqok){
                                //P-Value1
                                if(f1a2 > f0a2){
                                    pvalue1 = -cbd(f0a1*sequences.size(),f1a2*f0a1*sequences.size(),f0a2,true);
                                }else if(f1a2 < f0a2){
                                    pvalue1 = cbd(f0a1*sequences.size(),f1a2*f0a1*sequences.size(),f0a2,false);
                                }else{
                                    pvalue1 = 0;
                                }
                                //P-Value 2
                                if(f1a1 > f0a1){
                                    pvalue2 = -cbd(f0a2*sequences.size(),f1a1*f0a2*sequences.size(),f0a1,true);
                                }else if(f1a1 < f0a1){
                                    pvalue2 = cbd(f0a2*sequences.size(),f1a1*f0a2*sequences.size(),f0a1,false);
                                }else{
                                    pvalue2 = 0;
                                }

                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    //printf ("%c%d %c%d %i\n",num2aa(aa1),pos1+1,num2aa(aa2),pos2+1,(pvalue1+pvalue2)/2);
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    //printf("%s %s %d\n",residue1.c_str(),residue2.c_str(),edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }

    progress.close();
}

vector<string> Filter::filterCorrGraph(vector<tuple<string, string> > tup, int refseq){
    //Refseq must start withs 1
    vector<string> removed;

    //printf("%d\n\n",refseq);

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        string res1 = get<0>(corrGraph[i]);
        string res2 = get<1>(corrGraph[i]);
        char aa1 = res1[0];
        char aa2 = res2[0];
        int pos1 = this->AlignNumbering2Sequence(refseq,atoi(res1.substr(1).c_str()));
        int pos2 = this->AlignNumbering2Sequence(refseq,atoi(res2.substr(1).c_str()));
        string newRes1 = aa1 + to_string(pos1);
        string newRes2 = aa2 + to_string(pos2);

        //printf("%s - %s\n",newRes1.c_str(),newRes2.c_str());

        for(unsigned int j = 0; j < tup.size(); j++){
            string tupRes1 = get<0>(tup[j]);
            string tupRes2 = get<1>(tup[j]);

            if(newRes1 == tupRes1 && tupRes2 == newRes2){
                removed.push_back(res1 + "-" + res2);
                corrGraph.erase(corrGraph.begin() + i);
                i--;
                break;
            }
        }
    }

    return removed;
}

void Filter::CalculateReferenceVector(int seqnumber){
    unsigned int c1;
    //QMessageBox::information(NULL,"ok",QString::number(seqnumber));
    referencesequence=seqnumber;
    if(referencevector.size()>0) referencevector.clear();
    for(c1=0;c1<=sequences[0].size()-1;c1++)
        if(isaax(sequences[seqnumber-1][c1])) referencevector.push_back(c1);
}

unsigned int Filter::AlignNumbering2Sequence(int seqnumber, int position){
    //printf("PARS %d %d\n",seqnumber,position);
    this->CalculateReferenceVector(seqnumber);
    for(unsigned int c1=0;c1<=referencevector.size()-1;c1++)
        if (referencevector[c1]==position) return(c1+1);
    return 0;
}

unsigned int Filter::sequencenumbering2alignment(int seqnumber, int position){
    //printf("SEQNUMB2ALIGN: %s\n",sequencenames[seqnumber-1].c_str());
    vector<string> temp = split(sequencenames[seqnumber-1],'/');
    int offset = atoi(split(temp[1],'-')[0].c_str());
    int newpos = position-offset;
    int countGAP = 0;
    int countAA = 0;

    for(unsigned int i = 0; i < sequences[0].size(); i++){
        if(sequences[seqnumber-1][i] == '-' || sequences[seqnumber-1][i] == '.')
            countGAP++;
        else countAA++;
        if(countAA == newpos)
            return newpos+countGAP+1;
    }
    return -1;
}

void Filter::clearCommunity(){
    comunidades.clear();
}

void Filter::resetCommunities(){
    if (Communities.size()>0){
        for (unsigned int c1=0;c1<=Communities.size()-1;c1++){
            Communities[c1].pos.clear();
            Communities[c1].aa.clear();
        }
        Communities.clear();
    }

    tempcommunity.pos.clear();
    tempcommunity.aa.clear();
}

tuple<string,string,int> Filter::getCorrelationEdge(int i){
    return corrGraph[i];
}

unsigned int Filter::getCorrelationGraphSize(){
    return corrGraph.size();
}

void Filter::addCommunity(vector<string> comm){
    comunidades.push_back(comm);
}

void Filter::addToCommunity(string res, int i){
    if(i < comunidades.size())
        comunidades[i].push_back(res);
    else
        printf("error adding %s to community %d\n",res.c_str(),i);
}

void Filter::getCommunitiesFromRAM(){
    QProgressDialog progress("Getting communities...(3/6)", "Abort", 0,comunidades.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    this->resetCommunities();

    for(unsigned int i = 0; i < comunidades.size(); i++){
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        progress.setValue(i);
        if(progress.wasCanceled()) return;
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            string node = comunidades[i][j];

            tempcommunity.aa.push_back(node[0]);

            string tempPos = node.substr(1);

            tempcommunity.pos.push_back(atoi(tempPos.c_str())-1);
        }

        if(comunidades[i].size() > 0)
            Communities.push_back(tempcommunity);

        tempcommunity.aa.clear();
        tempcommunity.pos.clear();
    }

    progress.close();
}

int Filter::SubAlignmentFrequency(char aa, int pos){
    unsigned int c1;
    unsigned int result = 0;

    if(subalignmentseqs.size()==0) return -1;

    for(c1=0;c1<=subalignmentseqs.size()-1;c1++)
        if(sequences[subalignmentseqs[c1]][pos]==aa) result++;

    return result;
}

void Filter::SelfCorrelationMatrixCalculation(const std::vector<char> &aalist, const std::vector<int> &poslist){
    unsigned int i, j;

    if(selfcorrelationmatrix.size()!=0){
        for (i=0;i<=selfcorrelationmatrix.size()-1;i++){
            selfcorrelationmatrix[i].clear();
        }
        selfcorrelationmatrix.clear();
    }

    for (i=0;i<=aalist.size()-1;i++){
        selfcorrelationmatrix.push_back( vector<float> (aalist.size())) ;
        //for (j=0;j<=aalist.size()-1;j++) selfcorrelationmatrix[i].push_back(0);
    }

    for (j=0;j<=aalist.size()-1;j++){
        SubAlignmentIndices(aalist[j],poslist[j]);

        for (i=0;i<=aalist.size()-1;i++){
            //printf("%d\n",subalignmentseqs.size());
            if(i==j) selfcorrelationmatrix[i][j]=-1;
            else{
                selfcorrelationmatrix[i][j]=((float)SubAlignmentFrequency(aalist[i],poslist[i]))/((float)subalignmentseqs.size());
                //printf("%f / %d = %f \n",(float)SubAlignmentFrequency(aalist[i],poslist[i]),subalignmentseqs.size(),selfcorrelationmatrix[i][j]);
            }
        }
    }
}

void Filter::Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset){
    int nclusters = comunidades.size();
    vector<char> aalist;
    vector<int> poslist;
    this->communityX.clear();
    this->communityXAll.clear();
    this->residuesComm.clear();

    QProgressDialog progress("Calculating tables...(4/6)", "Abort", 0,nclusters);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(int i = 0; i < nclusters; i++){
        progress.setValue(i);
        if(progress.wasCanceled()) return;
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        aalist.clear();
        poslist.clear();
        vector<float> clusterXAll;

        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            string temp = comunidades[i][j];
            aalist.push_back(temp[0]);
            poslist.push_back(atoi(temp.substr(1).c_str())-1);
        }

        if(comunidades[i].size() > 1){
            SelfCorrelationMatrixCalculation(aalist,poslist);

            //ESCRITA SCM2HTML*RAM
            vector<string> clustersResidues;
            for(unsigned int j = 0; j < aalist.size(); j++){
                string residue;
                if(!renumber){
                    residue = aalist[j] + QString::number(poslist[j]+1).toStdString();
                }else if (AlignNumbering2Sequence(seqnumber,poslist[j])!=0){
                    residue = aalist[j] + QString::number(AlignNumbering2Sequence(seqnumber,poslist[j])+offset).toStdString();
                }else{
                    //residue = string(aalist[j]).c_str() + "X(";// + QString::number(poslist[j] + 1).toStdString() + ")";
                    char test[50];
                    sprintf(test,"%cX(%d)",aalist[j],poslist[j] + 1);
                    residue = test;
                }
                clustersResidues.push_back(residue);
            }
            residuesComm.push_back(clustersResidues);

            for(unsigned int j = 0; j < aalist.size(); j++){
                clusterXAll.push_back((float)100*frequencies[poslist[j]][freqmatrixposition(aalist[j])]/((float)sequences.size()));
            }

            this->communityX.push_back(selfcorrelationmatrix);
            this->communityXAll.push_back(clusterXAll);
        }
    }

    progress.close();
}

int Filter::getEdge(string v1, string v2){
    for(unsigned int i = 0; i < corrGraph.size(); i++){
        string gv1 = get<0>(corrGraph[i]);
        string gv2 = get<1>(corrGraph[i]);
        if((v1==gv1 && v2 == gv2) || (v1==gv2 && v2==gv1)){
            return get<2>(corrGraph[i]);
        }
    }
    return 0;
}

void Filter::DeltaCommunitiesCalculation(){
    QProgressDialog progress("Calculating Deltas...(5/6)", "Abort", 0,this->getNumOfUtilComms()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    Deltas.clear();

    for(unsigned int i = 0; i < this->comunidades.size(); i++){
        vector<float> vec;
        for(unsigned int j = 0; j < this->comunidades.size(); j++){
            vec.push_back(0);
        }
        Deltas.push_back(vec);
    }

    if(comunidades.size() > 0){
        for(unsigned int i = 0; i < this->comunidades.size()-1; i++){
            progress.setValue(i);
            if(progress.wasCanceled()) return;
            QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
            for(unsigned int j = i+1; j < this->comunidades.size(); j++){
                vector<string> commA = comunidades[i];
                vector<string> commB = comunidades[j];
                float N = commA.size();
                float M = commB.size();
                float sumW = 0;

                for(unsigned int k = 0; k < commA.size(); k++){
                    for(unsigned int l = 0; l < commB.size(); l++){
                        string an = commA[k];
                        string bm = commB[l];
                        int pvalue = getEdge(an,bm);
                        if(pvalue != 0){
                            sumW += pvalue;
                        }
                    }
                }

                Deltas[i][j] = sumW/(N*M);
            }
        }
    }

    printf("OK\n");
}

/*
void Filter::DeltaCommunitiesCalculation(){
    float Delta;
    int c1,c2,c3,c4;
    QProgressDialog progress("Calculating Deltas...(5/6)", "Abort", 0,Communities.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();


    if(Deltas.size()>0){
        for (c1=0;c1<=Deltas.size()-1;c1++)
            Deltas[c1].clear();
        Deltas.clear();
    }

    for(c1=0;c1<=Communities.size()-1;c1++){
        Deltas.push_back( vector<float>(Communities.size()) );
        for (c2=0;c2<=Communities.size()-1;c2++)
            Deltas[c1].push_back(0);
    }

    if(Communities.size()>0){
        for(c1=0;c1<=Communities.size()-1;c1++){
            progress.setValue(c1);
            if(progress.wasCanceled()) return;
            QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
            for(c2=0;c2<=Communities.size()-1;c2++){
                Delta=0;
                for(c3=0;c3<=Communities[c1].aa.size()-1;c3++){
                    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
                    for(c4=0;c4<=Communities[c2].aa.size()-1;c4++){
                        Delta+=(float)Singlepvalue(Communities[c1].aa[c3],Communities[c1].pos[c3],Communities[c2].aa[c4],Communities[c2].pos[c4]);
                    }
                }
                Deltas[c1][c2]=((float)Delta)/((float)(Communities[c1].aa.size()*Communities[c2].aa.size()));
            }
        }
    }

    progress.close();
}
*/
void Filter::pMatrix2HTMLRAM(bool renumber, int seqnumber){
    this->communityXps.clear();
    this->residuesCommPs.clear();
    QProgressDialog progress("Generating p-values matrixes..(6/6)", "Abort", 0,Communities.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(unsigned int c1 = 0; c1 < Communities.size(); c1++){
        progress.setValue(c1);
        if(progress.wasCanceled()) return;
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(Communities[c1].aa.size() > 1){

            vector<vector<int> > matrix = this->createBlankIntMatrix(Communities[c1].aa.size(),Communities[c1].aa.size(),-1);
            vector<string> clustersResidues;
            for(unsigned int j = 0; j < Communities[c1].aa.size(); j++){
                QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
                string residue;
                if(!renumber) residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                else if(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j]) != 0) residue = Communities[c1].aa[j] + QString::number(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j])).toStdString();
                else residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                clustersResidues.push_back(residue);
            }
            residuesCommPs.push_back(clustersResidues);

            for(unsigned int i = 0; i < Communities[c1].aa.size(); i++){
                QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
                for(unsigned int j = 0; j < Communities[c1].aa.size(); j++){
                    if(i != j){
                        matrix[i][j] = Singlepvalue(Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]);
                    }
                }
            }

            this->communityXps.push_back(matrix);
        }
    }

    progress.close();
}

unsigned int Filter::getNumOfUtilComms(){
    return this->communityX.size();
}

vector<tuple<int, float> > Filter::createCommuntitiesVector(int refseq){
    vector<tuple<int,float> > commvec;
    int nOfComms = this->getNumOfUtilComms();

    for(unsigned int i = 0; i < nOfComms; i++){
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            int commpos = atoi(comunidades[i][j].substr(1).c_str());
            tuple<int,float> tup;
            get<0>(tup) = commpos;
            get<1>(tup) = (float)(i+1)/(float)nOfComms;
            commvec.push_back(tup);
        }
    }

    return commvec;
}

void Filter::setSorOrder(vector<int> order){
    this->SortOrder = order;
}

vector<vector<int> > Filter::getSubsetFrequencies(){
    return this->subsetfrequencies;
}

void Filter::setSubsetFrequencies(vector<vector<int> > subset){
    this->subsetfrequencies = subset;
}

unsigned int Filter::getCommListSize(){
    return this->comunidades.size();
}

vector<int> Filter::getConsFreqRow(int i){
    return this->consvfreq[i];
}

unsigned int Filter::getConsFreqSize(){
    return this->consvfreq.size();
}

unsigned int Filter::getConsFreqPercSize(){
    return this->consfreqPerc.size();
}

vector<float> Filter::getConsFreqPercRow(int i){
    return this->consfreqPerc[i];
}

vector<string> Filter::getConsRes(float minCons){
    vector<char> conservedaa;
    vector<int> conservedpos;

    this->CalculateFrequencies();

    for(unsigned int i = 0; i < frequencies.size()-2; i++){
        for(unsigned int j = 1; j <= 20; j++){
            float freq = frequencies[i][j]/((float)sequences.size());
            //printf("freq=%f / minCons=%f\n",freq,minCons);
            if(freq >= minCons){
                conservedaa.push_back(num2aa(j));
                conservedpos.push_back(i+1);
            }
        }
    }

    vector<string> outVec;

    for(unsigned int i = 0; i < conservedaa.size(); i++){
        string res = conservedaa[i] + QString::number(conservedpos[i]).toStdString();
        outVec.push_back(res);
    }

    return outVec;
}

unsigned int Filter::getCorrGraphSize(){
    return this->corrGraph.size();
}

tuple<string,string,int> Filter::getCorrGraphTuple(int i){
    return this->corrGraph[i];
}

vector<string> Filter::getCommunitie(int i){
    return this->comunidades[i];
}

vector<string> Filter::getResiduesComm(int c){
    return this->residuesComm[c];
}

vector<string> Filter::getResiduesCommPs(int c){
    return this->residuesCommPs[c];
}

vector<float> Filter::getCommAll(int c){
    return this->communityXAll[c];
}

vector<float> Filter::getCommXRow(int c, int i){
    return this->communityX[c][i];
}

vector<int> Filter::getCommPsRow(int c, int i){
    return this->communityXps[c][i];
}

float Filter::PSA(int seqnumber, int communitynumber){
    unsigned int i,j;
    float sum=0;

    //QMessageBox::information(NULL,"a",QString::number(sequences.size()));

    if(Communities[communitynumber].aa.size()>1)
        for (i=0;i<=Communities[communitynumber].aa.size()-1;i++){
            for(j=0;j<=Communities[communitynumber].aa.size()-1;j++){
                if(((Communities[communitynumber].aa[i]==sequences[seqnumber][Communities[communitynumber].pos[i]])&&(Communities[communitynumber].aa[j]==sequences[seqnumber][Communities[communitynumber].pos[j]]))&&(Communities[communitynumber].pos[i]!=Communities[communitynumber].pos[j])){
                    //QMessageBox::information(NULL,"a","OK");
                    sum+=Singlepvalue(Communities[communitynumber].aa[i],Communities[communitynumber].pos[i],Communities[communitynumber].aa[j],Communities[communitynumber].pos[j]);
                    //QMessageBox::information(NULL,"a","OK");
                }
            }
        }
    //QMessageBox::information(NULL,"a","FIM PSA");
    return(sum/(float)(Communities[communitynumber].aa.size()*(Communities[communitynumber].aa.size()-1)));
}

unsigned int Filter::getUniprotMinedSize(){
    return uniprotMined.size();
}

string Filter::getUniprotEntryName(int i){
    return uniprotMined[i]->getName();
}

unsigned int Filter::getUniprotEntryNofFeatures(int i){
    return uniprotMined[i]->countFeatures();
}

int Filter::getResidueFeaturesByCommCount(string res){
    int total = 0;

    for(unsigned int i = 0; i < uniprotMined.size(); i++){
        for(int j = 0; j < uniprotMined[i]->countFeatures(); j++){
            Feature *f = uniprotMined[i]->getFeature(j);

            if(f->getAlignResidue() == res) total ++;
        }
    }

    return total;
}

vector<tuple<string,string,int> > Filter::getCorrelationGraph(){
    return this->corrGraph;
}

set<string> Filter::getCorrelationNodes(){
    set<string> nodes;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        nodes.insert(std::get<0>(tupCorr).c_str());
        nodes.insert(std::get<1>(tupCorr).c_str());
    }

    return nodes;
}

map<string,int> Filter::getNodesHubs(){
    map<string,int> hubs;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];
        string n1 = get<0>(tupCorr);
        string n2 = get<1>(tupCorr);

        if(hubs.find(n1) == hubs.end()){
            hubs[n1] = 1;
        }else{
            hubs[n1] += 1;
        }
        if(hubs.find(n2) == hubs.end()){
            hubs[n2] = 1;
        }else{
            hubs[n2] += 1;
        }
    }

    return hubs;
}

set<string> Filter::getPositiveCorrelationNodes(){
    set<string> nodes;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        if(std::get<2>(tupCorr) > 0){
            nodes.insert(std::get<0>(tupCorr).c_str());
            nodes.insert(std::get<1>(tupCorr).c_str());
        }
    }

    return nodes;
}

map<string,int> Filter::getPositiveNodeHubs(){
    map<string,int> hubs;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        if(get<2>(tupCorr) > 0){
            string n1 = get<0>(tupCorr);
            string n2 = get<1>(tupCorr);

            if(hubs.find(n1) == hubs.end()){
                hubs[n1] = 1;
            }else{
                hubs[n1] += 1;
            }
            if(hubs.find(n2) == hubs.end()){
                hubs[n2] = 1;
            }else{
                hubs[n2] += 1;
            }
        }
    }

    return hubs;
}

vector<tuple<string,string,int> > Filter::getEdgesByComm(int comm){
    vector<tuple<string,string,int> > graph;
    vector<string> residues = comunidades[comm];

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> edge = corrGraph[i];
        bool ok = false;

        for(unsigned int j = 0; j < residues.size(); j++){
            if(std::get<0>(edge) == residues[j]){
                for(unsigned int k = 0; k < residues.size(); k++){
                    if(std::get<1>(edge) == residues[k])
                        ok = true;
                }
            }
        }

        if(ok) graph.push_back(edge);
    }

    return graph;
}

vector<tuple<string,string,float> > Filter::getDeltasEdges(float cutoff){
    vector<tuple<string,string,float> > graph;

    for(unsigned int i = 0; i < this->comunidades.size(); i++){
        for(unsigned int j = 0; j < this->comunidades.size(); j++){
            if(i!=j){
                if((Deltas[i][j] > 0 && Deltas[i][j] > cutoff) || (Deltas[i][j] < 0 && Deltas[i][j] < (-1*cutoff))){
                    string c1 = "";
                    string c2 = "";
                    if(comunidades[i].size() > 1)
                        c1 = "Comm" + std::to_string(i+1);
                    else
                        c1 = comunidades[i][0];
                    if(comunidades[j].size() > 1)
                        c2 = "Comm" + std::to_string(j+1);
                    else
                        c2 = comunidades[j][0];

                    tuple<string,string,float> edge (c1,c2,Deltas[i][j]);
                    if(c1.substr(0,2) == "Co" || c2.substr(0,2) == "Co")
                        graph.push_back(edge);
                    //printf("%s\t%s\t%f\n",c1.c_str(),c2.c_str(),Deltas[i][j]);
                }
            }
        }
    }

    //Verifica as correlaçoes inversas e mantem a maior
    for(unsigned int i = 0; i < graph.size(); i++){
        tuple<string,string,float> edge = graph[i];
        string c1 = std::get<0>(edge);
        string c2 = std::get<1>(edge);
        float weight1 = std::get<2>(edge);
        float weight2 = 0;
        bool ok = false;
        int j = 0;

        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,float> edge2 = graph[j];
            if(c1 == std::get<1>(edge2) && std::get<0>(edge2) == c2){
                ok = true;
                weight2 = std::get<2>(edge2);
                break;
            }
        }

        if(ok){
            if(fabs(weight1) >= fabs(weight2)){
                graph.erase(graph.begin()+j);

                if(i > 0) i--;
            }
        }
    }

    return graph;
}

string Filter::getNoGAPSequence(int refseq){
    string seq = "";

    for(unsigned int i = 0; i < sequences[refseq].size(); i++){
        if(sequences[refseq][i] != '-' && sequences[refseq][i] != '.' && sequences[refseq][i] != ' ')
            seq += sequences[refseq][i];
    }

    return seq;
}

vector<tuple<int, float> > Filter::createConservationVectorDG(int refseq){//REFSEQ STARTS WITH 1
    vector<tuple<int,float> > consvec;

    for(unsigned int i = 0; i < sequences[0].size(); i++){
        char aa = sequences[refseq-1][i];

        if(aa != '-' && aa != '.' && aa != ' '){
            tuple<int,float> tup;
            if(dG[i] < 0){
                get<0>(tup) = i+1;
                get<1>(tup) = 0.0;
            }else{
                get<0>(tup) = i+1;
                get<1>(tup) = dG[i];
            }
            consvec.push_back(tup);
        }
    }

    return consvec;
}

vector<float> Filter::createConservationVector(int refseq){//REFSEQ STARTS WITH 1
    vector<float> consvec;
    //Para cada residuo da refseq, add o valor de freqperc referente aquele residuo
    string sequence = sequences[refseq-1];

    for(unsigned int i = 0; i < sequence.size(); i++){
        char residue = sequence[i];
        if(residue != '-' && residue != '.' && residue != ' '){
            //printf("%c",residue);
            switch(residue){
            case 'A':
            case 'a':
                consvec.push_back(consfreqPerc[i][0]);
                break;
            case 'C':
            case 'c':
                consvec.push_back(consfreqPerc[i][1]);
                break;
            case 'D':
            case 'd':
                consvec.push_back(consfreqPerc[i][2]);
                break;
            case 'E':
            case 'e':
                consvec.push_back(consfreqPerc[i][3]);
                break;
            case 'F':
            case 'f':
                consvec.push_back(consfreqPerc[i][4]);
                break;
            case 'G':
            case 'g':
                consvec.push_back(consfreqPerc[i][5]);
                break;
            case 'H':
            case 'h':
                consvec.push_back(consfreqPerc[i][6]);
                break;
            case 'I':
            case 'i':
                consvec.push_back(consfreqPerc[i][7]);
                break;
            case 'K':
            case 'k':
                consvec.push_back(consfreqPerc[i][8]);
                break;
            case 'L':
            case 'l':
                consvec.push_back(consfreqPerc[i][9]);
                break;
            case 'M':
            case 'm':
                consvec.push_back(consfreqPerc[i][10]);
                break;
            case 'N':
            case 'n':
                consvec.push_back(consfreqPerc[i][11]);
                break;
            case 'P':
            case 'p':
                consvec.push_back(consfreqPerc[i][12]);
                break;
            case 'Q':
            case 'q':
                consvec.push_back(consfreqPerc[i][13]);
                break;
            case 'R':
            case 'r':
                consvec.push_back(consfreqPerc[i][14]);
                break;
            case 'S':
            case 's':
                consvec.push_back(consfreqPerc[i][15]);
                break;
            case 'T':
            case 't':
                consvec.push_back(consfreqPerc[i][16]);
                break;
            case 'V':
            case 'v':
                consvec.push_back(consfreqPerc[i][17]);
                break;
            case 'W':
            case 'w':
                consvec.push_back(consfreqPerc[i][18]);
                break;
            case 'Y':
            case 'y':
                consvec.push_back(consfreqPerc[i][19]);
                break;
            default:
                consvec.push_back(0);
                break;
            }
        }
    }

    return consvec;
}

bool Filter::uniprotLook(bool cons, bool comm, vector<string> proteins, vector<int> idproteins, float minCons, vector<string> fullAlignment, vector<string> fullSequences){
    QProgressDialog progress("Reading data from webservice (1/3)","Abort",0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    vector<Uniprot*> dataprot;
    string url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/uniprot/look/";
    string post_content = "";

    //Monta a string POST
    for(unsigned int i = 0; i < proteins.size(); i++){
        post_content += proteins[i] + "\n";
    }

    QByteArray const data = QString::fromStdString(post_content).toUtf8();
    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString result = response->readAll();
    //printf("%s",result.toStdString().c_str());

    vector<string> lines = split(result.toStdString(),'\n');

    progress.setLabelText("Parsing UniprotKb data (2/3)");
    progress.setValue(0);
    progress.setMaximum(lines.size()+1);

    //Percorre linhas de proteínas
    for(unsigned int i = 0; i < lines.size(); i++){
        if(progress.wasCanceled()) return false;
        progress.setValue(i);

        vector<string> featVec = split(lines[i],'\t');
        if(featVec.size() > 2){
            string function = "";
            if(featVec[1].substr(0,11) == " FUNCTION: ") function = featVec[1].substr(11);
            else if(featVec[1].substr(0,10) == "FUNCTION: ") function = featVec[1].substr(10);
            else function = featVec[1];
            Uniprot *unientry = new Uniprot(featVec[0],function);

            //Percorre cada tipo de feature de um grupo
            for(unsigned int j = 2; j < featVec.size(); j++){
                string kindOfFeature = featVec[j];
                //printf("%s\n",kindOfFeature.c_str());

                if(kindOfFeature != "null" && kindOfFeature != " "){
                    vector<string> featVec2 = split(kindOfFeature,';');

                    for(unsigned int k = 0; k < featVec2.size(); k++){
                        Feature* f = this->parseFeature(featVec2[k]);

                        if(f->getType() != "")
                            unientry->addFeature(f);
                    }
                }
            }

            dataprot.push_back(unientry);
        }
    }


    //QMessageBox::information(NULL,"A","PRIMERA PARTE OK");
    //SEGUNDA PARTE => TRABALHAR OS DADOS OBTIDOS
    vector<string> residuesList;

    if(cons){
        //Calculate Conserved Residues
        vector<char> conservedaa;
        vector<int> conservedpos;

        this->CalculateFrequencies();

        for(unsigned int i = 0; i <= frequencies.size()-2; i++){
            for(unsigned int j = 1; j <= 20; j++){
                if(progress.wasCanceled()) return false;
                float freq = (float)frequencies[i][j]/((float)sequences.size());
                //printf("freq=%f / minCons=%f\n",freq,minCons);
                if(freq >= minCons){
                    conservedaa.push_back(num2aa(j));
                    conservedpos.push_back(i+1);
                    //printf("%c %d\n",num2aa(j),i+1);
                }
            }
        }
        progress.setValue(70);
        if(progress.wasCanceled()) return false;

        for(unsigned int i = 0; i < conservedaa.size(); i++){
            if(progress.wasCanceled()) return false;
            string alignRes = conservedaa[i] + to_string(conservedpos[i]);
            residuesList.push_back(alignRes);
        }
    }

    progress.setLabelText("Looking for matchs (3/3)");
    progress.setValue(0);
    progress.setMaximum(dataprot.size());

    uniprotMined.clear();

    for(unsigned int i = 0; i < dataprot.size(); i++){
        progress.setValue(i);
        Uniprot *entry = new Uniprot(*dataprot[i]);
        Uniprot *out = new Uniprot();
        out->setName(entry->getName());
        //printf("FUNCTION: %s\n",entry->getFunction().c_str());
        out->setFunction(entry->getFunction());

        if(progress.wasCanceled()) return false;

        //printf("%s\n",entry->toString().c_str());

        for(int j = 0; j < entry->countFeatures(); j++){
            Feature *f = entry->getFeature(j);
            //printf("%s\n",f->toString().c_str());

            if(cons){
                for(unsigned int k = 0; k < residuesList.size(); k++){
                    string respos = residuesList[k];
                    char aa = respos[0];
                    int alignPos = stoi(respos.substr(1));
                    int pos = AlignNumbering2Sequence2(idproteins[i]+1,alignPos,fullSequences) + GetOffsetFromSeqName(fullAlignment[idproteins[i]]);
                    if(pos > 0){
                        string newResPos = fullSequences[idproteins[i]][alignPos-1] + to_string(pos);
                        string newAlignPos = aa + to_string(alignPos);

                        if(pos == f->getPosition() || pos == f->getBegin() || pos == f->getEnd()){
                            Feature *f1 = new Feature();
                            f1->setAggregation(0);
                            f1->setBegin(f->getBegin());
                            f1->setDescription(f->getDescription());
                            f1->setEnd(f->getEnd());
                            f1->setId(f->getId());
                            f1->setOriginal(f->getOriginal());
                            f1->setPosition(f->getPosition());
                            f1->setResidueColigated(newResPos);
                            f1->setAlignResidue(newAlignPos);
                            f1->setType(f->getType());
                            f1->setVariation(f->getVariation());
                            //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                            out->addFeature(f1);
                        }
                    }
                }
            }

            if(comm){
                for(unsigned int k = 0; k < comunidades.size(); k++){
                    for(unsigned int l = 0; l < comunidades[k].size(); l++){
                        string respos = comunidades[k][l];
                        char aa = respos[0];
                        int alignPos = stoi(respos.substr(1));
                        int pos = AlignNumbering2Sequence2(idproteins[i]+1,alignPos-1,fullSequences) + GetOffsetFromSeqName(fullAlignment[idproteins[i]]);
                        if( pos > 0){
                            string newResPos = fullSequences[idproteins[i]][alignPos-1] + QString::number(pos).toStdString();
                            string newAlignPos = aa + to_string(alignPos);
                            printf("SEQUENCE: %s - ALIGNN: %s - SEQN: %s\n",fullAlignment[idproteins[i]].c_str(),newAlignPos.c_str(),newResPos.c_str());

                            //printf("POS: %d   -   %d  %d-%d\n",pos,f->getPosition(),f->getBegin(),f->getEnd());
                            if(pos == f->getPosition() || pos == f->getBegin() || pos == f->getEnd()){
                                Feature *f1 = new Feature();
                                f1->setAggregation(k+1);
                                f1->setBegin(f->getBegin());
                                f1->setDescription(f->getDescription());
                                f1->setEnd(f->getEnd());
                                f1->setId(f->getId());
                                f1->setOriginal(f->getOriginal());
                                f1->setPosition(f->getPosition());
                                f1->setResidueColigated(newResPos);
                                f1->setAlignResidue(newAlignPos);
                                f1->setType(f->getType());
                                f1->setVariation(f->getVariation());
                                //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                                out->addFeature(f1);
                            }
                        }
                    }
                }
            }
            f->kill();
        }
        entry->kill();
        uniprotMined.push_back(out);
    }
    progress.close();

    QMessageBox::information(NULL,"Uniprot Looking","Uniprot Looking has finished successfully");

    return true;
}

void Filter::removeItemOfCommunity(int comm, int item){
    comunidades[comm].erase(comunidades[comm].begin() + item);
}

void Filter::addItemToCommunity(string res, int commindex){
    comunidades[commindex].push_back(res);
}

unsigned int Filter::getRefSeqOffset(){
    if(refSeqName == "") return 0;

    vector<string> tokens = split(refSeqName,'/');
    string range = tokens[1];
    //printf("\nRANGE: %s\n",range.c_str());
    vector<string> tokens2 = split(range,'-');
    QString qoffset = QString::fromStdString(tokens2[0]);
    //printf("\nQOffset: %s\n",qoffset.toStdString().c_str());
    bool ok;
    unsigned int offset = qoffset.toInt(&ok);
    //printf("\nOffset: %d\n",offset);

    if(ok) return offset -1;
    return 0;
}

void Filter::applyAlphabetReduction(vector<string> oldChars, vector<char> newChars){

    for(unsigned int i = 0; i < sequences.size(); i++){
        string newSeq = "";
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            char c = toupper(sequences[i][j]);
            for(unsigned int k = 0; k < oldChars.size(); k++){
                if(c == '-'){
                    newSeq += '-';
                    break;
                }else if(c == '.'){
                    newSeq += '.';
                    break;
                }else if(c == 'X'){
                    newSeq += 'X';
                    break;
                }else if(oldChars[k].find(c) != std::string::npos){
                    newSeq += newChars[k];
                    break;
                }
            }
        }
        //printf("%s\n%s\n\n",sequences[i].c_str(),newSeq.c_str());
        sequences[i] = newSeq;
    }
}

void Filter::exportFilteredAlignment(QString filename, int type){
    switch(type){
        case 0://PFAM
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "pfam" && tempFN[tempFN.size()-1] != "PFAM")
                filename += ".pfam";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            for(unsigned int i = 0; i < sequences.size(); i++){
                out << sequencenames[i].c_str() << " " << sequences[i].c_str() << "\n";
            }

            f.close();
            break;
        }
        case 1://TXT
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            for(unsigned int i = 0; i < sequences.size(); i++){
                out << sequencenames[i].c_str() << " " << sequences[i].c_str() << "\n";
            }

            f.close();
            break;
        }
        case 2://XML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            out << "<?xml version=\"1.0\"?>\n\n";
            out << "<PFStats>\n";
            out << "   <filters>\n";

            string occ = to_string(this->minOcc);
            string minid = to_string(this->minId);
            string maxid = to_string(this->maxId);
            string refseq = this->refSeq;
            if(refseq == "") refseq = "NULL";

            out << "      <filter occ='" << occ.c_str() << "' minid='" << minid.c_str() << "' maxid='" << maxid.c_str() << "' refseq='" << refseq.c_str() << "' >\n";
            for(unsigned int i = 0; i < sequences.size(); i++){
                out << "         <entry id='" << i-1 << "' name='" << sequencenames[i].c_str() << "'>" << sequences[i].c_str() << "</entry>\n";
            }

            out << "      </filter>\n";
            out << "   </filters>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this alignment.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Alignment","Alignment saved succesfully.");
}

void Filter::exportRefs(QString filename, int type){
    switch(type){
    case 0:
    {
        vector<string> tempFN = split(filename.toStdString(),'.');
        if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
            filename += ".txt";

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }

        QTextStream out(&f);

        for(unsigned int i = 0; i < refseqs.size(); i++){
            out << refseqs[i].c_str() << "\n";
        }

        f.close();
        break;
    }
    case 1:
    {
        vector<string> tempFN = split(filename.toStdString(),'.');
        if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
            filename += ".xml";

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }

        QTextStream out(&f);

        out << "<?xml version=\"1.0\"?>\n";
        out << "<PFStats>\n";
        out << "<references>\n";

        for(unsigned int i = 0; i < refseqs.size(); i++){
            out << "<sequence>" << refseqs[i].c_str() << "</sequence>\n";
        }

        out << "</references>\n";
        out << "</PFStats>\n";

        f.close();
        break;
        break;
    }
    default:
    {
        QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
        return;
    }
    }
    QMessageBox::information(NULL,"Exporting Data","References sequences was exported.");
}

void Filter::exportFreq(QString filename, int type, bool perc){
        switch(type){
        case 0://TXT
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "#FILTER MIN_CONS\n";
            out << "#" << name.c_str() << " " << QString::number(cons_min) << "\n";

            if(perc){
                out.setRealNumberPrecision(1);
                out.setFieldAlignment(QTextStream::AlignLeft);
                out.setRealNumberNotation(QTextStream::FixedNotation);
                out << "pos  ALA  CYS  ASP  GLU  PHE  GLY  HIS  ILE  LYS  LEU  MET  ASN  PRO  GLN  ARG  SER  THR  VAL  TRP  TYR\n";
                for(unsigned int i = 0; i < consfreqPerc.size()-1; i++){
                    out.setFieldWidth(5);
                    out << i+1;
                    for(unsigned int j = 0; j < consfreqPerc[i].size(); j++){
                        out.setFieldWidth(5);
                        out << consfreqPerc[i][j];
                    }
                    out << qSetFieldWidth(0) << "\n";
                }
            }else{
                out << "pos  GAP   ALA   CYS   ASP   GLU   PHE   GLY   HIS   ILE   LYS   LEU   MET   ASN   PRO   GLN   ARG   SER   THR   VAL   TRP   TYR\n";
                for(unsigned int i = 0; i < consvfreq.size()-1; i++){
                    if(i <= 8)
                        out << i+1 << "    ";
                    else if(i >=9 && i <= 98)
                        out << i+1 << "   ";
                    else if(i > 99)
                        out << i+1 << "  ";
                    for(unsigned int j = 0; j < consvfreq[i].size(); j++){
                        if(consvfreq[i][j] >= 0 && consvfreq[i][j] <= 9)
                            out << consvfreq[i][j] << "     ";
                        else if(consvfreq[i][j] >= 10 && consvfreq[i][j] <= 99)
                            out << consvfreq[i][j] << "    ";
                        else if(consvfreq[i][j] > 99)
                            out << consvfreq[i][j] << "   ";
                    }
                    out << "\n";
                }
                out << "ALL        ";
                unsigned int lastpos = consvfreq.size()-1;
                for(unsigned int i = 1; i < consvfreq[lastpos].size(); i++){
                    if(consvfreq[lastpos][i] >= 0 && consvfreq[lastpos][i] <= 9)
                        out << consvfreq[lastpos][i] << "     ";
                    else if(consvfreq[lastpos][i] >= 10 && consvfreq[lastpos][i] <= 99)
                        out << consvfreq[lastpos][i] << "    ";
                    else if(consvfreq[lastpos][i] >= 100 && consvfreq[lastpos][i] <= 999)
                        out << consvfreq[lastpos][i] << "   ";
                    else if(consvfreq[lastpos][i] >= 1000 && consvfreq[lastpos][i] <= 9999)
                        out << consvfreq[lastpos][i] << "  ";
                    else out << consvfreq[lastpos][i] << " ";

                }
            }

            f.close();
            break;
        }
        case 1://CSV
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            if(perc){
                for(unsigned int i = 0; i < consfreqPerc.size(); i++){
                    out << i+1 << ",";
                    for(unsigned int j = 0; j < consfreqPerc[i].size()-1; j++)
                        out << consfreqPerc[i][j] << ",";
                    out << consfreqPerc[i][consfreqPerc[i].size()-1] << "\n";
                }
            }else{
                for(unsigned int i = 0; i < consvfreq.size()-1; i++){
                    out << i+1 << ",";
                    for(unsigned int j = 0; j < consvfreq[i].size()-1; j++)
                        out << consvfreq[i][j] << ",";
                    out << consvfreq[i][consvfreq[i].size()-1] << "\n";
                }
                out << "ALL,";
                unsigned int lastpos = consvfreq.size()-1;
                for(unsigned int i = 0; i < consvfreq[lastpos].size()-1; i++){
                    out << consvfreq[lastpos][i] << ",";
                }
                out << consvfreq[lastpos][consvfreq[lastpos].size()-1];
            }

            f.close();
            break;
        }
        case 2://XML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n\n";
            out << "<PFStats>\n";
            out << "   <conservation>\n";

            out << "      <parameters>\n";

            out << "         <filter>" << name.c_str() << "</filter>\n";
            out << "         <min_conservation>" << QString::number(cons_min) << "</min_conservation>\n";

            out << "      </parameters>\n";

            out << "   <positions>\n";

            if(perc){
                for(unsigned int i = 0; i < consfreqPerc.size(); i++){
                    out << "      <pos id='" << i+1 << "'>\n";
                    out << "         <ALA>\n";
                    out << "            <percent>" << consfreqPerc[i][0] << "</percent>\n";
                    out << "         </ALA>\n";
                    out << "         <CYS>\n";
                    out << "            <percent>" << consfreqPerc[i][1] << "</percent>\n";
                    out << "         </CYS>\n";
                    out << "         <ASP>\n";
                    out << "            <percent>" << consfreqPerc[i][2] << "</percent>\n";
                    out << "         </ASP>\n";
                    out << "         <GLU>\n";
                    out << "            <percent>" << consfreqPerc[i][3] << "</percent>\n";
                    out << "         </GLU>\n";
                    out << "         <PHE>\n";
                    out << "            <percent>" << consfreqPerc[i][4] << "</percent>\n";
                    out << "         </PHE>\n";
                    out << "         <GLY>\n";
                    out << "            <percent>" << consfreqPerc[i][5] << "</percent>\n";
                    out << "         </GLY>\n";
                    out << "         <HIS>\n";
                    out << "            <percent>" << consfreqPerc[i][6] << "</percent>\n";
                    out << "         </HIS>\n";
                    out << "         <ILE>\n";
                    out << "            <percent>" << consfreqPerc[i][7] << "</percent>\n";
                    out << "         </ILE>\n";
                    out << "         <LYS>\n";
                    out << "            <percent>" << consfreqPerc[i][8] << "</percent>\n";
                    out << "         </LYS>\n";
                    out << "         <LEU>\n";
                    out << "            <percent>" << consfreqPerc[i][9] << "</percent>\n";
                    out << "         </LEU>\n";
                    out << "         <MET>\n";
                    out << "            <percent>" << consfreqPerc[i][10] << "</percent>\n";
                    out << "         </MET>\n";
                    out << "         <ASN>\n";
                    out << "            <percent>" << consfreqPerc[i][11] << "</percent>\n";
                    out << "         </ASN>\n";
                    out << "         <PRO>\n";
                    out << "            <percent>" << consfreqPerc[i][12] << "</percent>\n";
                    out << "         </PRO>\n";
                    out << "         <GLN>\n";
                    out << "            <percent>" << consfreqPerc[i][13] << "</percent>\n";
                    out << "         </GLN>\n";
                    out << "         <ARG>\n";
                    out << "            <percent>" << consfreqPerc[i][14] << "</percent>\n";
                    out << "         </ARG>\n";
                    out << "         <SER>\n";
                    out << "            <percent>" << consfreqPerc[i][15] << "</percent>\n";
                    out << "         </SER>\n";
                    out << "         <THR>\n";
                    out << "            <percent>" << consfreqPerc[i][16] << "</percent>\n";
                    out << "         </THR>\n";
                    out << "         <VAL>\n";
                    out << "            <percent>" << consfreqPerc[i][17] << "</percent>\n";
                    out << "         </VAL>\n";
                    out << "         <TRP>\n";
                    out << "            <percent>" << consfreqPerc[i][18] << "</percent>\n";
                    out << "         </TRP>\n";
                    out << "         <TYR>\n";
                    out << "            <percent>" << consfreqPerc[i][19] << "</percent>\n";
                    out << "         </TYR>\n";
                    out << "      </pos>\n";
                }
            }else{
                for(unsigned int i = 0; i < consvfreq.size(); i++){
                    if(i == consvfreq.size()-1)
                        out << "      <total>\n";
                    else
                        out << "      <pos id='" << i+1 << "'>\n";
                    out << "         <GAP>\n";
                    out << "            <frequence>" << consvfreq[i][0] << "</frequence>\n";
                    out << "         </GAP>\n";
                    out << "         <ALA>\n";
                    out << "            <frequence>" << consvfreq[i][1] << "</frequence>\n";
                    out << "         </ALA>\n";
                    out << "         <CYS>\n";
                    out << "            <frequence>" << consvfreq[i][2] << "</frequence>\n";
                    out << "         </CYS>\n";
                    out << "         <ASP>\n";
                    out << "            <frequence>" << consvfreq[i][3] << "</frequence>\n";
                    out << "         </ASP>\n";
                    out << "         <GLU>\n";
                    out << "            <frequence>" << consvfreq[i][4] << "</frequence>\n";
                    out << "         </GLU>\n";
                    out << "         <PHE>\n";
                    out << "            <frequence>" << consvfreq[i][5] << "</frequence>\n";
                    out << "         </PHE>\n";
                    out << "         <GLY>\n";
                    out << "            <frequence>" << consvfreq[i][6] << "</frequence>\n";
                    out << "         </GLY>\n";
                    out << "         <HIS>\n";
                    out << "            <frequence>" << consvfreq[i][7] << "</frequence>\n";
                    out << "         </HIS>\n";
                    out << "         <ILE>\n";
                    out << "            <frequence>" << consvfreq[i][8] << "</frequence>\n";
                    out << "         </ILE>\n";
                    out << "         <LYS>\n";
                    out << "            <frequence>" << consvfreq[i][9] << "</frequence>\n";
                    out << "         </LYS>\n";
                    out << "         <LEU>\n";
                    out << "            <frequence>" << consvfreq[i][10] << "</frequence>\n";
                    out << "         </LEU>\n";
                    out << "         <MET>\n";
                    out << "            <frequence>" << consvfreq[i][11] << "</frequence>\n";
                    out << "         </MET>\n";
                    out << "         <ASN>\n";
                    out << "            <frequence>" << consvfreq[i][12] << "</frequence>\n";
                    out << "         </ASN>\n";
                    out << "         <PRO>\n";
                    out << "            <frequence>" << consvfreq[i][13] << "</frequence>\n";
                    out << "         </PRO>\n";
                    out << "         <GLN>\n";
                    out << "            <frequence>" << consvfreq[i][14] << "</frequence>\n";
                    out << "         </GLN>\n";
                    out << "         <ARG>\n";
                    out << "            <frequence>" << consvfreq[i][15] << "</frequence>\n";
                    out << "         </ARG>\n";
                    out << "         <SER>\n";
                    out << "            <frequence>" << consvfreq[i][16] << "</frequence>\n";
                    out << "         </SER>\n";
                    out << "         <THR>\n";
                    out << "            <frequence>" << consvfreq[i][17] << "</frequence>\n";
                    out << "         </THR>\n";
                    out << "         <VAL>\n";
                    out << "            <frequence>" << consvfreq[i][18] << "</frequence>\n";
                    out << "         </VAL>\n";
                    out << "         <TRP>\n";
                    out << "            <frequence>" << consvfreq[i][19] << "</frequence>\n";
                    out << "         </TRP>\n";
                    out << "         <TYR>\n";
                    out << "            <frequence>" << consvfreq[i][20] << "</frequence>\n";
                    out << "         </TYR>\n";
                    if(i == consvfreq.size()-1)
                        out << "      </total>\n";
                    else
                        out << "      </pos>\n";
                }
            }

            out << "   </positions>\n";
            out << "   </conservation>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        case 3://HTML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<!DOCTYPE html>\n";
            out << "<html>\n";
            out << "<body>\n";
            out << "<table border='1'>\n";
            out << "\t<tr>\n";
            out << "\t\t" << name.c_str() << "\n";
            out << "\t</tr>\n";
            out << "\t<tr>\n";
            //out << "\t\tChain: " << chain.c_str() << "\n";
            out << "\t</tr>\n";
            out << "\t<tr>\n";
            out << "\t\t<td><b>POS</b></td>\n";
            if(!perc) out << "\t\t<td><b>GAP</b></td>\n";
            out << "\t\t<td><b>ALA</b></td>\n";
            out << "\t\t<td><b>CYS</b></td>\n";
            out << "\t\t<td><b>ASP</b></td>\n";
            out << "\t\t<td><b>GLU</b></td>\n";
            out << "\t\t<td><b>PHE</b></td>\n";
            out << "\t\t<td><b>GLY</b></td>\n";
            out << "\t\t<td><b>HIS</b></td>\n";
            out << "\t\t<td><b>ILE</b></td>\n";
            out << "\t\t<td><b>LYS</b></td>\n";
            out << "\t\t<td><b>LEU</b></td>\n";
            out << "\t\t<td><b>MET</b></td>\n";
            out << "\t\t<td><b>ASN</b></td>\n";
            out << "\t\t<td><b>PRO</b></td>\n";
            out << "\t\t<td><b>GLN</b></td>\n";
            out << "\t\t<td><b>ARG</b></td>\n";
            out << "\t\t<td><b>SER</b></td>\n";
            out << "\t\t<td><b>THR</b></td>\n";
            out << "\t\t<td><b>VAL</b></td>\n";
            out << "\t\t<td><b>TRP</b></td>\n";
            out << "\t\t<td><b>TYR</b></td>\n";
            out << "\t</tr>\n";

            if(perc){
                for(unsigned int i = 0; i < consfreqPerc.size(); i++){
                    out << "\t<tr>\n";
                    out << "\t\t<td>" << i+1 << "</td>\n";
                    for(unsigned int j = 0; j < consfreqPerc[i].size(); j++){
                        out << "\t\t<td>" << consfreqPerc[i][j] << "</td>\n";
                    }
                    out << "</tr>\n";
                }
            }else{
                for(unsigned int i = 0; i < consvfreq.size()-1; i++){
                    out << "\t<tr>\n";
                    out << "\t\t<td>" << i+1 << "</td>\n";
                    for(unsigned int j = 0; j < consvfreq[i].size(); j++){
                        out << "\t\t<td>" << consvfreq[i][j] << "</td>\n";
                    }
                    out << "</tr>\n";
                }
                out << "\t<tr>\n";
                out << "\t\t<td>TOTAL</td>\n";
                unsigned int lastpos = consvfreq.size()-1;
                for(unsigned int i = 0; i < consvfreq[lastpos].size(); i++){
                    out << "\t\t<td>" << consvfreq[lastpos][i] << "</td>\n";
                }
                out << "</tr>\n";
            }

            out << "</table>\n";
            out << "</body>\n";
            out << "</html>\n";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Conservation data was exported.");
}

void Filter::exportConsRes(QString filename, int type, float mincons, vector<int> refSeqs, vector<string> fullAlignment, vector<string> fullSequences){
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;

    this->CalculateFrequencies();

    for(unsigned int i = 0; i < frequencies.size()-2; i++){
        for(unsigned int j = 1; j <= 20; j++){
            float freq = frequencies[i][j]/((float)sequences.size());
            //printf("freq=%f / minCons=%f\n",freq,minCons);
            if(freq >= mincons){
                conservedaa.push_back(num2aa(j));
                conservedpos.push_back(i);
                conservedfreq.push_back(100.0*freq);
            }
        }
    }

    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "Sequence ";
            for(unsigned int i = 0; i < conservedaa.size(); i++)
                out <<  conservedaa[i] << conservedpos[i]+1 << " (" << QString::number(conservedfreq[i],'f',1) << ") ";
            out << "\n";

            for(unsigned int i = 0; i < refSeqs.size(); i++){
                out << fullAlignment[refSeqs[i]].c_str() << " ";
                for(unsigned int j = 0; j < conservedaa.size(); j++){
                    if(AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) == 0) out << "- ";
                    else{
                        if(fullSequences[refSeqs[i]][conservedpos[j]]==conservedaa[j])
                            out << conservedaa[j] << AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]]) << " ";
                        else
                            out << fullSequences[refSeqs[i]][conservedpos[j]] << AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]]) << " ";
                    }
                }
                out << "\n";
            }
            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<conservedResidues>\n";

            for(unsigned int i = 0; i < conservedaa.size(); i++){
                out << "\t\t<residue alignN=\"" << conservedaa[i] << conservedpos[i]+1 << "\" freq=\"" << QString::number(conservedfreq[i],'f',1) << "\">\n";

                for(unsigned int j = 0; j < refSeqs.size(); j++){
                    out << "\t\t\t<entry protein=\"" << fullAlignment[refSeqs[j]].c_str() << "\" ";
                    if(AlignNumbering2Sequence2(refSeqs[j]+1,conservedpos[i],fullSequences) == 0)
                        out << "seqN=\"-\" conserv=\"false\"/>\n";
                    else{
                        if(fullSequences[refSeqs[j]][conservedpos[i]]==conservedaa[i]){
                            out << "seqN=\"" << conservedaa[i] << AlignNumbering2Sequence2(refSeqs[j]+1,conservedpos[i],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[j]]);
                            out << "\" conserv=\"true\"/>\n";
                        }else{
                            out << "seqN=\"" << fullSequences[refSeqs[j]][conservedpos[i]] << AlignNumbering2Sequence2(refSeqs[j]+1,conservedpos[i],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[j]]);
                            out << "\" conserv=\"false\"/>\n";
                        }
                    }
                }

                out << "\t\t</residue>\n";
            }

            out << "\t</conservedResidues>\n";
            out << "</PFStats>\n";
            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            out.setFieldAlignment(QTextStream::AlignLeft);
            out.setRealNumberNotation(QTextStream::FixedNotation);
            out.setRealNumberPrecision(1);

            out << "<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th><b>Sequence</b></th>";

            for (unsigned int c1=0;c1<=conservedaa.size()-1;c1++){
                out << "<th><b>" << conservedaa[c1] << conservedpos[c1]+1 << " (" << conservedfreq[c1] <<")</b></th>";
            }
            out << "</tr>\n";
            for (unsigned int c1=0;c1<=refSeqs.size()-1;c1++){
                out << "<tr><th><b>" << fullAlignment[refSeqs[c1]].c_str();
                for (unsigned int c2=0;c2<=conservedaa.size()-1;c2++){
                    if(AlignNumbering2Sequence2(refSeqs[c1]+1,conservedpos[c2],fullSequences) ==0){
                        out << "<th><font color=#FF0000>-</font></th>";
                    }else{
                        if (fullSequences[refSeqs[c1]][conservedpos[c2]]==conservedaa[c2])
                            out << "<th>" << conservedaa[c2] << AlignNumbering2Sequence2(refSeqs[c1]+1,conservedpos[c2],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[c1]]) << "</th>";
                        else
                            out << "<th><font color=#FF0000>" << fullSequences[refSeqs[c1]][conservedpos[c2]] << AlignNumbering2Sequence2(refSeqs[c1]+1,conservedpos[c2],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[c1]]) << "</font></th>";
                    }
                }
                out << "</tr>\n";
            }
            f.close();

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Conserved residues data was exported.");
}

void Filter::exportCorrGraph(QString filename, int type){
    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "#FILTER: " << name.c_str() << " ";
            out << "#REFSEQ: " << sequencenames[corr_refseq-1].c_str() << " ";
            out << "#MIN SCORE: " << QString::number(corr_min_score) << " ";
            out << "#MINSS FRACTION: " << QString::number(corr_minssfraction) << " ";
            out << "#DELTA FREQ: " << QString::number(corr_min_delta) << "\n";

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << std::get<0>(tupCorr).c_str() << " " << std::get<1>(tupCorr).c_str() << " " << std::get<2>(tupCorr) << "\n";
            }

            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << std::get<0>(tupCorr).c_str() << "," << std::get<1>(tupCorr).c_str() << "," << std::get<2>(tupCorr) << "\n";
            }
            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<correlation>\n";
            out << "\t\t<parameters>\n";

            out << "\t\t\t<filter>" << name.c_str() << "</filter>\n";
            out << "\t\t\t<refseq>" << sequencenames[corr_refseq-1].c_str() << "</refseq>\n";
            out << "\t\t\t<minScore>" << QString::number(corr_min_score) << "</minScore>\n";
            out << "\t\t\t<minss>" << QString::number(corr_minssfraction) << "</minss>\n";
            out << "\t\t\t<delta>" << QString::number(corr_min_delta) << "</delta>\n";

            out << "\t\t</parameters>\n";

            out << "\t\t<graph>\n";

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << "\t\t\t<entry res1=\"" << std::get<0>(tupCorr).c_str() << "\" res2=\"" << std::get<1>(tupCorr).c_str() << "\" value=\"" << std::get<2>(tupCorr) << "\" />\n";
            }

            out << "\t\t</graph>\n";
            out << "\t</correlation>\n";
            out << "</PFStats>\n";
            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Correlation list data was exported.");
}

void Filter::exportCommList(QString filename, int type){

    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << comunidades.size() << " communities\n";

            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << comunidades[i].size() << " nodes in community " << i+1 << "\n";
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    out << comunidades[i][j].c_str() << "\n";
                }
            }
            f.close();

            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<communities>\n";

            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << "\t\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    out << "\t\t\t<node>" << comunidades[i][j].c_str() << "</node>\n";
                }

                out << "\t\t</community>\n";
            }

            out << "\t</communities>\n";
            out << "</PFStats>";
            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Correlation list data was exported.");
}

void Filter::exportCorrTable(QString filename, int type, bool perc){
    if(perc){
        switch(type){
            case 0:
            {
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "ALL ";
                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " " << QString::number(communityXAll[i][j],'f',2) << " ";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == -1) out << "X ";
                            else out << QString::number(communityX[i][j][k]*100,'f',4) << " ";
                        }
                        out << "\n";
                    }

                    f.close();
                }

                break;
            }
            case 1:
            {
                vector<string> tempFN = split(filename.toStdString(),'.');
                if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                    filename += ".xml";

                //Salva em arquivo
                QFile f(filename);
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<?xml version=\"1.0\"?>\n";
                out << "<PFStats>\n";

                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    out << "<column>ALL</column>\n";
                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << "<column>" << residuesComm[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" c0=\"" << QString::number(communityXAll[i][j],'f',2) << "\" ";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == 0)
                                out << "c" << k+1 << "=\"X\" ";
                            else
                                out << "c" << k+1 << "=\"" << QString::number(communityX[i][j][k]*100,'f',4) << "\" ";
                        }
                        out << "/>\n";
                    }

                    out << "\t\t</table_data>\n";

                    out << "\t</community>\n";
                }

                out << "</PFStats>";

                f.close();
                break;
            }
            case 2:
            {
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n";
                    out << "<body>\n";

                    out << "<table border=1>\n";
                    out << "<center>\n";

                    out << "<tr>\n";
                    out << "<th>POS</th>\n<th>ALL</th>\n";

                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << "<th>" << residuesComm[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesComm[i][j].c_str() << "</b></td>\n";
                        out << "<td>" << QString::number(communityXAll[i][j],'f',1) << "</td>\n";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == 0)
                                out << "<td>X</td>\n";
                            else
                                if(communityX[i][j][k]*100 - communityXAll[i][j] > 15)
                                    out << "<td><font color=#00FF00>" << QString::number(communityX[i][j][k]*100,'f',1) << "</td>\n";
                                else out << "<td>" << QString::number(communityX[i][j][k]*100,'f',1) << "</td>\n";
                        }
                        out << "</tr>";
                    }


                    out << "</body>\n";
                    out << "</html>";
                    f.close();
                }

                break;
            }
            default:
            {
                QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
                return;
            }
        }
    }else{
        switch(type){
            case 0:
            {
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == -1) out << "X ";
                            else out << QString::number(communityXps[i][j][k]) << " ";
                        }
                        out << "\n";
                    }

                    f.close();
                }
                break;
            }
            case 1:
            {
                vector<string> tempFN = split(filename.toStdString(),'.');
                if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                    filename += ".xml";

                //Salva em arquivo
                QFile f(filename);
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<?xml version=\"1.0\"?>\n";
                out << "<PFStats>\n";

                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<column>" << residuesCommPs[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" ";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == 0)
                                out << "c" << k << "=\"X\" ";
                            else
                                out << "c" << k << "=\"" << QString::number(communityXps[i][j][k]) << "\" ";
                        }
                        out << "/>\n";
                    }

                    out << "\t\t</table_data>\n";

                    out << "\t</community>\n";
                }

                out << "</PFStats>";

                f.close();
                break;
            }
            case 2:
            {
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n";
                    out << "<body>\n";

                    out << "<table border=1>\n";
                    out << "<center>\n";

                    out << "<tr>\n";
                    out << "<th>POS</th>\n";

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<th>" << residuesCommPs[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesCommPs[i][j].c_str() << "</b></td>\n";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == 0)
                                out << "<td>X</td>\n";
                            else
                                out << "<td>" << QString::number(communityXps[i][j][k]) << "</td>\n";
                        }
                        out << "</tr>";
                    }


                    out << "</table>\n";
                    out << "</body>\n";
                    out << "</html>";
                    f.close();
                }
                break;
            }
            default:
            {
                QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
                return;
            }
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Correlation table data was exported.");
}

void Filter::exportAdh(QString filename, int type){
    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "PROTEIN_SEQUENCE\t";
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "Comm" << i+1 << " (" << residuesComm[i].size() << ")\t";
            }
            out << "\n";

            for(unsigned int i = 0; i < sequences.size()-1; i++){
                out << sequencenames[i].c_str() << "\t";

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << QString::number(psa,'f',6) << "\t";
                    }
                }
                out << "\n";
            }

            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            for(unsigned int i = 0; i < sequences.size()-1; i++){
                out << sequencenames[i].c_str();

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << "," << QString::number(psa,'f',6);
                    }
                }
                out << "\n";
            }

            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "<adherence>\n";

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                if(Communities[i].aa.size() > 1){
                    out << "\t<community id=\"" << i+1 << "\">\n";

                    for(unsigned int j = 0; j < sequences.size()-1; j++){
                        float psa = this->PSA(j,i);

                        out << "\t\t<protein value=\"" << QString::number(psa,'f',6) << "\">" << sequencenames[j].c_str() << "</protein>\n";
                    }
                    out << "\t</community>\n";
                }
            }

            out << "</adherence>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        case 3:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<html>\n";
            out << "<body>\n";

            out << "<table border=1>\n";
            out << "<center>\n";

            out << "<tr>\n";
            out << "<th>PROTEIN SEQUENCE</th>\n";

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "<th>Comm" << i+1 << " (" << residuesComm[i].size() << ")</th>\n";
            }
            out << "</tr>\n";

            for(unsigned int i = 0; i < sequences.size()-1; i++){
                out << "<tr>\n<td><b>" << sequencenames[i].c_str() << "</b></td>\n";

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << "<td>" << QString::number(psa,'f',6) << "</td>\n";
                    }
                }
                out << "</tr>\n";
            }

            out << "</table></body>\n</html>";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Adherence data was exported.");
}

void Filter::exportResComm(QString filename, int type, vector<string> fullAlignment, vector<string> fullSequences){
    vector<int> refCodes = getRefSeqCodes(fullAlignment);

    switch(type){
        case 0:
        {
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(unsigned int j = 0; j < tempFN.size()-1; j++){
                        path +=tempFN[j];
                    }
                }
                path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);


                out << "Sequence";

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t" << textCab.c_str();
                }
                out << "\n";

                for(unsigned int j = 0; j < refseqs.size(); j++){
                    out << fullAlignment[refCodes[j]].c_str();

                    for(unsigned int k = 0; k < Communities[i].pos.size(); k++){
                        if(fullSequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                            out << "\t" << textItem.c_str();
                        }else{
                            if(fullSequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "\t - ";
                            else{
                                string textItem = fullSequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                                out << "\t" << textItem.c_str();
                            }
                        }
                    }
                    out << "\n";
                }
                f.close();
            }
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "<commRes>\n";

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t\t<residue alignNumber=\"" << textCab.c_str() << "\">\n";


                    for(unsigned int k = 0; k < refseqs.size(); k++){
                        if(fullSequences[refCodes[k]][Communities[i].pos[j]] == Communities[i].aa[j]){
                            string textItem = Communities[i].aa[j] + QString::number(AlignNumbering2Sequence2(refCodes[k]+1,Communities[i].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"true\">" << fullAlignment[refCodes[k]].c_str() << "</sequence>\n";
                        }else if(fullSequences[refCodes[k]][Communities[i].pos[j]] != '-'){
                            string textItem = fullSequences[refCodes[k]][Communities[i].pos[j]] + QString::number(AlignNumbering2Sequence2(refCodes[k]+1,Communities[i].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"false\">" << fullAlignment[refCodes[k]].c_str() << "</sequence>\n";
                        }
                    }

                    out << "\t\t</residue>\n";
                }

                out << "\t</community>\n";
            }

            out << "</commRes>\n";
            out << "</PFStats>";

            f.close();
            break;
        }
        case 2:
        {
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(unsigned int j = 0; j < tempFN.size()-1; j++){
                        path +=tempFN[j];
                    }
                }
                path += "_comm" + QString::number(i+1).toStdString() + ".html";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n";
                out << "<body>\n";

                out << "<table border=1>\n";
                out << "<center>\n";

                out << "<tr>\n";
                out << "<th>Sequence</th>\n";

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "<th>" << textCab.c_str() << "</th>\n";
                }
                out << "</tr>\n";

                for(unsigned int j = 0; j < refseqs.size(); j++){
                    out << "<tr>\n<td><b>" << fullAlignment[refCodes[j]].c_str() << "</b></td>\n";

                    for(unsigned int k = 0; k < Communities[i].pos.size(); k++){
                        if(fullSequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                            out << "<td><b><font color=#00FF00>" << textItem.c_str() << "</font></b></td>\n";
                        }else{
                            if(fullSequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "<td><center>-</center></td>\n";
                            else{
                                string textItem = fullSequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                                out << "<td>" << textItem.c_str() << "</td>\n";
                            }
                        }
                    }
                    out << "</tr>\n";
                }
                out << "</table>\n";
                out << "</body>\n";
                out << "</html>";
                f.close();
            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Residues of communities data was exported.");
}

void Filter::exportLookProt(QString filename, int type){
    set<string> proteins;

    //GET LIST OF PROTEINS NAMES
    for(unsigned int i = 0; i < uniprotMined.size(); i++)
        proteins.insert(uniprotMined[i]->getName());

    switch(type){
        case 0:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "RESIDUE CONS/COMM TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){

                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature* f = entryprot->getFeature(j);

                            if(f->getResidueColigated() == "") out << "UNKNOWN ";
                            else out << f->getResidueColigated().c_str() << " ";

                            if(f->getAgregate() == 0) out << "CONS ";
                            else if(f->getAgregate() > 0) out << f->getAgregate() << " ";
                            else out << "UNKNOWN ";

                            if(f->getType() == "") out << "NONE ";
                            else out << f->getType().c_str() << " ";

                            if(f->getDescription() == "") out << "NONE ";
                            else out << f->getDescription().c_str() << " ";

                            if(f->getPosition() == -1) out << "NONE ";
                            else out << f->getPosition() << " ";

                            if(f->getBegin() == -1) out << "NONE ";
                            else out << f->getBegin() << " ";

                            if(f->getEnd() == -1) out << "NONE ";
                            else out << f->getEnd() << " ";

                            if(f->getOriginal() == "") out << "NONE ";
                            else out << f->getOriginal().c_str() << " ";

                            if(f->getVariation() == "") out << "NONE";
                            else out << f->getVariation().c_str();

                            out << "\n";
                        }

                    }

                }
                f.close();
            }
            break;
        }
        case 1:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature* f = entryprot->getFeature(j);

                            if(f->getResidueColigated() == "") out << "UNKNOWN,";
                            else out << f->getResidueColigated().c_str() << ",";

                            if(f->getAgregate() == 0) out << "CONS,";
                            else if(f->getAgregate() > 0) out << f->getAgregate() << ",";
                            else out << "UNKNOWN,";

                            if(f->getType() == "") out << "NONE,";
                            else out << f->getType().c_str() << ",";

                            if(f->getDescription() == "") out << "NONE,";
                            else out << f->getDescription().c_str() << ",";

                            if(f->getPosition() == -1) out << "NONE,";
                            else out << f->getPosition() << ",";

                            if(f->getBegin() == -1) out << "NONE,";
                            else out << f->getBegin() << ",";

                            if(f->getEnd() == -1) out << "NONE,";
                            else out << f->getEnd() << ",";

                            if(f->getOriginal() == "") out << "NONE,";
                            else out << f->getOriginal().c_str() << ",";

                            if(f->getVariation() == "") out << "NONE";
                            else out << f->getVariation().c_str();

                            out << "\n";
                        }

                    }

                }
                f.close();
            }

            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                out << "\t<protein name=\"" << protName.c_str() << "\" ";

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        if(entryprot->getDataset() == 0) out << "dataset=\"Swiss-Prot\">\n";
                        else out << "dataset=\"TrEMBL\">\n";
                        break;
                    }
                }

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature *f = entryprot->getFeature(j);

                            if(f->getAgregate() == 0) out << "\t\t<feature agregate=\"CONS\" ";
                            else out << "\t\t<feature agregate=\"" << f->getAgregate() << "\" ";

                            if(f->getType() != "")
                                out << "type=\"" << f->getType().c_str() << "\" ";
                            if(f->getDescription() != "")
                                out << "description=\"" << f->getDescription().c_str() << "\" ";
                            if(f->getId() != "")
                                out << "id=\"" << f->getId().c_str() << "\" ";
                            out << ">\n";

                            if(f->getOriginal() != "")
                                out << "\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                            if(f->getVariation() != "")
                                out << "\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                            if(f->getBegin() != -1 || f->getPosition() != -1){
                                out << "\t\t\t<location>\n";

                                if(f->getPosition() != -1)
                                    out << "\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                                if(f->getBegin() != -1 && f->getEnd() != -1){
                                    out << "\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                                    out << "\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                                }

                                out << "\t\t\t</location>\n";
                            }

                            out << "\t\t</feature>\n";
                        }

                    }
                }

                out << "\t</protein>\n";
            }

            out << "</PFStats>";
            f.close();

            break;
        }
        case 3:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".html";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n<body>\n<table border=1>\n<center>\n";
                out << "<tr>\n";
                out << "<th>Residue</th>\n";
                out << "<th>Communitie</th>\n";
                out << "<th>Type</th>\n";
                out << "<th>Description</th>\n";
                out << "<th>Position</th>\n";
                out << "<th>Begin</th>\n";
                out << "<th>End</th>\n";
                out << "<th>Original</th>\n";
                out << "<th>Variation</th>\n";
                out << "</tr>\n";

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            out << "<tr>\n";

                            Feature* f = entryprot->getFeature(j);

                            out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";

                            if(f->getAgregate() == 0) out << "<td>CONS</td>\n";
                            else if(f->getAgregate() > 0) out << "<td>" << f->getAgregate() << "</td>\n";
                            else out << "<td>UNKNOWN</td>\n";

                            if(f->getType() == "") out << "<td>NONE</td>\n";
                            else out << "<td>" << f->getType().c_str() << "</td>\n";

                            if(f->getDescription() == "") out << "<td>NONE</td>\n";
                            else out << "<td>" << f->getDescription().c_str() << "</td>\n";

                            if(f->getPosition() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getPosition() << "</td>\n";

                            if(f->getBegin() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getBegin() << "</td>\n";

                            if(f->getEnd() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getEnd() << "</td>\n";

                            if(f->getOriginal() == "") out << "<td></td>\n";
                            else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                            if(f->getVariation() == "") out << "<td></td>\n";
                            else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                            out << "</tr>\n";
                        }

                    }

                }
                out << "</body>\n</html>";
                f.close();

            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Uniprot Mined data was exported succesfully.");
}

void Filter::exportLookComm(QString filename, int type){
    switch(type){
        case 0:
        {
            //COMMS
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
                        out << resFeats[k]->getName().c_str() << " ";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << " ";
                        else out << "UNKNOWN ";

                        if(f->getType() != "") out << f->getType().c_str() << " ";
                        else out << "NONE ";

                        if(f->getDescription() != "") out << f->getDescription().c_str() << " ";
                        else out << "NONE ";

                        if(f->getPosition() == -1) out << "NONE ";
                        else out << f->getPosition() << " ";

                        if(f->getBegin() == -1) out << "NONE ";
                        else out << f->getBegin() << " ";

                        if(f->getEnd() == -1) out << "NONE ";
                        else out << f->getEnd() << " ";

                        if(f->getOriginal() == "") out << "NONE ";
                        else out << f->getOriginal().c_str() << " ";

                        if(f->getVariation() == "") out << "NONE";
                        else out << f->getVariation().c_str();

                        out << "\n";

                    }

                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes(cons_min);

            for(unsigned int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
                    out << resFeats[k]->getName().c_str() << " ";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << " ";
                    else out << "UNKNOWN ";

                    if(f->getType() != "") out << f->getType().c_str() << " ";
                    else out << "NONE ";

                    if(f->getDescription() != "") out << f->getDescription().c_str() << " ";
                    else out << "NONE ";

                    if(f->getPosition() == -1) out << "NONE ";
                    else out << f->getPosition() << " ";

                    if(f->getBegin() == -1) out << "NONE ";
                    else out << f->getBegin() << " ";

                    if(f->getEnd() == -1) out << "NONE ";
                    else out << f->getEnd() << " ";

                    if(f->getOriginal() == "") out << "NONE ";
                    else out << f->getOriginal().c_str() << " ";

                    if(f->getVariation() == "") out << "NONE";
                    else out << f->getVariation().c_str();

                    out << "\n";

                }

                f.close();
            }

            break;
        }
        case 1:
        {
            //COMM
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".csv";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
                        out << resFeats[k]->getName().c_str() << ",";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << ",";
                        else out << "UNKNOWN,";

                        if(f->getType() != "") out << f->getType().c_str() << ",";
                        else out << "NONE,";

                        if(f->getDescription() != "") out << f->getDescription().c_str() << ",";
                        else out << "NONE,";

                        if(f->getPosition() == -1) out << "NONE,";
                        else out << f->getPosition() << ",";

                        if(f->getBegin() == -1) out << "NONE,";
                        else out << f->getBegin() << ",";

                        if(f->getEnd() == -1) out << "NONE,";
                        else out << f->getEnd() << ",";

                        if(f->getOriginal() == "") out << "NONE,";
                        else out << f->getOriginal().c_str() << ",";

                        if(f->getVariation() == "") out << "NONE";
                        else out << f->getVariation().c_str();

                        out << "\n";

                    }

                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes(cons_min);

            for(unsigned int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
                    out << resFeats[k]->getName().c_str() << ",";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << ",";
                    else out << "UNKNOWN,";

                    if(f->getType() != "") out << f->getType().c_str() << ",";
                    else out << "NONE,";

                    if(f->getDescription() != "") out << f->getDescription().c_str() << ",";
                    else out << "NONE,";

                    if(f->getPosition() == -1) out << "NONE,";
                    else out << f->getPosition() << ",";

                    if(f->getBegin() == -1) out << "NONE,";
                    else out << f->getBegin() << ",";

                    if(f->getEnd() == -1) out << "NONE,";
                    else out << f->getEnd() << ",";

                    if(f->getOriginal() == "") out << "NONE,";
                    else out << f->getOriginal().c_str() << ",";

                    if(f->getVariation() == "") out << "NONE";
                    else out << f->getVariation().c_str();

                    out << "\n";

                }

                f.close();
            }


            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            //COMM
            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    out << "\t\t<residue alignN=\"" << comunidades[i][j].c_str() << "\">\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
                        out << "\t\t\t<feature ";
                        out << "protein=\"" << resFeats[k]->getName().c_str() << "\" ";

                        if(resFeats[k]->getDataset() == 0) out << "dataset=\"Swiss-Prot\" ";
                        else out << "dataset=\"TrEMBL\" ";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getType() != "")
                            out << "type=\"" << f->getType().c_str() << "\" ";
                        if(f->getDescription() != "")
                            out << "description=\"" << f->getDescription().c_str() << "\" ";
                        if(f->getId() != "")
                            out << "id=\"" << f->getId().c_str() << "\" ";
                        out << ">\n";

                        if(f->getOriginal() != "")
                            out << "\t\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                        if(f->getVariation() != "")
                            out << "\t\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                        if(f->getBegin() != -1 || f->getPosition() != -1){
                            out << "\t\t\t\t<location>\n";

                            if(f->getPosition() != -1)
                                out << "\t\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                            if(f->getBegin() != -1 && f->getEnd() != -1){
                                out << "\t\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                                out << "\t\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                            }

                            out << "\t\t\t\t</location>\n";
                        }

                        out << "\t\t\t</feature>\n";
                    }

                    out << "\t\t</residue>\n";
                }

                out << "\t</community>\n";
            }

            //CONS
            vector<string> residues = this->getConsRes(cons_min);

            out << "\t<community id=\"CONS\">\n";

            for(unsigned int i = 0; i < residues.size(); i++){
                out << "\t\t<residue alignN=\"" << residues[i].c_str() << "\">\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
                    out << "\t\t\t<feature ";
                    out << "protein=\"" << resFeats[k]->getName().c_str() << "\" ";

                    if(resFeats[k]->getDataset() == 0) out << "dataset=\"Swiss-Prot\" ";
                    else out << "dataset=\"TrEMBL\" ";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getType() != "")
                        out << "type=\"" << f->getType().c_str() << "\" ";
                    if(f->getDescription() != "")
                        out << "description=\"" << f->getDescription().c_str() << "\" ";
                    if(f->getId() != "")
                        out << "id=\"" << f->getId().c_str() << "\" ";
                    out << ">\n";

                    if(f->getOriginal() != "")
                        out << "\t\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                    if(f->getVariation() != "")
                        out << "\t\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                    if(f->getBegin() != -1 || f->getPosition() != -1){
                        out << "\t\t\t\t<location>\n";

                        if(f->getPosition() != -1)
                            out << "\t\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                        if(f->getBegin() != -1 && f->getEnd() != -1){
                            out << "\t\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                            out << "\t\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                        }

                        out << "\t\t\t\t</location>\n";
                    }

                    out << "\t\t\t</feature>\n";
                }

                out << "\t\t</residue>\n";
            }

            out << "\t</community>\n";
            out << "</PFStats>";

            f.close();
            break;
        }
        case 3:
        {
            //COMM
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n<body>\n<table border=1>\n<center>\n";
                    out << "<tr>\n";
                    out << "<th>Protein</th>\n";
                    out << "<th>Seq. Number</th>\n";
                    out << "<th>Type</th>\n";
                    out << "<th>Description</th>\n";
                    out << "<th>Position</th>\n";
                    out << "<th>Begin</th>\n";
                    out << "<th>End</th>\n";
                    out << "<th>Original</th>\n";
                    out << "<th>Variation</th>\n";
                    out << "</tr>\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
                        out << "<tr>\n";

                        out << "<td>" << resFeats[k]->getName().c_str() << "</td>\n";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";
                        else out << "<td>UNKNOWN</td>";

                        if(f->getType() != "") out << "<td>" << f->getType().c_str() << "</td>\n";
                        else out << "<td>NONE</td>";

                        if(f->getDescription() != "") out << "<td>" << f->getDescription().c_str() << "</td>\n";
                        else out << "<td>NONE</td>\n";

                        if(f->getPosition() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getPosition() << "</td>\n";

                        if(f->getBegin() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getBegin() << "</td>\n";

                        if(f->getEnd() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getEnd() << "</td>\n";

                        if(f->getOriginal() == "") out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                        if(f->getVariation() == "") out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                        out << "<tr>\n";

                    }

                    out << "</body>\n</html>";
                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes(cons_min);

            for(unsigned int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n<body>\n<table border=1>\n<center>\n";
                out << "<tr>\n";
                out << "<th>Protein</th>\n";
                out << "<th>Seq. Number</th>\n";
                out << "<th>Type</th>\n";
                out << "<th>Description</th>\n";
                out << "<th>Position</th>\n";
                out << "<th>Begin</th>\n";
                out << "<th>End</th>\n";
                out << "<th>Original</th>\n";
                out << "<th>Variation</th>\n";
                out << "</tr>\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
                    out << "<tr>\n";

                    out << "<td>" << resFeats[k]->getName().c_str() << "</td>\n";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";
                    else out << "<td>UNKNOWN</td>";

                    if(f->getType() != "") out << "<td>" << f->getType().c_str() << "</td>\n";
                    else out << "<td>NONE</td>";

                    if(f->getDescription() != "") out << "<td>" << f->getDescription().c_str() << "</td>\n";
                    else out << "<td>NONE</td>\n";

                    if(f->getPosition() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getPosition() << "</td>\n";

                    if(f->getBegin() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getBegin() << "</td>\n";

                    if(f->getEnd() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getEnd() << "</td>\n";

                    if(f->getOriginal() == "") out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                    if(f->getVariation() == "") out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                    out << "<tr>\n";

                }

                out << "</body>\n</html>";
                f.close();

            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Uniprot Mined data was exported succesfully.");
}

vector<Uniprot *> Filter::getAllResidueFeatures(string res){
    vector<Uniprot*> outVec;

    for(unsigned int i = 0; i < uniprotMined.size(); i++){
        for(int j = 0; j < uniprotMined[i]->countFeatures(); j++){
            Feature *f = uniprotMined[i]->getFeature(j);

            if(f->getAlignResidue() == res){
                //QMessageBox::information(NULL,"a","OK");
                Uniprot *entry = new Uniprot();
                entry->setDataset(uniprotMined[i]->getDataset());
                entry->setName(uniprotMined[i]->getName());
                entry->addFeature(f);
                outVec.push_back(entry);
            }
        }
    }

    return outVec;
}

unsigned int Filter::getMinssVectorSize(){
    return minssData.size();
}

string Filter::getRefSeqName(){
    return refSeqName;
}

void Filter::setRefSeqName(string ref){
    refSeqName = ref;
}

string Filter::getSequence(string seqname){
    for(unsigned int i = 0; i < sequencenames.size(); i++){
        if(sequencenames[i] == seqname) return sequences[i];
    }
    return "";
}

string Filter::getUniprotFunction(int i){
    return uniprotMined[i]->getFunction();
}

Feature* Filter::getUniprotFeature(int i, int j){
    return uniprotMined[i]->getFeature(j);
}

unsigned int Filter::getDeltasSize(){
    return Deltas.size();
}

void Filter::addDeltaLine(vector<float> line){
    Deltas.push_back(line);
}

string Filter::generateXML(){
    string xml = "";

    xml += "\t<filter name='" + name + "' type='" + typeToString() + "' taxon='" + taxon + "' occ='"
            + QString::number(minOcc).toStdString() + "' minid='" + QString::number(minId).toStdString() + "' maxid='" + QString::number(maxId).toStdString()
            + "' refseq='" + refSeq + "' alphabet='" + alphabet + "' >\n";

    xml += "\t\t<seqlist>\n";

    for(unsigned int i = 0; i < sequences.size(); i++){
        xml += "\t\t<sequence id='" + to_string(i+1) + "' name='" + sequencenames[i] + "'>" + sequences[i] + "</sequence>\n";
    }

    xml += "\t\t</seqlist>\n";

    if(refseqs.size() > 0){
        xml += "\t<references>\n";

        for(unsigned int i = 0; i < refseqs.size(); i++){
            xml += "\t\t<sequence>" + refseqs[i] + "</sequence>\n";
        }

        xml += "\t</references>\n";
    }

    if(consDG.size() > 0){
        xml += "\t<conservation>\n";

        xml += "\t\t<parameters>\n";

        if(conservedPDBpath != "") xml += "\t\t\t<pdb>" + conservedPDBpath + "</pdb>\n";
        xml += "\t\t\t<minimum>" + QString::number(cons_min).toStdString() + "</minimum>\n";

        xml += "\t\t</parameters>\n";

        xml += "\t\t<positions>\n";

        for(unsigned int i = 0; i < consDG.size(); i++){
            xml += "\t\t\t<pos id='" + to_string(i+1) + "'>\n";
            xml += "\t\t\t<deltaG>" + QString::number(consDG[i],'f',4).toStdString() + "</deltaG>\n";
            xml += "\t\t\t<GAP>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][0]) + "</frequence>\n";
            xml += "\t\t\t</GAP>\n";
            xml += "\t\t\t<ALA>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][1]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][0],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</ALA>\n";
            xml += "\t\t\t<CYS>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][2]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][1],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</CYS>\n";
            xml += "\t\t\t<ASP>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][3]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][2],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</ASP>\n";
            xml += "\t\t\t<GLU>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][4]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][3],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</GLU>\n";
            xml += "\t\t\t<PHE>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][5]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][4],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</PHE>\n";
            xml += "\t\t\t<GLY>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][6]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][5],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</GLY>\n";
            xml += "\t\t\t<HIS>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][7]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][6],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</HIS>\n";
            xml += "\t\t\t<ILE>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][8]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][7],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</ILE>\n";
            xml += "\t\t\t<LYS>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][9]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][8],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</LYS>\n";
            xml += "\t\t\t<LEU>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][10]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][9],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</LEU>\n";
            xml += "\t\t\t<MET>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][11]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][10],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</MET>\n";
            xml += "\t\t\t<ASN>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][12]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][11],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</ASN>\n";
            xml += "\t\t\t<PRO>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][13]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][12],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</PRO>\n";
            xml += "\t\t\t<GLN>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][14]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][13],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</GLN>\n";
            xml += "\t\t\t<ARG>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][15]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][14],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</ARG>\n";
            xml += "\t\t\t<SER>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][16]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][15],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</SER>\n";
            xml += "\t\t\t<THR>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][17]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][16],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</THR>\n";
            xml += "\t\t\t<VAL>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][18]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][17],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</VAL>\n";
            xml += "\t\t\t<TRP>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][19]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][18],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</TRP>\n";
            xml += "\t\t\t<TYR>\n";
            xml += "\t\t\t\t<frequence>" + to_string(consvfreq[i][20]) + "</frequence>\n";
            xml += "\t\t\t\t<percent>" + QString::number(consfreqPerc[i][19],'f',3).toStdString() + "</percent>\n";
            xml += "\t\t\t</TYR>\n";
            xml += "   </pos>\n";
        }

        xml += "\t\t</positions>\n";

        xml += "\t</conservation>\n";
    }

    if(minssData.size() > 0){
        xml += "\t<minss>\n";

        for(unsigned int i = 0; i < minssData.size(); i++){
            xml += "\t\t<data id='" + to_string(i+1) + "'>" + QString::number(minssData[99-i],'f',6).toStdString() + "</data>\n";
        }

        xml += "\t</minss>\n";
    }

    if(corrGraph.size() > 0){
        xml += "\t<correlation>\n";

        xml += "\t\t<parameters>\n";

        if(commPDBPath != "") xml += "\t\t\t<pdb>" + commPDBPath + "</pdb>\n";
        xml += "\t\t\t<min_score>" + QString::number(corr_min_score).toStdString() + "</min_score>\n";
        xml += "\t\t\t<minss>" + QString::number(corr_minssfraction).toStdString() + "</minss>\n";
        xml += "\t\t\t<min_delta>" + QString::number(corr_min_delta).toStdString() + "</min_delta>\n";
        xml += "\t\t\t<refseq>" + QString::number(corr_refseq).toStdString() + "</refseq>\n";

        xml += "\t\t</parameters>\n";

        xml += "\t\t<graph>\n";

        for(unsigned int i = 0; i < corrGraph.size(); i++){
            string v1 = std::get<0>(corrGraph[i]);
            string v2 = std::get<1>(corrGraph[i]);
            int val = std::get<2>(corrGraph[i]);

            xml += "\t\t\t<edge v1='" + v1 + "' v2='" + v2 + "'>" + to_string(val) + "</edge>\n";
        }

        xml += "\t\t</graph>\n";

        if(comunidades.size() > 0){
            xml += "\t\t<communities>\n";

            for(unsigned int i = 0; i < comunidades.size(); i++){
                xml += "\t\t\t<community id='" + to_string(i+1) + "'>\n";

                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    xml += "\t\t\t\t<node>" + comunidades[i][j] + "</node>\n";
                }

                 xml += "\t\t\t</community>\n";
            }


            xml += "\t\t</communities>\n";
        }

        if(communityX.size() > 0 || communityXps.size() > 0){
            xml += "\t\t<output>\n";

            for(unsigned int i = 0; i < communityX.size(); i++){
                xml += "\t\t\t<community id='" + to_string(i+1) + "'>\n";

                xml += "\t\t\t\t<table>\n";
                xml += "\t\t\t\t\t<column>ALL</column>\n";
                for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                    xml += "\t\t\t\t\t<column>" + residuesComm[i][j] + "</column>\n";
                }

                xml += "\t\t\t\t</table>\n";

                xml += "\t\t\t\t<table_data>\n";

                for(unsigned int j = 0; j < communityX[i].size(); j++){
                    xml += "\t\t\t\t\t<row id='" + to_string(j) + "' c0='" + QString::number(communityXAll[i][j],'f',4).toStdString() + "' ";
                    for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                        if(j==k) xml += "c" + to_string(k+1) + "='X' ";
                        else xml += "c" + to_string(k+1) + "='" + QString::number(communityX[i][j][k]*100,'f',4).toStdString() + "' ";
                    }
                    xml += "/>\n";
                }

                xml += "\t\t\t\t</table_data>\n";
                xml += "\t\t\t</community>\n";
            }

            for(unsigned int i = 0; i < communityXps.size(); i++){
                xml += "\t\t\t<logP c='" + to_string(i+1) + "'>\n";
                xml += "\t\t\t\t<table>\n";

                for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                    xml += "\t\t\t\t\t<column>" + residuesCommPs[i][j] + "</column>\n";
                }

                xml += "\t\t\t\t</table>\n";

                xml += "\t\t\t\t<table_data>\n";

                for(unsigned int j = 0; j < communityXps[i].size(); j++){
                    xml += "\t\t\t\t\t<row id='" + to_string(j) + "' ";
                    for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                        if(j==k)xml += "c" + to_string(k) + "='X' ";
                        else xml += "c" + to_string(k) + "='" + to_string(communityXps[i][j][k]) + "' ";
                    }
                    xml += "/>\n";
                }

                xml += "\t\t\t\t</table_data>\n";

                xml += "\t\t\t</logP>\n";
            }

            xml += "\t\t</output>\n";
        }

        if(Deltas.size() > 0){
            xml += "\t\t<deltas>\n";

            for(unsigned int i = 0; i < Deltas.size(); i++){
                xml += "\t\t\t<row comm='" + to_string(i+1) + "' ";
                for(unsigned int j = 0; j < Deltas.size(); j++){
                    if(i == j) xml += "val" + to_string(j+1) + "='0.00' ";
                    else{
                        xml += "val" + to_string(j+1) + "='" + QString::number(Deltas[i][j],'f',4).toStdString() + "' ";
                    }
                }
                xml += "/>\n";
            }

            xml += "\t\t</deltas>\n";
        }

        xml += "\t</correlation>\n";
    }

    xml += "\t</filter>\n";

    return xml;
}

bool Filter::henikoffWeights(){
    vector<string> aa_list;
    int length = sequences[0].size();

    weights.clear();

    int progressCount = 0;
    QProgressDialog progress("Creating the list of alphabets...(1/3)", "Abort", 0,length);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    //Make the list of aa types per position
    for(unsigned int j = 0; j < length; j++){
        set<char> types;

        progressCount++;
        progress.setValue(progressCount);
        if(progress.wasCanceled()){
            weights.clear();
            return false;
        }

        for(unsigned int i = 0; i < sequences.size(); i++){
            types.insert(sequences[i][j]);

            if(progress.wasCanceled()){
                weights.clear();
                return false;
            }
        }
        string str = "";
        for(auto c : types){
            str += c;
        }
        aa_list.push_back(str);
    }

    progress.setLabelText("Calculating occurrences...(2/3)");
    progress.setMaximum(aa_list.size());
    progress.setValue(0);

    vector<map<char,int> > occurences;
    for(unsigned int i = 0; i < aa_list.size(); i++){
        progressCount++;
        progress.setValue(progressCount);
        if(progress.wasCanceled()){
            return false;
        }

        string aas = aa_list[i];
        map<char,int> aa_count;
        for(unsigned int j = 0; j < aas.size(); j++){
            char aa = aas[j];
            int count = 0;
            for(unsigned int k = 0; k < sequences.size(); k++){
                if(progress.wasCanceled()){
                    return false;
                }

                if(sequences[k][i] == aa) count++;
            }
            aa_count[aa] = count;
        }
        occurences.push_back(aa_count);
    }

    progress.setLabelText("Calculating weights...(3/3)");
    progress.setMaximum(sequences.size());
    progress.setValue(0);
    for(unsigned int i = 0; i < sequences.size(); i++){
        progressCount++;
        progress.setValue(progressCount);
        if(progress.wasCanceled()){
            return false;
        }

        float sum_w = 0.0;
        for(unsigned int j = 0; j < sequences[0].size(); j++){
            if(progress.wasCanceled()){
                return false;
            }

            int k = aa_list[j].size();
            int n = occurences[j][sequences[i][j]];
            float temp = 1/((float)k*(float)n);
            sum_w += temp;
        }
        weights.push_back(sum_w/(float)length);
    }

    /*
    //Para cada sequencia ele vai dar um peso
    for(unsigned int i = 0; i < sequences.size(); i++){
        float sum = 0;

        progressCount++;
        progress.setValue(progressCount);
        if(progress.wasCanceled()){
            weights.clear();
            return false;
        }

        //Percorrer colunas para somar
        for(unsigned j = 0; j < length; j++){
            char actualAA = sequences[i][j];

            if(progress.wasCanceled()){
                weights.clear();
                return false;
            }

            //Conta quantas vezes este AA esta presente na coluna
            int nxi = countAA(actualAA,j);
            float calc = (float)1/((float)typesCount[j]*(float)nxi);
            sum += calc;
        }
        weights.push_back(sum/(float)length);
    }
    */
    //for(unsigned int i = 0; i < sequences.size(); i++){
    //    printf("%s - %f\n",sequencenames[i].c_str(), weights[i]);
    //}

    progress.close();
    return true;
}

void Filter::addConsFreqRow(vector<int> row){
    this->consvfreq.push_back(row);
}

void Filter::addConsFreqPercRow(vector<float> row){
    this->consfreqPerc.push_back(row);
}

void Filter::printConsFreq(){
    for(unsigned int i = 0; i < consvfreq.size(); i++){
        for(unsigned int j = 0; j < consvfreq[i].size(); j++){
            printf(" %d ",consvfreq[i][j]);
        }
        printf("\n");
    }
}

void Filter::printConsFreqPerc(){
    for(unsigned int i = 0; i < consfreqPerc.size(); i++){
        for(unsigned int j = 0; j < consfreqPerc[i].size(); j++){
            printf(" %f ",consfreqPerc[i][j]);
        }
        printf("\n");
    }
}

void Filter::setConsDG(vector<float> dg){
    this->consDG = dg;
}

int Filter::getDGsize(){
    return consDG.size();
}

float Filter::getDGPosition(int i){
    return consDG[i];
}

void Filter::setMinss(vector<float> data){
    this->minssData = data;
}

void Filter::addCorrEdge(string v1, string v2, int score){
    tuple<string,string,int> node(v1,v2,score);

    this->corrGraph.push_back(node);
}

void Filter::addResiduesComm(vector<string> residues){
    this->residuesComm.push_back(residues);
}

void Filter::addCommXAll(vector<float> resAll){
    this->communityXAll.push_back(resAll);
}

void Filter::addCommX(vector<vector<float> > commX){
    this->communityX.push_back(commX);
}

void Filter::addResiduesCommPs(vector<string> residuesPs){
    this->residuesCommPs.push_back(residuesPs);
}

void Filter::addCommXPs(vector<vector<int> > commXPs){
    this->communityXps.push_back(commXPs);
}

void Filter::updateCommunitiesData(){
    Communities.clear();
    tempcommunity.pos.clear();
    tempcommunity.aa.clear();

    for(unsigned int i = 0; i < comunidades.size(); i++){
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            string node = comunidades[i][j];

            tempcommunity.aa.push_back(node[0]);

            string tempPos = node.substr(1);

            tempcommunity.pos.push_back(atoi(tempPos.c_str())-1);
        }

        if(comunidades[i].size() > 0)
            Communities.push_back(tempcommunity);

        tempcommunity.aa.clear();
        tempcommunity.pos.clear();
    }
}

void Filter::updateSequencesData(){
    SortOrder.clear();
    subsetfrequencies.clear();

    if(sequences.size()>0){
        for (unsigned int i = 0; i < sequences.size(); i++)
            SortOrder.push_back(i);

        for(unsigned int i = 0; i <= sequences[0].size(); i++){ // total positions: sequencesize + 1 (positions + totals)
            subsetfrequencies.push_back( vector<int>(21) );
            for(unsigned int j = 0; j <= 20; j++)
                subsetfrequencies[i].push_back(0);
        }
    }
}

string Filter::getResidueColor(string residue){
    for(unsigned int i = 0; i < comunidades.size(); i++){
        if(comunidades[i].size() > 1){
            for(unsigned int j = 0; j < comunidades[i].size(); j++){
                if(comunidades[i][j] == residue) return c->getColor(i);
            }
        }else return "";
    }

    return "";
}

vector<string> Filter::getReducedSequences(string alphabet){
    vector<string> oldChars;
    vector<char> newChars;

    if(alphabet == "T2"){
        oldChars.push_back("AGTSNQDEHRKP");
        newChars.push_back('P');
        oldChars.push_back("CMFILVWY");
        newChars.push_back('Y');
    }else if(alphabet == "T5"){
        oldChars.push_back("IVL");
        newChars.push_back('I');
        oldChars.push_back("FYWH");
        newChars.push_back('F');
        oldChars.push_back("KRDE");
        newChars.push_back('K');
        oldChars.push_back("GACS");
        newChars.push_back('G');
        oldChars.push_back("TMQNP");
        newChars.push_back('T');
    }else if(alphabet == "T6"){
        oldChars.push_back("IVL");
        newChars.push_back('I');
        oldChars.push_back("FYWH");
        newChars.push_back('F');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("DE");
        newChars.push_back('D');
        oldChars.push_back("GACS");
        newChars.push_back('G');
        oldChars.push_back("TMQNP");
        newChars.push_back('T');
    }else if(alphabet == "3IMG"){
        oldChars.push_back("IVLFCMAW");
        newChars.push_back('I');
        oldChars.push_back("GTSYPH");
        newChars.push_back('G');
        oldChars.push_back("DNEQKR");
        newChars.push_back('D');
    }else if(alphabet == "5IMG"){
        oldChars.push_back("GAS");
        newChars.push_back('G');
        oldChars.push_back("CDPNT");
        newChars.push_back('C');
        oldChars.push_back("EVQH");
        newChars.push_back('E');
        oldChars.push_back("MILKR");
        newChars.push_back('M');
        oldChars.push_back("FYW");
        newChars.push_back('F');
    }else if(alphabet == "11IMG"){
        oldChars.push_back("AVIL");
        newChars.push_back('A');
        oldChars.push_back("F");
        newChars.push_back('F');
        oldChars.push_back("CM");
        newChars.push_back('C');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("W");
        newChars.push_back('W');
        oldChars.push_back("Y");
        newChars.push_back('Y');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("DE");
        newChars.push_back('D');
        oldChars.push_back("NQ");
        newChars.push_back('N');
        oldChars.push_back("HKR");
        newChars.push_back('H');
    }else if(alphabet == "Murphy15"){
        oldChars.push_back("LVIM");
        newChars.push_back('L');
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("A");
        newChars.push_back('A');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("S");
        newChars.push_back('S');
        oldChars.push_back("T");
        newChars.push_back('T');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FY");
        newChars.push_back('F');
        oldChars.push_back("W");
        newChars.push_back('W');
        oldChars.push_back("E");
        newChars.push_back('E');
        oldChars.push_back("D");
        newChars.push_back('D');
        oldChars.push_back("N");
        newChars.push_back('N');
        oldChars.push_back("Q");
        newChars.push_back('Q');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');
    }else if(alphabet == "Murphy10"){
        oldChars.push_back("LVIM");
        newChars.push_back('L');
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("A");
        newChars.push_back('A');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQ");
        newChars.push_back('E');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');
    }else if(alphabet == "Murphy8"){
        oldChars.push_back("LVIMC");
        newChars.push_back('L');
        oldChars.push_back("AG");
        newChars.push_back('A');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQ");
        newChars.push_back('E');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');
    }else if(alphabet == "Murphy4"){
        oldChars.push_back("LVIMC");
        newChars.push_back('L');
        oldChars.push_back("AGSTP");
        newChars.push_back('A');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQKRH");
        newChars.push_back('E');
    }else if(alphabet == "Murphy2"){
        oldChars.push_back("LVIMCAGSTPFYW");
        newChars.push_back('P');
        oldChars.push_back("EDNQKRH");
        newChars.push_back('E');
    }else if(alphabet == "Wang5"){
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATH");
        newChars.push_back('A');
        oldChars.push_back("GP");
        newChars.push_back('G');
        oldChars.push_back("DE");
        newChars.push_back('E');
        oldChars.push_back("SNQRK");
        newChars.push_back('K');
    }else if(alphabet == "Wang5v"){
        oldChars.push_back("CMFI");
        newChars.push_back('I');
        oldChars.push_back("LVWY");
        newChars.push_back('L');
        oldChars.push_back("ATGS");
        newChars.push_back('A');
        oldChars.push_back("NQDE");
        newChars.push_back('E');
        oldChars.push_back("HPRK");
        newChars.push_back('K');
    }else if(alphabet == "Wang3"){
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATHGPR");
        newChars.push_back('A');
        oldChars.push_back("DESNQK");
        newChars.push_back('E');
    }else if(alphabet == "Wang2"){
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATHGPRDESNQK");
        newChars.push_back('A');
    }else if(alphabet == "Li10"){
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("FYW");
        newChars.push_back('Y');
        oldChars.push_back("ML");
        newChars.push_back('L');
        oldChars.push_back("IV");
        newChars.push_back('V');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("ATS");
        newChars.push_back('S');
        oldChars.push_back("NH");
        newChars.push_back('N');
        oldChars.push_back("QED");
        newChars.push_back('E');
        oldChars.push_back("RK");
        newChars.push_back('K');
    }else if(alphabet == "Li5"){
        oldChars.push_back("CFYW");
        newChars.push_back('Y');
        oldChars.push_back("MLIV");
        newChars.push_back('I');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("PATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('N');
    }else if(alphabet == "Li4"){
        oldChars.push_back("CFYW");
        newChars.push_back('Y');
        oldChars.push_back("MLIV");
        newChars.push_back('I');
        oldChars.push_back("GPATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('E');
    }else if(alphabet == "Li3"){
        oldChars.push_back("CFYWMLIV");
        newChars.push_back('I');
        oldChars.push_back("GPATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('E');
    }

    Filter* filter = new Filter();
    filter->addSequences(sequencenames,sequences);
    filter->applyAlphabetReduction(oldChars,newChars);
    return filter->sequences;
}

char Filter::getReducedAminoAcid(char c, string alphabet){
    if(alphabet != "T2" && alphabet != "T5" && alphabet != "T6" && alphabet != "3IMG" && alphabet != "5IMG"
            && alphabet != "11IMG" && alphabet != "Murphy15" && alphabet != "Murphy10" && alphabet != "Murphy8"
            && alphabet != "Murphy4" && alphabet != "Murphy2" && alphabet != "Wang5" && alphabet != "Wang5v"
            && alphabet != "Wang3" && alphabet != "Wang2" && alphabet != "Li10" && alphabet != "Li5"
            && alphabet != "Li4" && alphabet != "Li3") return 'X';
    else{
        if(alphabet == "T2"){
            string a1 = "AGTSNQDEHRKP";
            string a2 = "CMFILVWY";
            if(a1.find(c) != std::string::npos) return 'P';
            else if(a2.find(c) != std::string::npos) return 'Y';
        }else if(alphabet == "T5"){
            string a1 = "IVL";
            string a2 = "FYWH";
            string a3 = "KRDE";
            string a4 = "GACS";
            string a5 = "TMQNP";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'F';
            else if(a3.find(c) != std::string::npos) return 'K';
            else if(a4.find(c) != std::string::npos) return 'G';
            else if(a5.find(c) != std::string::npos) return 'T';
        }else if(alphabet == "T6"){
            string a1 = "IVL";
            string a2 = "FYWH";
            string a3 = "KR";
            string a4 = "DE";
            string a5 = "GACS";
            string a6 = "TMQNP";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'F';
            else if(a3.find(c) != std::string::npos) return 'K';
            else if(a4.find(c) != std::string::npos) return 'D';
            else if(a5.find(c) != std::string::npos) return 'G';
            else if(a6.find(c) != std::string::npos) return 'T';
        }else if(alphabet == "3IMG"){
            string a1 = "IVLFCMAW";
            string a2 = "GTSYPH";
            string a3 = "DNEQKR";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'G';
            else if(a3.find(c) != std::string::npos) return 'D';
        }else if(alphabet == "5IMG"){
            string a1 = "GAS";
            string a2 = "CDPNT";
            string a3 = "EVQH";
            string a4 = "MILKR";
            string a5 = "FYW";
            if(a1.find(c) != std::string::npos) return 'G';
            else if(a2.find(c) != std::string::npos) return 'C';
            else if(a3.find(c) != std::string::npos) return 'E';
            else if(a4.find(c) != std::string::npos) return 'M';
            else if(a5.find(c) != std::string::npos) return 'F';
        }else if(alphabet == "11IMG"){
            string a1 = "HKR";
            string a2 = "AVIL";
            string a3 = "CM";
            string a4 = "ST";
            string a5 = "DE";
            string a6 = "NQ";
            if(a1.find(c) != std::string::npos) return 'H';
            else if(a2.find(c) != std::string::npos) return 'A';
            else if(c == 'F') return 'F';
            else if(a3.find(c) != std::string::npos) return 'C';
            else if(c == 'G') return 'G';
            else if(a4.find(c) != std::string::npos) return 'S';
            else if(c == 'W') return 'W';
            else if(c == 'Y') return 'Y';
            else if(c == 'P') return 'P';
            else if(a5.find(c) != std::string::npos) return 'D';
            else if(a6.find(c) != std::string::npos) return 'N';
        }else if(alphabet == "Murphy15"){
            string a1 = "LVIM";
            string a2 = "FY";
            string a3 = "KR";
            if(a1.find(c) != std::string::npos) return 'L';
            else if(a2.find(c) != std::string::npos) return 'F';
            else if(a3.find(c) != std::string::npos) return 'K';
            else if(c == 'C') return 'C';
            else if(c == 'A') return 'A';
            else if(c == 'G') return 'G';
            else if(c == 'S') return 'S';
            else if(c == 'T') return 'T';
            else if(c == 'P') return 'P';
            else if(c == 'W') return 'W';
            else if(c == 'E') return 'E';
            else if(c == 'D') return 'D';
            else if(c == 'N') return 'N';
            else if(c == 'Q') return 'Q';
            else if(c == 'H') return 'H';
        }else if(alphabet == "Murphy10"){
            string a1 = "LVIM";
            string a2 = "ST";
            string a3 = "FYW";
            string a4 = "EDNQ";
            string a5 = "KR";
            if(a1.find(c) != std::string::npos) return 'L';
            else if(a2.find(c) != std::string::npos) return 'S';
            else if(a3.find(c) != std::string::npos) return 'F';
            else if(a4.find(c) != std::string::npos) return 'E';
            else if(a5.find(c) != std::string::npos) return 'K';
            else if(c == 'C') return 'C';
            else if(c == 'A') return 'A';
            else if(c == 'G') return 'G';
            else if(c == 'P') return 'P';
            else if(c == 'H') return 'H';
        }else if(alphabet == "Murphy8"){
            string a1 = "LVIMC";
            string a2 = "AG";
            string a3 = "ST";
            string a4 = "FYW";
            string a5 = "EDNQ";
            string a6 = "KR";
            if(a1.find(c) != std::string::npos) return 'L';
            else if(a2.find(c) != std::string::npos) return 'A';
            else if(a3.find(c) != std::string::npos) return 'S';
            else if(a4.find(c) != std::string::npos) return 'F';
            else if(a5.find(c) != std::string::npos) return 'E';
            else if(a6.find(c) != std::string::npos) return 'K';
            else if(c == 'H') return 'H';
            else if(c == 'P') return 'P';
        }else if(alphabet == "Murphy4"){
            string a1 = "LVIMC";
            string a2 = "AGSTP";
            string a3 = "FYW";
            string a4 = "EDNQKRH";
            if(a1.find(c) != std::string::npos) return 'L';
            else if(a2.find(c) != std::string::npos) return 'A';
            else if(a3.find(c) != std::string::npos) return 'F';
            else if(a4.find(c) != std::string::npos) return 'E';
        }else if(alphabet == "Murphy2"){
            string a1 = "LVIMCAGSTPFYW";
            string a2 = "EDNQKRH";
            if(a1.find(c) != std::string::npos) return 'P';
            else if(a2.find(c) != std::string::npos) return 'E';
        }else if(alphabet == "Wang5"){
            string a1 = "CMFILVWY";
            string a2 = "ATH";
            string a3 = "GP";
            string a4 = "DE";
            string a5 = "SNQRK";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'A';
            else if(a3.find(c) != std::string::npos) return 'G';
            else if(a4.find(c) != std::string::npos) return 'E';
            else if(a5.find(c) != std::string::npos) return 'K';
        }else if(alphabet == "Wang5v"){
            string a1 = "CMFI";
            string a2 = "LVWY";
            string a3 = "ATGS";
            string a4 = "NQDE";
            string a5 = "HPRK";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'L';
            else if(a3.find(c) != std::string::npos) return 'A';
            else if(a4.find(c) != std::string::npos) return 'E';
            else if(a5.find(c) != std::string::npos) return 'K';
        }else if(alphabet == "Wang3"){
            string a1 = "CMFILVWY";
            string a2 = "ATHGPR";
            string a3 = "DESNQK";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'A';
            else if(a3.find(c) != std::string::npos) return 'E';
        }else if(alphabet == "Wang2"){
            string a1 = "CMFILVWY";
            string a2 = "ATHGPRDESNQK";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'A';
        }else if(alphabet == "Li10"){
            string a1 = "FYW";
            string a2 = "ML";
            string a3 = "IV";
            string a4 = "ATS";
            string a5 = "NH";
            string a6 = "QED";
            string a7 = "RK";
            if(a1.find(c) != std::string::npos) return 'Y';
            else if(a2.find(c) != std::string::npos) return 'L';
            else if(a3.find(c) != std::string::npos) return 'V';
            else if(a4.find(c) != std::string::npos) return 'S';
            else if(a5.find(c) != std::string::npos) return 'N';
            else if(a6.find(c) != std::string::npos) return 'E';
            else if(a7.find(c) != std::string::npos) return 'K';
            else if(c == 'C') return 'C';
            else if(c == 'G') return 'G';
            else if(c == 'P') return 'P';
        }else if(alphabet == "Li5"){
            string a1 = "CFYW";
            string a2 = "MLIV";
            string a3 = "PATS";
            string a4 = "NHQEDRK";
            if(a1.find(c) != std::string::npos) return 'Y';
            else if(a2.find(c) != std::string::npos) return 'I';
            else if(a3.find(c) != std::string::npos) return 'S';
            else if(a4.find(c) != std::string::npos) return 'N';
            else if(c == 'G') return 'G';
        }else if(alphabet == "Li4"){
            string a1 = "CFYW";
            string a2 = "MLIV";
            string a3 = "GPATS";
            string a4 = "NHQEDRK";
            if(a1.find(c) != std::string::npos) return 'Y';
            else if(a2.find(c) != std::string::npos) return 'I';
            else if(a3.find(c) != std::string::npos) return 'S';
            else if(a4.find(c) != std::string::npos) return 'E';
        }else if(alphabet == "Li3"){
            string a1 = "CFYWMLIV";
            string a2 = "GPATS";
            string a3 = "NHQEDRK";
            if(a1.find(c) != std::string::npos) return 'I';
            else if(a2.find(c) != std::string::npos) return 'S';
            else if(a3.find(c) != std::string::npos) return 'E';
        }
    }

    return 'X';
}

float Filter::getResidueFrequence(char aa, int pos, string alphabet){//alignmentpos
    int countAA = 0;

    if(pos > sequences[0].size()) return -1;

    if(alphabet == "T20"){
            for(unsigned int i = 0; i < sequences.size(); i++){
                if(sequences[i][pos-1] == aa) countAA++;
            }
    }else{
        if(alphabet != "T2" && alphabet != "T5" && alphabet != "T6" && alphabet != "3IMG" && alphabet != "5IMG"
                && alphabet != "11IMG" && alphabet != "Murphy15" && alphabet != "Murphy10" && alphabet != "Murphy8"
                && alphabet != "Murphy4" && alphabet != "Murphy2" && alphabet != "Wang5" && alphabet != "Wang5v"
                && alphabet != "Wang3" && alphabet != "Wang2" && alphabet != "Li10" && alphabet != "Li5"
                && alphabet != "Li4" && alphabet != "Li3") return -1;

        vector<string> reducedsequences = getReducedSequences(alphabet);
        char newAA = getReducedAminoAcid(aa,alphabet);

        for(unsigned int i = 0; i < reducedsequences.size(); i++){
            if(reducedsequences[i][pos-1] == newAA) countAA++;
        }
    }

    //printf("%d/%d = %f\n",countAA,sequences.size(),(float)countAA/(float)sequences.size());
    return (float)countAA/(float)sequences.size();
}

bool Filter::containsSequence(string seq){
    for(unsigned int i = 0; i < sequencenames.size(); i++)
        if(seq == sequencenames[i]) return true;
    return false;
}

int Filter::getSequenceIndex(string refseq){
    for(unsigned int i = 0; i < sequencenames.size(); i++){
        if(sequencenames[i] == refseq)
            return i;
    }

    return -1;
}

void Filter::convertLowerDots(){
    for(unsigned int i = 0; i < sequences.size(); i++){
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            if(sequences[i][j] == '.') sequences[i][j] = '-';
            else sequences[i][j] = toupper(sequences[i][j]);
        }
    }
}

int Filter::getWeightsSize(){
    return weights.size();
}

void Filter::sortCommunitiesVector(){
    sort(comunidades.begin(),comunidades.end(),
         [](const std::vector<string>& a, const std::vector<string>& b) {
        return a.size() > b.size();
    });
}
