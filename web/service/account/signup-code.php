<?php
/*
 * Use POST to validate code sent by email.
 * 
 * POST["code"] = Code to validate.
 */

require("../../php/mysql.php");
require("../../php/user.php");

session_start();

$mysql = mysql_init();

$code = preg_match("/0-9+/", $_POST["code"] ?? "");

$stmt = $mysql->prepare("UPDATE user SET signup_code=0 WHERE user_id=? AND signup_code=?");
$stmt->bind_param("ii", $_SESSION["user_id"], $code);
$stmt->execute();

$result = [];
if ($mysql->affected_rows > 0) {
  $result = ["success" => "Success."];
} else {
  $result = ["error" => "Invalid code."];
}

header("Content-Type: application/json; charset=utf-8");
echo(json_encode($result));

?>