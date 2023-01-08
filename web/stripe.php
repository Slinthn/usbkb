<?php

$request = isset($_GET["request"]) ? $_GET["request"] : "";
if (preg_match("/[^a-z]/", $request)) {
  echo("Invalid request.");
}

switch ($request) {
case "new": {
  session_start();

  $crl = curl_init("https://api.stripe.com/v1/checkout/sessions");
  $headers = [
    "Authorization: Bearer rk_test_51MLchsAo0d54OTN0OKqNEWBRDRNS0wRZZE1jmOU4iPuQkr0nHJDb9lnptcsTjPTOKgenohWcrl6IIskyBvN3IcGa00kfATmWPO"
  ];
  $fields = [
    "mode" => "payment",
    "success_url" => "http://127.0.0.1/inkoverflow/src/index.php",
    "line_items[0][price]" => "price_1MMKRNAo0d54OTN0FnX4QCjs",
    "line_items[0][quantity]" => "1",
    "customer_creation" => "always",
    "shipping_options[0][shipping_rate]" => "shr_1MMGIyAo0d54OTN0g6r5txzf"
  ];

  curl_setopt($crl, CURLOPT_HEADEROPT, CURLOPT_HTTPHEADER);
  curl_setopt($crl, CURLOPT_HTTPHEADER, $headers);
  curl_setopt($crl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($crl, CURLOPT_RETURNTRANSFER , true);
  curl_setopt($crl, CURLOPT_POSTFIELDS , http_build_query($fields));
  curl_setopt($crl, CURLINFO_HEADER_OUT, true);
  $result = curl_exec($crl);

  if ($result) {
    var_dump($result);
  } else {
    echo(curl_error($crl));
  }

  curl_close($crl);
} break;
}

?>