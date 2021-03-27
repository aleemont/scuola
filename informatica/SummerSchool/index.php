<head>
    <title>Summer School</title>
</head>
<body>
    <form action="queries.php" method="GET">
    <select id="studenti" name="studenti">
    <?php
        $dbuser = "ospite";
        $dbpassword = "ospite";
        try{
          $pdo = new PDO("mysql:dbname=SummerSchool;host=localhost",$dbuser,$dbpassword);
        } catch (PDOException $e) {
          echo 'Connection failed: '.$e->getMessage();
        }
        $query = "SELECT idStudente, Nome, Cognome FROM SC_STUDENTE;";
        $stmt = $pdo -> query($query);
        $res = $stmt -> fetchAll(PDO::FETCH_ASSOC);
        foreach ($res as $row) {
            echo '<option value="'.$row["idStudente"].'">'.$row["idStudente"]." ".$row["Nome"]." ".$row["Cognome"].'</option>';
        }
      ?>
    </select>
    <input type="submit" value="Invia"/>
    </form>
</body>
    
	
