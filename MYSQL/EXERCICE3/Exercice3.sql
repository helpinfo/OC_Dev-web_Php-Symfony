/* *********************
  Gestion Commentaire
********************* */

## ------------------
##  Vue matèrialisée
## ------------------

CREATE TABLE VM_Nombre_commentaires
ENGINE = InnoDB
SELECT Article.id AS Art_id,
	DATE_FORMAT(Date_publication, '%d/%m/%Y') AS Date_publication,
	Utilisateur.pseudo AS Auteur,
	Article.titre AS Titre,
	Article.resume AS Résumé,
	COUNT(commentaire.id) AS Nbr_Commentaires
FROM Article
INNER JOIN Utilisateur 
	ON Article.auteur_id = Utilisateur.id
INNER JOIN Commentaire
	ON Commentaire.article_id = Article.id
GROUP BY Article.date_publication, Utilisateur.pseudo, Article.titre, Article.resume
ORDER BY date_publication DESC;

ALTER TABLE `vm_nombre_commentaires` 
	ADD PRIMARY KEY(`Art_id`);
	
ALTER TABLE VM_Nombre_commentaires 
	ADD CONSTRAINT fk_vm_nombre_commentaires FOREIGN KEY (Art_id) REFERENCES Article(id);

## ---------
##  TRIGGER
## ---------
	
DELIMITER |

-- -------------------
--  Ajout commentaire
-- -------------------

CREATE TRIGGER before_insert_commentaire BEFORE INSERT
ON Commentaire FOR EACH ROW
BEGIN
	/* IF {Condition voir si des commentaire existe} THEN
		
			-- si aucun commentaire existe
			-- ajout d'une nouvelle ligne dans VM_Nombre_commentaires
			-- avec 1 en valeur à Nbr_Commentaires
			
			-- (J'ai beau lire les cours et fouiner sur le net j'arrive pas a mettre en place cette condition !!)
		
		END IF; 
	*/
	
	-- Si commentaire >= 1 alors mise à jour de la valeur de Nbr_Commentaires à +1
	UPDATE VM_Nombre_commentaires
	SET Nbr_Commentaires = Nbr_Commentaires + 1
	WHERE Art_id = NEW.article_id;
END |

-- -------------------------
--  suppression commentaire
-- -------------------------

CREATE TRIGGER after_delete_commentaire AFTER DELETE
ON Commentaire FOR EACH ROW
BEGIN	
		-- S'il reste des commentaires mise à jours de Nbr_Commentaires
		UPDATE VM_Nombre_commentaires
		SET Nbr_Commentaires = Nbr_Commentaires - 1
		WHERE Art_id = OLD.article_id;
		
		-- Si tous les commentaire d'un article sont supprimer, suppression de la ligne dans VM_Nombre_commentaires
		DELETE FROM VM_Nombre_commentaires
		WHERE Art_id = OLD.article_id
		AND Nbr_Commentaires = 0;	
END |

DELIMITER ;


/* *********************
  Gestion Article
********************* */

/* 
	Vu qu'un article corporte obligatoirement une categorie 
	j'ai décidé de poser un trigger sur cette table 
	pour automatiser le controle de la présence du resumé
*/


## -----------
##  PROCEDURE
## -----------

/* Prend en paramètre l'id de l'article envoyé par le trigger after_insert_categorie_article */
DELIMITER |
	
	CREATE PROCEDURE update_resume_article(IN p_new_article_id INT)
	BEGIN
		-- Si le resumé de l'article est vide alors mise a jour avec les 150 premiers charactère
		UPDATE Article
			SET resume = SUBSTR(contenu, 1, 150)
			WHERE id = p_new_article_id
				AND resume IS NULL;
	END|
	
DELIMITER ;

-- -------------------------
--  Ajout categorie
-- -------------------------


## ---------
##  TRIGGER
## ---------

DELIMITER |

CREATE TRIGGER after_insert_categorie_article AFTER INSERT
ON categorie_article FOR EACH ROW
BEGIN	
		-- Envoie de l'id du nouvel article à la procedure 
		-- Pour vérification et update si nécéssaire.
		CALL update_resume_article(NEW.article_id);						
END |

DELIMITER ;


/* **************************
  Gestion Statistique admin
************************** */

/*
	Avec une simple commande les admin peuvent voir les statisque
	
	Syntax : CALL statistique_admin();
*/

## -----------
##  PROCEDURE
## -----------

DELIMITER |
	
	CREATE PROCEDURE update_statistique() -- Cette Procedure créée et mais a jours les diferente vue
	BEGIN
		CREATE OR REPLACE VIEW V_total_inscrit
		AS SELECT COUNT(*) AS Total_Inscrit 
		FROM utilisateur;

		CREATE OR REPLACE VIEW V_total_article
		AS SELECT COUNT(*) AS Total_Article 
		FROM article;

		CREATE OR REPLACE VIEW V_dernier_article
		AS SELECT date_publication AS Date_Dernier_Article
		FROM article
		ORDER BY date_publication DESC
		LIMIT 0,1;

		CREATE OR REPLACE VIEW V_total_commentaire
		AS SELECT COUNT(*) AS Total_Commentaire 
		FROM commentaire;

		CREATE OR REPLACE VIEW V_dernier_commentaire
		AS SELECT date_commentaire AS Date_Dernier_commentaire
		FROM commentaire
		ORDER BY date_commentaire DESC
		LIMIT 0,1;
		
		CREATE OR REPLACE VIEW V_statistique_admin 
		AS SELECT * FROM
			V_total_inscrit,
			V_total_article,
			V_dernier_article,
			V_total_commentaire,
			V_dernier_commentaire;					
	END|
	
DELIMITER ;

DELIMITER |
	
	CREATE PROCEDURE statistique_admin() -- Procedure principale lance la procedure d'update des vue et affiche la vue V_statistique_admin
	BEGIN
		Call update_statistique();
		
		SELECT * FROM V_statistique_admin;
		
	END|
	
DELIMITER ;