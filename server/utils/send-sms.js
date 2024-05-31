const twilio = require("twilio");

const accountSid = "  ";
const authToken = "  ";

const client = new twilio(accountSid, authToken);

let number = [];

number.forEach(function (number) {
  client.messages
    .create({
      body: "Hello from Pond Turtle Monitoring System!",
      to: number, // example +1234567890
      from: "+18449845241",
    })
    .then((message) => console.log(message.sid));
});
