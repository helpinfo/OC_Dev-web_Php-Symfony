-- Requêtes d'affichage

-- ***********************************************************
-- requête pour la page d'accueil : les articles sont affichés (titre, date, auteur et résumé). Ils sont triés par date de publication.
SELECT 'PAGE D''ACCUEIL'; -- pour clarifier l'affichage

SELECT art_titre 'Titre', art_date 'Date', util_pseudo 'Auteur', art_resume 'Resume'  -- pour clarifier utiliser : SUBSTRING(art_resume,1,20) 'Resume'
FROM Articles
    LEFT OUTER JOIN Utilisateurs ON art_auteur = id_util
-- Left Outer Join n'est pas indispensable car on a forcément un auteur connu.
ORDER BY Date;

-- *********************************************************************************
-- requete page utilisateur : les articles écrits par un utilisateur triés par date.
-- ** en fait d'article on n'en reprend que le titre afin de simplifier l'affichage
-- ** ici on considère que l'utilisateur n'est pas connecté au préalable, sinon on disposerait déjà de son id et la jointure ne serait pas utile.

SELECT 'PAGE UTILISATEUR : util B'; -- 

SELECT art_titre 'Titre', art_date 'Date'
FROM Articles
    INNER JOIN Utilisateurs ON id_util = art_auteur
WHERE
    util_pseudo = 'util B' -- mettre le pseudo de l'utilisateur
    AND util_pwd = 'p2' -- mettre le mot de passe de l'utilisateur
ORDER BY art_date;    
    

-- requête page catégorie : les articles d’une catégorie, également triés par date   
-- ** comme dans le cas précédent, si on sélectionne la catégorie dans une liste auparavant, on travaillerait directement à partir de l'id de la catégorie et non de son nom. Le om de la catégorie est ici utilisé deux fois dans la requête

SELECT 'PAGE CATEGORIE : pour Categ 2';
(SELECT art_titre 'Titre', art_date 'Date'
FROM Categorie
    INNER JOIN Categorie_Article ON id = categorie_id
    INNER JOIN Articles ON id_art = article_id
WHERE
    nom = 'Categ 2' -- Mettre le nom de la catégorie recherchée
) UNION (
-- deuxième requête pour sélectionner les articles dont la catégorie principale est celle cherchée si la table Catégorie_Article n'est pas à jour.
SELECT art_titre, art_date
FROM Articles
    INNER JOIN Categorie ON art_categ = categorie.id
WHERE
    Categorie.nom = 'Categ 2' -- Remettre le nom de la catégorie recherchée
)
ORDER BY Date;    


-- requête page article : article complet ainsi que ses commentaires par ordre chronologique.
-- cette fois-ci je suppose que l'on connait l'id de l'article a afficher, attention, il est utilisé deux fois dans la requête

SELECT 'PAGE ARTICLE : pour (id 2) - (pour plus de lisibilite les textes sont tronques.)';
(SELECT art_titre 'Titre', SUBSTRING(art_texte,1, 20) 'Article / Commentaires', util_pseudo 'Auteur', art_date 'Date'
FROM Articles
    INNER JOIN Utilisateurs ON art_auteur = id_util
WHERE 
    id_art = '2' -- Mettre le numéro de l'article recherché
)
UNION
( SELECT  '', SUBSTRING(com_commentaire,1, 20), util_pseudo, com_date
FROM Commentaires
    INNER JOIN Utilisateurs ON com_util = id_util
WHERE
    com_art = '2' -- Remettre le numéro de l'article recherché
) 
ORDER BY Titre desc, Date
-- le tri par Titre permet de s'assurer que l'article est bien positionné en premier (dans le cas où certains commentaires auraient été créés avec une date erronée ) 