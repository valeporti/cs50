<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
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
            if(0 != CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $username, password_hash($password, PASSWORD_DEFAULT)))
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
