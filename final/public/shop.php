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
        $rows = CS50::query("SELECT platillo, ingredientes, cantidad, unidad, numPersonas FROM recetas WHERE user_id = ? ORDER BY ingredientes, unidad", $_SESSION["id"]);
        $found = count($rows);
        //query for shoped things
        $storedRows = CS50::query("SELECT ingredientes, unidad, cantidad, consumoD FROM almacen WHERE user_id = ? ORDER BY ingredientes, unidad", $_SESSION["id"]);
        $foundStr = count($storedRows);
        //store in sections[] the information needed
        $recetas = [];
        
        if ($found == 0) 
        {
            $recetas[] = [
                "apology" => "Sorry, you don't have any elements to show yet."
                ];
        }
        else 
        {
            foreach ($rows as $row)
            {
                $recetas[] = [
                    "platillo" => $row["platillo"],
                    "ingrediente" => $row["ingredientes"],
                    "cantidad" => $row["cantidad"],
                    "unidad" => $row["unidad"],
                    "numP" => $row["numPersonas"]
                ];
            }
        }
        
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
                    "cantidad" => $storedRow["cantidad"],
                    "consumo" => $storedRow["consumoD"]
                    ];
            }
        }
        //tal vez sería un análisis primero de si es para 4 o  para cuantas perosnas (lo dejaré para después)
        // else render form
        render("shop_form.php", ["title" => "Shop", "recetas" => $recetas, "found" => $found, "storedArr" => $stored, "foundStored" => $foundStr]);
    }

    // else if user reached page via POST (as by submitting a form via POST)

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        print("hello");
    }

?>
