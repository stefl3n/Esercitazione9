/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _XFACTOR_H_RPCGEN
#define _XFACTOR_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define NUMGIUDICI 5
#define NUMCANDIDATI 10
#define MAXNAME 30
#define MAXFILENAME 255

struct Candidato {
	char *nome;
	char *giudice;
	char categoria;
	char *nomefile;
	char fase;
	int voto;
};
typedef struct Candidato Candidato;

struct Candidati {
	Candidato candidato[NUMCANDIDATI];
};
typedef struct Candidati Candidati;

struct Giudice {
	char *nome;
	int punteggio;
};
typedef struct Giudice Giudice;

struct Giudici {
	Giudice giudice[NUMGIUDICI];
};
typedef struct Giudici Giudici;

struct Input {
	char *nome;
	char operazione;
};
typedef struct Input Input;

#define XFACTOR 0x20000013
#define XFACTORVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define CLASSIFICA_GIUDICI 1
extern  Giudici * classifica_giudici_1(void *, CLIENT *);
extern  Giudici * classifica_giudici_1_svc(void *, struct svc_req *);
#define ESPRIMI_VOTO 2
extern  int * esprimi_voto_1(Input *, CLIENT *);
extern  int * esprimi_voto_1_svc(Input *, struct svc_req *);
extern int xfactor_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CLASSIFICA_GIUDICI 1
extern  Giudici * classifica_giudici_1();
extern  Giudici * classifica_giudici_1_svc();
#define ESPRIMI_VOTO 2
extern  int * esprimi_voto_1();
extern  int * esprimi_voto_1_svc();
extern int xfactor_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Candidato (XDR *, Candidato*);
extern  bool_t xdr_Candidati (XDR *, Candidati*);
extern  bool_t xdr_Giudice (XDR *, Giudice*);
extern  bool_t xdr_Giudici (XDR *, Giudici*);
extern  bool_t xdr_Input (XDR *, Input*);

#else /* K&R C */
extern bool_t xdr_Candidato ();
extern bool_t xdr_Candidati ();
extern bool_t xdr_Giudice ();
extern bool_t xdr_Giudici ();
extern bool_t xdr_Input ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_XFACTOR_H_RPCGEN */
