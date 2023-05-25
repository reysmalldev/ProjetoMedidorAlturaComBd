<?php
 $servername = "localhost";
 $username = "root";
 $password = "";
 $dbname = "bdaltura";
 $conn = new mysqli($servername, $username, $password, $dbname);
 if ($conn->connect_error) {
     //Gravar log de erros
     die("Não foi possível estabelecer conexão com o BD: " . $conn->connect_error);
 } else {
    echo '<br>conexão criada com sucesso!<br>';
 }
 $conn->close();
?>