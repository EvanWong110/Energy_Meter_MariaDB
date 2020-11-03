<?php
    require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados
    date_default_timezone_set('America/Sao_Paulo');      //configura a timezone

print_r($_SESSION);
    if(isset($_SESSION['begin_time']) && isset($_SESSION['end_time'])){      //exige preenchimento dos inputs de pesquisa
        $time1 = (string) strtotime($_SESSION['begin_time']);            //selecao de itens pesquisados UnixTIMESTAMP
        $time2 = (string) strtotime($_SESSION['end_time']);
        $tamanho = (int) $time2 - (int) $time1;            

        $hostname = "192.168.0.251";
        $username = "admin";
        $password = "password";
        $db = "energymeter";

        $dbconnect=mysqli_connect($hostname,$username,$password,$db);

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
#    echo '<pre>'; print_r($data); echo '</pre>';
#    echo '<pre>'; print_r($data2); echo '</pre>';
    ?>

<html>
  <head>
    <meta charset="utf-8" />
    <title>Power Monitor App</title> <!--titulo da janela-->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <style>
        .card-home {
            padding: 30px 0 0 0;
            width: 100%;
            margin: 0 auto;
        }
    </style>
    
    <!-- O codigo abaixo é uma api do googlecharts para geração de gráficos-->    
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script> 
    <script type="text/javascript">
        google.charts.load('current', {'packages':['corechart']});
        google.charts.setOnLoadCallback(drawChart);        

        function drawChart() {              //funcao de montagem do googlechart
            var data = new google.visualization.DataTable();
               data.addColumn('number', 'TimeStamp');   //adicao das colunas
                data.addColumn('number', 'Tensão');
                data.addColumn('number', 'Corrente');
                data.addColumn('number', 'Pot. Reativa');
                data.addColumn('number', 'Pot. Aparente');
                data.addColumn('number', 'Pot. Ativa');
                data.addColumn('number', 'Frequência');
                data.addColumn('number', 'Fator de Potência');
                data.addRows(<?php echo json_encode($data); ?>);  //adicao das linhas de dados presentes do array $data

            var options = {   //opcoes de criação do grafico
                title: 'Power Measurements',
                hAxis: {
                    title: 'Linha do tempo',
                    },
                curveType: 'function',
                legend: { position: 'right' },
                logScale: true   //escala logaritmica permite a melhor visualização de todos os valores no mesmo grafico
            };

            colunas_ativas = [{
                type: 'datetime',
                label: data.getColumnLabel(0),
                calc: function (dt, row) {
                    var timestamps = dt.getValue(row, 0) * 1000; // convert to milliseconds
                    return new Date(timestamps);
                }
            }, 1, 2, 3, 4, 5, 6, 7];  //variavel que armazena as colunas que estao visiveis no grafico
            
            var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));  //seleção do garfico do tipo linechart
            chart.draw(data, options);  //chamada de criação do grafico
            view = new google.visualization.DataView(data);
            view.setColumns(colunas_ativas);
            
            chart.draw(view, options);
            
            function altera_colunas(inds) {  //inverte o estado de exibicao da coluna informada em 'inds' entre true e false
                var auxiliar = colunas_ativas.indexOf(inds);
                if (auxiliar === -1){
                    colunas_ativas.push(inds)
                } else {
                    colunas_ativas.splice(auxiliar, 1);
                }
                view.setColumns(colunas_ativas);
                chart.draw(view, options);
            }

            var oculta_tensao = document.getElementById("btTensao").onclick = function() {  //funcao executada durante o clique no botao bttensao
                view = new google.visualization.DataView(data);
                altera_colunas(1);
            }
            
            var oculta_corrente = document.getElementById("btCorrente").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(2);
            }
            
            var oculta_pot_reativa = document.getElementById("btPotRe").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(3);
            }
            
            var oculta_pot_aparente = document.getElementById("btPotAp").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(4);
            }
            
            var oculta_pot_ativa = document.getElementById("btPotAt").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(5);
            }
            
            var oculta_freq = document.getElementById("btFreq").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(6);
            }
            
            var oculta_fp = document.getElementById("btFP").onclick = function() {
                view = new google.visualization.DataView(data);
                altera_colunas(7);
            }

            var resetar = document.getElementById("btReset");  //habilita a visualizacao de todas as colunas
            resetar.onclick = function() {
                view = new google.visualization.DataView(data);
                colunas_ativas = [0, 1, 2, 3, 4, 5, 6, 7];
                view.setColumns(colunas_ativas);
            }
        }
    </script>
  </head>


<style> 
.bt {
border:1px solid #25692A;
border-radius:4px;
display:inline-block;
cursor:pointer;
font-family:Verdana;
font-weight:bold;
font-size:13px;
padding:6px 10px;
text-decoration:none;
}
</style>

  <body>
    <nav class="navbar navbar-dark bg-dark">
      <a class="navbar-brand" href="#">
        <img src="logo.png" width="30" height="30" class="d-inline-block align-top" alt="">
        Power Monitor App  <!--Titulo ao lado da imagem -->
      </a>
      <ul class="navbar-nav">
        <li class="nav-item">
          <a class="nav-link" href="logoff.php">SAIR</a>  <!--Executa logoff da página -->
      </ul>
    </nav>

    <div style="float: right; width: 18%"  align="center">
        <br>
        <h6>Consumo no período selecionado:<br></h6>
        <?php
            if (isset($data2[0])){      //calcula as médias dos valores pesquisados 
                $somatorio = [0, 0];
                $qtd_data = count($data2);
                foreach($data2 as $indice => $valor){
                    $somatorio[0] = $somatorio[0] + $data2[$indice][0];
                    $somatorio[1] = $somatorio[1] + $data2[$indice][1];
                }
                $intervalo_entre_uploads = $data[1][0]-$data[0][0];
                $somatorio[0] = $somatorio[0]/(3600*1000);
                $somatorio[1] = $somatorio[1]/(3600*1000);
                echo "$somatorio[0] kVAh <br>";
                echo "$somatorio[1] kWh <br>";
                
            }
        ?>
        <h6><br><br>Estimativa conforme informações deste período: <br></h6>
        <?php
        if (isset($data[0])){      //calcula as médias dos valores pesquisados
           # $consumo_mensal = ($media[5]*720)/1000;
           # echo ("Consumo mensal: ".number_format($consumo_mensal,0)." kWh") ;
        }
        ?>
        
    </div>
          
  
    <div class="container">
            <div class="row">
                <div class="card-home">
                  <div class="card">
                    <div class="card-header">
                      Gráfico
                    </div>
                    <div class="card-body">
                        <div id="curve_chart" style="width: 1000px; height: 500px"></div>
                    </div>
                  </div>
                  <div class="col-15 d-flex justify-content-center">
                     <h6>Ativar / Desativar Visualização: &nbsp; </h6>
                     <button class="bt" type="button" id="btReset">Mostrar todos</button>
                     <button class="bt" type="button" id="btTensao">Tensao</button>
                     <button class="bt" type="button" id="btCorrente">Corrente</button>
                     <button class="bt" type="button" id="btPotRe">Pot. Reativa</button>
                     <button class="bt" type="button" id="btPotAp">Pot. Aparente</button>
                     <button class="bt" type="button" id="btPotAt">Pot. Ativa</button>
                     <button class="bt" type="button" id="btFreq">Frequência</button>
                     <button class="bt" type="button" id="btFP">Fator de Potencia</button>
                  </div>
                </div>
            </div>
    </div>
    <div style="clear: both"></div>
  </body>
</html>