<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Minichat</title>
        <style>
            h1,form {
                width:50%; margin: 5px auto;
            }
            label {
                width:25%; float:left;
            }
            input[type="submit"]{
                margin-left:25%;
            }
        </style>
    </head>
    <body>

        <h1>Participer au minichat :</h1>
        <form method="post" action="minichat_post.php">
            <label for="message">Pseudo :</label><input type="text" name="pseudo" id="pseudo" value="<?php echo $_COOKIE['pseudo'] ?>"/><br>
            <label for="message">Message :</label><input type="text" name="message" id="message"/><br>
            <input type="submit" value="Envoyer"/>
        </form>

        <?php
        // connexion à la base de données
        try {
            $bdd = new PDO('mysql:host=localhost;dbname=activiteminichat;charset=utf8', 'root', 'root', array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION));
        } catch (Exception $e) {
            die('Erreur : ' . $e->getMessage());
        }
        // requête et boucle pour afficher les 20 derniers messages
        $reponse = $bdd->query('SELECT pseudo, message, DATE_FORMAT(date_ajout, "%d/%m/%Y %Hh%imin%ss") AS date FROM minichat ORDER BY ID DESC LIMIT 0,20');
        while ($donnees = $reponse->fetch()) {
            echo '<p> [' . htmlspecialchars($donnees['date']) . '] <strong>' . htmlspecialchars($donnees['pseudo']) . '</strong> :  ' . htmlspecialchars($donnees['message']) . '</p>';
        }
        // Clotûre de la requête
        $reponse->closeCursor();
        ?>

    </body>
</html>

