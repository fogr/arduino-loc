
<?php
header('Content-Type: application/force-download');
header('Content-disposition: attachment; filename=export.xls');

// Fix for crappy IE bug in download.
header("Pragma: ");
header("Cache-Control: ");
echo "<br>";
echo "<h2 style='color:blue;text-align:center;'>BẢNG CHẤM CÔNG</h2>";
echo $_REQUEST['data'];
?>
