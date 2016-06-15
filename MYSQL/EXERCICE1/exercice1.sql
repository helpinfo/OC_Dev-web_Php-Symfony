#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------

#------------------------------------------------------------
# BASE: p2p_blog
#------------------------------------------------------------

-- CREATE DATABASE p2p_blog CHARACTER SET 'utf8';
USE p2p_blog;

#------------------------------------------------------------
# Table: Article
#------------------------------------------------------------

CREATE TABLE Article(
        article_id int UNSIGNED AUTO_INCREMENT NOT NULL,
        titre Varchar (255) NOT NULL,
        texte Text NOT NULL,
        resume Varchar (255) NOT NULL,
        date_creation Date NOT NULL,
        utilisateur_id Int UNSIGNED NOT NULL,
        PRIMARY KEY (article_id )
)ENGINE=InnoDB;

--
-- Contenu de la table `Article`
--

INSERT INTO `Article` (`article_id`, `titre`, `texte`, `resume`, `date_creation`, `utilisateur_id`) VALUES
(1, 'Nouvel ASR 1002-HX', 'L’ASR 1000 continue de progresser sur le plan des performances. J’avais à ce titre annoncé dans cet article 2 châssis 1006-X et 1009-X avec des interfaces 100GE en septembre dernier. Nous continuons de faire évoluer les modèles « tout-en-un » avec l’ASR1001-X (jusqu’à 20Gbps) et maintenant l’ASR1002-HX qui offre jusqu’à 100Gbps de performance, et une densité d’interfaces vraiment intéressante. Regardons les principales caractéristiques de ce routeur…', 'L’ASR 1000 continue de progresser sur le plan des performances. J’avais à ce titre annoncé dans cet article 2 châssis 1006-X et 1009-X avec des interfaces 100GE en septembre dernier...', '2016-06-14', 1),
(2, 'Outil pour la mesure de la QoS sur les réseaux IP', 'La qualité de service (QoS pour "Quality of service") est la capacité à véhiculer dans de bonnes conditions un type de trafic donné en termes de disponibilité, débit, délai de transmission, gigue, taux de perte de paquets... (source Wiki)\r\n\r\nLa notion de qualité de service est une notion subjective, de ressenti utilisateur face à l''utilisation d''un système informatique. Il n''est pas trivial de mesurer cette QoS. Nous allons dans ce billet aborder quelques outils libres permettant d''obtenir des indicateurs chiffrés en nous focalisant sur la problématique des réseaux IP.', 'La qualité de service (QoS pour "Quality of service") est la capacité à véhiculer dans de bonnes conditions un type de trafic donné en termes de disponibilité, débit, délai de transmission, gigue, taux de perte de paquets... (source Wiki)', '2009-03-13', 3),
(3, 'Instagram annonce le changement de son algorithme', 'C’est la nouvelle qui a fait le plus parler d’elle ce mois-ci. Personne ne sait quand, mais Instagram va classer les photos et les vidéos dans le fil d’actualités des utilisateurs pour leur montrer les contenus les plus « intéressants » en premier.', 'C’est la nouvelle qui a fait le plus parler d’elle ce mois-ci. Personne ne sait quand, mais Instagram va ...', '2016-04-25', 2),
(4, 'Les moteurs de croissance derrière les systèmes de bases de données multi-modèles', 'En 2014, le bureau d''étude Gartner a indiqué dans le rapport « Magic Quadrant for Operational Database Management Systems » qu''en 2017 la qualification « NoSQL » ne permettrait plus d''opérer une distinction entre des modèles de base de données. Et au rapport Gartner de conclure que « d''ici là, tous les fournisseurs offriront des systèmes de base de données qui regroupent les modèles NoSQL et relationnels en une seule et même plate-forme ».', 'En 2014, le bureau d''étude Gartner a indiqué dans le rapport « Magic Quadrant for Operational Database Management Systems » qu''en 2017 la qualification « NoSQL »', '2016-03-15', 2);



#------------------------------------------------------------
# Table: Utilisateur
#------------------------------------------------------------

CREATE TABLE Utilisateur(
        utilisateur_id int UNSIGNED AUTO_INCREMENT NOT NULL,
        pseudo Varchar (255) NOT NULL,
        email Varchar (255) NOT NULL,
        mot_de_passe Varchar (255) NOT NULL,
        PRIMARY KEY (utilisateur_id),
        UNIQUE (pseudo)
)ENGINE=InnoDB;

--
-- Contenu de la table `Utilisateur`
--

INSERT INTO `Utilisateur` (`utilisateur_id`, `pseudo`, `email`, `mot_de_passe`) VALUES
(1, 'mikamin', 'mikadmin@gmail.com', SHA1('tonton')),
(2, 'paty', 'paty@yahoo.fr', SHA1('tata')),
(3, 'helpinfo', 'hello@world.com', SHA1('#ti2UY7gfZ.'));

#------------------------------------------------------------
# Table: Categorie
#------------------------------------------------------------

CREATE TABLE Categorie (
	id INT UNSIGNED AUTO_INCREMENT,
	nom VARCHAR(150) NOT NULL,
	PRIMARY KEY(id)
);

ALTER TABLE `Categorie` ADD `description` VARCHAR(255) NOT NULL ;

--
-- Contenu de la table `Categorie`
--

INSERT INTO `Categorie` (`id`, `nom`, `description`) VALUES
(1, 'Réseau', 'Tous ce qui touche les réseaux informatique'),
(2, 'Sgbd', 'Système de gestion de base de données'),
(3, 'Web', 'Tous ce qui ce passe sur le net'),
(4, 'Équipement', 'Équipement informatique');

#------------------------------------------------------------
# Table: Categorie_article
#----------------------------

CREATE TABLE Categorie_article (
	categorie_id INT UNSIGNED,
	article_id INT UNSIGNED,
	PRIMARY KEY (categorie_id, article_id)
);

--
-- Contenu de la table `Categorie_article`
--

INSERT INTO `Categorie_article` (`categorie_id`, `article_id`) VALUES
(1, 1),
(4, 1),
(1, 2),
(3, 3),
(2, 4);

#------------------------------------------------------------
# Table: Commentaire
#------------------------------------------------------------

CREATE TABLE Commentaire(
        commentaire_id int UNSIGNED AUTO_INCREMENT NOT NULL,
        contenu Text NOT NULL,
		date_commentaire Date NOT NULL ,
        utilisateur_id Int UNSIGNED,
        article_id Int UNSIGNED NOT NULL,
        PRIMARY KEY (commentaire_id )
)ENGINE=InnoDB;

--
-- Contenu de la table `Commentaire`
--

INSERT INTO `Commentaire` (`commentaire_id`, `contenu`, `utilisateur_id`, `article_id`) VALUES
(1, 'prem''s', 1, 1),
(2, '+1', NULL, 2),
(3, 'trooolooooooollooooolloooooo !!!!! youppii jue suisss inconu !!', NULL, 3),
(4, 'Super article merci du partage !!', 2, 4),
(5, 'Bon ben on va faire fumer la carte bleu !!', 3, 1);

#------------------------------------------------------------
# Contrainte de clé étrangère
#------------------------------------------------------------

ALTER TABLE Article ADD CONSTRAINT FK_Article_utilisateur_id FOREIGN KEY (utilisateur_id) REFERENCES Utilisateur(utilisateur_id);

ALTER TABLE Commentaire ADD CONSTRAINT FK_Commentaire_utilisateur_id FOREIGN KEY (utilisateur_id) REFERENCES Utilisateur(utilisateur_id);
ALTER TABLE Commentaire ADD CONSTRAINT FK_Commentaire_article_id FOREIGN KEY (article_id) REFERENCES Article(article_id);

ALTER TABLE Categorie_article ADD CONSTRAINT FK_Categorie_article_article_id FOREIGN KEY (article_id) REFERENCES Article(article_id);
ALTER TABLE Categorie_article ADD CONSTRAINT FK_Categorie_article_categorie_id FOREIGN KEY (categorie_id) REFERENCES Categorie(id);
