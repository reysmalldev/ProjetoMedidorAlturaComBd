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
    if (filter_input(INPUT_SERVER,'REQUEST_METHOD') == 'POST') {
        $nome = filter_input(INPUT_POST,'nome');
        $idade = filter_input(INPUT_POST,'idade');
        $peso = filter_input(INPUT_POST,'peso');
        
        print "nome: {$nome}<br>Idade: {$idade}<br>Peso: {$peso}";
    }
     else {
        print "Deu ruim";
    }
    ?>
</body>
</html>