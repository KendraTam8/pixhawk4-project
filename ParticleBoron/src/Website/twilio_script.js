const accountSid = 'AC8eefdb7a72cac677dd22470202bbaf76';
const authToken = 'ca32d3235d429c3f592fe607513f4a2e';

const client = require('twilio')(accountSid,authToken);

client.messages.create({
    to: '+16478237838',
    from: '+18456179168',
    body: 'hello i am potato'
})
.then(message => console.log(message.sid));