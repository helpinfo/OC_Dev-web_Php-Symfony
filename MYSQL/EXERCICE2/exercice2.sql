#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------

#------------------------------------------------------------
# p2p_blog : Page accueil
#------------------------------------------------------------

SELECT DATE_FORMAT(Article.date_publication, '%d/%m/%Y') AS Date_publication,
	Utilisateur.pseudo AS Auteur,
	Article.titre AS Titre,
	Article.resume AS Résumé,
	COUNT(Commentaire.id) AS Nbr_Commentaires
FROM Article
INNER JOIN Utilisateur 
	ON Article.auteur_id = Utilisateur.id
INNER JOIN Commentaire
	ON Commentaire.article_id = Article.id
GROUP BY Article.date_publication, Utilisateur.pseudo, Article.titre, Article.resume
ORDER BY date_publication DESC;

#------------------------------------------------------------
# p2p_blog : Page catégorie
#------------------------------------------------------------

SELECT DATE_FORMAT(Article.date_publication, '%d/%m/%Y - %H:%i') AS Date_publication,
	Utilisateur.pseudo AS Auteur,
	Article.titre AS Titre,
	Article.resume AS Résumé
FROM Categorie
INNER JOIN Categorie_article 
	ON Categorie.id = Categorie_article.categorie_id
INNER JOIN Article
	ON Categorie_article.article_id = Article.id
INNER JOIN Utilisateur 
	ON Article.auteur_id = Utilisateur.id
WHERE
	Categorie.nom = 'amour'
ORDER BY Date_publication DESC

#------------------------------------------------------------
# p2p_blog : Page auteur
#------------------------------------------------------------

SET lc_time_names = 'fr_FR';
SELECT DATE_FORMAT(Article.date_publication, '%d %M ''%y') AS Date_publication,
	Utilisateur.pseudo AS Auteur,
	Article.titre AS Titre,
	Article.resume AS Résumé
FROM Article
INNER JOIN Utilisateur 
	ON Article.auteur_id = Utilisateur.id
WHERE
	Article.auteur_id = "2"
ORDER BY date_publication DESC;

#------------------------------------------------------------
# p2p_blog : Page article
#------------------------------------------------------------

SET lc_time_names = 'fr_FR';
SELECT DATE_FORMAT(Article.date_publication, '%d %M %Y à %H heures %i') AS Date_publication,
	Article.titre AS Titre,
	Article.contenu AS Contenu,
	Utilisateur.pseudo AS Auteur,
	GROUP_CONCAT(Categorie.nom) AS Catégories
FROM Categorie
INNER JOIN Categorie_article 
	ON Categorie.id = Categorie_article.categorie_id
INNER JOIN Article
	ON Categorie_article.article_id = Article.id
INNER JOIN Utilisateur 
	ON Article.auteur_id = Utilisateur.id
WHERE
	Article.id = "4";

-- Requête donnée
SELECT Commentaire.contenu,
	DATE_FORMAT(Commentaire.date_commentaire, '%d/%m/%Y'), 
	Utilisateur.pseudo
FROM Commentaire
LEFT JOIN Utilisateur 
	ON Commentaire.auteur_id = Utilisateur.id
WHERE Commentaire.article_id = 2
ORDER BY Commentaire.date_commentaire;