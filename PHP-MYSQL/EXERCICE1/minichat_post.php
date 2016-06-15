<?php
// On démarre la session
session_start();

// Connexion à la base de données
try
{
	$bdd = new PDO('mysql:host=localhost;dbname=test;charset=utf8', 'root', '');
}
catch(Exception $e)
{
        die('Erreur : '.$e->getMessage());
}

// Insertion du message dans la base via un requete préparée
$req = $bdd->prepare('INSERT INTO minichat (pseudo, message, date_message) VALUES(?, ?, NOW())');
$req->execute(array($_POST['pseudo'], $_POST['message']));

// Récupération du pseudo dans la variable de session
$_SESSION['pseudo'] = $_POST['pseudo'];

// Puis rediriger vers minichat.php comme ceci :
header('Location: index.php');
?>