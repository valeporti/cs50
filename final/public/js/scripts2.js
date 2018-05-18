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

var selRecipe = "";

function asignChoiceDrpdwn(platillo) {
    //colocar en variable
    selRecipe = platillo;
    //y colocar en texto de cosa
    $("#dropdownMenu1").text(platillo);
}

function showRecipe(recetas) {
    //se recibe el array completo, aislar los ingredientes del producto deseado
    platillo = selRecipe;
    if (platillo == "") {
        $("#middle").append("<br><br><p><b>Something, missing, maybe ingredients :S</b></p>");
        return; //early end of javascript function
    }
    var arr = [];
    for (var i = 0; i < recetas.length; i ++) {
        if (platillo == recetas[i].platillo) {
            arr.push(recetas[i]);
            if ((i == recetas.length - 1) || (platillo != recetas[i + 1].platillo)) {
                break;
            }
        }
    }
    console.log(arr);
    //ver si el input de número de personas está llenado, si no usar como default el ya existente
    var inputElements = document.getElementsByTagName('input'); //solo habrá uno
    var personas = 0;
    var recPer = personas = arr[0].numP;
    console.log(inputElements[0].value);
    if (!Boolean(inputElements[0].value)) {
        personas = arr[0].numP;
    } else {
        personas = inputElements[0].value;
    }
    console.log(personas);
    //renderizar
    var htmlCode = "";
    var factor = Math.round((personas / recPer) * 10000) / 10000; //con 4 decimales para calcular
    
    htmlCode = "<div class='showRecipe'>"
        + "<h4 class='section showPlatillo'>" + platillo + " for " + personas + " persons" + "</h4>"
        + "<table id='table_port'>";
    //add each row to the table
    for (var i = 0; i < arr.length; i ++) {
        htmlCode += "<tr class='elem_table_port'>"
            + "<td>" + arr[i].ingrediente + "</td>"
            + "<td>" + Math.round(arr[i].cantidad * factor * 1000) / 1000 + "</td>"
            + "<td>" + arr[i].unidad + "</td>"
            + "</tr>";
    }
    //final del htmlCode
    htmlCode += "</table></div>";
    
    //Colocar en DOM
    $("#middle").append(htmlCode);
}

function clearRecipes() {
    $( ".showRecipe" ).remove(); //elimina todos los elementos de esa clase y que estén dentro de esa clase
}

function manageProductsTime(data) {
    //PRueba para manejar date
//    console.log(data);
  //  var dateMan = data[data.length - 1].datime;
    //console.log("hay datos: " + data.length);

    //var dateArr = [];
//    dateArr = dateMan.split(/[- :]/g); // --> [yy, mm, dd, hh, min, sec] : typeof() = string
    //console.log("del SQL " + dateArr);
    //dateArr = toSpecTimeZone(-6, dateArr); // --> [yy, mm, dd, hh, min, sec] : UTC correction + typeof() = string
    //console.log("analizada " + dateArr); 
    //for (var i = 0; i < 6; i ++) {
    //    console.log(typeof(dateArr[i]));
    //}
    //crear nuevo objeto de todos los datos, con fecha corregida
    var newArr = [];
    var dateStr = "";
    var dateArr = [];
    var dateObj = {};
    for (var i = 0; i < data.length; i ++) {
        dateStr = data[i].datime;
        dateArr = dateStr.split(/[- :]/g); // --> [yy, mm, dd, hh, min, sec] : typeof() = string
        //!\ VErificar cambio de horario en verano para determinar lo de UTC
        dateObj = new Date(Date.UTC(dateArr[0], dateArr[1] - 1, dateArr[2], dateArr[3], dateArr[4], dateArr[5]));
        //dateArr = toSpecTimeZone(-6, dateArr); //-6 por horario UTC en México 
        // --> [yy, mm, dd, hh, min, sec] : UTC correction + typeof() = number
        newArr.push(
                {
                    "dateObj": dateObj,
                    "platillo": data[i].platillo
                }
            );
    }
    return newArr;
}


/**
 * NO USADA PEro gardada con orgullo
 * Antes de entender DATE OBJECTS
 */
function toSpecTimeZone(UTCdiff, arr) { //arr must be: "[yy, mm, dd, hh, min, sec]" format
    //lo que tenemos que cambiar es la hora
    var yy = Number(arr[0]);
    var mm = Number(arr[1]);
    var dd = Number(arr[2]);
    var hh = Number(arr[3]);
    var min = Number(arr[4]);
    var ss = Number(arr[5]);
    
    var maxDay = 0;
    
    var ch = 0; //para calcular la hora
    ch = hh + UTCdiff;
    if (ch < 24 && ch >= 0) {
        return [yy, mm, dd, ch, min, ss];
    }
    else if (ch >= 24)  {
        ch = ch - 24;
        dd ++;
        maxDay = daysInMonth(yy, mm, 1); //maximos días de ese mes, para ver si no se pasa
        console.log(maxDay);
        if (dd > maxDay) {
            mm ++;
            dd = 1;
            if (mm > 12) {
                mm = 1;
                yy ++;
            }
        }
    }
    else if (ch < 0) {
        ch = 24 + ch;
        dd --;
        if (mm == 1) {
            mm = 12;
            dd = 31;
            yy --;
        } 
        else if (dd == 0) {
            mm --;
            maxDay = daysInMonth(yy, mm, 1); //maximos días del mes anterior
            dd = maxDay;
        }
    }
    return [yy, mm, dd, ch, min, ss];
}

//http://stackoverflow.com/questions/1184334/get-number-days-in-a-specified-month-using-javascript
function daysInMonth(month, year) {
    return new Date(year, month, 1).getDate();
}

function assignPeriod(hh) {
    //dataArr format: [yy, mm, dd, hh, min, ss]
    //https://www.englishclub.com/ref/esl/Power_of_7/7_Times_of_the_Day_2939.htm
    //console.log(dateArr)
    //var hh = dateArr[3]; // <-- Antes, cuando usaba un array
    if (0 <= hh && hh < 6) {
        return "Dawn";
    }
    else if (6 <= hh && hh < 11) {
        return "Morning";
    }
    else if (11 <= hh && hh < 16) {
        return "Afternoon";
    }
    else if (16 <= hh && hh < 19) {
        return "Evening";
    }
    else if (19 <= hh && hh < 23) {
        return "Night";
    }
    else if (23 <= hh && hh < 24) {
        return "Dawn";
    }
    else {
        return "error";
    }
}

// *
// Envío de inputs de compras
//
function addbought() {
    var inputElements = document.getElementsByTagName('input');
    //PAra cada elemento encontrado, ver si el valor ingresado es "" o es un número (todos los inputs deben de ser números)
    var qtyShoped = 0;
    var ingredientShoped = "";
    var unitShoped = "";
    var inputID = "";
    var elemIn = "";
    var arr = [];
    for (var i = 0; i < inputElements.length; i ++) {
        elemIn = inputElements[i];
        if (elemIn.value != "") { //o si es un número
            qtyShoped = elemIn.value;
            inputID = elemIn.id;
            arr = inputID.split("_"); //será de la forma [shopedInput, ingrediente, unidad]
            ingredientShoped = arr[1];
            unitShoped = arr[2];
            
            var data = {
                "request": "addGrocery",
                "Qty": qtyShoped,
                "ing": ingredientShoped,
                "uni": unitShoped
                //colocar datos a enviar aquí
            };
            console.log(data);
            //una vez obtenidos los valores envíar a base de datos donde coincidan ambos
            $.getJSON("shop_bought.php", data); // a la Base de DATOS
            //habra un elemento de tabla con id de la forma: st_ingrediente_unidad
            var storedBefore = Number($("#st_" + ingredientShoped + "_" + unitShoped).text());
            console.log(storedBefore);
            $("#st_" + ingredientShoped + "_" + unitShoped).text(storedBefore + Number(qtyShoped)); //Al front end que ve el usuario
            $("#shopedInput_" + ingredientShoped + "_" + unitShoped).val("");
        }
        unitShoped = "";
        ingredientShoped = "";
    }
}

/**
 * llevar el comportameinto de lo consumido.
 */
 //To convert string to Date: http://stackoverflow.com/questions/5619202/converting-string-to-date-in-js
 //To create date object: https://developer.mozilla.org/es/docs/Web/JavaScript/Referencia/Objetos_globales/Date/UTC
function llevaCtrl(data, platArr, storedArr) {
    //Iniciar acomodando datos como queremos
    
    stored = storedArr;
    console.log(stored);
    platObj = crearObjPlat(data, platArr);
    console.log(platObj);
    
    //antes de salir de la página, enviar todos los datos obtenidos
    $(window).bind('beforeunload', function(){
        //calcular consumo 
        for (var i = 0; i < stored.length; i ++) {
            for (var j = 0; j < platObj.length; j ++) {
                if (platObj[j].value.hasOwnProperty("ingArr")) {
                    for (var k = 0; k < platObj[j].value.ingArr.length; k ++) {
                        if ((platObj[j].value.ingArr[k].ing == stored[i].ingrediente) && (platObj[j].value.ingArr[k].uni == stored[i].unidad)) {
                            //lo consumido es [(cantidad usada en producto del ingrediente * factor de comportamiento)]
                            stored[i].consumo += platObj[j].value.prodPerDay * platObj[j].value.ingArr[k].qty; 
                            console.log("es de " + stored[i].ingrediente + stored[i].consumo + "");
                        }
                    }
                }
            }
        }
        console.log(stored);
        console.log(stored[0].cantidad + " de " + stored[0].ingrediente);
        
        var data = {
            "request": "addBehavior",
            "stored": stored
        };
        
        $.getJSON("shop_bought.php", data);
        
    });
}

/**
 * Crear Objeto para manejar los platllos
 */
function crearObjPlat(data, platArr) {
    //entenidendoLasFechasComoAcomodarlas(data); //valido para cuando manejaba arrays para la fecha
    
    var arr = [];
    arr = manageProductsTime(data); //array de objetos
    //console.log(data);
    //console.log(arr);

    var platillos = d3.nest()
        .key(function(d) { return d.platillo; })
        .rollup(function(v) {
            //console.log(v);
            var num = v.length;
            //a lo mejor hay algúna manera más astuta d ecalcularlo: 
            //mar en cuenta los días laborales, o algo por el estilo
            //var max = d3.max(v, function(d) { return d.dateObj; });
            var max = new Date();
            var min = d3.min(v, function(d) { return d.dateObj; });
            //http://stackoverflow.com/questions/3224834/get-difference-between-2-dates-in-javascript
            var diff = (max.getTime() - min.getTime()) / (24 * 60 * 60000); //obtener la diferencia en números 
                //unidades: [Milisegundos / [milisegundos/día]] = días
            return {
                count: num,
                diff: Math.round(diff * 10000) / 10000, //rpund to 4 decimal places
                maxDate: max,
                minDate: min,
                prodPerDay: Math.round((num / diff) * 10000) / 10000
                //: count/(maxDate - minDate)
            };  
        })
        .entries(arr);
    //Una opción que se me ocurre, en lugar de hacer un array de arrays, hacer un array de objetos
    //Agregar ingrediente si existe al objeto indicado
    var maxIterations = platArr.length;
    var matches = 0;
    for (var i = 0; i < platillos.length; i ++) {
        for (var j = 0; j < maxIterations; j ++) {
            if (platArr[j].pla.toUpperCase() == platillos[i].key.toUpperCase()) { //Ingore Case (Si es mayúscula o minúscula)
                platillos[i].value.recipesKey = platArr[j].pla; //para no tener problemas cuando regresemos la información
                platillos[i].value.ingArr = platArr[j].ingArr;
                matches ++;
                //console.log("hay " + matches + " matches en " + platillos[i].key);
                break;
            }
        }
        if (matches == 3) {
            break;
        }
    }
    //console.log(platArr);
    //console.log(platillos);
    return platillos;
}

/**
 * Entender el Objeto Date y manejarlo para mi conveniencia
 */
function entenidendoLasFechasComoAcomodarlas(data) {
    var arr = [];
    arr = manageProductsTime(data);
    console.log(data);
    darr = [];
    darr = data[0].datime.split(/[- :]/g);
    var date3 = new Date(Date.UTC(darr[0], darr[1] - 1, darr[2], darr[3], darr[4], darr[5]));
    console.log(date3);
    console.log(date3.getHours());
    var date = new Date(arr[0].dateArr[0], arr[0].dateArr[1] - 1, arr[0].dateArr[2], arr[0].dateArr[3], arr[0].dateArr[4], arr[0].dateArr[5], 0);
    var date2 = new Date(Date.UTC(arr[1].dateArr[0], arr[1].dateArr[1] - 1, arr[1].dateArr[2], arr[1].dateArr[3], arr[1].dateArr[4], arr[1].dateArr[5], 0));
    var lol = 0; 
    if (date > date2) {
        lol = 2;
    }
    else if (date <= date2) {
        lol = 3;
    }
    else {
        lol = 1;
    }
    console.log(date);
    console.log(date2);
    console.log(lol); 
}

/**
 * Función que tratará los datos otorgados desde Base de Datos dentro de la interfáz de RECETAS
 */
var porIng = [];
var porUni = [];
function dataClientRecipes(recipes) {
    console.log(recipes);
    if (!recipes[0].hasOwnProperty("apology")) {
        porIng = recipes.map( function(d) {return d.ingrediente;} );
        porIng = porIng.filter(function(item, index, arr) {
            return arr.indexOf(item) == index;
        });
        porUni = recipes.map( function(d) {return d.unidad;} );
        porUni = porUni.filter(function(item, index, arr) {
            return arr.indexOf(item) == index;
        });
        console.log(porIng);
        console.log(porUni);
        // configure typeahead
        // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
        typeaheadFunc(porIng, ".ingrediente");
        typeaheadFunc(porUni, ".unidad");
    }
}


function typeaheadFunc(arr, DOMele) {

    $(DOMele).typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: encuentraMatchTypeahead(arr),
    });
    //.on("input", function(e) {
//        var myVal = e.target.value;
  //      console.log(e.target),
    //    console.log(myVal)
    //});
    
}

//http://codepen.io/balajinatarajan/pen/ocKxC
function encuentraMatchTypeahead(strs) {
  return function findMatches(q, cb) {
    var matches, substrRegex, subLength;
 
    // an array that will be populated with substring matches
    matches = [];
 
    // regex used to determine if a string contains the substring `q`
    //substrRegex = new RegExp(q, 'i');
    subLength = q.length;
 
    // iterate through the pool of strings and for any string that
    // contains the substring `q`, add it to the `matches` array
    $.each(strs, function(i, str) {
        
        if (str.substr(0, subLength).toUpperCase() == q.toUpperCase()) {
            // the typeahead jQuery plugin expects suggestions to a
            // JavaScript object, refer to typeahead docs for more info
            matches.push({ value: str });
        } 
    });
    cb(matches);
  };
};

function todaviano() {

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);
    
}

/**
 * Función que tratará los datos otorgados desde Base de Datos dentro de la interfáz de MENU MODIFY
 */
var porSec = [];
var porTyp = [];
function modMenuCtrl(data) {
    console.log(data);
    if (!data[0].hasOwnProperty("apology")) { //significa que no hay nungún dato, entonces no colocar nada
        porSec = data.map( function(d) {return d.secc;});
        porSec = porSec.filter(function(item, index, arr) { //para quitar elementos repetidos
            return arr.indexOf(item) == index;
        });
        porTyp = data.map( function(d) {return d.tipo;});
        porTyp = porTyp.filter(function(item, index, arr) {
            return arr.indexOf(item) == index;
        });
        console.log(porSec);
        console.log(porTyp);
        
        typeaheadFunc(porSec, ".sec");
        typeaheadFunc(porTyp, ".type");
    }
}