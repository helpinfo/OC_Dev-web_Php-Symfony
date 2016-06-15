SELECT 'Remplissage de la table Categorie';
INSERT IGNORE INTO Categorie (nom) 
VALUES ('Categ 1'), ('Categ 2'), ('Categ 3'), ('Categ 4'), ('Categ 7'), ('Categ 6'), ('Categ 5');
SHOW WARNINGS;

SELECT 'Remplissage de la table Utilisateurs';
INSERT IGNORE INTO Utilisateurs (util_pseudo, util_pwd)
VALUES ('util A', 'p1'), ('util B', 'p2'), ('util C', 'p3'), ('util D', 'p5'), ('util E', 'p5');
SHOW WARNINGS;

SELECT 'Remplissage de la table Articles';


-- Attention à l'emplacement du fichier rajouter éventuellement le chemin complet pour y accéder par exemple "C:/Users/Documents/SQL/TP1_data.csv
LOAD DATA LOCAL INFILE 'TP1_data.csv' IGNORE  
INTO TABLE Articles                                                       
FIELDS
    TERMINATED BY ';'
LINES 
    STARTING BY '*' 
    TERMINATED BY '\n'
IGNORE 1 LINES
(art_titre, art_texte, art_resume, art_auteur, art_date, art_categ);       
SHOW WARNINGS;

SELECT 'Remplissage de la table Categorie_article';
-- A partir de la table Article remplie ci-dessus
INSERT IGNORE INTO Categorie_Article
SELECT art_categ, id_art
    FROM Articles;
SHOW WARNINGS;

-- plus qq'uns pour avoir des articles sur plusieurs catégories
INSERT IGNORE INTO Categorie_article (categorie_id, article_id)
VALUES (1,1),(1,2), (2,2), (4, 4);
SHOW WARNINGS;

SELECT 'Remplissage de la table Commentaires';

-- Attention à l'emplacement du fichier rajouter éventuellement le chemin complet pour y accéder par exemple "C:/Users/Documents/SQL/TP1_data.csv
LOAD DATA LOCAL INFILE 'TP1_data.csv' IGNORE  
INTO TABLE Commentaires                                                       
FIELDS
    TERMINATED BY ';'
LINES 
    STARTING BY 'Comment' 
    TERMINATED BY '\n'
IGNORE 17 LINES
(com_util, com_art, com_commentaire, com_date);    
SHOW WARNINGS;
