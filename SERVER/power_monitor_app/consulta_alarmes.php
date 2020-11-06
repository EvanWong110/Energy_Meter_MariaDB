<?php
require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados
date_default_timezone_set('America/Fortaleza');      //configura a timezone
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

  <?php
print_r($_SESSION);
?>

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
<?php
  date_default_timezone_set('America/Sao_Paulo');      //configura a timezone
    if(isset($_SESSION['begin_time']) && isset($_SESSION['end_time'])){      //exige preenchimento dos inputs de pesquisa
        $time1 = (string) strtotime($_SESSION['begin_time']);            //selecao de itens pesquisados UnixTIMESTAMP
        $time2 = (string) strtotime($_SESSION['end_time']);
        $tamanho = (int) $time2 - (int) $time1;            

        $hostname = $_SESSION['ini_array']['HOST'];
        $username = $_SESSION['ini_array']['USER'];
        $password = $_SESSION['ini_array']['PASSWORD'];
        $database = $_SESSION['database'];

        $dbconnect=mysqli_connect($hostname,$username,$password, $database);
 
        if ($dbconnect->connect_error) {
            die("Database connection failed: " . $dbconnect->connect_error);
        }
            $comando = "SELECT * FROM data WHERE timestamp BETWEEN $time1 AND $time2";
            $query = mysqli_query($dbconnect, $comando)
            or die (mysqli_error($dbconnect));                  
    }
      	$data=array();
    if(isset($tamanho)){    
        while ($row = mysqli_fetch_array($query)) {
            $data[]=array(
                (int) $row['timestamp'], 
                (float) $row['tensao'], 
                (float) $row['corrente'],
                (float) $row['pot_re'],
                (float) $row['pot_ap'],
                (float) $row['pot_at'],
                (float) $row['freq'],
                (float) $row['FP']
            );
            $data2[]=array(
                (float) $row['apparent_energy'],
                (float) $row['active_energy']           
            );
        }
    }
  ?>

  </body>
</html>