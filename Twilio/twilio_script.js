var Particle = require('particle-api-js');
var keys = require('../ParticleBoron/src/Website/config.js');
console.log(keys);
// const client = require('twilio')(keys.twilioAccountSid,keys.twilioAuthToken);

// client.messages.create({
//     to: '+16478237838',
//     from: '+18456179168',
//     body: 'hello i am potato'
// })
// .then(message => console.log(message.sid));

// // var particle = new Particle();
// let myId = keys.particleId;
// let accessToken = keys.particleAuthToken;
// let infoList = ["voltage","battery","gpsLat","gpsLong","gpsSatsVis","altitude","roll","pitch","yaw","missionCurrent","airspeed","heading"];
// let latitiude = 43.6532;
// let longitude = -79.3832;
// let count = 0;
// let invalidCoordinates = false;

// exports.callAPI = function() {
//     console.log('hello');
//     count = 0;
//     return callParticleFunc();

// }

// function callParticleFunc() {
//     var fnPr = particle.callFunction({deviceId: myId, name: 'getMavlink', argument: '1', auth: accessToken});

//     fnPr.then(
//     function() {
//         console.log('Function called succesfully');
//         return getParticleVar();
//     }, function(err) {
//         console.log('An error occurred:', err);
//     });
// }

// function getParticleVar() {
//     particle.getVariable({ deviceId: myId, name: 'gpsLat', auth: accessToken }).then(function(data) {
//         console.log('Device variable retrieved successfully:', data.body.result);
//         return data.body.result;
//       }, function(err) {
//         console.log('An error occurred while getting attrs:', err);
//       });
// }
/*
function getParticleVar(vrPr, info) {
    let value;
    vrPr.then(function(varData){
        value = varData.body.result;
        if (info == "gpsLat") {
            value = parseInt(value);
            invalidCoordinates = Number.isNaN(value);
            if (!invalidCoordinates) {
                latitiude = value;
            }
        }
        else if (info == "gpsLong") {
            value = parseInt(value);
            invalidCoordinates = Number.isNaN(value);
            if (!invalidCoordinates) {
                longitude = value;
            }
        }
        document.getElementById(info).innerHTML = value;
        count++
        if (count >= infoList.length-1) {
            document.getElementById("get").disabled = false;
            document.getElementById("get").innerHTML = "Get data";
            count = 0;
            refreshMap();
            console.log("Successfully retrieved");
        }
    }, function(err) {
        document.getElementById("get").disabled = false;
        document.getElementById("get").innerHTML = "Get data";
        count = 0;
        document.getElementById(info).innerHTML = "";
        console.log("Error with getting ", info);
        console.log("An error occurred:", err);
    });
}

*/