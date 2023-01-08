<?php
/*
 * Email services, validation, sanitisation.
 */


/*
 * Check the MySQL database for any entries already using
 * the same email as the parameter.
 * 
 * Returns true if the email is in use, or if the email is invalid.
 * Returns false if the email is valid and available to use
 *   (all checks successful).
 */
function email_check($mysql, $email)
{
  if (!($email = email_validate($email)))
    return true;
  
  $stmt = $mysql->prepare("SELECT COUNT(*) FROM user WHERE email=?");
  $stmt->bind_param("s", $email);
  $stmt->bind_result($count);
  $stmt->execute();
  $stmt->fetch();

  return $count > 0;
}

/*
 * Sanitises and validates emails.
 *
 * Returns the email string if succeeded.
 * Returns false if email is invalid.
 */
function email_validate($email)
{
  if (empty($email))
    return false;
  
  $email = filter_var($email, FILTER_SANITIZE_EMAIL);
  if (!filter_var($email, FILTER_VALIDATE_EMAIL))
    return false;

  return $email;
}

?>