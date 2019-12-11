#include <stdio.h>
#include <string.h>
#include "xfactor.h"
static int inizializzato=0;
static Candidati candidati;
static Giudici giudici;
static int n=2; //giudici

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
    
    inizializzato = 1;
    printf("Fine inizializzazione\n");
}

void scambia(int max, int min){
    Giudice temp = giudici.giudice[max];
    giudici.giudice[max] = giudici.giudice[min];
    giudici.giudice[min] = temp;
}

void ordinaGiudici(){
    int i,temp, ordinato = 0;
    temp = n;
    while (temp>1 && ordinato==0){
        ordinato = 1;
        for (i=0; i<temp-1; i++)
            if ((giudici.giudice[i].punteggio)<(giudici.giudice[i+1].punteggio)) {
                scambia(i, i+1);
                ordinato = 0; 
            }
        temp--;
    }
}

void quicksort(int primo,int ultimo){
   int i, j, pivot, temp;
   if(primo<ultimo){
      pivot=primo;
      i=primo;
      j=ultimo;     
      
      while(i<j){
         while(giudici.giudice[i].punteggio>=giudici.giudice[pivot].punteggio&&i<ultimo)
            i++;
         while(giudici.giudice[j].punteggio<giudici.giudice[pivot].punteggio)
            j--;
         if(i<j){   
            scambia(i, j);
         }
      }

      scambia(pivot, j);
      quicksort(primo,j-1);
      quicksort(j+1,ultimo);
   }
}



Giudici * classifica_giudici_1_svc(void *in, struct svc_req *rqstp){
    int j;
    //inizializza();
    quicksort(0, NUMGIUDICI-1);
    ordinaGiudici();
    
    for(j=0; j<n; j++){
        printf("%s %d\n", giudici.giudice[j].nome, giudici.giudice[j].punteggio);
    }
    return (&giudici);
}

int * esprimi_voto_1_svc(Input *input, struct svc_req *rqstp){
    static int result;
    int i;
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        if(strcmp(input->nome, candidati.candidato[i].nome)==0){
            if(input->operazione == '+'){
                candidati.candidato[i].voto++;
                printf("%s: %d\n", candidati.candidato[i].nome, candidati.candidato[i].voto);
                result = 0;
                return &result;
            }
            else if(input->operazione == '-'){
                candidati.candidato[i].voto--;
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