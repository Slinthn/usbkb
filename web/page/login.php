<!DOCTYPE html>
<html lang="en-IE">
  <head>
    <title>Slin</title>
    <?php
    require("../component/head.php");
    ?>
    <script src="js/signup.js"></script>
  </head>
  <body>
    <header>
      <?php
      require("../component/header.php");
      ?>
    </header>
    <main>
    <div id="login-signup">
        <!-- Sign Up form -->
        <form id="signup-form" method="POST">
          <fieldset>
            <legend>Sign Up</legend>
            <!-- Email -->
            <label for="form-signup-email">E-mail:</label>
            <input id="form-signup-email" name="email" type="email"
              placeholder="Username" maxlength="256" required>
            <p id="form-signup-email-message" class="form-error"></p>
            <!-- Password -->
            <label for="form-signup-password">Password:</label>
            <input id="form-signup-password" name="password" type="password"
              placeholder="Password" minlength="5" maxlength="488" required>
            <p id="form-signup-password-message" class="form-error"></p>
            <!-- Password Confirm -->
            <label for="form-signup-confirm-password">Confirm password:</label>
            <input id="form-signup-confirm-password" type="password"
              placeholder="Confirm password" minlength="5" maxlength="488" required>
            <p id="form-signup-confirm-password-message" class="form-error"></p>
            <!-- Submit -->
            <input type="submit" value="Sign Up">
          </fieldset>
        </form>
        <!-- Login form -->
        <form id="login-form" method="POST">
          <fieldset>
            <legend>Login</legend>
            <!-- Email -->
            <label for="form-login-email">E-mail:</label>
            <input id="form-login-email" name="email" type="email"
              placeholder="Username" maxlength="256" required>
            <p id="form-login-email-message" class="form-error"></p>
            <!-- Password -->
            <label for="form-login-password">Password:</label>
            <input id="form-login-password" name="password" type="password"
              placeholder="Password" minlength="5" maxlength="488" required>
            <p id="form-login-password-message" class="form-error"></p>
            <!-- Submit -->
            <input type="submit" value="Log in">
          </fieldset>
        </form>
      </div>
    </main>
    <footer>
      <div class="left">
        <a href="home">Slin</a>
      </div>
      <div class="right">
        <div class="column">
          <a href="keyboards">Keyboards</a>
          <a href="home">Arduinos</a>
        </div>
        <div class="column">
          <a href="" class="login-menu">Login</a>
          <a href="" class="signup-menu">Signup</a>
        </div>
      </div>
    </footer>
  </body>
</html>