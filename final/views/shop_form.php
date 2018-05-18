
<div id="middle">
    <div class="envioReceta">
        <button onclick='addbought()' class='btn btn-success'>Send Shopping Inputs :)</button>
    </div>
    <br>
    <div id="shopTable">
        <table id='table_port'>
            <tr id="shopFirstRow">
                <td id="shfrIng">Ingredient</td>
                <td id="shfrStr">On Storage</td>
                <td id="shfrBgh">Bought (input)</td>
                <td id="shfrNee">Needed</td>
            </tr>
        </table>
        <table id='table_port'>
        
    <?php
    
        if ($found == 0)
        {
            print("<h3 id='apology'>" . $recetas[0]["apology"] . "</h3>");
        }
        else 
        {
            $tempo = "";
            $unidadTempo = "";
            $first = true;
            $stored = 0;
            $dailyCons = 0;
            $ingStyledHTML = "";
            $ingStyledHTMLtemp = "";
            $arr = [];
            //las ordenaré en una lista de ingredientes y luego unidades
                        
            foreach ($recetas as $receta) {
                //descubrir cuando cambia el ingrediente
                $actual = $receta["ingrediente"];
                $unidadAct = $receta["unidad"];
                if (ctype_space($actual)) {
                    $arr = explode(" ", $actual);
                    $ingStyledHTML = implode("+", $arr);
                } else {
                    $ingStyledHTML = $actual;
                }
                //en la primera está claro que no son iguales por lo tanto: se puede iniciar con la primera apertura
                if ($tempo !== $actual || $unidadTempo!== $unidadAct) {
                    if ($first == false) {
                        //colocar cantidad guardada y unidad
                        print("<td id='st_{$tempo}_{$unidadTempo}' class='storedIng'>{$stored}</td>");
                        print("<td class='storedUni'>{$unidadTempo}</td>"); //es la anterior unidad la que se pone, no la que se acaba de detectar
                        //colocar los inputs para compras
                        print("<td class='shopedIng'><input id='shopedInput_{$tempo}_{$unidadTempo}' class='shopedQty' type='number' placeholder='Quantity'></td>");
                        print("<td class='shopedUni'>{$unidadTempo}</td>");
                        //fila de needed
                        //print("<td class='shopedUnit'>{$unidadTempo}</td>");
                        print("<td class='consIng'>" . round($dailyCons, 2) . "</td>");
                        print("<td class='consUni'>{$unidadTempo}/day</td>");
                        //terminar fila anterior
                        print("</tr>");
                    }
                    //solo se requiere hacer una vez, entonces se pasa a false, y así se queda
                    $first = false;
                    //actualizar valores para continuar comparación
                    $tempo = $actual;
                    $unidadTempo = $unidadAct;
                    //agregar nueva fila de tabla
                    print("<tr id='row_{$actual}_{$unidadAct}' class='elem_table_port'>");
                    print("<td class='ingName'>{$actual}</td>");
                    
                    //para este nuevo ingrediente investigar si ya existe algún valor en STORED
                    if ($foundStored == 0) {
                        $stored = 0;
                    }
                    //si sí, asignar el correspondiente de ingrediente y de unidad, si no pues $stored sería 0
                    else {
                        $coincidence = false;
                        foreach ($storedArr as $storedElem) {
                            if ($storedElem["ingrediente"] == $actual && $storedElem["unidad"] == $unidadAct) {
                                $stored = $storedElem["cantidad"] + 0; //el "+ 0" para eliminar 0 extras decimales
                                $dailyCons = $storedElem["consumo"] + 0;
                                $coincidence = true;
                            }
                        }
                        if ($coincidence != true) {
                            $stored = 0;
                            $dailyCons = 0;
                        }
                    }
                    
                }
            }
            //escribir las últimas líneas
            //colocar cantidad guardada y unidad
            print("<td id='st_{$actual}_{$unidadAct}' class='storedIng'>{$stored}</td>");
            print("<td class='storedUni'>{$unidadTempo}</td>"); //es la anterior unidad la que se pone, no la que se acaba de detectar
            //colocar los inputs para compras
            print("<td class='shopedIng'><input id='shopedInput_{$actual}_{$unidadAct}' class='shopedQty' type='number' placeholder='Quantity'></td>");
            print("<td class='shopedUni'>{$unidadTempo}</td>");
            //fila de needed
            //print("<td class='shopedUnit'>{$unidadTempo}</td>");
            print("<td class='consIng'>" . round($dailyCons, 2) . "</td>");
            print("<td class='consUni'>{$unidadTempo}/day</td>");
            //terminar fila anterior
            print("</tr>");
        }
    ?>
        </table>
    </div>
</div>

