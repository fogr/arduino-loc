<!DOCTYPE html>
<html>
<head>
	<style>
		table {
			border-collapse: collapse;
			width: 100%;
			color: #1f5380;
			font-family: monospace;
			font-size: 20px;
			text-align: left;}

		th {background-color: #1f5380; color: white;}
		tr{background-color: white !important;color: black !important;}
		/* tr:nth-child(even) {background-color: #FDF5E6}
		tr:nth-child(odd) {background:#EEE8AA} */
	</style>
</head>

<?php
$hostname = "localhost";
$username = "root";		
$password = "";
$dbname = "nodemcu_ldr";
$conn = mysqli_connect($hostname, $username, $password, $dbname);
if ($conn->connect_error) {
	die("Database Connection failed: " . $conn->connect_error);
}

date_default_timezone_set('Asia/Ho_Chi_Minh');
$d = date("Y-m-d");
$t = date("H:i:s");

$lastIdQuery = "SELECT LAST_INSERT_ID()";

$id = 0;
if (!empty($_POST['cb1'])) {
	// $ldrvalue = $_POST['cb1'];
	$sql = "INSERT INTO nodemcu_ldr_table (stt, ngay, giovao) VALUES (NULL, '".$d."', '".$t."')";
	if ($conn->query($sql) === TRUE) {
		$id = mysqli_insert_id($conn);
		echo $id;} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;}}

if (!empty($_POST['cb2'])) {
	$sql = "UPDATE nodemcu_ldr_table SET satkhuan = 'ok' WHERE stt = (SELECT MAX(stt) FROM nodemcu_ldr_table)";
	if ($conn->query($sql) === TRUE) {
		echo 'success cb2';} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;	}}

if (!empty($_POST['nhietdo'])) {
	$nhietdo = $_POST['nhietdo'];
	$sql = "UPDATE nodemcu_ldr_table SET nhietdo = $nhietdo WHERE stt = (SELECT MAX(stt) FROM nodemcu_ldr_table)";
	if ($conn->query($sql) === TRUE) {
		echo 'success nhetdo';} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;	}}

if (!empty($_POST['ten'])) {
	$ten = $_POST['ten'];
	$sql = "UPDATE nodemcu_ldr_table SET ten = '$ten' WHERE stt = (SELECT MAX(stt) FROM nodemcu_ldr_table)";
	if ($conn->query($sql) === TRUE) {
		echo 'success ten';} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;	}}

if (!empty($_POST['khautrang'])) {
	$khautrang = $_POST['khautrang'];
	$sql = "UPDATE nodemcu_ldr_table SET khautrang = '$khautrang' WHERE stt = (SELECT MAX(stt) FROM nodemcu_ldr_table)";
	if ($conn->query($sql) === TRUE) {
		echo 'success khautrang';} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;	}}

if (!empty($_POST['giora'])) {
	$cardnumber = $_POST["giora"];
	if($cardnumber == "KH1") {
		$sql = "UPDATE nodemcu_ldr_table SET giora = '$t' WHERE ten ='KHACH HANG 1' and ngay = '$d'";
	}else if($cardnumber =="KH2") { 
		$sql = "UPDATE nodemcu_ldr_table SET giora = '$t' WHERE ten ='KHACH HANG 2' and ngay = '$d'";
	} else if($cardnumber =="KH3") { 
		$sql = "UPDATE nodemcu_ldr_table SET giora = '$t' WHERE ten ='NGUYEN XUAN LOC' and ngay = '$d'";
	}
	if ($conn->query($sql) === TRUE) {
		echo 'success gio ra';} 
	else {
		echo "Error: " . $sql . "<br>" . $conn->error;	}}
?>

<body>
<!-- <form method="post" action="read_db.php" name ="day" id= "day">
			<input type="date" name="day" id="day" alt = "selectDate"  value="<?php echo date("Y-m-d"); ?>" />
			<input type="submit" Value ="Xem"/>
		</form> -->
	<!-- <form action="export_to_excel.php" method="get"> -->


		<div id="tableReport">
			<table border="1" id="header_fixed" style="width:100%"> 
				<tr style="position: sticky;z-index: 50;top:0;">
					<th style="color:#ff0000;font-size:90%;" >STT</th>
					<!-- <h1 style="color:#ff0000;font-size:200%" align="center" >ĐỒ ÁN TỐT NGHIỆP</h1> -->
					<th style="color:#ff0000;font-size:90%" align="center" >SÁT KHUẨN</th>
					<th style="color:#ff0000;font-size:90%;width:80px;" align="center">NHIỆT ĐỘ</th>
					<th style="color:#ff0000;font-size:90%;width:80px;" align="center">TÊN</th>
					<th style="color:#ff0000;font-size:90%" align="center">KHẨU TRANG</th>
					<th style="color:#ff0000;font-size:90%" align="center">NGÀY</th>
					<th style="color:#ff0000;font-size:90%" align="center">GIỜ VÀO</th>
					<th style="color:#ff0000;font-size:90%" align="center">GIỜ RA</th>
				</tr>
				<?php
				session_start();
				$day1 = $_SESSION["day"];
				echo $day1;
				$table = mysqli_query($conn, "SELECT stt, satkhuan, nhietdo, ten, khautrang, ngay, 
		giovao, giora FROM nodemcu_ldr_table  where ngay = '".$day1."' order by stt desc ");
				
				while ($row = mysqli_fetch_array($table)) {
				?>
					<tr>
						<td style="width:100px;"><center><?php echo $row["stt"]; ?></td>
						<td style="width:100px;"><center><?php echo $row["satkhuan"]; ?></td>
						<td style="width:100px;"><center><?php echo $row["nhietdo"]; ?></td>
						<td style="width:150px;"><center><?php echo $row["ten"]; ?></td>
						<td style="width:100px;"><center><?php echo $row["khautrang"]; ?></td>
						<td style="width:150px;" ><center><?php echo $row["ngay"]; ?></td>
						<td style="width:150px;"><center><?php echo $row["giovao"]; ?></td>
						<td style="width:150px;"><center><?php echo $row["giora"]; ?></td>
					</tr>
				<?php
				}
				?>
			</table>
		</div>
	<!-- </form> -->
<!-- <script src="https://code.jquery.com/jquery-3.6.0.min.js" integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
<script>  
$(document).ready(function(){  
		$('#create_excel').click(function(){  
			var excel_data = $('#tableReport').html();  
			$("#tableData").val(excel_data);
			// window.location="export_to_excel.php?data="+$("#tableData").val();   
		});  
});  
</script>  -->
</body>
</html>