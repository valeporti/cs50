
            <div id="middle">
                
                <?php
                    if ($found == false)
                    {
                        print("<h3>{$sections[0]["apology"]}</h3>");
                    }
                    else 
                    {
                        $tempo = "";
                        $first = true;
                        print("<form id='formMenu'>");
                        
                        foreach ($sections as $section)
                        {
                            $actual = $section["secc"];
                            
                            if ($tempo !== $actual) {
                                //si no son iguales, enonces actualizar "tempo" para poder continuar con la comparación
                                if ($first == false) {
                                    //terminar la tabla anterior
                                    print("</table>");
                                    print("</div>");
                                    print("<br>");
                                }
                                $tempo = $section["secc"];
                                //y además agregar nueva tabla
                                print("<div id='{$actual}' class='secMenu'>");
                                print("<h4 class='section'>{$actual}</h4>");
                                print("<table id='table_port' class='{$actual}'>");
                                //solo se requiere hacer una vez, entonces se pasa a false
                                $first = false;
                            }
                            //output cada sección de la tabla
                            print("<tr id='row_{$section["platillo"]}' class='elem_table_port'>");
                            print("<td width=25%>{$section["platillo"]}</td>");
                            print("<td width=25%>$ " . number_format($section["precio"], 2) . "</td>");
                            print("<td width=25%>{$section["tipo"]}</td>");
                            print("<td width=25%><button class='btn btn-default btnPush' onclick='elimina(\"{$section["platillo"]}\")'>X Erase</button></td>"); // name='platillo' value='{$section["platillo"]}'
                            print("</tr>");
                        }
                        //ya terminó la inserción de datos, ya se puede cerrar la última tabla
                        //antes agregandole un espacio para que inserte algo nuevo
                        print("</table>");
                        print("</div>");
                        print("</form>");
                    }
                    if ($found  == false)
                    {
                        print("<br>");
                        print("<h5>Please, insert another category with its elements</h5>");
                    }
                    else
                    {
                        print("<h5 id='orStat'>Or insert another category with its elements</h5>");
                    }
                    print("<div class='inputDiv'>");
                    print("<form autocomplete='off'>");
                    print("<table>");
                    print("<tr>");
                        print("<td><input id='secId' class='sec inputCarr' name='section' type='text' placeholder='Section' required></td>");
                        print("<td><input id='platId' class='plat inputCarr' name='platillo' type='text' placeholder='Main Dish' required></td>");
                        print("<td><input id='priceId' class='price inputCarr' name='precio' type='text' placeholder='Price' required></td>");
                        print("<td><input id='typeId' class='type inputCarr' name='tipo' type='text' placeholder='Type' required></td>");
                        print("<td><input type='submit' id='newCat' class='btn btnPush'></td>");
                    print("</tr>");
                    print("</table>");
                    print("</form>");
                    print("</div>");
                ?>
                <!-- Execute JAvascript function -->
                <script>
                    modMenuCtrl(<?php echo json_encode($sections); ?>);
                </script>
                
            </div>

