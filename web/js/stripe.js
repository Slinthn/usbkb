client_key = "rk_test_51MLchsAo0d54OTN0VPtf4Cs0qBUEjcpbDCG0Hk6b3Xb1xl \
  z9L82jLheYYjb4uxdZm517Cxvtzi4NCgXJMxwqatC800FsSu0niK";
url = "https://api.stripe.com/v1/products";

parameters =
{
  "headers":
  {
    "Authorization": `Bearer ${client_key}`
  }
};

async function stripe()
{
  data = await (await fetch(url, parameters)).json();
}

stripe();
