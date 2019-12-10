const NUMGIUDICI=5;
const NUMCANDIDATI=10;

struct Candidato{
    string nome <30>;
    string giudice <30>;
    char categoria;
    string nomefile <256>;
    char fase;
    int voto;
};

struct Candidati{
    Candidato candidato[NUMCANDIDATI];
};

struct Giudice{ 
    string nome <30>;
    int punteggio;
};

struct Giudici{
    Giudice giudice[NUMGIUDICI];
};

struct Input{
    string nome <30>;
    char operazione;
};

program XFACTOR{
    version XFACTORVERS{
        Giudici CLASSIFICA_GIUDICI(void) = 1;
        int ESPRIMI_VOTO(Input) = 2;
    } = 1;
} = 0x20000013;