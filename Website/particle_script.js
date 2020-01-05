let particle = new Particle();
let myId = "e00fce682f9153fb1a6ab1b1";
let accessToken = "390f30e183fb700b60b380048bb4b68c7067bd6d";
let infoList = ["voltage","battery","gpsLat","gpsLong","gpsSatsVis","altitude","roll","pitch","yaw","missionCurrent","airspeed","heading"];
let latitiude = 43.6532;
let longitude = -79.3832;
let count = 0;
let invalidCoordinates = false;

function callAPI() {
    count = 0;
    document.getElementById("get").innerHTML = "Getting data...";
    document.getElementById("get").disabled = true;
    console.log("Retrieving data...");
    callParticleFunc();

}

function callParticleFunc() {
    var fnPr = particle.callFunction({deviceId: myId, name: 'getMavlink', argument: '1', auth: accessToken});

    fnPr.then(
    function(data) {
        console.log('Function called succesfully');
        for (i = 0; i < infoList.length; i++) {
            let vrPr = particle.getVariable({deviceId: myId, name: infoList[i], auth: accessToken});
            getParticleVar(vrPr,infoList[i]);
        }    
    }, function(err) {
        document.getElementById("get").disabled = false;
        document.getElementById("get").innerHTML = "Get data";
        count = 0;
        document.getElementById(info).innerHTML = "";
        console.log("Error with calling the function");
        console.log('An error occurred:', err);
    });
}

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

function refreshMap() {
    var map = new google.maps.Map(document.getElementById('map'), {
        center: {lat: latitiude, lng: longitude},
        zoom: 15
    });

    if (!invalidCoordinates) {
        var marker = new google.maps.Marker({
            position: {lat: latitiude, lng: longitude},
            map: map,
            title: 'Drone Location'
        });

        marker.setMap(map);
    }
}

