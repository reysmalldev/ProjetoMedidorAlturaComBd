<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CalculoFeito</title>
</head>
<body>
    
    <?php

        //include 'conexao.php';

        if (filter_input(INPUT_SERVER,'REQUEST_METHOD') == 'POST') {
            $nome = filter_input(INPUT_POST,'nome');
            $idade = filter_input(INPUT_POST,'idade');
            $peso = filter_input(INPUT_POST,'peso');
            print 'Dados que serão inseridos<hr>';
            print "nome: {$nome}<br>Idade: {$idade}<br>Peso: {$peso}<br>";
        }
        else {
            print "Deu ruim";
        }

        //Conecta ao banco de dados
        $servername = "85.10.205.173";
        $username = "usercaue_14";
        $password = "mlkzicka";
        $dbname = "db_caue14";

        //Cria uma conexão
        $conn = mysqli_connect($servername, $username, $password);

        //Verifica se houve erro na conexão
        if ($conn->connect_error) {
            //Gravar log de erros
            die("Não foi possível estabelecer conexão com o BD: " . $conn->connect_error);
        } else {
            echo "conexão criada com sucesso!";
        }

        //Prepara a query INSERT
        $sql = "INSERT INTO db_caue14.pessoa (nome, idade, peso) VALUES ('$nome', '$idade', $peso)";

        if (mysqli_query($conn, $sql)) {
            echo "<br><hr>Inserção realizada com sucesso!";
                
        } else {
            echo "<br><hr>Erro ao inserir na tabela: " . mysqli_error($conn);
        }
        
        //Fecha a conexão
        mysqli_close($conn);
    ?>
</body>
</html>
