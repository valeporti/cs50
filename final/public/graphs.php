<?php

//If query is passed a SELECT statement, it will return an array with 0 or more rows. 
//If query is instead passed a DELETE, INSERT, or UPDATE statement, 
//it will return a non-negative integer that represents the number of rows deleted, inserted, or updated, respectively.

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //Tomar todas las partes del MENU que haya querido incluir la persona
        //query database for user info
        $rows = CS50::query("SELECT platillo, datime FROM pedidos WHERE user_id = ? ORDER BY platillo DESC", $_SESSION["id"]);
        $found = true;
        
        if (count($rows) == 0) 
        {
            $found = false;
            $envio[] = [
                "apology" => "Sorry, you don't have any elements to show yet."
                ];
        }
        else 
        {
            //store in envio[] the information needed
            $envio = [];
            
            foreach ($rows as $row)
            {
                $envio[] = [
                    "platillo" => $row["platillo"],
                    "datime" => $row["datime"]
                ];
            }
        }
        
        // output places as JSON (pretty-printed for debugging convenience)
        //header("Content-type: application/json");
        $envio = json_encode($envio);//, JSON_PRETTY_PRINT);
        //print($envio);
        render("graphs_form.php", ["title" => "Graphs", "data" => $envio, "found" => $found]);
    }

    // else if user reached page via POST (as by submitting a form via POST)

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        print("hello");
    }
?>
