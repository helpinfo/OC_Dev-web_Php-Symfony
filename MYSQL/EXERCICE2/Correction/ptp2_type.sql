SELECT a.id, DATE_FORMAT(a.date_publication, '%d/%m/%Y') AS date_publication, u.pseudo, a.titre, a.resume, COUNT(c.id) as nb_commentaires
FROM Article AS a
INNER JOIN Utilisateur AS u ON a.auteur_id = u.id
INNER JOIN Commentaire AS c ON c.article_id = a.id
GROUP BY a.date_publication, u.pseudo, a.titre, a.resume
ORDER BY a.date_publication;

SELECT a.id, DATE_FORMAT(a.date_publication, '%d %M \'%y') AS date_publication, u.pseudo, a.titre, a.resume
FROM Article AS a
INNER JOIN Utilisateur AS u ON a.auteur_id = u.id
WHERE u.id = 2
ORDER BY a.date_publication;

SELECT a.id, DATE_FORMAT(a.date_publication, '%d/%m/%Y %h:%i') AS date_publication, a.titre, a.resume
FROM Article AS a
INNER JOIN Categorie_article AS ca ON ca.article_id = a.id 
WHERE ca.categorie_id = 3
ORDER BY a.date_publication;

SELECT a.id, DATE_FORMAT(a.date_publication, '%d %M %Y à %h %i') AS date_publication, u.pseudo, a.titre, a.contenu, GROUP_CONCAT(c.nom SEPARATOR ', ')
FROM Article AS a
INNER JOIN Utilisateur AS u ON a.auteur_id = u.id
INNER JOIN Categorie_article AS ca ON ca.article_id = a.id 
INNER JOIN Categorie AS c ON ca.categorie_id = c.id
WHERE a.id = 4
GROUP BY a.id;