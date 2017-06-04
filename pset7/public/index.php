<?php

    // configuration
    require("../includes/config.php"); 
    
    //query database for user info
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    //store in positions[] the information needed
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    $cash = CS50::query("SELECT cash, username FROM users WHERE id = ?", $_SESSION["id"]);

    // render portfolio
    //render("portfolio.php", ["title" => "Portfolio"]);
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash" => $cash]);

?>
