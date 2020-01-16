//put into twilio function
const Particle = require('particle-api-js')

exports.handler = function(context, event, callback) {
    let particle = new Particle();
    let twiml = new Twilio.twiml.MessagingResponse();
    let info = event.Body;
    
    console.log(info);
    var fnPr = particle.callFunction({deviceId: context.PARTICLE_ID, name: 'incomingSMS', argument: info, auth: context.PARTICLE_AUTH});

    fnPr.then(
    function() {
        console.log('Function called succesfully');
        callback(null);
    }, function(err) {
        console.log("Error with calling the function");
        callback(err,null);
    });
};