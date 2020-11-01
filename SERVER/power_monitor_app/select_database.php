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
        $hostname = "192.168.0.251";
        $username = "admin";
        $password = "password";
        $db = "energymeter";
        $databases = array();
        $dbconnect=mysqli_connect($hostname,$username,$password,$db);

        if ($dbconnect->connect_error) {
            die("Database connection failed: " . $dbconnect->connect_error);
        }
            $comando = "SHOW DATABASES;";
            $query = mysqli_query($dbconnect, $comando)
            or die (mysqli_error($dbconnect));                  

        while ($row = mysqli_fetch_array($query)) {
            array_push($databases, $row[0]);
     #       print($row[0]);
        }
?>


    <nav class="navbar navbar-dark bg-dark">
        <a class="navbar-brand" href="#">
          <img src="logo.png" width="30" height="30" class="d-inline-block align-top" alt="">
          Power Monitor App
        </a>
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
                    <select id="database" name="Selecione">
                      <?php foreach($databases as $database)
                      {
                        print "<option value=$database>$database</option>";
                      }
                      ?>
                      </select>
                      <br/>              
                      <br/>              
                    <button class="btn btn-lg btn-info btn-block" type="submit">Entrar</button>
                  </form>
              </div>
            </div>
          </div>
      </div>
    </body>