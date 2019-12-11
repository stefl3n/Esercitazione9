#include <stdio.h>
#include <string.h>
#include "xfactor.h"
static int inizializzato=0;
static int giudiciOrdinati=0;
static Candidati candidati;
static Giudici giudici;

void inizializza(){
    int i, j, esiste;
    
    if(inizializzato == 1) return;
    
    printf("Inizio inizializzazione\n");
    
    for(i=0; i<NUMCANDIDATI; i++){
        candidati.candidato[i].nome = (char*) malloc (30*sizeof(char));
        candidati.candidato[i].giudice = (char*) malloc (30*sizeof(char));
        candidati.candidato[i].nomefile = (char*) malloc (30*sizeof(char));
        strcpy(candidati.candidato[i].nome, "L");
        strcpy(candidati.candidato[i].giudice, "L");
        strcpy(candidati.candidato[i].nomefile, "L");
        candidati.candidato[i].categoria = 'L';
        candidati.candidato[i].fase = 'L';
        candidati.candidato[i].voto = -1;
        
    }
    
    for(i=0; i<NUMGIUDICI; i++){
        giudici.giudice[i].nome = (char*) malloc(30*sizeof(char));
        strcpy(giudici.giudice[i].nome, "L");
        giudici.giudice[i].punteggio = -1;
    }

    //inizializzo Secondo e Terzo come da Proposta
    strcpy(candidati.candidato[1].nome, "Brasco");
    strcpy(candidati.candidato[1].giudice, "Bowie");
    strcpy(candidati.candidato[1].nomefile, "BrascoProfile.txt");
    candidati.candidato[1].categoria = 'U';
    candidati.candidato[1].fase = 'A';
    candidati.candidato[1].voto = 100;
    
    strcpy(giudici.giudice[0].nome, "Bowie");
    giudici.giudice[0].punteggio = 100;
    
    strcpy(candidati.candidato[2].nome, "Viga");
    strcpy(candidati.candidato[2].giudice, "Winehouse");
    strcpy(candidati.candidato[2].nomefile, "VigaProfile.txt");
    candidati.candidato[2].categoria = 'D';
    candidati.candidato[2].fase = 'S';
    candidati.candidato[2].voto = 50;
    
    
    strcpy(giudici.giudice[1].nome, "Winehouse");
    giudici.giudice[1].punteggio = 50;
    
    strcpy(giudici.giudice[2].nome, "Leone");
    giudici.giudice[2].punteggio = 1;
    
    strcpy(giudici.giudice[3].nome, "Davide");
    giudici.giudice[3].punteggio = 2;
    
    strcpy(giudici.giudice[4].nome, "Stefano");
    giudici.giudice[4].punteggio = 300;
    
    inizializzato = 1;
    printf("Fine inizializzazione\n");
}

void scambia(int max, int min){
    Giudice temp = giudici.giudice[max];
    giudici.giudice[max] = giudici.giudice[min];
    giudici.giudice[min] = temp;
}

void ordinaGiudici(){
    int i, n, ordinato = 0;
    n = NUMGIUDICI;
    while (n>1 && ordinato==0){
        ordinato = 1;
        for (i=0; i<n-1; i++)
            if ((giudici.giudice[i].punteggio)<(giudici.giudice[i+1].punteggio)) {
                scambia(i, i+1);
                ordinato = 0; 
            }
        n--;
    }
    printf("GiudiciRiordinati\n");
    giudiciOrdinati=1;
}

Giudici * classifica_giudici_1_svc(void *in, struct svc_req *rqstp){
    int j;
    inizializza();
    
    if(!giudiciOrdinati) ordinaGiudici();
    
    return (&giudici);
}

int * esprimi_voto_1_svc(Input *input, struct svc_req *rqstp){
    static int result;
    int i,j;
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        if(strcmp(input->nome, candidati.candidato[i].nome)==0){
            if(input->operazione == '+'){
                giudiciOrdinati=0;
                candidati.candidato[i].voto++;
                
                for(j=0; j<NUMGIUDICI; j++){
                    if(strcmp(giudici.giudice[j].nome, candidati.candidato[i].nome)==0)
                        giudici.giudice[j].punteggio++;
                }
                
                printf("%s: %d\n", candidati.candidato[i].nome, candidati.candidato[i].voto);
                result = 0;
                return &result;
            }
            else if(input->operazione == '-'){
                giudiciOrdinati=0;
                candidati.candidato[i].voto--;
                
                 for(j=0; j<NUMGIUDICI; j++){
                    if(strcmp(giudici.giudice[j].nome, candidati.candidato[i].nome)==0)
                        giudici.giudice[j].punteggio--;
                }
                
                printf("%s: %d\n", candidati.candidato[i].nome, candidati.candidato[i].voto);
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