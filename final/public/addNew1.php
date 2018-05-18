<!DOCTYPE html>

<h1>HEllo I'm lyndsay Lohan</h1>

<?php

    // configuration
    require("../includes/config.php");

        
      //algo que se puede verificar es que no exista ya el producto a insertar.
      //$rows = CS50::query("SELECT * FROM menu WHERE user_id = 3 AND platillo = 'croissant'");
      $ver = CS50::query("INSERT INTO pedidos (user_id, platillo, datime) VALUES(3, 'flan', Now())");  
             //no se si con un fot each
      //if (count($rows) != 0)
      //{
        //$ver = count($rows);
      //}
      //else
      //{
        //$ver = "es cero";
        //CS50::query("INSERT INTO menu (user_id, secc, platillo, precio, tipo) VALUES (3, 'postres', 'croissant', 30, 'francesa')");
      //}
    //foreach ($rows as $row)
    //{
    //  $ver = $row;
    //}
    //print($rows);
    header("Content-type: application/json");
    print(json_encode($ver, JSON_PRETTY_PRINT));
?>