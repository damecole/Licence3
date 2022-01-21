/* Lancement d'un client : client_tcp port machineServeur */
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



#include <sys/stat.h>

#define BUFSIZE 150 //taille des packets a envoyer 

// PORT NOM FICHIER_READ FICHIER_WRITE

int main (int argc, char **argv)
{
    int sock;
    char buf[256];
    char buf_block[256];
    struct sockaddr_in adresse_serveur;
    struct hostent *hote;
    unsigned short port;
    struct stat sb; //Pour recupere la taille du fichier 


    int nbo_lus=0;
	int nbo_ecr=0;
	char chaine[30];
	int fichierfd, fdcopie;
	chaine[30]='\0';



    /* creation de la socket locale */
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    /* recuperation de l'adresse IP du serveur (a partir de son nom) */
    if((hote = gethostbyname(argv[2])) == NULL){
        perror("gethostbyname");
        exit(2);
    }
    /* preparation de l'adresse du serveur */
    port = (unsigned short) atoi(argv[1]);

    adresse_serveur.sin_family = AF_INET;
    adresse_serveur.sin_port = htons(port);
    bcopy(hote->h_addr, &adresse_serveur.sin_addr, hote->h_length);
    //printf("L'adresse du serveur en notation pointee %s \n", inet_ntoa(adresse_serveur.sin_addr));
    fflush(stdout);

    /* demande de connexion au serveur */
    if(connect(sock, (struct sockaddr *) &adresse_serveur, sizeof(adresse_serveur)) == -1){
        perror("connect");
        exit(3);
    }

    printf("Le serveur accept le connexion \n ");
    fflush(stdout);


    printf("Nom du fichier à copier : %s\n", argv[3]);
    printf("Nom du fichier copié : %s\n", argv[4]);


    fichierfd=open(argv[3],O_RDONLY);
   if (fichierfd <0 )
		{
		perror("open");
		exit(-1);
		}
	printf("Descripteur de fichier ouvert pour le 1er fichier : %d \n",fichierfd);
   
   /* open() - récupération du desc. de fichier sur le nouveau fichier en écriture */
   fdcopie=open(argv[4],O_CREAT|O_WRONLY|O_TRUNC, 0640);
   if (fdcopie <0 )
		{
		perror("open");
		exit(-1);
		}
	printf("Descripteur de fichier ouvert pour le 2ème fichier : %d \n",fdcopie);
    printf("le fichier ouvert pour ecriture est: %s \n",argv[4]);

    strcpy(chaine,argv[4]);
    printf("chaine : %s \n",chaine);

    if(write(sock, chaine, strlen(chaine)+1) != strlen(chaine)+1){
            perror("Erreur lors du write \n");
            exit(4);
    }
   
  /* Boucle de copie (lecture/ecriture) dans le fichier de BUFSIZE octets jusqu'à la fin */
   while ((nbo_lus=read(fichierfd,chaine,BUFSIZE)) >0)
	{
        printf("nb octets lus : %d\n",nbo_lus);
        /* Affichage des BUFSIZE lus */
        //printf("%s \n",chaine);

     
        //Il faut envoyer sur le socket en fonction du nombre d'octet lu 
        if(write(sock, chaine, nbo_lus) != nbo_lus){
            perror("Erreur lors du write \n");
            exit(4);
        }

	}
	
   /* Fermeture des descripteurs de fichiers ouverts */
   close(fichierfd);
   close(fdcopie);

        
}	


  
