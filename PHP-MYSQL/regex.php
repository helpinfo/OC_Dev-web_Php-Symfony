<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Mon super site</title>
    </head>
    <body>
		<!-- regex verif telephone -->
		<p>
		<?php
		if (isset($_POST['telephone']))
		{
			$_POST['telephone'] = htmlspecialchars($_POST['telephone']); // On rend inoffensives les balises HTML que le visiteur a pu entrer

			if (preg_match("#^0[1-68]([-. ]?[0-9]{2}){4}$#", $_POST['telephone']))
			{
				echo 'Le ' . $_POST['telephone'] . ' est un numéro <strong>valide</strong> !';
			}
			else
			{
				echo 'Le ' . $_POST['telephone'] . ' n\'est pas valide, recommencez !';
			}
		}
		?>
		</p>

		<form method="post">
		<p>
			<label for="telephone">Votre téléphone ?</label> <input id="telephone" name="telephone" /><br />
			<input type="submit" value="Vérifier le numéro" />
		</p>
		</form>
		
		<!-- regex verif mail -->
		<p>
		<?php
		if (isset($_POST['mail']))
		{
			$_POST['mail'] = htmlspecialchars($_POST['mail']); // On rend inoffensives les balises HTML que le visiteur a pu rentrer

			if (preg_match("#^[a-z0-9._-]+@[a-z0-9._-]{2,}\.[a-z]{2,4}$#", $_POST['mail']))
			{
				echo 'L\'adresse ' . $_POST['mail'] . ' est <strong>valide</strong> !';
			}
			else
			{
				echo 'L\'adresse ' . $_POST['mail'] . ' n\'est pas valide, recommencez !';
			}
		}
		?>
		</p>

		<form method="post">
		<p>
			<label for="mail">Votre mail ?</label> <input id="mail" name="mail" /><br /> 
			<input type="submit" value="Vérifier le mail" />
		</p>
		</form>
    </body>
</html>