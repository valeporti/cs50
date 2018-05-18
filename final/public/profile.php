<?php

        // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("profile_form.php", ["title" => "Profile"]);
    }
    
     // else if user reached page via POST (as by submitting a form via POST)-->submitting something to search
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //Lo único que se va a poder modificar, es la contraseña, se podrá accesar al forma de cambio de contraseña y listo
        render("change_pass_form.php", ["title" => "Change Password"]);
        // redirect to portfolio 
        redirect("/");
    }

?>