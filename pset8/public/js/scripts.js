/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        },
        
        //dar color tipo "vintage" al mapa
        {
            elementType: "geometry",
            stylers: [
              {
                color: "#ebe3cd"
              }
            ]
          },
          //los de labels no son necesarios pues ya se eliminaron en la parte de arriba
//          {
//            elementType: "labels.text.fill",
  //          stylers: [
    //          {
      //          color: "#523735"
        //      }
          //  ]
  //        },
//          {
    //        elementType: "labels.text.stroke",
      //      stylers: [
        //      {
          //      color: "#f5f1e6"
    //        //  }
      //      ]
//          },
          {
            featureType: "administrative",
            elementType: "geometry.stroke",
            stylers: [
              {
                color: "#c9b2a6"
              }
            ]
          },
          {
            featureType: "administrative.land_parcel",
            elementType: "geometry.stroke",
            stylers: [
              {
                color: "#dcd2be"
              }
            ]
          },
          {
            featureType: "administrative.land_parcel",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#ae9e90"
              }
            ]
          },
          {
            featureType: "landscape.natural",
            elementType: "geometry",
            stylers: [
              {
                color: "#dfd2ae"
              }
            ]
          },
          {
            featureType: "poi",
            elementType: "geometry",
            stylers: [
              {
                color: "#dfd2ae"
              }
            ]
          },
          {
            featureType: "poi",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#93817c"
              }
            ]
          },
          {
            featureType: "poi.park",
            elementType: "geometry.fill",
            stylers: [
              {
                color: "#a5b076"
              }
            ]
          },
          {
            featureType: "poi.park",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#447530"
              }
            ]
          },
          {
            featureType: "road",
            elementType: "geometry",
            stylers: [
              {
                color: "#f5f1e6"
              }
            ]
          },
          {
            featureType: "road.arterial",
            elementType: "geometry",
            stylers: [
              {
                color: "#fdfcf8"
              }
            ]
          },
          {
            featureType: "road.highway",
            elementType: "geometry",
            stylers: [
              {
                color: "#f8c967"
              }
            ]
          },
          {
            featureType: "road.highway",
            elementType: "geometry.stroke",
            stylers: [
              {
                color: "#e9bc62"
              }
            ]
          },
          {
            featureType: "road.highway.controlled_access",
            elementType: "geometry",
            stylers: [
              {
                color: "#e98d58"
              }
            ]
          },
          {
            featureType: "road.highway.controlled_access",
            elementType: "geometry.stroke",
            stylers: [
              {
                color: "#db8555"
              }
            ]
          },
          {
            featureType: "road.local",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#806b63"
              }
            ]
          },
          {
            featureType: "transit.line",
            elementType: "geometry",
            stylers: [
              {
                color: "#dfd2ae"
              }
            ]
          },
          {
            featureType: "transit.line",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#8f7d77"
              }
            ]
          },
          {
            featureType: "transit.line",
            elementType: "labels.text.stroke",
            stylers: [
              {
                color: "#ebe3cd"
              }
            ]
          },
          {
            featureType: "transit.station",
            elementType: "geometry",
            stylers: [
              {
                color: "#dfd2ae"
              }
            ]
          },
          {
            featureType: "water",
            elementType: "geometry.fill",
            stylers: [
              {
                color: "#b9d3c2"
              }
            ]
          },
          {
            featureType: "water",
            elementType: "labels.text.fill",
            stylers: [
              {
                color: "#92998d"
              }
            ]
          }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 37.4236, lng: -122.1619}, // Coordinates of Stanford, California
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // TODO
    var markerLatLong = new google.maps.LatLng(parseFloat(place.latitude), parseFloat(place.longitude));
    //var label = place["place_name"] + ", " + place["admin_name1"];
    var pic = "/img/newsicon.png"; //"http://maps.google.com/mapfiles/kml/pal2/icon31.png";


    // create labeled marker
    var marker = new MarkerWithLabel({
        position: markerLatLong,
        map: map,
        labelContent: place.place_name + ", " + place.admin_code1,
        labelAnchor: new google.maps.Point(0, 0),
        icon: pic
    });
    //push the marker into array
    markers.push(marker);
    
    //$.getJSON("articles.php", "geo=" + place.place_name);

    // load articles in info window upon label click
    // "showInfo" es una función descrta más abajo
    marker.addListener("click", function() { 
        $.getJSON("articles.php", "geo=" + place.place_name)
            .done(function(data, textStatus, jqXHR) {
                // if there are any articles
                // add items in data to list
                // else, set content default message
                var content = data;
                var articles = "<ul>";
                var len = data.length;
                for(var i = 0; i<len;i++)
                {
                   articles += "<li><a href=" + content[i].link + ">" + content[i].title + "</a></li>"
                }  
                articles += "</ul>"
                
                // call typeahead's callback with search results (i.e., places)
                showInfo(marker, articles);
            })
            //.fail(function(jqXHR, textStatus, errorThrown) {
        
                // log error to browser's console
                //console.log(errorThrown.toString());
            //})
            });

    //Op 1    
    // load articles in info window upon label click
    //google.maps.event.addListener(marker, "click", function() { 
        //showInfo(marker, $.getJSON("articles.php", "geo: place.postal_code"))});
        
    //OP2    
    // get places matching query (asynchronously)
    //var parameters = {
        //geo: place.postal_code
    //};
    // load articles in info window upon label click
    //goolge.maps.event.addListener(marker, "click", function() { 
        //showInfo(marker, $.getJSON("articles.php", parameters))});
        
            //.done(function(data, textStatus, jqXHR) {
        
                // call typeahead's callback with search results (i.e., places)
                //cb(data);
            //})
            //.fail(function(jqXHR, textStatus, errorThrown) {
        
                // log error to browser's console
                //console.log(errorThrown.toString());
            //});
    //}
    //La parte de "my touch"
    //var zoom = parseInt(document.getElementById('zoom').value, 10);
    //var size = parseInt(document.getElementById('size').value, 10);
    //var style = parseInt(document.getElementById('style').value, 10);
    //zoom = zoom === -1 ? null : zoom;
    //size = size === -1 ? null : size;
    //style = style === -1 ? null: style;
    
   // var markerClusterer = new MarkerClusterer(map, markers, {
        //maxZoom: zoom,
        //gridSize: size,
        //styles: styles[style]
    //});
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_name1 %>, <%- postal_code %></p>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {
      console.log("typeahead select");
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

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    //TODO
    //esta los borra todos y no permite ver nada de marcadores
    //clearMarkers();
    //markers = [];
    
    //con lo siguiente, cada vez que se usa update vuelve a poner marcadores pero no todos, escoge algunos aleatorios
    // remove marker from markers
    for (var i = 0, n = markers.length; i < n; i++)
    {
	markers[i].setMap(null);
    }

    // reset length to 0
    markers.length = 0;
 
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    console.log(parameters);
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        console.log(data);
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
  console.log("showinfo");
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
  console.log("update")
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}