<table id="table_port">
    
    <tr id="elem_table_port">
        <td><b>Symbol</b></td>
        <td><b>Name</b></td>
        <td><b>Shares</b></td>
        <td><b>Price</b></td>
    </tr>
    
    <?php

        foreach ($positions as $position)
        {
            print("<tr id='elem_table_port'>");
            print("<td width=10%>{$position["symbol"]}</td>");
            print("<td>{$position["name"]}</td>");
            print("<td>" . number_format($position["shares"], 2) . "</td>");
            print("<td>" . number_format($position["price"], 2) . "</td>");
            print("</tr>");
        }

    ?>
    
</table>
<br/><br/><p id="curr_cash"><b>
    <?php
        print("Your current cash is: ->" . number_format($cash[0]["cash"], 2));
    ?>
</b></p>