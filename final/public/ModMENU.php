<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //Tomar todas las partes del MENU que haya querido incluir la persona
        //query database for user info
        $rows = CS50::query("SELECT secc, platillo, precio, tipo FROM menu WHERE user_id = ? ORDER BY secc", $_SESSION["id"]);
        $found = true;
        
        if (count($rows) == 0) 
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
                    "precio" => $row["precio"] + 0,
                    "tipo" => $row["tipo"]
                ];
            }
        }
        // else render form
        render("ModMENU_form.php", ["title" => "Edit Menu", "sections" => $sections, "found" => $found]);
    }

    // else if user reached page via POST (as by submitting a form via POST)

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        print("hello");
    }

?>
