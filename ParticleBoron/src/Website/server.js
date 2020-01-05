const http = require('http');
const express = require('express');
const particle = require('./particle_script');
const MessagingResponse = require('twilio').twiml.MessagingResponse;

const app = express();

app.post('/sms', (req, res) => {
    const twiml = new MessagingResponse();
    
    particle.callAPI();
    twiml.message('The Robots are coming! Head for the hills!');

    res.writeHead(200, {'Content-Type': 'text/xml'});
    res.end(twiml.toString());
});

http.createServer(app).listen(1337, () => {
    console.log('Express server listening on port 1337');
});

//run below while running server.js to send and respond to text
//twilio phone-numbers:update "+18456179168" --sms-url="http://localhost:1337/sms"