function signupmenu_enable(dropdown, menu0, menu1)
{
  if (dropdown.classList.contains("active") && menu0.classList.contains("active")) {
    dropdown.classList.remove("active");
    menu0.classList.remove("active");
  } else {
    dropdown.classList.add("active");
    menu0.classList.add("active");
    menu1.classList.remove("active");
  }
}

function signupmenu_signup_enable(element, event)
{
  event.preventDefault();

  signupmenu_enable(document.querySelector("#login-signup"),
    document.querySelector("#signup-form"),
    document.querySelector("#login-form"));
}

function signupmenu_login_enable(element, event)
{
  event.preventDefault();

  signupmenu_enable(document.querySelector("#login-signup"),
  document.querySelector("#login-form"),
    document.querySelector("#signup-form"));
}

function signupmenu_init()
{
  document.querySelectorAll(".signup-menu").forEach(e =>
    e.addEventListener("click", signupmenu_signup_enable.bind(null, e)));
  document.querySelectorAll(".login-menu").forEach(e =>
    e.addEventListener("click", signupmenu_login_enable.bind(null, e)));
}

document.addEventListener("DOMContentLoaded", signupmenu_init);