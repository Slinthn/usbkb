<?php
/*
 * Use GET to check if an email is in use.
 * 
 * GET["email"] = Email to check.
 */

require("../../php/mysql.php");
require("../../php/email.php");

$email = $_GET["email"] ?? exit("No email in GET.");

$mysql = mysql_init();

$result = [];
$result["used"] = email_check($mysql, $email);

header("Content-Type: application/json; charset=utf-8");
echo(json_encode($result));

?>