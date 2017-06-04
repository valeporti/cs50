<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //si sale get, unicamente mostrar los cuadros donde se pondrán el símbolo y los shares
        render("buy_form.php", ["title" => "Buy Shares"]);
    }
    
     // else if user reached page via POST (as by submitting a form via POST)-->submitting something to search
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //en caso de recibir post, priemro ver el precio del share del símbolo, ver si alcanza con lo que teiene el usuario
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("Please, fill all te blanks");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            if ($stock == false)
            {
                apologize("There's a problem with the stock, it may not exist");
            }
            else
            {
                //verify if the quantity typed by the user is correct, else apologize
                if ((preg_match("/^\d+$/", $_POST["shares"])) == true)
                {
                    //calcular la cantidad de stocks a comprar
                    $amount = $stock["price"] * $_POST["shares"];
                    //query the cash in order to compare with the amount to buy
                    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
                    if($amount <= $cash[0]["cash"])
                    {
                        //put the remainder quantity in the portfolio, in the cash section
                        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $amount, $_SESSION["id"]);
                        
                        //verify if symbol already exists, if it does, add it
                        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"], $_POST["shares"]);
                    
                        //colocar transacción en el historial
                        CS50::query("INSERT INTO history (status, datime, symbol, shares, price, user_id) VALUES('BUY', Now(), ?, ?, ?, ?)", strtoupper($stock["symbol"]), $_POST["shares"], $stock["price"], $_SESSION["id"]);
                        
                        // redirect to portfolio 
                        redirect("/");
                    }
                    else
                    {
                        apologize("You don't have enough cash");
                    }
                }
                else
                {
                    apologize("You must type a positive number, without decimals");
                }
            }
        }
        
    }

?>