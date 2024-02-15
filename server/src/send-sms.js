const twilio = require('twilio');

const accountSid = 'AC595211c5deab5bd9d19e0c1764cb4c7b';
const authToken = '94ca666b8ba495e952965fbe7fff4cee';

const client = new twilio(accountSid, authToken);

client.messages.create({
    body: 'Hello from Pond Turtle Monitoring System!',
    to: '', // example +1234567890
    from: '+18449845241'
})
    .then((message) => console.log(message.sid));
