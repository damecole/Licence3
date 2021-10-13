package fs;

public class Fichier extends CibleDeLien {
	String nom;
	
	Fichier(String n){	//Constructeur
		//Si on a pas de super, y a implicitement: super();
		super(n);
	}
}
