let particle = new Particle();
let myId = "e00fce682f9153fb1a6ab1b1";
let accessToken = "390f30e183fb700b60b380048bb4b68c7067bd6d";
let infoList = ["gpsFix","gpsLat","gpsLong","gpsSpeed","gpsSatsVis"];
let latitiude = 43.6532;
let longitude = -79.3832;

function callAPI() {
    for (i = 0; i < infoList.length; i++) {
        let vrPr = particle.getVariable({deviceId: myId, name: infoList[i], auth: accessToken});
        getParticleVar(vrPr,infoList[i]);
    }    
}

function getParticleVar(vrPr, info) {
    let value;
    vrPr.then(function(varData){
        if (info == "gpsLat") {
            document.getElementById("map").src = "https://maps.google.com/maps?q=" + latitiude + "," + longitude + "&hl=en;z=14&amp;output=embed";
            //latitiude = value;
        }
        else if (info == "gpsLong") {
            document.getElementById("map").src = "https://maps.google.com/maps?q=" + latitiude + "," + longitude + "&hl=en;z=14&amp;output=embed";
            //longitude = value;
        }
        value = varData.body.result;
        document.getElementById(info).innerHTML = value;
    }, function(err) {
        document.getElementById(info).innerHTML = "error";
        console.log("Error with getting ", info);
        console.log("An error occurred:", err);
    });
}