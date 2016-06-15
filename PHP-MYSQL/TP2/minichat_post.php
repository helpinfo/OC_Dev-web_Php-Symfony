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

// Insertion du message à l'aide d'une requête préparée
$req = $bdd->prepare('INSERT INTO minichat (pseudo, message, date_message) VALUES(?, ?, NOW())');
$req->execute(array($_POST['pseudo'], $_POST['message']));
$_SESSION['pseudo'] = $_POST['pseudo'];

// Puis rediriger vers minichat.php comme ceci :
header('Location: minichat.php');
?>