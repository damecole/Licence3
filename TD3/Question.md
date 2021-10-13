<h1> Question 4 TD3 : </h1>

**2)** On ne fait rien: la visibilité par default des constructeurs 
interdit deja l'instanciation de l'exterieur de fs

**3)**
```java
abstract class ElementDeRep{
	private String nom;
	...
	public String getNom(){
		return this.nom;
	}
}
```
**4)**
```java
public class Lien ...{
	private CibleDeLien cible;
	public CibleDeLien getCible(){
		return this.cible;
	}
}
```
**5)**
```java
public class Repertoire ...() {
	private ElementDeRep[] contenu;
	...

	public ElementDeRep[] getContenu(){
		return this.contenu.clone(); //Ne pas oublier clone
	}
}
```

**6)**

Repertoire

public createFichier
public createLien
public createRep
