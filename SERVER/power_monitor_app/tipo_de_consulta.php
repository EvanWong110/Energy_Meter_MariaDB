<?php
require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados
date_default_timezone_set('America/Fortaleza');      //configura a timezone
$hostname = $_SESSION['ini_array']['HOST'];
$username = $_SESSION['ini_array']['USER'];
$password = $_SESSION['ini_array']['PASSWORD'];
if (isset($_POST['database'])){
    $_SESSION['database'] = $_POST['database'];
}
$dbconnect=mysqli_connect($hostname,$username,$password,$_SESSION['database']);
?>

<html>
<head>
    <meta charset="utf-8" />
    <title>Power Monitor App</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <style>
      .card-login {
        padding: 30px 0 0 0;
        width: 350px;
        margin: 0 auto;
      }
    </style>
  </head>

  <body>
  <nav class="navbar navbar-dark bg-dark">
        <a class="navbar-brand" href="#">
          <img src="logo.png" width="30" height="30" class="d-inline-block align-top" alt="">
          Power Monitor App
        </a>
       
        <ul class="nav">
        <li class="nav-item">
            <a class="nav-link" href="select_database.php">VOLTAR</a>  <!--Executa logoff da página -->
        </li>
        <li class="nav-item">
            <a class="nav-link" href="logoff.php">SAIR</a>  <!--Executa logoff da página -->
        </li>
        </ul>
  </nav>
  <div>
       
    <div class="container" >    
        <div class="row">
            <div class="card" style="width: 50rem;">      
                <div class="card" >
                    <center>
                    <div class="card-header">
                        Selecione um período e um tipo de consulta:
                    </div>
                    <div class="card-body">
                        <form action="direciona.php" method="post">
                            <div class="card-body"> 
                                <div class="card-body"> 
                                    Inicio:
                                    <input type="datetime-local" id="begin_time" name="begin_time"
                                    <?php 
                                    $date1hourago = strtotime('-1 hour');
                                    print('value='.date('Y-m-d\TH:i',$date1hourago));  #atualiza com a data atual
                            ?>                      
                                    > 
                                </div>
                                <div class="card-body"> 
                                    Fim:
                                    <input type="datetime-local" id="end_time" name="end_time"
                                    <?php 
                                    echo('value='.date('Y-m-d\TH:i'));  #atualiza com a data atual
                            ?>                      
 
                                    > 
                                </div><br/>
                            </div>
                            <input type="radio" id="grafico" name="tipo" value="grafico">
                            <label for="detalhada">Consulta por Gráfico</label><br>
                            <input type="radio" id="alarmes" name="tipo" value="alarmes">
                            <label for="alarmes">Consulta de Alarmes</label><br>
                            <input type="radio" id="basica" name="tipo" value="basica">
                            <label for="basica">Consulta Básica</label>
                            <br/><br/>              
                            <button class="btn btn-lg btn-info btn-block" type="submit">Selecionar</button>
                        </form>
                    </div>
                </div>
            </div>
            <div class="card" style="width: 15rem;">
                <div class="card-header">    
                <ul>
                    <li> Detalhada: Apresenta um gráfico do período com todas as amostras coletadas. </li>
                    <li> Consulta de Alarmes: Apresenta uma lista com todos os alarmes registrados no período. </li>
                    <li> Consulta Básica: Apresenta um resumo de consumo e log das falhas mais recentes. </li>
                </ul>
                </div>
            </div>
        </div>
    </div>
  </body>
</html>