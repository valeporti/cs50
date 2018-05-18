<?php

    // configuration
    require("../includes/config.php");

    // TODO: search database for places matching $_GET["geo"], store in $places
    
    //lo que entra por GET
    $request = $_GET["action"];
    
    if ($request == "borraDB")
    {
        $platillo = $_GET["plat"];
        $ingrediente = $_GET["ing"];
        $unidad = $_GET["uni"];
        //borrar de las recetas
        CS50::query("DELETE FROM recetas WHERE user_id = ? AND platillo = ? AND ingredientes = ?", $_SESSION["id"], $platillo, $ingrediente);
        //y de almacén
        CS50::query("DELETE FROM almacen WHERE user_id = ? AND ingredientes = ? AND unidad = ?", $_SESSION["id"], $ingrediente, $unidad);
    }
    else if ($request == "addIng")
    {
        $plat = $_GET["platillo"];
        $numP = $_GET["numP"];
        $ing = $_GET["ing"];
        $uni = $_GET["uni"];
        $cant = $_GET["cant"];
        //insertar rows
        CS50::query("INSERT INTO recetas (user_id, platillo, ingredientes, cantidad, unidad, numPersonas) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["id"], $plat, $ing, $cant, $uni, $numP);
        //insertar en alamcén
        CS50::query("INSERT INTO almacen (user_id, ingredientes, unidad, cantidad, consumoD) VALUES(?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE cantidad = cantidad", $_SESSION["id"], $ing, $uni, 0, 0);
    }
?>