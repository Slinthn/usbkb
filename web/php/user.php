<?php
/*
 * User sessions.
 */


/*
 * Start a user session.
 */
function user_start() {
  session_start();
}

function user_send_code_email() {
  mail($_SESSION["email"], "Account Activation", "Activate your account.");
}

?>