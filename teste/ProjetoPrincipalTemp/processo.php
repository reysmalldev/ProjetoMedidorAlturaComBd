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

        include 'conexao.php';

        if (filter_input(INPUT_SERVER,'REQUEST_METHOD') == 'POST') {
            $nome = filter_input(INPUT_POST,'nome');
            $idade = filter_input(INPUT_POST,'idade');
            $peso = filter_input(INPUT_POST,'peso');
            print 'Dados que serão inseridos<hr>';
            print "nome: {$nome}<br>Idade: {$idade}<br>Peso: {$peso}";
        }
        else {
            print "Deu ruim";
        }

        $altura = filter_input(INPUT_GET, 'alturaPessoa',FILTER_SANITIZE_NUMBER_FLOAT);
        if (is_null($altura)) {
            echo("<hr>Dados inválidos");
        } else {
            echo("<hr>Dados validos");
        }

        /*
        $sql = "INSERT INTO pessoa (nome, idade, peso)
        VALUES ('$nome', '$idade', '$peso')";

        if (!$conn->query($sql)) {
            //Gravar log de erros
            die("Erro na gravação dos dados no BD");
            
        }
        $conn->close();
        */

        //Conecta ao banco de dados
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "bdaltura";

        //Cria uma conexão
        $conn = mysqli_connect($servername, $username, $password, $dbname);

        //Verifica se houve erro na conexão
        if (!$conn) {
            die("Conexão falhou: " . mysqli_connect_error());
        }

        //Prepara a query INSERT
        $sql = "INSERT INTO pessoa (nome, idade, peso, altura)
        VALUES ('$nome', '$idade', '$peso', '$altura')";

        //Executa a query somente se todas as informações estiverem completas(não esta funcionando)
        if (empty($nome) && empty($idade) && empty($peso) && empty($altura)) {
            if (mysqli_query($conn, $sql)) {
                echo "<br><hr>Inserção realizada com sucesso!";
                echo "altura: ".$altura;
            } else {
                echo "<br><hr>Erro ao inserir na tabela: " . mysqli_error($conn);
            }
          } else {
            echo 'Sim! Estou vazio!<br>';
            echo 'dados incompletos';
          }
        
        //Fecha a conexão
        mysqli_close($conn);
    ?>
</body>
</html>