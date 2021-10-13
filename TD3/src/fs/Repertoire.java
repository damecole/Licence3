package fs;

import java.util.Arrays;

public class Repertoire extends CibleDeLien {
	private ElementDeRep[] contenu;
	Repertoire(String n){
		super(n);
		this.contenu = new ElementDeRep[0];
	}
	
	ElementDeRep add(ElementDeRep e) {
		boolean trouve = false;
		for(int i =0; i< this.contenu.length && !trouve ; i++)
			trouve = this.contenu[i].nom.equals(e);
		if(trouve)
			return null;
		this.contenu = Arrays.copyOf(this.contenu, this.contenu.length+1);
		this.contenu[this.contenu.length-1] = e;
		return e;	
	}
	
	
	public static final RACINE = new Repertoire("/");
	
	
	/*
	 * C'est 3 méthode transforme Repertoire en "usine a fichier"
	 */
	Fichier createFich(String nom) {
		return (Fichier) this.add(new Fichier(nom));
	}
	Repertoire createRep(String nom) {
		return (Repertoire) this.add(new Repertoire(nom));
	}
	Lien createLien(String nom, CibleDeLien c) {
		return (Lien) this.add(new Lien(nom,c));
	}
}
