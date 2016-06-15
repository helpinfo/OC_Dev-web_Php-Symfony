<?php
// On démarre la session
session_start();
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
		<title>Mon MiniChat</title>
    </head>
	
	<!-- CSS centrage du formulaire -->
	<style>
    form
    {
        text-align:center;
    }
	</style>
 
    <body>
		<!-- Creation formulaire-->
		<form method="post" action="minichat_post.php">
			<p>
			<!-- Champ pseudo avec auto remplissage via variable de session-->
			<label for="pseudo">Pseudo</label> : <input type="text" name="pseudo" id="pseudo" value=<?php echo $_SESSION['pseudo']?> /><br />
			<!-- Champ text-->
			<label for="message">Message</label> : <input type="text" name="message" id="message" /><br />
			<!-- Bouton envoyer-->
			<input type="submit" value="Envoyer" />
		</p>
		</form>
		
<!-- Zone de chat-->
<?php
// connection BASE
try
{
	$bdd = new PDO('mysql:host=localhost;dbname=test;charset=utf8', 'root', '');
}
catch(Exception $e)
{
	die('Erreur : '.$e->getMessage());
}

// requete recupération des 15 derniers messages
$reponse = $bdd->query('SELECT pseudo, message, DATE_FORMAT(date_message, \'%d/%m/%Y à %Hh%imin%ss\') AS date_message_fr FROM minichat ORDER BY ID DESC LIMIT 0, 15');

// Affichage de chaque message (données protégées par htmlspecialchars)
while ($donnees = $reponse->fetch()) 
{
?>

<p><em>[Le <?php echo htmlspecialchars($donnees['date_message_fr']) ?>]</em> <strong><?php echo htmlspecialchars($donnees['pseudo'])?></strong> : <?php echo htmlspecialchars($donnees['message'])?></p>

<?php
}
// cloture de la requete
$reponse->closeCursor();
?>
    </body>
</html>