/**
 * charts.js
 *
 * Computer Science 50
 * Final Project
 *
 * Global JavaScript, if any.
 */

/**
 * Nothing.. for tests
 */
$(document).ready(function() {
     //generaGraph(data);
});

/**
 * Function which is meant to be for creating graphs
 */
 //http://alignedleft.com/tutorials/d3/
function generaGraph(data) {
    //console.log("hay " + data.length + "datos recogidos de la base de datos: ");
    //console.log(data);
    //modifying data for bar chart
    var dataByPlatillo = d3.nest()
        .key(function(d) { return d.platillo; })
        .entries(data);
    //console.log(dataByPlatillo);
    var platillosCount = d3.nest()
        .key(function(d) { return d.platillo; })
        .rollup(function(v) { return v.length; })
        .entries(data);
    //console.log(platillosCount);
    
    var maxValue = d3.max(platillosCount, function(d) { return d.value; });
    //console.log(maxValue);
     
    // --> http://alignedleft.com/tutorials/d3/making-a-bar-chart
    //decide size of the new SVG
    //Width and height
    var w = 600;
    var h = 200;
    //set the bar widths to be proportional
    var barPadding = 4;  // <-- New!
    //Para el tamaño de las barras, (lo largo)
    //var barMultHeight = 10;
    //Para evitar que algunso elementos se salgan del espacio
    var paddingSup = 23;
    var paddingInf = 23;
    var paddingDer = 23;
    var paddingIzq = 23; //No pUedo aun controlar por separado los padding, se desconfigura
    
    //console.log(platillosCount.map(function(d) { return d.key; }));
    //SCALES (no se necesitan ahorita pues ya está escalado, puede funcionar en algun otro caso) (no lo he probado si funciona)
    var xScale = d3.scaleOrdinal()
        .domain(platillosCount.map(function(d) { return d.key; }))
        .range([paddingIzq, w - paddingDer]);
    //console.log(xScale);
    var yScale = d3.scaleLinear()
        .domain([0, maxValue])
        //.range([paddingInf, h - paddingSup]); //el - 15 es para que quepan las letras
        .range([h - paddingInf, paddingSup]); 
        
    //Create an empty SVG element and add it to the DOM
    var svg = d3.select("#barChart")
        .append("svg")
        .attr("width", w) 
        .attr("height", h)
        //.attr("align", "center"); //No noté diferencia
        .attr("id", "barChartSVG");
        //This inserts a new <svg> element just before the closing </body> tag
        //console.log(xScale.domain());
        //console.log(xScale.range());
    //Next, instead of creating divs, we generate rects and add them to svg.
    svg.selectAll("rect") //Even if they don't exist previously, we create them this way : "select empty elements":
    //they're just placeholders at that point
        .data(platillosCount)
        .enter()
        .append("rect")
        //.attr("x", 0)
        //.attr("y", 0)
        //.attr("width", 20)
        //.attr("width", (w / platillosCount.length) - barPadding) //Set the bar widths to be proportional
        .attr("width", ((xScale.range()[1] - xScale.range()[0]) / xScale.domain().length) - barPadding)
        //.attr("height", 100)
        .attr("height", function(d) {
            //return d.value * barMultHeight;
            //console.log("valor " + d.value);
            //console.log("height " + yScale(d.value));
            //console.log("la nueva " + (h - yScale(d.value)));
            //console.log("--");
            //return yScale(d.value) - yScale.range()[0]; //" - yScale.range()[0]" es para quitarle el padding de abajo
            return h - yScale(d.value) - yScale.range()[1];
        })
       //Then, data(dataset) sees that we have 20 values in the data set, so it calls enter() 20 times. 
       //enter(), in turn, returns a placeholder selection for each data point that does not yet have a 
       //corresponding rect — which is to say, all of them.
       //...Let’s fix the overlap
        .attr("x", function(d, i) {
            //return i * (w / platillosCount.length);  //Bar width of 20 plus 1 for padding
            //console.log(xScale.domain()[1].length);
            return i * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0];
        })
        //...Let's fix the direction of growth from the bars:
        .attr("y", function(d) {
            //return h - d.value * barMultHeight;  //Height minus data value
            //var doThis = h - yScale(d.value);
            //console.log(yScale(d.value));
            //console.log(doThis);
            return yScale(d.value);
        })
        //Add Color
        .attr("fill", function(d) {

            if (d.value == maxValue) {
                    return "#FF6A5C";
                } else {
                    return "teal";
                }
            });
        //.attr("fill", function(d) {
            //return "rgb(2, 132, " + (d.value * barMultHeight) + ")";
        //})
    
    //Labels
    svg.selectAll("text")
        .data(platillosCount)
        .enter()
        .append("text")
        //add value to each elemtn
        .text(function(d) {
           return d.value; 
        })
        //x and y position of the text
        .attr("x", function(d, i) {
            //return i * (w / platillosCount.length) + (w / (platillosCount.length * 2));
            return (i + 0.5) * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0];
        })
        //anchor to the middle
        .attr("text-anchor", "middle")
        .attr("y", function(d) {
            //return h - (yScale(d.value) + 2); //+2 para que estén un poco más arriba de la linea las letras
            return yScale(d.value) - 2;
        });
        //to add color
        //.attr("fill", "white")
    
    //AXIS
    var yAxis = d3.axisLeft(yScale)
        .ticks(4);
        //.scale(yScale);
    var xAxis = d3.axisBottom(xScale)
        .tickValues(xScale.domain());
        
    svg.append("g")
        .attr("class", "axis")
        .attr("transform", "translate(" + xScale.range()[0] +", 0)") //colocarla dentro del SVG que si no no se ve (sale hasta la orilla, solo se ve una raya)
        //.attr("transform", "rotate(-180)")
        .call(yAxis)
        .style("font-size", "12px");
    
    var parteAbajo = svg.append("g")
        .attr("class", "axis")
        .attr("transform", "translate(0, " + (h - yScale.range()[1]) + ")")
        .call(xAxis)
        .style("font-size", "12px")
        .selectAll("g")
        .attr("transform", function(d, i) {
            return "translate(" + ((i + 0.5) * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0]) + ", 0)";
        });
}

function productsOnTime(data) {
    
    var arr = [];
    arr = manageProductsTime(data);
    //console.log(arr);
    var productTiming = d3.nest()
        .key(function(d) {
            return assignPeriod(d.dateObj.getHours());
            })
        .rollup(function(v) { return v.length; })
        .entries(arr);
        
    console.log(productTiming);
    //CREATE BARChart
    var maxValue = d3.max(productTiming, function(d) { return d.value; });
    
    //agregar DIV donde estará puesto el bar Chart
    $("#chart").append("<br>"
        + "<div class='chartTitle'>Consomation Behavior On Time</div>"
        + "<div id='barChart2'></div>");

    //Width and height
    var w = 600;
    var h = 200;
    //set the bar widths to be proportional
    var barPadding = 4; 

    //Para evitar que algunso elementos se salgan del espacio
    var padding = 23;
    
        //SCALES (no se necesitan ahorita pues ya está escalado, puede funcionar en algun otro caso) (no lo he probado si funciona)
    var xScale = d3.scaleOrdinal()
        .domain(productTiming.map(function(d) { return d.key; }))
        .range([padding, w - padding]);
    //console.log(xScale);
    var yScale = d3.scaleLinear()
        .domain([0, maxValue])
        //.range([paddingInf, h - paddingSup]); //el - 15 es para que quepan las letras
        .range([h - padding, padding]);
        
    //Create an empty SVG element and add it to the DOM
    var svg = d3.select("#barChart2")
        .append("svg")
        .attr("width", w) 
        .attr("height", h)
        .attr("id", "barChart2SVG");
        //This inserts a new <svg> element just before the closing </body> tag

    //Next, instead of creating divs, we generate rects and add them to svg.
    svg.selectAll("rect") 
        .data(productTiming)
        .enter()
        .append("rect")
        .attr("width", ((xScale.range()[1] - xScale.range()[0]) / xScale.domain().length) - barPadding)
        .attr("height", function(d) {
            return h - yScale(d.value) - yScale.range()[1];
        })
        .attr("x", function(d, i) {
            return i * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0];
        })
        .attr("y", function(d) {
            return yScale(d.value);
        })
        .attr("fill", function(d) {

            if (d.value == maxValue) {
                    return "#FF6A5C";
                } else {
                    return "teal";
                }
            });
            
    //Labels
    svg.selectAll("text")
        .data(productTiming)
        .enter()
        .append("text")
        .text(function(d) {
           return d.value; 
        })
        //x and y position of the text
        .attr("x", function(d, i) {
            return (i + 0.5) * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0];
        })
        .attr("text-anchor", "middle")
        .attr("y", function(d) {
            return yScale(d.value) - 2;
        });
    
    //AXIS
    var yAxis = d3.axisLeft(yScale)
        .ticks(4);
    var xAxis = d3.axisBottom(xScale)
        .tickValues(xScale.domain());
        
    svg.append("g")
        .attr("class", "axis")
        .attr("transform", "translate(" + xScale.range()[0] +", 0)") 
        .call(yAxis)
        .style("font-size", "12px");
    
    var parteAbajo = svg.append("g")
        .attr("class", "axis")
        .attr("transform", "translate(0, " + (h - yScale.range()[1]) + ")")
        .call(xAxis)
        .style("font-size", "12px")
        .selectAll("g")
        .attr("transform", function(d, i) {
            return "translate(" + ((i + 0.5) * (xScale.range()[1] - xScale.range()[0])/(xScale.domain().length) + xScale.range()[0]) + ", 0)";
        });
}

