on cree un manager dans la scene qui a une array d'une UENUM Quest qui a :
- une ID
- un text descriptif
-un nombre d'avancé
- un nombre necessaire pour la terminer
ex : pour nettoyer 3 canons
	- ID = 456783
	- text = "nettoyer canons (0/3)
	- nb = 0 (puis 1, puis 2, puis 3
	- nb necessaire = 3


le joueur a une array d'une UENUM Quest qui se remplit de X quetes choisi aleatoirement


sur la scene, il y a des trigger qui ont 
- l'ID de la quete

si le joueur n'a pas le bon ID, ca ne s'active pas
si le joueur a le bon ID, il peut l'activer,
	si il l'active, cooldown et fin, 
		il update sa quete et le trigger se desactive


si le joueur constate qu'une quete est terminé
	- il la supprime de son HUD
	- il check si son array quete est vide si vide, VICTOIRE