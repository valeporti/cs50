<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //Tomar todas las partes del MENU que haya querido incluir la persona
        //query database for user info
        $rows = CS50::query("SELECT secc, platillo, precio FROM menu WHERE user_id = ? ORDER BY secc", $_SESSION["id"]);
        $found = true;
        
        if ($rows == false) 
        {
            $found = false;
            $sections[] = [
                "apology" => "Sorry, you don't have any elements to show yet."
                ];
        }
        else 
        {
            //store in sections[] the information needed
            $sections = [];
            
            foreach ($rows as $row)
            {
                $sections[] = [
                    "secc" => $row["secc"],
                    "platillo" => $row["platillo"],
                    "precio" => $row["precio"]
                ];
            }
        }
        
        $behavior = CS50::query("SELECT platillo, datime FROM pedidos WHERE user_id = ? ORDER BY platillo", $_SESSION["id"]);
        $foundBeh = true;
        $behaviorArr = [];
        $ingredients = CS50::query("SELECT platillo, ingredientes, cantidad, unidad, numPersonas FROM recetas WHERE user_id = ? ORDER BY platillo", $_SESSION["id"]);
        $foundIng = count($ingredients);
        $platArr = [];
        $ingArr = [];
        
        
        if ($foundIng == 0) 
        {
            $ingArr[] = [
                "ing" => "No ingredients loaded"
                ];
            $plaArr[] = [
                "ingArr" => $ingArr
                ];
        }
        else {
            $tempo = "";
            $actual = "";
            $first = true;
            $i = 0;
            //hacer que haya por cada platillo una serie de ingredientes
            foreach ($ingredients as $ingredientElem)
            {
                $actual = $ingredientElem["platillo"];
                if ($actual != $tempo) 
                {
                    if ($first == false) 
                    {
                        $platArr[] = [
                            "pla" => $tempo,
                            "ingArr" => $ingArr
                            ];
                        $ingArr = [];
                    }
                    $tempo = $actual;
                    $first = false;
                }
                //Hacer cálculos para dejarlo por persona aunque diga por dos
                $cantidad = $ingredientElem["cantidad"] + 0;
                $numPersonas = $ingredientElem["numPersonas"];
                if ($numPersonas != 1) {
                    $cantidad = $cantidad / $numPersonas;
                }
                $ingArr[] = [
                    "ing" => $ingredientElem["ingredientes"],
                    "qty" => $cantidad,
                    "uni" => $ingredientElem["unidad"]
                    ];
                //Verificar si es el útlimo para no perder la oportunidad de introducr el útlimo congunto de ingredientes recopilado
                $i ++;
                if ($i == $foundIng) {
                    $platArr[] = [
                        "pla" => $tempo,
                        "ingArr" => $ingArr
                        ];
                }
            }
        }
        
        if (count($behavior) == 0) 
        {
            $foundBeh = false;
            $behaviorArr[] = [
                "apology" => "Sorry, you don't have any elements on behavior to show yet."
                ];
        }
        else 
        {
            foreach ($behavior as $behaviorElem)
            {
                //asignar ingredientes si existe, si no, olvidarse y escribir apology
//                foreach ($ingredients as $ingredientElem)
  //              {
    //                if ($behaviorElem["platillo"] == $ingredientElem["platillo"]) {
      //                  //Hacer cálculos para dejarlo por persona aunque diga por dos
        //                $cantidad = $ingredientElem["cantidad"];
          //              $numPersonas = $ingredientElem["numPersonas"];
            //            if ($numPersonas != 1) {
              //              $cantidad = $cantidad / $numPersonas;
                //        }
                  //      $ingArr[] = [
                    //        "ing" => $ingredientElem["ingredientes"],
                      //      "qty" => $cantidad,
                        //    "uni" => $ingredientElem["unidad"]
                          //  ];
                    //}
                //}
                    
                $behaviorArr[] = [
                    "platillo" => $behaviorElem["platillo"],
                    "datime" => $behaviorElem["datime"]
                    //"ingArr" => $ingArr
                ];
            }
        }
        
        //query for shoped things
        $storedRows = CS50::query("SELECT ingredientes, unidad, cantidad FROM almacen WHERE user_id = ? ORDER BY ingredientes, unidad", $_SESSION["id"]);
        $foundStr = count($storedRows);
        $stored = [];
        if ($foundStr == 0) 
        {
            $stored[] = [
                "apology" => "No Stored Ingredients"
                ];
        }
        else 
        {
            foreach ($storedRows as $storedRow)
            {
                $stored[] = [
                    "ingrediente" => $storedRow["ingredientes"],
                    "unidad" => $storedRow["unidad"],
                    "cantidad" => $storedRow["cantidad"] + 0,
                    "consumo" => 0
                    ];
            }
        }
        
        // else render form
        render("MENU_form.php", ["title" => "Principal Menu", "sections" => $sections, "found" => $found, "behavior" => $behaviorArr, "foundBeh" => $foundBeh, "platArr" => $platArr, "foundIng" => $foundIng, "stored" => $stored, "foundStr" => $foundStr]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    //NO VA  a tener post pues todo se hace por medio de jQuery
    // por si a leer: http://stackoverflow.com/questions/9458466/ajax-listen-event-on-a-button-click-then-runs-a-php-file
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        if ($_POST["action"] == "pedidos")
        {
            $platillo = $_POST["platillo"];

            print("<h1>Se posteo algo : " . $platillo . "</h1>");
            
            CS50::query("INSERT INTO pedidos (user_id, platillo) VALUES(?, ?)", $_SESSION["id"], $platillo);
        }

        
    }
    else
    {
        $username = $_POST["username"];
        $password = $_POST["password"];
        $confirmation = $_POST["confirmation"];
        
        if (empty($username) || empty($password) || empty($confirmation))
        {
            apologize("You must fullfill every section, thank you!");
        }
        else if($password != $confirmation)
        {
            apologize("Not Identical Passwords");
        }
        else
        {
            if(0 != CS50::query("INSERT IGNORE INTO users (username, hash) VALUES(?, ?)", $username, password_hash($password, PASSWORD_DEFAULT)))
            {
                // query database for user
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $id;
                // redirect to portfolio
                redirect("index.php");
            }
            else
            {
                apologize("Error in storing user, may be already existant");
            }
        }
    }

?>
