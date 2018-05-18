<?php

    // configuration
    require("../includes/config.php");

    $request = $_GET["request"];
    $message = "";

    if ($request == "addGrocery")
    {
        //lo que entra por GET
        $Qty = $_GET["Qty"];
        $ing = $_GET["ing"];
        $uni = $_GET["uni"];
        
        $message = $Qty . $ing . $uni;
        
        //!\IMPORTANTE NOTA: En el siguiente query, el "ON DUPLICATE KEY UPDATE" 
            //verifica si se duplica una row de acuerdo a un UNIQUE index o Primary key
            //Al necesitar que verificara 2 columnas, y muy probablemente los valres en estas columnas se repetirían
            //no era posible hacer UNIQUE una o ambas, se hizo un index que tomaba en cuenta ambas.. y listo !!! :)
        
        //si el conteo es cero, significa que no existe platillo y se puede insertar
        CS50::query("INSERT INTO almacen (user_id, ingredientes, unidad, cantidad) VALUES(?, ?, ?, ?) ON DUPLICATE KEY UPDATE cantidad = cantidad + ?", $_SESSION["id"], $ing, $uni, $Qty, $Qty);
        $message = "Ingredient '" . $ing . "' has been added.";
    }
    else if ($request == "addBehavior") {
        $storedS = $_GET["stored"];
        foreach ($storedS as $stored) {
            $uni = $stored["unidad"];
            $con = $stored["consumo"];
            $ing = $stored["ingrediente"];
            $qty = $stored["cantidad"];
            //poner el consumo diario y la cantidad restante del ingrediente usado
            CS50::query("UPDATE almacen SET consumoD = ?, cantidad = ? WHERE (user_id = ? AND (ingredientes = ? AND unidad = ?))", $con, $qty, $_SESSION["id"], $ing, $uni);
            
        }
    }
    else
    {
        $message = "Request no entró bien";
    }
    //output places as JSON (pretty-printed for debugging convenience)
    //header("Content-type: application/json");
    //print(json_encode($message, JSON_PRETTY_PRINT));
?>