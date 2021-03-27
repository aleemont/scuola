<?php

  include("index.php");

  $studente="";
  if (isset($_GET["studenti"])) {
    $studente = $_GET["studenti"];
  }
  $query = "SELECT SC_FREQUENTA.idCorso, SC_CORSO.Argomento
    FROM SC_STUDENTE, SC_FREQUENTA, SC_CORSO
    WHERE SC_STUDENTE.idStudente=SC_FREQUENTA.idStudente and SC_FREQUENTA.idCorso=SC_CORSO.idCorso
    and SC_STUDENTE.idStudente=" . $studente . ";";
  $stmt = $pdo -> query($query);
  try{
    $res = $stmt -> fetchAll(PDO::FETCH_ASSOC);
  }
  catch(Exception $e){
    echo $e->getMessage();
  }
  echo "<h3>Studente ".$studente."</h3>";
  echo '<table style="border-collapse: collapse">';
  echo "<tr>";
  foreach ($res[0] as $key => $value) {
    echo '<th style="border: 1px solid #000;">'.$key."</th>";
  }
  echo "</th>";
  foreach ($res as $row) {
    echo "<tr>";
    foreach ($row as $key => $value) {
      echo '<td style="border: 1px solid #000;">'.$value."</td>";
    }
    echo "</tr>";
  }
  echo "</table>";
  
?>
