-- Tables
CREATE TABLE Article (
	id INT UNSIGNED AUTO_INCREMENT,
	titre VARCHAR(200) NOT NULL,
	resume TEXT,
	contenu TEXT NOT NULL,
	auteur_id INT UNSIGNED NOT NULL,
	date_publication DATETIME NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE Utilisateur (
	id INT UNSIGNED AUTO_INCREMENT,
	pseudo VARCHAR(100) NOT NULL,
	email VARCHAR(200) NOT NULL,
	password CHAR(40) NOT NULL,   -- le mot de passe sera hashé avec sha1, ce qui donne toujours une chaîne de 40 caractères
	PRIMARY KEY(id)
);

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

CREATE TABLE Commentaire (
	id INT UNSIGNED AUTO_INCREMENT,
	article_id INT UNSIGNED NOT NULL,
	auteur_id INT UNSIGNED,
	contenu TEXT NOT NULL,
	date_commentaire DATETIME NOT NULL,
	PRIMARY KEY(id)
);

-- Clés étrangères
ALTER TABLE Article 
ADD CONSTRAINT fk_auteur_article FOREIGN KEY (auteur_id) REFERENCES Utilisateur(id);

ALTER TABLE Categorie_article 
ADD CONSTRAINT fk_article_cat FOREIGN KEY (article_id) REFERENCES Article(id),
ADD CONSTRAINT fk_categorie_cat FOREIGN KEY (categorie_id) REFERENCES Categorie(id);

ALTER TABLE Commentaire  
ADD CONSTRAINT fk_article_com FOREIGN KEY (article_id) REFERENCES Article(id),
ADD CONSTRAINT fk_auteur_com FOREIGN KEY (auteur_id) REFERENCES Utilisateur(id);

-- Index
CREATE UNIQUE INDEX unique_email
ON Utilisateur(email);

CREATE UNIQUE INDEX unique_pseudo
ON Utilisateur(pseudo);

CREATE INDEX index_date_article 
ON Article(date_publication);

CREATE INDEX index_date_commentaire
ON Commentaire(date_commentaire);
