#include <stdio.h>
#include <string.h>
#include <time.h>
#include "xfactor.h"
static int inizializzato=0;
static int giudiciOrdinati=0;
static Candidati candidati;
static Giudici giudici;
static int cntTest;

void inizializza(){
    int i, j, esiste;
    
    if(inizializzato == 1) return;
    
    printf("Inizio inizializzazione\n");
    
    for(i=0; i<NUMCANDIDATI; i++){
        candidati.candidato[i].nome = (char*) malloc (MAXNAME*sizeof(char));
        candidati.candidato[i].giudice = (char*) malloc (MAXNAME*sizeof(char));
        candidati.candidato[i].nomefile = (char*) malloc (MAXFILENAME*sizeof(char));
        strcpy(candidati.candidato[i].nome, "L");
        strcpy(candidati.candidato[i].giudice, "L");
        strcpy(candidati.candidato[i].nomefile, "L");
        candidati.candidato[i].categoria = 'L';
        candidati.candidato[i].fase = 'L';
        candidati.candidato[i].voto = -1;
        
    }
    
    for(i=0; i<NUMGIUDICI; i++){
        giudici.giudice[i].nome = (char*) malloc(MAXNAME*sizeof(char));
        strcpy(giudici.giudice[i].nome, "L");
        giudici.giudice[i].punteggio = -1;
    }

    //inizializzo Secondo e Terzo come da Proposta
    strcpy(candidati.candidato[1].nome, "Brasco");
    strcpy(candidati.candidato[1].giudice, "Bowie");
    strcpy(candidati.candidato[1].nomefile, "BrascoProfile.txt");
    candidati.candidato[1].categoria = 'U';
    candidati.candidato[1].fase = 'A';
    candidati.candidato[1].voto = 0;
    
    
    strcpy(candidati.candidato[2].nome, "Viga");
    strcpy(candidati.candidato[2].giudice, "Winehouse");
    strcpy(candidati.candidato[2].nomefile, "VigaProfile.txt");
    candidati.candidato[2].categoria = 'D';
    candidati.candidato[2].fase = 'S';
    candidati.candidato[2].voto = 0;
    
    strcpy(candidati.candidato[3].nome, "0");
    strcpy(candidati.candidato[3].giudice, "Winehouse");
    strcpy(candidati.candidato[3].nomefile, "0.txt");
    candidati.candidato[3].categoria = 'D';
    candidati.candidato[3].fase = 'S';
    candidati.candidato[3].voto = 0;
    
        strcpy(candidati.candidato[4].nome, "1");
    strcpy(candidati.candidato[4].giudice, "Bowie");
    strcpy(candidati.candidato[4].nomefile, "1.txt");
    candidati.candidato[4].categoria = 'D';
    candidati.candidato[4].fase = 'S';
    candidati.candidato[4].voto = 0;
    
        strcpy(candidati.candidato[5].nome, "2");
    strcpy(candidati.candidato[5].giudice, "Davide");
    strcpy(candidati.candidato[5].nomefile, "2.txt");
    candidati.candidato[5].categoria = 'D';
    candidati.candidato[5].fase = 'S';
    candidati.candidato[5].voto = 0;
    
        strcpy(candidati.candidato[6].nome, "3");
    strcpy(candidati.candidato[6].giudice, "Leone");
    strcpy(candidati.candidato[6].nomefile, "3.txt");
    candidati.candidato[6].categoria = 'D';
    candidati.candidato[6].fase = 'S';
    candidati.candidato[6].voto = 0;
    
        strcpy(candidati.candidato[7].nome, "4");
    strcpy(candidati.candidato[7].giudice, "Stefano");
    strcpy(candidati.candidato[7].nomefile, "4.txt");
    candidati.candidato[7].categoria = 'D';
    candidati.candidato[7].fase = 'S';
    candidati.candidato[7].voto = 0;
    
    
    strcpy(giudici.giudice[0].nome, "Bowie");
    giudici.giudice[0].punteggio = 0;
    
    strcpy(giudici.giudice[1].nome, "Winehouse");
    giudici.giudice[1].punteggio = 0;
    
    strcpy(giudici.giudice[2].nome, "Leone");
    giudici.giudice[2].punteggio = 0;
    
    strcpy(giudici.giudice[3].nome, "Davide");
    giudici.giudice[3].punteggio = 0;
    
    strcpy(giudici.giudice[4].nome, "Stefano");
    giudici.giudice[4].punteggio = 0;
    
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

   giudiciOrdinati=1;
}



Giudici * classifica_giudici_1_svc(void *in, struct svc_req *rqstp){
    int j;
    inizializza();
    
    //quicksort(0, NUMGIUDICI-1);
    //ordinaGiudici();
    if(!giudiciOrdinati) ordinaGiudici();
    //if(!giudiciOrdinati) quicksort(0, NUMGIUDICI-1);
    
    for(j=0; j<NUMGIUDICI; j++){
        printf("%s %d\n", giudici.giudice[j].nome, giudici.giudice[j].punteggio);
    }
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
                    if(strcmp(giudici.giudice[j].nome, candidati.candidato[i].giudice)==0)
                        giudici.giudice[j].punteggio++;
                }
                
                printf("%s: %d\n", candidati.candidato[i].nome, candidati.candidato[i].voto);
                result = 0;
                return &result;
            }
            else if(input->operazione == '-'){
                giudiciOrdinati=0;
                candidati.candidato[i].voto--;
                if(candidati.candidato[i].voto<=0)
                {
                    candidati.candidato[i].voto=0;
                }
                
                 for(j=0; j<NUMGIUDICI; j++){
                    if(strcmp(giudici.giudice[j].nome, candidati.candidato[i].giudice)==0)
                        giudici.giudice[j].punteggio--;
                        if(giudici.giudice[j].punteggio<=0)
                        {
                            giudici.giudice[j].punteggio=0;
                        }
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