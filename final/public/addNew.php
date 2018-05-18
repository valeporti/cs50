<?php

    // configuration
    require("../includes/config.php");

    $request = $_GET["request"];
    $message = "";

    if ($request == "agregaDish")
    {
        //lo que entra por GET
        $seccion = $_GET["seccion"];
        $platillo = $_GET["platillo"];
        $precio = $_GET["precio"];
        $tipo = $_GET["tipo"];
        
        $message = $seccion . $platillo . $precio . $tipo;
        
        //algo que se puede verificar es que no exista ya el producto a insertar.
        $existe = CS50::query("SELECT * FROM menu WHERE user_id = ? AND platillo = ?", $_SESSION["id"], $platillo);
        
        //si es cero significa que no hay nada y que se puede cotninuar
        if (count($existe) != 0)
        {
            $message = "the MainDish '"  . $platillo . "' already exists";    
        }
        else
        {
          //si el conteo es cero, significa que no existe platillo y se puede insertar
          CS50::query("INSERT INTO menu (user_id, secc, platillo, precio, tipo) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], $seccion, $platillo, $precio, $tipo);
          $message = "MainDish '" . $platillo . "' has been added.";
        }              
    }
    else
    {
        $message = "Request no entró bien";
    }
    // output places as JSON (pretty-printed for debugging convenience)
    //header("Content-type: application/json");
    //print(json_encode($message, JSON_PRETTY_PRINT));
?>