-- Tables
-- -------
-- -------

-- Tables déjà fournies
-- ------------------------------------------
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
-- ------------------------------------------


CREATE TABLE Article (
	id INT UNSIGNED AUTO_INCREMENT,
	titre VARCHAR(200),
	resume TEXT,
	contenu TEXT,
	auteur_id INT UNSIGNED,
	date_publication CHAR(10),
	PRIMARY KEY(id)
);


CREATE TABLE Utilisateur (
	id INT UNSIGNED AUTO_INCREMENT,
	pseudo VARCHAR(100) NOT NULL,
	email VARCHAR(200) NOT NULL,
	password CHAR(40) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE Commentaire (
	id INT UNSIGNED AUTO_INCREMENT,
	article_id INT UNSIGNED NOT NULL,
	auteur_id INT UNSIGNED NOT NULL,
	contenu TEXT,
	date_commentaire CHAR(10),
	PRIMARY KEY(id)
);

-- Clés étrangères
-- ----------------
-- ----------------

ALTER TABLE Article 
ADD FOREIGN KEY (auteur_id) REFERENCES Utilisateur(id);

ALTER TABLE Categorie_article 
ADD FOREIGN KEY (article_id) REFERENCES Article(id),
ADD FOREIGN KEY (categorie_id) REFERENCES Categorie(id);

ALTER TABLE Commentaire  
ADD FOREIGN KEY (article_id) REFERENCES Article(id),
ADD FOREIGN KEY (auteur_id) REFERENCES Utilisateur(id);

-- Index
-- ------
-- ------

CREATE UNIQUE INDEX unique_email
ON Utilisateur(email);

CREATE UNIQUE INDEX unique_pseudo
ON Utilisateur(pseudo);