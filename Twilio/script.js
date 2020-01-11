var Particle = require('particle-api-js');
var config = require('./config.js');
const client = require('twilio')(config.twilioAccountSid,config.twilioAuthToken);

// client.messages.create({
//     to: '+16478237838',
//     from: '+18456179168',
//     body: 'hello i am potato'
// })
// .then(message => console.log(message.sid));

let particle = new Particle();
let infoList = ["voltage","battery","gpsLat","gpsLong","gpsSatsVis","altitude","roll","pitch","yaw","missionCurrent","airspeed","heading","all"];

exports.callAPI = function(info) {
    if (infoList.indexOf(info) != -1) {
        return callParticleFunc(info);
    }
    return "invalid info wanted";

}

function callParticleFunc(info) {
    var fnPr = particle.callFunction({deviceId: config.particleId, name: 'getMavlink', argument: '1', auth: config.particleAuthToken});

    fnPr.then(
    function() {
        console.log('Function called succesfully');
        let response = "";
        value = "";
        
        if (info == "all") {
            for (i = 0; i < infoList.length; i++) {
                let vrPr = particle.getVariable({deviceId: config.particleId, name: infoList[i], auth: config.particleAuthToken});
                value = getParticleVar(vrPr,infoList[i]);
                response = `${response}${info}: ${value}\n`;
            } 
        }
        else {
            let vrPr = particle.getVariable({deviceId: config.particleId, name: info, auth: config.particleAuthToken});
            value = getParticleVar(vrPr,info);
            response = `${info}: ${value}\n`;
        }
        return response;

    }, function(err) {
        console.log('An error occurred:', err);
        return err;
    });
}

function getParticleVar(info) {
    particle.getVariable({ deviceId: config.particleId, name: info, auth: config.particleAuthToken}).then(function(data) {
        console.log('Device variable retrieved successfully:', data.body.result);
        return data.body.result;
    }, function(err) {
        console.log('An error occurred while getting:', err);
        return err;
    });
}