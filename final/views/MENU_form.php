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
                        print("<form>"); //action='MENU.php' method='post'
                        
                        foreach ($sections as $section)
                        {
                            $actual = $section["secc"];
                            
                            if ($tempo !== $actual) {
                                //si no son iguales, enonces actualizar "tempo" para poder continuar con la comparación
                                if ($first == false) {
                                    //terminar la tabla anterior
                                    print("</table>");
                                    print("</div>");
                                    //print("<br>");
                                }
                                $tempo = $section["secc"];
                                //y además agregar nueva tabla
                                ;
                                //print("<div class='title'>");
                                print("<div class='secMenu unifMenu'>");
                                print("<h4 class='section'>{$actual}</h4>");
                                //print("</div>");
                                print("<table id='table_port'>");
                                //solo se requería hacer una vez, entonces se pasa a false y así se queda para siempre ya colocar los fines de tabla
                                $first = false;
                            }
                            //output cada sección de la tabla
                            print("<tr class='elem_table_port'>");
                            //print("<td width=30%>{$section["secc"]}</td>");
                            print("<td><button class='btn btn-default btnPush' onclick='storeV(\"{$section["platillo"]}\")'>{$section["platillo"]}</button></td>"); // name='platillo' value='{$section["platillo"]}'
                            print("<td class='precio'>$ " . number_format($section["precio"], 2) . "</td>");
                            print("</tr>");
                        }
                        //ya terminó la inserción de datos, ya se puede cerrar la última tabla
                        print("</table>");
                        print("</div>");
                        print("</form>");
                    }
                ?>
                <!-- Execute JAvascript function -->
                <script>
                    llevaCtrl(<?php echo json_encode($behavior); ?>, <?php echo json_encode($platArr); ?>, <?php echo json_encode($stored); ?>);
                </script>
            </div>

