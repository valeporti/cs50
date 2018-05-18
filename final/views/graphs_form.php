
            
<div id="middle">
    <div id="chart">
        <?php
        if ($found == false) {
            print("<h2>Sorry, no data to show yet.. Start Selling! :)</h2>");
        }
        else { ?>
            <div class="chartTitle">Consomation Behavior On Quantities</div>
            <!-- http://stackoverflow.com/questions/13731800/send-php-variable-to-javascript-function -->
            <div id="barChart"></div> <!-- Se coloca aquí para que cuando se corra "generaGraph(data);"
            ya esté este elemento en el DOM -->
            
            <script>
                var data = <?php echo($data); ?>;
                generaGraph(data);
                productsOnTime(data);
            </script>
        <?php } ?>
        <!-- decide the size of the SVG -->
        <!-- <svg width="315" height="245"></svg> // voy a hacerlo directamente agregandolo en el DOM con .js-->
        <!-- http://stackoverflow.com/questions/13731800/send-php-variable-to-javascript-function -->

        <?php
        if ($found == false) {
        }
        else {
            ?>
            <script>
                var data = <?php echo($data); ?>;
                manageProductsTime(data);
            </script>
        <?php } ?>
    </div>
</div>
