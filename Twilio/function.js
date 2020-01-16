require('dotenv').config()

const http = require('http');
const express = require('express');
const MessagingResponse = require('twilio').twiml.MessagingResponse;
const request = require('request')
const qs = require('qs')

const app = express();


app.post('/sms', (req, res) => {
    let outcome = callAPI("1");
    const twiml = new MessagingResponse();
    
    if (outcome == 'invalid') {
        twiml.message("Invalid Request.");
        res.writeHead(200, {'Content-Type': 'text/xml'});
        res.end(twiml.toString());
    }
    else if (outcome == 'success') {
        twiml.message("Input another number when ready.");
        res.writeHead(200, {'Content-Type': 'text/xml'});
        res.end(twiml.toString());
    }
    else {
        twiml.message("Error.");
        res.writeHead(200, {'Content-Type': 'text/xml'});
        res.end(twiml.toString());
    }
});

http.createServer(app).listen(1337, () => {
    console.log('Express server listening on port 1337');
});

function callAPI(info) {
    if (isNaN(info)) {
        return 'invalid';
    }
    
    info = Number(info);
    return callParticle(info);
    
}

function callParticle(info) {

    const uri = `https://api.particle.io/v1/devices/${process.env.PARTICLE_ID}/incomingSMS?access_token=${process.env.PARTICLE_AUTH}`;
    request.post(uri, {
        body: qs.stringify({
            args: info
        })
    }, (error, res, body) => {
        if (error) {
          console.log(error);
          return 'error';
        }
        console.log(`statusCode: ${res.statusCode}`);
        console.log(body.return_value);
        return 'success';
    })


}
// **code above is for easier testing instead of using twilio functions


// **put the code below in twilio function for recieving a message**

// const qs = require('qs')
// const request = require('request')

// exports.handler = function(context, event, callback) {
//     let twiml = new Twilio.twiml.MessagingResponse();
//     let info = event.Body;
    
//     if (isNaN(info)) {
//         twiml.message("Invalid Request.");
//         callback(null, twiml);
//     }
//     const uri = `https://api.particle.io/v1/devices/${context.PARTICLE_ID}/incomingSMS?access_token=${context.PARTICLE_AUTH}`;
//     console.log(info);
//     request.post(uri, {
//         body: qs.stringify({
//             args: info
//         })
//     }, (error, res, body) => {
//         if (error) {
//             console.error(error);
//             twiml.message("Error. Try again");
//             callback(null, twiml);
//         }
//         console.log(`statusCode: ${res.statusCode} ${body}`);
//         if (res.statusCode == 400) {
//             twiml.message(`Error: ${body.error}. Try again`);
//             callback(null, twiml);
//         }
//         callback(null);
//     })
// };
























//Expose a function through the Cloud so that it can be called with POST /v1/devices/{DEVICE_ID}/{FUNCTION}

//run below while running 'node server.js' to send and respond to text
//twilio phone-numbers:update "+18456179168" --sms-url="http://localhost:1337/sms"