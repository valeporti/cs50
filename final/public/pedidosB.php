<?php

    // configuration
    require("../includes/config.php");

    // TODO: search database for places matching $_GET["geo"], store in $places
    
    //lo que entra por GET
    $request = $_GET["action"];
    $platillo = $_GET["valor"];
    
    if ($request == "borraDB")
    {
        //borrar del menu
        CS50::query("DELETE FROM menu WHERE user_id = ? AND platillo = ?", $_SESSION["id"], $platillo);
        //borrar de la parte de platillos
        CS50::query("DELETE FROM pedidos WHERE user_id = ? AND platillo = ?", $_SESSION["id"], $platillo);
    
        // output places as JSON (pretty-printed for debugging convenience)
        //header("Content-type: application/json");
        //print(json_encode($platillo . " borrado", JSON_PRETTY_PRINT));
    }
    
?>