const NUMGIUDICI=5;
const NUMCANDIDATI=10;
const MAXNAME=30;
const MAXFILENAME=255;

struct Candidato{
    string nome <MAXNAME>;
    string giudice <MAXNAME>;
    char categoria;
    string nomefile <MAXFILENAME>;
    char fase;
    int voto;
};

struct Candidati{
    Candidato candidato[NUMCANDIDATI];
};

struct Giudice{ 
    string nome <MAXNAME>;
    int punteggio;
};

struct Giudici{
    Giudice giudice[NUMGIUDICI];
};

struct Input{
    string nome <MAXNAME>;
    char operazione;
};

program XFACTOR{
    version XFACTORVERS{
        Giudici CLASSIFICA_GIUDICI(void) = 1;
        int ESPRIMI_VOTO(Input) = 2;
    } = 1;
} = 0x20000013;