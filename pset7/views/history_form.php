<table id="table_port">
        <tr id="elem_table_port">
        <td><b>Status</b></td>
        <td><b>DateTime</b></td>
        <td><b>Symbol</b></td>
        <td><b>Shares</b></td>
        <td><b>Price</b></td>
        </tr>
    <?php

        foreach ($transactions as $transaction)
        {
            print("<tr id='elem_table_port'>");
            print("<td width=10%>{$transaction["status"]}</td>");
            print("<td>{$transaction["datime"]}</td>");
            print("<td>{$transaction["symbol"]}</td>");
            print("<td>" . number_format($transaction["shares"], 2) . "</td>");
            print("<td>" . number_format($transaction["price"], 2) . "</td>");
            print("</tr>");
        }

    ?>
</table>
