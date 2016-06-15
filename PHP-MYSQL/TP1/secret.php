<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Mon super site</title>
    </head>
    <body>
		<?php
		if (htmlspecialchars($_POST['pass']) == "kangourou") // SI l'âge est inférieur ou égal à 12
		{
			echo "Bienvenue voici le codes NSA [Ojhdv#256hg*212hsxcert]!<br />";
			
		}
		else // SINON
		{
		echo "L'acces ne vous est pas autorisé !<br />";			
		}
		?>
    </body>
</html>