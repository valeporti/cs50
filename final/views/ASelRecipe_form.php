
<div id="middle">
    <div id="SelectRecipe">
        <div class='dropdown drpdwn1'>
            <button class="btn btn-default dropdown-toggle" type="button" id="dropdownMenu1" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true">
            <?php
                
                if ($found == 0)
                {
                    print("No recipes yet ;)");
                    //print($recetas[0]["apology"]);
                    print("</button>");
                }
                else 
                {
                    print("Select Recipe");
                    print("<div id='spanCaret'><span class='caret'></span></div>");
                    print("</button>");
                    print("<ul class='dropdown-menu' aria-labelledby='dropdownMenu1'>");
                    $tempo = "";
                    $numPTempo = "";
                    $first = true;
                    //las ordenaré en una lista de ingredientes
                    foreach ($recetas as $receta)
                    {
                        //tomar el platillo estudiado en el elemento $receta para después compararlo con el siguiente y así 
                        //descubrir cuando cambia platillo y se tenga que separar una receta de otra
                        $actual = $receta["platillo"];
                        $numPAct = $receta["numP"];
                        //en la primera está claro que no son iguales por lo tanto: se puede iniciar con la primera apertura
                        if ($tempo !== $actual) {
                            print("<li class='seldrpdwn'><a href='#' onclick='asignChoiceDrpdwn(\"{$actual}\")'>{$actual}</a></li>");
                            $tempo = $actual;
                            $numPTempo = $numPAct;
                            //solo se requiere hacer una vez, entonces se pasa a false, y así se queda
                            $first = false;
                        }
                    }
                }
            ?>
            </ul>
        </div>
        <div class="inputDiv">
            <input id="recNumP" type="number" placeholder="for how many people?">
        </div>
        <div class="btnSendRec bothSendRec">
            <button class='btn btn-success btnPush' onclick='showRecipe( <?php echo json_encode($recetas); ?> )'>Go For iT</button>
        </div>
        <div class="btnSendRec2 bothSendRec">
            <button class='btn btn-warning btnPush' onclick='clearRecipes()'>Clear Tableau</button>
        </div>
    </div>
    <br>
</div>

