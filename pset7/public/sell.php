<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //si sale get, obtener los distintos valores de los shares comprados por el usuario y enlistarlos
        
        //query database for user info
        $symbols = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        
        //si no hay nada de shares, disculparse, si no mostrarlos
        if (count($symbols) == 0)
        {
            apologize("Nothing to sell");
        }
        else
        {
            //display shares
            render("sell_form.php", ["title" => "Sell Shares", "symbols" => $symbols]);
        }
    }
    
     // else if user reached page via POST (as by submitting a form via POST)-->submitting something to search
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        //una vez que se dijo cual share a vender, habrá que eliminarlo de los datos y agregar el precio por el que se vendió
        
        //ver cuantos stok tiene el usuario y guardarlo en variable
        $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //buscar el precio del stock
        $stock = lookup($_POST["symbol"]);
        
        $total = $shares[0]["shares"] * $stock["price"];
    
        //agregarlo al cash que tiene el usuario
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $_SESSION["id"]);
        
        //borrar los stocks
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //colocar transacción en el historial
        CS50::query("INSERT INTO history (status, datime, symbol, shares, price, user_id) VALUES('SELL', Now(), ?, ?, ?, ?)", strtoupper($stock["symbol"]), $shares[0]["shares"], $stock["price"], $_SESSION["id"]);
            
        // redirect to portfolio 
        redirect("/");
    }

?>