<?php
/*
 * Use POST to signup user to database.
 * 
 * POST["email"] = User email.
 * POST["password"] = User password.
 */

require("../../php/mysql.php");
require("../../php/email.php");
require("../../php/user.php");

$email = $_POST["email"] ?? exit("No email in POST.");

$email = filter_var($email, FILTER_SANITIZE_EMAIL);
if (!($email = email_validate($email)))
  exit("Invalid email.");

$mysql = mysql_init();

if (email_check($mysql, $email))
  exit("Email already in use.");

$password = password_hash($_POST["password"], PASSWORD_DEFAULT);
$code = rand(100000, 999999);


$stmt = $mysql->prepare(
  "INSERT INTO user (email, password, signup_code) VALUES (?, ?, ?)"
);
$stmt->bind_param("ssi", $email, $password, $code);
$stmt->execute();

user_start();

$_SESSION["user_id"] = $mysql->insert_id;
$_SESSION["email"] = $email;

user_send_code_email();

?>