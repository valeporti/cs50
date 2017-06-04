<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
     // else if user reached page via POST (as by submitting a form via POST)-->submitting something to search
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = $_POST["symbol"];
        $stock = lookup($_POST["symbol"]);
        
        if (empty($symbol))
        {
            apologize("Please, enter a symbol");
        }
        else if ($stock == false)
        {
            apologize("Please, submit a valid symbol");
        }
        else if ($stock == true)
        {
            render("quote_display.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
        }
        else
        {
            apologize("Revise code");
        }
    }

?>