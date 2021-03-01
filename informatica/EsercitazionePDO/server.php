<?php
	$dbhost = "localhost";
	$dbuser = "ospite";
	$dbpass = "ospite";
	$db = "grossisti";

	$p = new PDO('mysql:host='.$dbhost.';dbname='.$db.'', $dbuser, $dbpass);

	$table = $_POST["tabelle"];
	$r = $p->query("SELECT * FROM $table LIMIT 25");
?>

<html>
	<head>
		<title>Tabelle</title>
	</head>
	<?php
		switch($table){
			case "Clienti":
				 ?>
				 echo $table;
				<table border=1>
					<th>Cod</th>
					<th>Cognome</th>
					<th>Nome</th>
					<th>Provincia</th>
					<th>Rappresentante</th>
					<tbody>
						<?php while($fetch = $r->fetch()){ ?>
							<tr>
									<td><?php echo $fetch['cod']?></td>
									<td><?php echo $fetch['cognome']?></td>
									<td><?php echo $fetch['nome']?></td>
									<td><?php echo $fetch['provincia']?></td>
									<td><?php echo $fetch['rappresentante']?></td>
							</tr>
						<?php } ?>
					</tbody>
				</table>
				<?php break;
			case "Fatture":
				echo $table; ?>
				<table border=1>
					<th>Numero</th>
					<th>Data</th>
					<th>Importo</th>
					<th>Cliente</th>
					<tbody>
						<?php while($fetch = $r->fetch()){ ?>
							<tr>
									<td><?php echo $fetch['numero']?></td>
									<td><?php echo $fetch['data']?></td>
									<td><?php echo $fetch['importo']?></td>
									<td><?php echo $fetch['cliente']?></td>
							</tr>
						<?php } ?>
					</tbody>
				</table>
				<?php break;
			case "Rappresentanti":
				echo $table; ?>
				<table border=1>
					<th>Matricola</th>
					<th>Cognome</th>
					<th>Nome</th>
					<tbody>
						<?php while($fetch = $r->fetch()){ ?>
							<tr>
									<td><?php echo $fetch['matr']?></td>
									<td><?php echo $fetch['cognome']?></td>
									<td><?php echo $fetch['nome']?></td>
							</tr>
						<?php } ?>
					</tbody>
				</table>
				<?php break; ?>
	<?php	}?>
</html>
