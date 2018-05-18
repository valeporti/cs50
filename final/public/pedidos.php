<?php

    // configuration
    require("../includes/config.php");

    // TODO: search database for places matching $_GET["geo"], store in $places
    
    //lo que entra por GET
    $request = $_GET["action"];
    $platillo = $_GET["valor"];
    //separar el query si es que se hizo una solicitudo con varios elementos
    //CS50::query("INSERT INTO test (text1, text2, num) VALUES(?, ?, 4)", $_GET["action"], $_GET["valor"]);
    $res = CS50::query("INSERT INTO pedidos (user_id, platillo, datime) VALUES(?, ?, NOW())", $_SESSION["id"], $platillo);
    
    //if ($res > 0) {
        //print($platillo . " cargado // numero col insertadas: " . $res);
    //}
    //else
    //{
        //print("no salió");
    //}
    

    // output places as JSON (pretty-printed for debugging convenience)
    //header("Content-type: application/json");
    //print(json_encode($platillo . " cargado :" . $res, JSON_PRETTY_PRINT));
?>