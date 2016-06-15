<?php setcookie('pseudo',$_POST['pseudo'], time() + 365*24*3600, null, null, false, true); ?>
<?php
// après avoir mis un cookie pour conserver le pseudo, on se connecte à la bdd
try {
    $bdd = new PDO('mysql:host=localhost;dbname=activiteminichat;charset=utf8', 'root', 'root', array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION));
} catch (Exception $e) {

    die('Erreur : ' . $e->getMessage());
}
//Après avoir vérifié si les champs pseudo et message sont remplis on enregistre dans la bdd
if (!empty($_POST['pseudo']) AND !empty($_POST['message'])) {
    $requete = $bdd->prepare('INSERT INTO minichat (pseudo, message,date_ajout) VALUES(?,?,NOW())');
    $requete->execute(array($_POST['pseudo'], $_POST['message']));
}
// Redirection du visiteur vers la page du minichat
header('Location: minichat.php');
?>
