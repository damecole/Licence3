/* Lancement d'un serveur : serveur_tcp port */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

#define TRUE 1

#define BUFSIZE 50 //taille des packets a envoyer 

//port 5555
//nom machine en local = localhost

//gcc FTP_client.c -o FTP_client
//gcc FTP_serveur.c -o FTP_serveur


int main (int argc, char **argv)
{
    int socket_RV, socket_service;
    char buf[256];
    struct sockaddr_in adresseRV;
    int lgadresseRV;
    struct sockaddr_in adresseClient;
    int lg_adresseClient;
    unsigned short port;


       
	int nbo_lus=0;
	int nbo_ecr=0;
	char chaine[30];
	int fichierfd, fdcopie;
	chaine[30]='\0';
    int nb_octet_lu = 0;

    


    /* creation de la socket de RV */
    if((socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    /* preparation de l'adresse locale */
    port = (unsigned short) atoi(argv[1]);
    
    adresseRV.sin_family = AF_INET;
    adresseRV.sin_port = htons(port);
    adresseRV.sin_addr.s_addr = htonl(INADDR_ANY);
    lgadresseRV = sizeof(adresseRV);

    /* attachement de la socket a l'adresse locale */
    if((bind(socket_RV, (struct sockaddr *) &adresseRV, lgadresseRV)) == -1){
        perror("bind");
        exit(3);
    }
    printf("le num de la socket est : %d \n", socket_RV);
    /* declaration d'ouverture du service */
    if(listen(socket_RV, 10) == -1){
        perror("listen");
        exit(4);
    }

    int flag = 0;
    char buffer_ecriture[100];
    int return_read;

    while (TRUE)
    {

        /* boucle d'attente de connexion */
        printf("Debut de boucle\n");
        fflush(stdout);
        /* attente d'un client */
        lg_adresseClient = sizeof(adresseClient);
        socket_service=accept(socket_RV, (struct sockaddr *) & adresseClient, &lg_adresseClient);
        /* traitement des erreurs */
        if(socket_service == -1 && errno == EINTR){
            //continue;   //reception d'un signal
        }
        if(socket_service == -1){
            perror("accept");   //erreur
            exit(5);
        }

         /* un client est arrive */
        printf("connexion acceptee\n");
        fflush(stdout);


         strcpy(buffer_ecriture, "ok");

        

        if((return_read= read(socket_service, chaine, sizeof(chaine))) < 0){
            perror("read");
            exit(6);
        }

        char chaine_nom[30];
        int i=0;
        while (chaine[i] != '\0')
        {
            chaine_nom[i] = chaine[i];
            i++;
        }
        
        char * nom_fichier;
        nom_fichier = &chaine_nom;

        printf("nom du fichier ouvert/cree: %s \n", nom_fichier);
        /* open() - récupération du desc. de fichier sur le nouveau fichier en écriture */
        fdcopie=open(nom_fichier,O_CREAT|O_WRONLY|O_TRUNC, 0640);
        if (fdcopie <0 )
        {
            perror("open");
            exit(-1);
        }


        printf("Descripteur de fichier ouvert pour le 1ème fichier : %d \n",fdcopie);


        /* lecture dans la socket d'une chaine de caractères */
        while ((nbo_lus= read(socket_service, chaine, sizeof(chaine))) >0)
        {       
            nb_octet_lu += nbo_lus;
            printf("nb octets lus : %d\n",nbo_lus);
            /* Affichage des BUFSIZE lus */
            //printf("%s \n",chaine);

            if ((nbo_ecr=write(fdcopie,chaine,nbo_lus))!= nbo_lus)
            {
                perror("Erreur write \n");
                exit(-1);
            }
        
        }

        printf("la connection a lu %d octets \n", nb_octet_lu);
        close(socket_service);


    }

    close(socket_RV);

    printf("transmission fini \n");
}
