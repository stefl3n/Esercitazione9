#include <stdio.h>
#include <string.h>
static int inizializza=0;
static Candidati candidati;

void inizializza(){
    int i;
    
    if(inizializza == 1) return;
    
    for(i=0; i<NUMCANDIDATI; i++){
        strcpy(Candidati.candidato[i].nome, "L");
        strcpy(Candidati.candidato[i].giudice, "L");
        strcpy(Candidati.candidato[i].nomefile, "L");
        Candidati.candidato[i].categoria = 'L';
        Candidati.candidato[i].fase = 'L';
        Candidati.candidato[i].voto = -1;
    }
    
    //inizializzo Secondo e Terzo come da Proposta
    strcpy(Candidati.candidato[1].nome, "Brasco");
    strcpy(Candidati.candidato[1].giudice, "Bowie");
    strcpy(Candidati.candidato[1].nomefile, "BrascoProfile.txt");
    Candidati.candidato[1].categoria = 'U';
    Candidati.candidato[1].fase = 'A';
    Candidati.candidato[1].voto = 100;
    
    strcpy(Candidati.candidato[2].nome, "Viga");
    strcpy(Candidati.candidato[2].giudice, "Winehouse");
    strcpy(Candidati.candidato[2].nomefile, "VigaProfile.txt");
    Candidati.candidato[2].categoria = 'D';
    Candidati.candidato[2].fase = 'S';
    Candidati.candidato[2].voto = 50;
    
    inizializza = 1;
}

void scambia(Giudice giudice1, Giudice giudice2){
    Giudice temp = giudice1;
    giudice1 = giudice2;
    giudice2 = temp;
}

void ordinaGiudici(Giudici giudici, int n){
    int i; int ordinato = 0;
    while (n>1 && ordinato==0){
        ordinato = 1;
        for (i=0; i<n-1; i++)
            if (giudici.giudice[i].punteggio>giudici.giudice[i+1].punteggio) {
                scambia(giudice.giudice[i], giudice.giudice[i+1]);
                ordinato = 0; 
            }
        n--;
    }
}

Giudici * classifica_giudici(void *in, struct svc_req *rqstp){
    static Giudici giudici;
    int i, j, n=0, esiste; // n: numero giudici
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        esiste = 0;
        for(j=0; j<n && !esiste; j++){
            if(strcmp(candidati.candidato[i].giudice, giudici.giudice[j].nome)==0){
                esiste=1;
                giudice.giudici[j].punteggio += candidati.candidato[i].voto;
            }
        }
        
        if(!esiste){
            n++;
            giudice.giudici[n].punteggio += candidati.candidato[i].voto;
        }
    }
    ordinaGiudici(giudici, n);
    return &giudici;
}

int * esprimi_voto(Input *input, struct svc_req *rqstp){
    static int result;
    int i;
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        if(strcmp(input.nome, candidati.candidato[i].nome)==0){
            trovato=1;
            if(input.operazione == '+'){
                candidati.candidato[i].voto++;
                result = 0;
                return &result;
            }
            else if(input.operazione == '-'){
                candidati.candidato[i].voto--;
                result = 0;
                return &result;
            }
            else{
                result = -1;
                return &result; //errore operatore
            }
        }
    }
    result = -2;
    return &result; //candidato non esistente
}