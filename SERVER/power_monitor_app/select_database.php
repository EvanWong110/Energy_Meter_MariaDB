<?php
require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados
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


  
<?php
        $projeto_root = (explode("SERVER",$_SERVER['DOCUMENT_ROOT']));
        $ini_array_full = parse_ini_file($projeto_root[0].'/config.ini', true);
        $ini_array = $ini_array_full['MARIADB_DATABASE'];
        $_SESSION['ini_array'] = $ini_array;       
        $hostname = $ini_array['HOST'];
        $username = $ini_array['USER'];
        $password = $ini_array['PASSWORD'];
        $dbconnect=mysqli_connect($hostname,$username,$password,'information_schema');
        $databases = array();
 
        if ($dbconnect->connect_error) {
            die("Database connection failed: " . $dbconnect->connect_error);
        }
            $comando = "SHOW DATABASES;";
            $query = mysqli_query($dbconnect, $comando)
            or die (mysqli_error($dbconnect));                  

        while ($row = mysqli_fetch_array($query)) {
            array_push($databases, $row[0]);
        }
?>

    <nav class="navbar navbar-dark bg-dark">
        <a class="navbar-brand" href="#">
          <img src="logo.png" width="30" height="30" class="d-inline-block align-top" alt="">
          Power Monitor App
        </a>
        <ul class="navbar-nav">
        <li class="nav-item">
          <a class="nav-link" href="logoff.php">SAIR</a>  <!--Executa logoff da página -->
      </ul>
      </nav>
      <div class="container">    
        <div class="row">
          <div class="card-login">
            <div class="card">
              <div class="card-header">
                Selecione um dispositivo:
              </div>
              <div class="card-body">
                <form action="tipo_de_consulta.php" method="post">
                    <label for="database">Database:</label>
                    <select id="database" name="database">
                      <?php foreach($databases as $database)
                      {
                        print "<option value=$database>$database</option>";
                      }
                      ?>
                      </select>
                      <br/>              
                      <br/>              
                    <button class="btn btn-lg btn-info btn-block" type="submit">Selecionar</button>
                  </form>
              </div>
            </div>
          </div>
      </div>
    </body>