<?php

    // configuration
    require("../includes/config.php"); 
    
    //query database for user info
    $transactions = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    if ($transactions == false)
    {
        apologize("No transactions history to show");
    }
    else 
    {
        render("history_form.php", ["transactions" => $transactions, "title" => "history"]);
    }

?>
