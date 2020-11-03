<?php
require "validador_acesso.php";   //protege o acesso a pagina para usuarios logados

if ($_POST['tipo'] == 'grafico') {
    $_SESSION['begin_time'] = $_POST['begin_time'];
    $_SESSION['end_time'] = $_POST['end_time'];
    header('Location: consulta_grafica.php');
}

if ($_POST['tipo'] == 'alarmes') {
    $_SESSION['begin_time'] = $_POST['begin_time'];
    $_SESSION['end_time'] = $_POST['end_time'];
    header('Location: consulta_alarmes.php');
}

?>