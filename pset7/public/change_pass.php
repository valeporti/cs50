<?php

        // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("change_pass_form.php", ["title" => "Change Password"]);
    }
    
     // else if user reached page via POST (as by submitting a form via POST)-->submitting something to search
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //verificar que la contaseña antigua sea la correcta, además de que coincidan las dos nuevas
        $password = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $old_pass = $_POST["old_pass"];
        $new_pass = $_POST["new_pass"];
        $confirm = $_POST["confirmation"];
        
        if (empty($old_pass) || empty($new_pass) || empty($confirm))
        {
            apologize("You must type on every section");
        }
        else if (password_verify($old_pass, $password[0]["hash"]))
        {
            //verify that new password and confirmation does match
            if ($new_pass == $old_pass)
            {
                apologize("New password must be different than the old one");
            }
            else if ($new_pass != $confirm)
            {
                apologize("New Password and its confirmation doesn't match");
            }
            else
            {
                CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($new_pass, PASSWORD_DEFAULT), $_SESSION["id"]);
                
                render("changed_pass_form.php", ["title" => "Changed Password"]);
            }
        }
        else
        {
            apologize("Actual password doesn't match");
        }
        
        // redirect to portfolio 
        redirect("/");
    }

?>