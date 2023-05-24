<?php
 $servername = "localhost";
 $username = "root";
 $password = "";
 $dbname = "dbAltura";
 $conn = new mysqli($servername, $username, $password, $dbname);
 if ($conn->connect_error) {
     //Gravar log de erros
     die("Não foi possível estabelecer conexão com o BD: " . $conn->connect_error);
 } 
 $conn->close();
?>