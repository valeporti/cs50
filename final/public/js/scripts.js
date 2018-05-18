/**
 * scripts.js
 *
 * Computer Science 50
 * Final Project
 *
 * Global JavaScript, if any.
 */
 
 //--> Alguna expliación de cómo falla getJSON : http://stackoverflow.com/questions/5492838/why-does-getjson-silently-fail
 //-->https://en.wikipedia.org/wiki/Same-origin_policy

/**
 * Universal Variables
 */
var platObj;
var stored;

$(document).ready(function () {
//http://stackoverflow.com/questions/25881204/how-to-use-jquery-post-method-to-submit-form-values
//http://stackoverflow.com/questions/30848965/sending-input-data-to-a-javascript-file
    $("#newCat").on("click", function(event) {
        event.preventDefault();
        console.log(event.type);
        var precio = 0;
        //ver si ninguno de los valores
        var newDish = {
            "request": "agregaDish",
            "platillo": $.trim($("#platId")[0].value),
            "seccion": $.trim($("#secId")[0].value),
            "precio": $.trim($("#priceId")[0].value),
            "tipo": $.trim($("#typeId")[0].value) //Con class seleccionada, antes tenía ".val()"
        };
        console.log(newDish);
        precio = newDish.precio;
        //Solo si se cumple lo siguietne se agrega
        if (newDish.platillo != "" && newDish.seccion != "" && newDish.precio != "" && newDish.tipo != "") {
            //console.log(newDish.request + newDish.platillo + newDish.seccion + newDish.precio + newDish.tipo);
            event.preventDefault();
            $.getJSON("addNew.php", newDish);
                //.done(function(data, textStatus, jqXHR) {
            
                    //console.log(data);
                //})
                //.fail(function(jqXHR, textStatus, errorThrown) {
            
                    // log error to browser's console
                    //alert("error: " + errorThrown.toString());
                    //console.log("error : " + textStatus + errorThrown.toString());
                //});
            //ya que ahora sin .done no lo llena solito, haré que ponga el elemento "manualmente"
            //Agregar al DOM
            //console.log("appenderá a " + newDish.seccion);
            creaEntorno("#formMenu", newDish);
            
            //$("<tr id='row_" + newDish.platillo + "' class='elem_table_port'>"
              //  + "<td width='25%'>" + newDish.platillo + "</td>"
                //+ "<td width='25%'>" + parseFloat(Math.round(precio * 100) / 100).toFixed(2) + "</td>"
            //    + "<td width='25%'>" + newDish.tipo + "</td>"
              //  + "<td width='25%'><button class='btn btn-default' onclick='elimina(\"" + newDish.platillo + "\")'>X Erase</button></td>"
                //+ "</tr>").appendTo("." + newDish.seccion);
            
            //como se hace la prevención de carga, quitar lo q ya está puesto en input
            $("#platId")[0].value;
            $("#secId")[0].value;
            $("#priceId")[0].value;
            $("#typeId")[0].value;
            
        } else {
            console.log("faltan datos");
        }
        
    });
    
});

/**
 * Nothing.. for tests
 */
function averq(data) {
     alert(data);
 }

function storeV(platillo) 
{
    event.preventDefault();
    
    var data = {
        "action": "pedidos",
        "valor": platillo
    };
    
    $.getJSON("pedidos.php", data);
    //no entiendo por qué pero la primera vez que lo hace saca error y la segunda no, y sin embargo las dos lo inserta bien
    //El error debe de venir de alguna otra parte que de la solicitud del PHP, prácticamente seguro que es de la comunicación
    //entre el documento PHP y la solicitud getJSON. Ayer encontré que tenía que ver con algo de same origin policy.
    
        //.done(function(data, textStatus, jqXHR) {
    
            //alert(data);
            //console.log(data);
        //})
        //.fail(function(jqXHR, textStatus, errorThrown) {
    
            // log error to browser's console
            //alert("error: " + errorThrown.toString());
            //console.log(textStatus + errorThrown.toString());
        //});
    //$.ajax("js/addtofavorites.php", {
        // Pass our data to the server
        //data: { "get" : "runfunction", "action" : "favorites1" },
        // Pass using the appropriate method
        //method: "POST",
        // When the request is completed and successful, run this code.
        //success: function (response) {
        // Successfully added to favorites. JS code goes here for this condition.
        //alert ("successfully loaded")
        //}          
    //});   
    
    //NUEVO !! :)
    //Hacer calculos y asignar a variable
    var match = false;
    for (var i = 0; i < platObj.length; i ++) {
        if (platObj[i].key == platillo) {
            //hacer análisis
            platObj[i].value.count ++;
            platObj[i].value.prodPerDay = platObj[i].value.count / platObj[i].value.diff;
            //console.log(platObj[i]);
            
            //Ahora analizar si tiene ingredientes y si sí ver su estado
            if (platObj[i].value.hasOwnProperty("ingArr")) {
                //ver que los ingredientes existan, y si sí, hacer algo con ellos
                for (var k = 0; k < platObj[i].value.ingArr.length; k ++) {
                    for (var j = 0; j < stored.length; j ++) {
                        if (stored[j].ingrediente == platObj[i].value.ingArr[k].ing) {
                            stored[j].cantidad = stored[j].cantidad - platObj[i].value.ingArr[k].qty;
                            if (stored[j].cantidad < 0) {
                                stored[j].cantidad = 0;
                            }
                            match = true;
                            break;
                        } else {
                            console.log("no se tiene uno de los ingredientes de " + platObj[i].value.ingArr[k].ing + " en recetas");
                        }
                    }
                    if (match == true) {
                        break;
                    }
                }
            } else {
                console.log("no se tiene la receta de " + platObj[i].key);
            }
            console.log(platObj[i]);
            console.log(stored);
            break;
        }
    }
    
}


/**
 * Erase from DB the product.
 */
function elimina(platillo)
{
    var data = {
        "action": "borraDB",
        "valor": platillo
    };
    
    $.getJSON("pedidosB.php", data);
        //.done(function(data, textStatus, jqXHR) {
    
            // call typeahead's callback with search results (i.e., places)
            //alert(data);
            //console.log(data);
            
            //lo que quiero que haga en caso de èxito, es que borre entonces de la lista el elemento contenedor
            $("#row_" + platillo).remove();
        //})
        //.fail(function(jqXHR, textStatus, errorThrown) {
    
            // log error to browser's console
            //alert("error: " + errorThrown.toString());
            //console.log("error: " + textStatus + errorThrown.toString());
        //});
}
 

function creaEntorno(w, d) {
    if (document.getElementById(d.seccion) == null) { //(!$.contains(w, "#" + d.seccion))?? no se si sirva
        console.log("detecto nuevo DIV");
        if (document.getElementById(w) == null) {
            console.log("detectó que no había un form y lo colcó");
            $("h3").remove();
            $("<form id='formMenu'></form>").prependTo("#middle"); //por si es el primer elemento de MENU
        }
        $("<br><div id='" + d.seccion + "' class='secMenu'>"
            + "<h4 class='section'>" + d.seccion + "</h4>"
            + "<table id='table_port' class='" + d.seccion + "'>"
            + "<tr id='row_" + d.platillo + "' class='elem_table_port'>" 
            + "<td width='25%'>" + d.platillo + "</td>"
            + "<td width='25%'>$ " + d.precio + "</td>"
            + "<td width='25%'>" + d.tipo + "</td>"
            + "<td width='25%'><button class='btn btn-default btnPush' onclick='elimina(\"" + d.platillo + "\")'>X Erase</button></td>"
            + "</tr></table>"
            + "</div>"
            ).appendTo(w);
    } else {
        console.log("colocó juego para " + d.platillo + " con ingrrediente: " + d.ing);

        $("<tr id='row_" + d.platillo + "' class='elem_table_port'>"
            + "<td width='25%'>" + d.platillo + "</td>"
            + "<td width='25%'>$ " + parseFloat(Math.round(d.precio * 100) / 100).toFixed(2) + "</td>"
            + "<td width='25%'>" + d.tipo + "</td>"
            + "<td width='25%'><button class='btn btn-default btnPush' onclick='elimina(\"" + d.platillo + "\")'>X Erase</button></td>"
            + "</tr>").appendTo("." + d.seccion);
    }
 }

/** 
 * la siguiente función tinee como fin agregar un row a la tabla para que se pueda acumular los ingredientes deseados
 */
var addedRows = 0;
function addRow(tabla) {
    //"tabla" será un string de la forma "tabla_(lo q sea)_(para numero de personas)"
    //necesitamos quitar esta parte y al final agregarla (po problemas de append to y el script para guardarrcetas)
    var arr = tabla.split("_");
    var platillo = arr[1];
    var numP = arr[2];
    var idinputCarr = "inputNewIng";
    var idtr = "newCol";
    addedRows ++;

    //console.log(platillo);
    if (numP != 0) {
     $("<tr id='row_" + platillo + "_new' class='newIng'>"
            + "<td id='" + idtr + addedRows + "' class='" + platillo + "_" + numP + "'><input id='" + idinputCarr + "' class='ingrediente' type='text' placeholder='Ingredient'></td>"
            + "<td id='" + idtr + addedRows +  "' class='" + platillo + "_" + numP + "'><input id='" + idinputCarr + "' class='cant' type='number' placeholder='Quantity'></td>"
            + "<td id='" + idtr + addedRows +  "' class='" + platillo + "_" + numP + "'><input id='" + idinputCarr + "' class='unit' type='text' placeholder='Unit'></td>"
        + "</tr>").appendTo("." + tabla);
    }
    else {
     $("<tr id='row_" + platillo + "_new' class='newIng'>"
            + "<td id='" + idtr + addedRows +  "' class='" + platillo + "'><input id='" + idinputCarr + "' class='ingrediente' type='text' placeholder='Ingredient'></td>"
            + "<td id='" + idtr + addedRows +  "' class='" + platillo + "'><input id='" + idinputCarr + "' class='cant' type='number' placeholder='Quantity'></td>"
            + "<td id='" + idtr + addedRows +  "' class='" + platillo + "'><input id='" + idinputCarr + "' class='unit' type='text' placeholder='Unit'></td>"
        + "</tr>").appendTo("." + tabla);
        
    }
    //asignar los typeahead
    //"#" + idtr + addedRows + " .ingrediente" selecciona de manera descendete el elemento del DOM (parent -> child)
    typeaheadFunc(porIng, "#" + idtr + addedRows + " .ingrediente");
    typeaheadFunc(porUni, "#" + idtr + addedRows + " .unit");
 }
 
function addRecipe() {
    //Tomar todos los campos con información para procesarlos
    //para insertar un ingrediente, cada input de la línea de ingrediente debe tener un valor
    //para insertar una nueva receta, debe existir también el platillo y la cantidad de personas para las que está planeado
    
    //var inputElements = document.getElementsByTagName('input');
    var inputElements = $("input");
    //console.log(inputElements.length);
    //var lol = $("input")
    //console.log(lol.length);
    //console.log(lol[3].closest("td").className); //.parentsUntil("td"));
    //console.log(lol[3].parentNode.tagName);
    //console.log(lol[4].closest("td"));
    //console.log(lol[4].parentNode.tagName);
    //console.log(typeof(lol));
    //console.log(lol);
    //console.log(lol[4].parentNode.is("td"));
    //http://stackoverflow.com/questions/608410/finding-the-type-of-an-element-using-jquery
    
    //los elementos que no queremos no tienen ID puede ser un punto de oportunidad
    for (var i = 0; i < inputElements.length; i ++) {
        if (inputElements[i].id == "") { //lol[i].id == ""
            inputElements.splice(i, 1); //lol.splice(i, 1);
            //delete lol[i]; //esta manera no odifica el length
        }
    }
    //console.log(lol);
    //console.log(lol.length);
    //console.log(lol[2].className);
    //console.log(lol[2].className.split(" "));
    //for (var j = 0; j < lol.length; j ++) {
        //console.log(lol[j].value);
    //}
    
    //REPROCESAR ANTIGUA FUNCION Y ADAPTARLA PARA RESPONDER A NUEVO ENTORNO (EBIDO A TYPEAHEAD QUE AGREGA UN INPUT ELEMENT Y SPAN)
    // **/ Para detalles de antigua función ver  addRecipeANTERIOR()
    
    //Procesar Inputs : 1 de si es nueva receta los 2 "principales" paltillo y numPersonas y luego las ternas de ingredientes
    var count = 0; //Se puede quitar, sólo sirve para contar los numeros de ternas obtenidas
    var countEnv = 0; //Se puede quitar, sólo sirve para contar los numeros de enradas a envoltura
    var envoltura = [];
    var elementoPlatillo = [];
    var envoAct = "";
    var envoTempo = "";
    
    var splitClass = [];
    
    var ingredienteTrio = [];
    var primeraCorrida = true;
    
    var inputPair = [];
    var ignoreNew = false; //pretende decir si se lee o no lee lo coorrespondiente a las lineas respectivas de newRec (de manera a exigir se pongan los 2 valores numPer y NombrePlat) 
    console.log("Se revisarán un total de inputs: --> " + inputElements.length);
    //-->Loop en cada elemento class "receta" y así ver sus valores o la inexistencia de los mismos
    for (var i = 0; i < inputElements.length; i ++) {
        
        //La idea es envolver para cada platillo su numero de elementos
        envoAct = inputElements[i].closest("td").className; //Lograremos así leer la clase que nos interesa
        console.log(envoAct);
        if (envoAct != envoTempo) {
            if (primeraCorrida == false && elementoPlatillo.length != 0) {
                //console.log("detectó que ya no era la prmera corrda y pusheará");
                //Cuando se haya pasado el primer ParentNode diferente, se entrará aquí
                //Algo que se puede hacer es colocar el nombre del parentNode como string y luego los arrays coorrespondientes
                if (envoTempo == "newRec" && elementoPlatillo.length > 1) {
                    //en este caso para evitar que sólo se meta el array con MainDish y NumPErsonas sin ingredientes
                    envoltura.push(elementoPlatillo);
                    countEnv ++;
                    console.log("push en 1");
                }
                else if (envoTempo != "newRec") {
                    envoltura.push(elementoPlatillo);
                    countEnv ++;
                    console.log("push en 2");
                }
                elementoPlatillo = [];
                envoTempo = envoAct;
            }
            else {
                primeraCorrida = false;
                envoTempo = envoAct;
            }
        }
        
        //Si el parentNode es diferente a NewRec, significa qua ya solo interesan los 3 valores siguientes
        //En cambio si es newRec y no son los primeros 2 valores que serían el "nombrePlat" + "numPersonas" se almacenarán igual solo si,
        //existieron previamente estos dos valores
        inputPair = [];
        if (envoAct != "newRec") {
            //Aqui va qué hacer con inputs de tipo no Nuevo
            //Obtener valores de input estudiado
            inputPair[0] = envoAct;
            splitClass = inputElements[i].className.split(" "); 
            inputPair[1] = splitClass[0]; //así aunque tenga una clase el input (como anteriormente, se obtendrá el valor deseado)
            inputPair[2] = inputElements[i].value;
            //solo poner en array en caso de que si exista un valor
            if (inputPair[2] != "") {
                ingredienteTrio.push(inputPair);
            }
        }
        else if (ignoreNew == false) {
            //Aqui va qué hacer en caso de que en efecto exista input para platillo y numPersonas en NewRec (ignoreNew == false)
            //y también en caso de que i < 2 (osea que se esté estudiando nombrePlat y numPers) y ahí se define ignoreNew
            //Obtener valores de input estudiado
            inputPair[0] = envoAct;
            splitClass = inputElements[i].className.split(" "); 
            inputPair[1] = splitClass[0];
            inputPair[2] = inputElements[i].value;
            //solo poner en array en caso de que si exista un valor
            if (inputPair[2] != "") {
                ingredienteTrio.push(inputPair);
            }
        }
        splitClass = [];
        //En caso de que no, seguir sin hacer nada, posteriormente en bloque de análisis se dará cuenta que se ignoró
        //Pues el array de filaIngrediente (o valueTrio) no será 3
        
        
        // < -- ANALISIS DE LO QUE SE VA A HACER CON LOS VALORES OBTENIDOS unicamente cuando haya 2 valores o haya trios -->
        //Aqui crear ternas de valores ingrediente + cantidad + unidad
    
        //Esto es para los casos de los "títulos" para las nuevas recetas o para las ternas de valores
        if (i == 1 || (i-1)%3 == 0) {
            //Primero vienen las reglas para las ternas (son las que considero se podrìan repetir más, por eso primero, ahorrar tiempo)
            if (ingredienteTrio.length == 3) {
                elementoPlatillo.push(ingredienteTrio);
                count ++;
            }
            //primero si alguno de los dos valores "platillo" o "numPersonas" falta que no se inserte nada de lo siguiente
            //es el unico que podrìa tener length 2 e i == 1
            else if (ingredienteTrio.length == 2 && i == 1) {
                elementoPlatillo.push(ingredienteTrio);
                ignoreNew = false;
            }
            else if (i == 1 && ingredienteTrio.length < 2) {
                console.log("Missing Main dish, ingredient, #of people, quantiy or unit, please, fullfill every space. Thanks! :)");
                ignoreNew = true;
            }
            else {
                console.log(ingredienteTrio.length);
                console.log("Missing Ingredient, quantity or unit, please, fullfill every space. Thanks! :)");
            }
            ingredienteTrio = [];
            //finalmente cerrar Array 
        }
        //colocar algo que marque el cambio, puede ser, 
        //si el valueTrio no es 3 de length significa que hay algún valor que falta, pedir que lo meta
        //si ni siquiera se tiene el ingrediente pedirlo
        
        //Para ganatizar que el Entorno tega contenido en caso de haberlo, en la última vuelta del loop se push() el valor que se tenga
        if (i == inputElements.length - 1 && elementoPlatillo.length != 0) {
            if (envoAct == "newRec" && elementoPlatillo.length > 1) {
                    //en este caso para evitar que sólo se meta el array con MainDish y NumPErsonas sin ingredientes
                envoltura.push(elementoPlatillo);
                countEnv ++;
                console.log("push en 3");
            }
            else if (envoAct != "newRec") {
                envoltura.push(elementoPlatillo);
                countEnv ++;
                console.log("push en 4");
            }
        }
    }
    //ver si entro todo bien, si sí, hacer la función de inserción, si no, no hacer nada hasta que el usuario meta toda la información
    
    console.log("Envoltura tiene " + countEnv + " elementos : ");
    console.log(envoltura);
    if (envoltura.length != 0) {
        console.log("se logró entrar a la función  <--------------");
        //función
        cargaReceta(envoltura);

    }
}
function addRecipeANTERIOR() {
    //Tomar todos los campos con información para procesarlos
    //para insertar un ingrediente, cada input de la línea de ingrediente debe tener un valor
    //para insertar una nueva receta, debe existir también el platillo y la cantidad de personas para las que está planeado
    
    var inputElements = document.getElementsByTagName('input');

    //Procesar Inputs : 1 de si es nueva receta los 2 "principales" paltillo y numPersonas y luego las ternas de ingredientes
    var count = 0; //Se puede quitar, sólo sirve para contar los numeros de ternas obtenidas
    var countEnv = 0; //Se puede quitar, sólo sirve para contar los numeros de enradas a envoltura
    var envoltura = [];
    var elementoPlatillo = [];
    var envoAct = "";
    var envoTempo = "";
    
    var ingredienteTrio = [];
    var primeraCorrida = true;
    
    var inputPair = [];
    var ignoreNew = false; //pretende decir si se lee o no lee lo coorrespondiente a las lineas respectivas de newRec (de manera a exigir se pongan los 2 valores numPer y NombrePlat) 
    console.log("Se revisarán un total de inputs: --> " + inputElements.length);
    //-->Loop en cada elemento class "receta" y así ver sus valores o la inexistencia de los mismos
    for (var i = 0; i < inputElements.length; i ++) {
        
        //La idea es envolver para cada platillo su numero de elementos
        envoAct = inputElements[i].parentNode.className; //Esto se puede sustituir por inputElements[i].closest("td").className;
        console.log(envoAct);
        if (envoAct != envoTempo) {
            //console.log("detectó que eran diferentes");
            if (primeraCorrida == false && elementoPlatillo.length != 0) {
                //console.log("detectó que ya no era la prmera corrda y pusheará");
                //Cuando se haya pasado el primer ParentNode diferente, se entrará aquí
                //Algo que se puede hacer es colocar el nombre del parentNode como string y luego los arrays coorrespondientes
                if (envoTempo == "newRec" && elementoPlatillo.length > 1) {
                    //en este caso para evitar que sólo se meta el array con MainDish y NumPErsonas sin ingredientes
                    envoltura.push(elementoPlatillo);
                    countEnv ++;
                    console.log("push en 1");
                }
                else if (envoTempo != "newRec") {
                    envoltura.push(elementoPlatillo);
                    countEnv ++;
                    console.log("push en 2");
                }
                elementoPlatillo = [];
                envoTempo = envoAct;
            }
            else {
                //console.log("detectó que era la primera corrida");
                primeraCorrida = false;
                envoTempo = envoAct;
            }
        }
        //console.log(inputElements[i].parentNode.className);
        //console.log("------");
        
        //Si el parentNode es diferente a NewRec, significa qua ya solo interesan los 3 valores siguientes
        //En cambio si es newRec y no son los primeros 2 valores que serían el "nombrePlat" + "numPersonas" se almacenarán igual solo si,
        //existieron previamente estos dos valores
        inputPair = [];
        //console.log(envoAct);
        if (envoAct != "newRec") {
            //Aqui va qué hacer con inputs de tipo no Nuevo
            //Obtener valores de input estudiado
            inputPair[0] = envoAct;
            inputPair[1] = inputElements[i].className;
            inputPair[2] = inputElements[i].value;
            //solo poner en array en caso de que si exista un valor
            if (inputPair[2] != "") {
                ingredienteTrio.push(inputPair);
            }
        }
        else if (ignoreNew == false) {
            //Aqui va qué hacer en caso de que en efecto exista input para platillo y numPersonas en NewRec (ignoreNew == false)
            //y también en caso de que i < 2 (osea que se esté estudiando nombrePlat y numPers) y ahí se define ignoreNew
            //Obtener valores de input estudiado
            inputPair[0] = envoAct;
            inputPair[1] = inputElements[i].className;
            inputPair[2] = inputElements[i].value;
            //solo poner en array en caso de que si exista un valor
            if (inputPair[2] != "") {
                ingredienteTrio.push(inputPair);
            }
        }
        //En caso de que no, seguir sin hacer nada, posteriormente en bloque de análisis se dará cuenta que se ignoró
        //Pues el array de filaIngrediente (o valueTrio) no será 3
        
        
        // < -- ANALISIS DE LO QUE SE VA A HACER CON LOS VALORES OBTENIDOS unicamente cuando haya 2 valores o haya trios -->
        //Aqui crear ternas de valores ingrediente + cantidad + unidad
    
        //Esto es para los casos de los "títulos" para las nuevas recetas o para las ternas de valores
        if (i == 1 || (i-1)%3 == 0) {
            //Primero vienen las reglas para las ternas (son las que considero se podrìan repetir más, por eso primero, ahorrar tiempo)
            if (ingredienteTrio.length == 3) {
                elementoPlatillo.push(ingredienteTrio);
                count ++;
                //console.log("Se hizo " + count + " matches");
                //console.log("En Platillo : " + ingredienteTrio[0][0]);
                //console.log("ingrediente: " + ingredienteTrio[0][2] + "| cantidad: " + ingredienteTrio[1][2] + "| unidad: " + ingredienteTrio[2][2]);
                //console.log("elementoPlatillo:");
                //console.log(elementoPlatillo.length);
                //console.log(elementoPlatillo);
            }
            //primero si alguno de los dos valores "platillo" o "numPersonas" falta que no se inserte nada de lo siguiente
            //es el unico que podrìa tener length 2 e i == 1
            else if (ingredienteTrio.length == 2 && i == 1) {
                //console.log(ingredienteTrio.length);
                //console.log("Existing Main Dish Name: " + ingredienteTrio[0][2] + " and # of People: " + ingredienteTrio[1][2] + " :)");
                elementoPlatillo.push(ingredienteTrio);
                ignoreNew = false;
                //console.log("elementoPlatillo:");
                //console.log(elementoPlatillo.length);
                //console.log(elementoPlatillo);
                //Colocar esto también para tener esos dos valores
                //envoltura.push(elementoPlatillo);
                //elementoPlatillo = [];
            }
            else if (i == 1 && ingredienteTrio.length < 2) {
                //console.log(ingredienteTrio.length);
                console.log("Missing Main dish, ingredient, #of people, quantiy or unit, please, fullfill every space. Thanks! :)");
                ignoreNew = true;
            }
            else {
                console.log(ingredienteTrio.length);
                console.log("Missing Ingredient, quantity or unit, please, fullfill every space. Thanks! :)");
            }
            //console.log(ingredienteTrio);
            ingredienteTrio = [];
            //finalmente cerrar Array 
        }
        //console.log(elementoPlatillo);
        //colocar algo que marque el cambio, puede ser, 
        //si el valueTrio no es 3 de length significa que hay algún valor que falta, pedir que lo meta
        //si ni siquiera se tiene el ingrediente pedirlo
        
        //Para ganatizar que el Entorno tega contenido en caso de haberlo, en la última vuelta del loop se push() el valor que se tenga
        if (i == inputElements.length - 1 && elementoPlatillo.length != 0) {
            //console.log("Elemento Platillo antes de pushear");
            //console.log(elementoPlatillo);
            if (envoAct == "newRec" && elementoPlatillo.length > 1) {
                    //en este caso para evitar que sólo se meta el array con MainDish y NumPErsonas sin ingredientes
                envoltura.push(elementoPlatillo);
                countEnv ++;
                console.log("push en 3");
            }
            else if (envoAct != "newRec") {
                envoltura.push(elementoPlatillo);
                countEnv ++;
                console.log("push en 4");
            }
        }
        
        //eliminar contenido de inputs
        //$(".plat").val('');
        //console.log("value input : " + inputElements[i].value);
       //inputElements[i].value = "";
    }
    //ver si entro todo bien, si sí, hacer la función de inserción, si no, no hacer nada hasta que el usuario meta toda la información
    
    console.log("Envoltura tiene " + countEnv + " elementos : ");
    console.log(envoltura);
    if (envoltura.length != 0) {
        console.log("se logró entrar a la función  <--------------");
        //función
        cargaReceta(envoltura);

    }
 }
 
function eliminaIng(plat, ing, uni) {
    
    var data = {
        "action": "borraDB",
        "plat": plat,
        "ing": ing,
        "uni": uni
    };
    
    $.getJSON("recipeAnalysis.php", data);
    $("#row_" + plat + "_" + ing).remove();

 }
 
 /**
 * Add ingredients from recipes into mySQL.
 */
function cargaReceta(env) {
    console.log(env);
    //eliminaEntorno(); 
    
     var arrPlatYNum = [];
     var platAct = "";
     var numPAct = "";
     var ing = "";
     var cant = "";
     var uni = "";
     var sigArr = false;
        //Para cada elemento agregarlo en mySQL
        for (var e = 0; e < env.length; e ++) {
            //si la siguiente condicional es verdadera significa que ese array pertenece a "NuevaReceta"
            if (env[e][0][0][0] == "newRec") {
                platAct = env[e][0][0][2];
                numPAct = env[e][0][1][2];
                sigArr = true;
            }
            else {
                arrPlatYNum = env[e][0][0][0].split("_");
                platAct = arrPlatYNum[0];
                numPAct = arrPlatYNum[1];
            }
            //en est caso ya no es más lineal como arriba (no todo se arreglará con "ifs") por ello emplearemos loops
            for (var eP = 0; eP < env[e].length; eP ++) {
                //Solo para quitarnos del primer array si es que se trata de newRec donde viene platillo y numP
                if (sigArr === true) {
                    eP ++;
                    sigArr = false;
                }
                //a partir de aqui ya son siempre 3 arrays con 3 valores cada uno
                //1- Ingrediente
                ing = env[e][eP][0][2];
                //1- Canidad
                cant = env[e][eP][1][2];
                //1- unidad
                uni = env[e][eP][2][2];
                
                //Ya que se tienen todos los valores se puede hacer el envío de datos
                var data = {
                    "action": "addIng",
                    "platillo": platAct,
                    "numP": numPAct,
                    "ing": ing,
                    "cant": cant,
                    "uni": uni,
                    "tip": env[e][0][0][0]
                };
                
                console.log(data);
                $.getJSON("recipeAnalysis.php", data);
                //append to
                //creaEntorno(data);
            }
        }
    //Falta hacer que aparezcan los rows nuevos de inmediato. y desaparezcan los de inserción
    congratsReload(); // No logro cargar los contenidos, entonces enviaré una congratlación y luego cargaré
    //window.location.href = '/recipes.php';
    //window.location.reload(true);
    //console.log("si llega hasta aca")
    //igual también se podría hacer con JQuery pero es más largo
}

function congratsReload() {

    $("<div id='camu'>"
        + "<p id='camuText'>Info Loaded to Your Recipes DataBase :)</p>"
        + "</div>"
        ).prependTo("#middle");
        
    $("#camu").delay(1500).fadeOut("slow");
    
    timeOut = setTimeout(function() {
        window.location.href = '/recipes.php';
    }, 1500);
}

function asignChoiceDrpdwn(platillo) {
    console.log(platillo);
}


 
