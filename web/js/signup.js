async function signup_check_email()
{
  var email = document.querySelector("#form-signup-email").value;
  var data = await (await fetch(
    `service/account/email-checker.php?email=${email}`)).json();
  document.querySelector("#form-signup-email-message").innerHTML =
    data["used"] ? "Email in use." : "";
}

function signup_check_password()
{
  var matches = document.querySelector("#form-signup-password").value !=
    document.querySelector("#form-signup-confirm-password").value;

  document.querySelector("#form-signup-confirm-password-message").innerHTML =
    matches ? "Passwords do not match." : "";
  return !matches;
}

async function signup_complete()
{
  var data = new FormData(document.querySelector("#signup-form"));

  var params =
  {
    method: "POST",
    body: data
  };

  await (await fetch("service/account/signup.php", params)).json();
}

function signup_init() {
  document.querySelector("#signup-form")
    .addEventListener("submit", function(event)
  {
    event.preventDefault();
    if (!signup_check_password()) {
      return;
    }

    signup_complete();
  });

  document.querySelector("#signup-form")
    .addEventListener("submit", signup_check_password);

  document.querySelector("#form-signup-email").addEventListener("blur", function()
  {
    signup_check_email();
  });
}

document.addEventListener("DOMContentLoaded", signup_init);