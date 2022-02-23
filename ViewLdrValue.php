<!DOCTYPE html>
<html>
<head>
<style>
body {
    background-color: #7FFFD4;
}
</style>
</head>
<body>
</body>
</html>
<!-- Trắng: #FFFFFF
Hồng nhạt: #FFCCE6
Nâu đỏ nung: #993300
Màu chàm - #4B0082
Tím - #EE82EE -->

<!DOCTYPE html>
<html>
	<head>
		<title>NodeMCU ESP8266 MySQL Database</title>
		<meta charset="utf-8">
		<!-- Script for updating pages without refreshing the page -->
		<script src="jquery.min.js"></script>
		<script>
			$(document).ready(function() {
				setInterval(function(){get_data()},1000);
				function get_data()
				{
					jQuery.ajax({
						type:"GET",
						url: "read_db.php",
						data:"",
						beforeSend: function() {
						},
						complete: function() {
						},
						success:function(data) {
							$("table").html(data);
						}
					});
				}
			});
		</script>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
				color: #1f5380;
				font-family: monospace;
				font-size: 20px;
				text-align: left;
			} 
			th {
				background-color: #1f5380;
				color: white;
			}
			tr:nth-child(even) {background-color: #f2f2f2}
		</style>
	</head>
	<body>
		<h1 style="color:#ff0000;font-size:200%" align="center" >ĐỒ ÁN TỐT NGHIỆP</h1>
		<h1 style="color:#1f5380;font-size:150%" align="center" >Đề Tài: Nghiên cứu, thiết kế và chế tạo máy đo thân nhiệt thông minh kết hợp xử lý ảnh</h1>
		<h2 style="color:#3300FF;font-size:100%" align="center" >Nhóm Sinh Viên Thực Hiện: Nguyễn Xuân Lộc - Hồ Quốc Biên  |  Giảng Viên Hướng Dẫn: TS. Đoàn Thị Hương Giang</h2>
		<!-- <h4 align="center" style="color:#1f5380;">Hệ Thống Điều Khiển Và Giám Sát Web Sever</h4> -->
		<div style="width: 100%;">
			<form method="get" action="ViewLdrValue.php" name ="day" id= "day" style="float: left;width:80%">
				<input type="date" name="day" id="day" alt = "selectDate"  value="<?php $day = $_GET["day"]; echo $day; ?>" />
				<input type="submit" Value ="Xem"/>
				<?php
					session_start();
					$day = $_GET["day"];
					$_SESSION["day"] = $day;
				?>
			</form>

			<form action="export_to_excel.php" method="get" style="float: left;width:20%;text-align: right;">
				<input type="text"  name="data" id="tableData" style="display: none;">
				<button style="color: white; background-color: orangered; padding: 8px; border: none; border-radius: 5px;" id="create_excel">Export To Excel</button>
			</form>
		</div>
		

	<div style="overflow-y: auto; height: 600px; width:100%">
		<table>
			<!-- <tr>
				<th>No</th> 
				<th>LDR Value</th> 
				<th>Date</th>
				<th>Time</th>
				<th>STT</th> 
				<th>SÁT KHUẨN</th> 
				<th>NGÀY</th>
				<th>GIỜ</th>
			</tr> -->
		</table>
	</div>
	<script src="https://code.jquery.com/jquery-3.6.0.min.js" integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
	<script>  
	$(document).ready(function(){  
			$('#create_excel').click(function(){  
				var excel_data = $('#tableReport').html();  
				$("#tableData").val(excel_data);
				window.location="export_to_excel.php?data="+excel_data;   
			});  
	});  
	</script> 
	</body>
</html>