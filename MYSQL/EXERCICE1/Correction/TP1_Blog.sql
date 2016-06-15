-- Nettoyage de l'environnement
DROP DATABASE IF EXISTS p2p_blog; 

-- Programme SQL de départ, fourni

CREATE DATABASE p2p_blog CHARACTER SET 'utf8';
USE p2p_blog;

CREATE TABLE Categorie (
	id INT UNSIGNED AUTO_INCREMENT,
	nom VARCHAR(150) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE Categorie_article (
	categorie_id INT UNSIGNED,
	article_id INT UNSIGNED,
	PRIMARY KEY (categorie_id, article_id)
);

-- Enrichissement
-- les selects seuls permettent de suivre le déroulement des scripts de création et d'identifier les points de blocages.

-- Modification des tables de base
SELECT 'Modification table Categorie';
-- Ajout de la colonne 'description' et de l'unicité du nom
ALTER TABLE Categorie
    ADD description VARCHAR(150),
    ADD UNIQUE idx_cat_nom (nom);

SELECT 'Creation table Utilisateurs';
CREATE TABLE Utilisateurs (
	id_util INT UNSIGNED AUTO_INCREMENT,
	util_pseudo VARCHAR(50) NOT NULL UNIQUE,
    util_email VARCHAR(254),
    util_pwd varchar(254),
    PRIMARY KEY(id_util)
)
ENGINE = INNODB;

SELECT 'Creation table Articles';
CREATE TABLE Articles (
	id_art INT UNSIGNED AUTO_INCREMENT,
	art_titre VARCHAR(150) NOT NULL,
    art_texte LONGTEXT,
    art_resume TEXT,
    art_auteur INT UNSIGNED NOT NULL,
    art_date DATE NOT NULL,
    art_categ INT UNSIGNED NOT NULL, -- catégorie principale ("Les articles doivent appartenir à au moins une catégorie")
	PRIMARY KEY(id_art),
    CONSTRAINT fk_art_auteur FOREIGN KEY (art_auteur) REFERENCES utilisateurs(id_util) ON DELETE RESTRICT,
    CONSTRAINT fk_art_categ FOREIGN KEY (art_categ) REFERENCES Categorie (id) ON DELETE RESTRICT,
--    CONSTRAINT fk_id_categ FOREIGN KEY(id_art) REFERENCES Categorie_article (categorie_id), retiré car crée des contraintes croisées et avec Catégorie_Article et bloque la création d'articles.
    UNIQUE idx_titre_aut_date (art_titre, art_auteur, art_date)
) ENGINE = INNODB;

SELECT 'Modification table Categorie_Article'; -- Ajout des contraintes
ALTER TABLE Categorie_article
    ADD CONSTRAINT fk_CA_catid FOREIGN KEY (categorie_id) REFERENCES categorie(id) ON DELETE RESTRICT,
    ADD CONSTRAINT fk_CA_artid FOREIGN KEY (article_id) REFERENCES articles(id_art) ON DELETE CASCADE;

SELECT 'creation table commentaires';
CREATE TABLE IF NOT EXISTS Commentaires (
	id_comment INT UNSIGNED AUTO_INCREMENT,
	com_util INT UNSIGNED,  -- peut être nul si utilisateur non enregistré
    com_art INT UNSIGNED NOT null,
    com_commentaire TEXT,
    com_date DATETIME NOT null DEFAULT now(),
    PRIMARY KEY(id_comment),
    CONSTRAINT fk_com_util FOREIGN KEY (com_util) REFERENCES utilisateurs(id_util) ON DELETE CASCADE,
    CONSTRAINT fk_com_art FOREIGN KEY (com_art) REFERENCES articles(id_art) ON DELETE CASCADE
)
ENGINE = INNODB;
