<?php

    require("../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    // TODO: search database for places matching $_GET["geo"], store in $places
    
    //lo que entra por GET
    $request= $_GET["geo"];
    //separar el query si es que se hizo una solicitudo con varios elementos
    $req_array = explode(" ", urldecode($request));
    
    //verificar que no haya carácters raros
    if (preg_match("/[\'^£$%&*()}{@#~?><>|=_+¬-]/", $request))
    {
        print("Please, write valid characters.");
    }
    else
    {
        
        //contar los elementos
        $count = count($req_array);
        
        //print($request . " ");
        //print($count . " ");
        
        //si hay alguno de los valores que sea numérico, nos uqedamos con ese
        $i = 0;
        $CP = false;
        while (($i < $count) && ($CP == false))
        {
            //print($req_array[$i] . " ");
            $CP = is_numeric($req_array[$i]);
            $i ++;
        }
        
        //print($CP);
        
        //Puede ser mejor idea analizar primero la petición por GET para saber dónde buscar
        if ($CP == true)
        {
            //print("CP es true ->");
            //print($req_array[$i] . " ");
            $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ?", $req_array[$i - 1] . "%");
        }
        //else if ($count == 2)
        //{ 
           //$request = implode(" ", $req_array);
            
            //$places = CS50::query("SELECT * FROM places WHERE MATCH(place_name, admin_name1) AGAINST (?)", 
               // $request . "%");
        //}
        else
        {
            //$request = implode(" ", $req_array);
            //print("CP es false");
            $places = CS50::query("SELECT * FROM places WHERE MATCH(place_name, admin_name1) AGAINST (?)", $request . "%");
        }
       
        // output places as JSON (pretty-printed for debugging convenience)
        header("Content-type: application/json");
        print(json_encode($places, JSON_PRETTY_PRINT));
    }
?>