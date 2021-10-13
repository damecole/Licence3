package fs;

public class Lien extends ElementDeRep {
	CibleDeLien cible;
	
	Lien(String n ,CibleDeLien c){	//Constructeur
		super(n);
		this.cible = c;
	}
}
