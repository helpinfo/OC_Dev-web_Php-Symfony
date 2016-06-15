<?php
// On démarre la session
session_start();
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
		<link href="style.css" rel="stylesheet" />
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
			<!-- Champ pseudo-->
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

// requete 15 denoiers message
$reponse = $bdd->query('SELECT pseudo, message, DATE_FORMAT(date_message, \'%d/%m/%Y à %Hh%imin%ss\') AS date_message_fr FROM minichat ORDER BY ID DESC LIMIT 0, 15');

// Affichage de chaque message (toutes les données sont protégées par htmlspecialchars)
while ($donnees = $reponse->fetch())
{
	echo '<p><em>[Le ' . htmlspecialchars($donnees['date_message_fr']) . ']</em> <strong>' . htmlspecialchars($donnees['pseudo']) . '</strong> : ' . htmlspecialchars($donnees['message']) . '</p>';
}

$reponse->closeCursor();
?>
    </body>
</html>