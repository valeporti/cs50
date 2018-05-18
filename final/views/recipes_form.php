
            <div id="middle">
                <div class="envioReceta">
                    <button onclick='addRecipe()' class='btn btn-success'>Send Recipes Inputs :)</button>
                </div>
                <br>
                <div id="newRecDiv" class="inputDiv"> <!-- aqui le quité un newRec class//por si alo falla -->
                    <h4 class='section'>New Main Dish</h4>
                    <table class="tabla_newRec">
                        <tr id="newRecRow">
                            <td id="colNewUp" class="newRec"><input id='inputNewMD' class='platillo' type='text' placeholder='Main Dish'></td> <!-- name='platillo' -->
                            <td id="colNewUp" class="newRec"><input id='inputNewMD' class='numPer' type='number' placeholder='For how many People?'></td> <!-- name='numP' -->
                        </tr>
                    </table>
                    <table class="tabla_newRec_0">
                        <tr id="newRecRow">
                            <!-- Quito los names, pues al momento de pedir con jQuery los elementos con tag "input", duplica -->
                            <!-- una vez con la clase y otra con el name -->
                            <td class="newRec" width=15%><input id='inputNewMD' class='ingrediente' type='text' placeholder='Ingredient'></td>
                            <td class="newRec" width=15%><input id='inputNewMD' class='cantidad' type='number' placeholder='Quantity'></td>
                            <td class="newRec" width=15%><input id='inputNewMD' class='unidad' type='text' placeholder='Unit'></td>
                        </tr>
                    </table>
                    <button class='btn btn-default btnPush' onclick='addRow("tabla_newRec_0")'>+ Add ingredient</button>
                </div>
                <br>
                
                <?php
                
                    if ($found == 0)
                    {
                        print("<h3>" . $recetas[0]["apology"] . "</h3>");
                    }
                    else 
                    {
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
                                //si no son iguales, enonces actualizar "tempo" para poder continuar con la comparación
                                if ($first == false) {
                                    //todas y cada una de las recetas van a tener un espacio que diga si se quiere agregar algún ingrediente
                                    //print("<tr class='elem_table_port'>");
                                    print("</tr>");
                                    //terminar la tabla anterior
                                    print("</table>");
                                    print("<button class='btn btn-default btnPush' onclick='addRow(\"tabla_{$tempo}_{$numPTempo}\")'>+ Add ingredient</button>");
                                    print("</div>");
                                    print("<br>");
                                }
                                $tempo = $actual;
                                $numPTempo = $numPAct;
                                //Colocar div par identificar
                                //agregar nueva lista
                                print("<div id='div_{$actual}' class='recetas secMenu'>");
                                print("<h4 class='section'>{$actual} // Thought for {$numPAct} Persons</h4>");
                                print("<table id='table_port' class='tabla_{$actual}_{$numPAct}'>");
                                //solo se requiere hacer una vez, entonces se pasa a false, y así se queda
                                $first = false;
                            }
                            //output cada sección de la tabla
                            print("<tr id='row_{$actual}_{$receta["ingrediente"]}' class='elem_table_port'>"); //"row_X_Y" es para acceder al elemento y eliminarlo si se pide
                            print("<td width=15%>{$receta["ingrediente"]}</td>");
                            print("<td width=15%>" . ($receta["cantidad"] + 0) . "</td>");
                            print("<td width=15%>{$receta["unidad"]}</td>");
                            print("<td width=15%><button class='btn btn-default btnPush' onclick='eliminaIng(\"{$actual}\", \"{$receta["ingrediente"]}\", \"{$receta["unidad"]}\")'>X Erase</button></td>"); // name='platillo' value='{$section["platillo"]}'
                            print("</tr>");
                        }
                        //todas y cada una de las recetas van a tener un espacio que diga si se quiere agregar algún ingrediente
                        //print("<tr class='elem_table_port'>");
                        //-->Nota: veridicar que sí está agarrando bien el "{$receta["platillo"]}"
                        //print("</tr>");
                        //ya terminó la inserción de datos, ya se puede cerrar la última tabla
                        //antes agregandole un espacio para que inserte algo nuevo
                        print("</table>");
                        print("<button class='btn btn-default btnPush' onclick='addRow(\"tabla_{$actual}_{$numPAct}\")'>+ Add ingredient</button>");
                        print("</div>");
                        print("<br>");
                    }
                ?>
                <!-- Execute JAvascript function -->
                <script>
                    dataClientRecipes(<?php echo json_encode($recetas); ?>);
                </script>
                
            </div>

