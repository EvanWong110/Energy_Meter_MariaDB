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
  </body>
</html>