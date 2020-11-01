<?php
require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados

function imprimir(){
 print ("oi");
}
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
print_r($_POST);
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
  <div>
    <center>
              <br><h5><br>Selecione a data para visualização: </h5>
    </center>
    <div class="col-15 d-flex justify-content-center">
        <table border="0" width="500">
            <tr>
                <th>
                    Inicio:
                </th>
                <th>
                    Fim:
                </th>
            </tr>
            <tr>
                <form>
                    <td>
                        <input type="datetime-local" id="begin_time" name="begin_time" 
                            <?php 
                                if(isset($_GET['begin_time'])){
                                    echo('value='.$_GET['begin_time'] ); //no caso de atualizar a pagina preenche automaticamente as input com os valores anteriores
                                }
                                else {
                                    $date1hourago = strtotime('-1 hour');
                                    echo('value='.date('Y-m-d\TH:j',$date1hourago)); //senao atualiza com a data atual
                                }
                            ?>                            
                        >
                    </td>
                    <td>
                            <input type="datetime-local" id="end_time" name="end_time" 
                            <?php 
                                if(isset($_GET['end_time'])){
                                    echo('value='.$_GET['end_time'] ); 
                                }
                                else {
                                echo('value='.date('Y-m-d\TH:j')); //senao atualiza com a data atual
                                }
                            ?>                            
                            >
                        </td>
                        <td>
                            <input type="submit" value="Pesquisar"></button>
                        </td>
                     </form>
                </tr>
            </table>
        </div>                               
    </div>

    <div class="container" >    
        <div class="row">
            <div class="card-login">
                <div class="card">
                    <div class="card-header">
                        Selecione um tipo de consulta:
                    </div>
                    <div class="card-body">
                        <form action="tipo_de_consulta.php" method="post">
                            <input type="radio" id="detalhada" name="tipo" value="detalhada">
                            <label for="detalhada">Consulta Detalhada</label><br>
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
            <div class="card-body">
            <ul>
                <li> Detalhada: Apresenta um gráfico do período com todas as amostras coletadas. </li>
                <li> Consulta de Alarmes: Apresenta uma lista com todos os alarmes registrados no período. </li>
                <li> Consulta Básica: Apresenta um resumo de consumo e log das falhas mais recentes. </li>
            </ul>
            </div>
        </div>
    </div>
  </body>
</html>