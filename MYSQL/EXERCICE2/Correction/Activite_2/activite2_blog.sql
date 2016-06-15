--Accueil
SELECT DATE_FORMAT(article.date_publication, '%d/%m/%Y') AS parution, utilisateur.pseudo, article.titre, article.resume, COUNT(commentaire.article_id) AS nb_commentaires
FROM article
INNER JOIN utilisateur ON article.auteur_id = utilisateur.id
LEFT JOIN commentaire ON commentaire.article_id = article.id
GROUP BY article.id
ORDER BY article.date_publication DESC;



-- Auteur - id de l'auteur = 2
SELECT DATE_FORMAT(article.date_publication, '%d %M ''%y') AS parution, utilisateur.pseudo, article.titre, article.resume
FROM article
INNER JOIN utilisateur ON article.auteur_id = utilisateur.id
WHERE article.auteur_id = 2
ORDER BY article.date_publication DESC;



-- Categorie - id de la categorie = 3
SELECT DATE_FORMAT(article.date_publication, '%d/%m/%Y - %H:%i') AS parution, utilisateur.pseudo, article.titre, article.resume
FROM article
INNER JOIN utilisateur ON article.auteur_id = utilisateur.id
INNER JOIN categorie_article ON article.id = categorie_article.article_id
WHERE categorie_article.categorie_id = 3
ORDER BY article.date_publication DESC;



-- Article - id de l'article = 4
SELECT DATE_FORMAT(article.date_publication, '%d %M %Y à %H heures %i') AS parution, article.titre, article.contenu, GROUP_CONCAT(categorie.nom) AS nom_categorie, utilisateur.pseudo
FROM article
INNER JOIN utilisateur ON article.auteur_id = utilisateur.id
INNER JOIN categorie_article ON categorie_article.article_id = article.id
INNER JOIN categorie ON categorie.id = categorie_article.categorie_id
WHERE article.id = 4;