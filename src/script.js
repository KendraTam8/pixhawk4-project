var particle = new Particle();
var myId = "e00fce682f9153fb1a6ab1b1";
var accessToken = "390f30e183fb700b60b380048bb4b68c7067bd6d";

function callAPI() {    
    var fnPr = particle.callFunction({ deviceId: myId, name: "getValue", argument: "go", auth: accessToken });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });

    var vrPr = particle.getVariable({deviceId: myId, name: "returnValue", auth: accessToken});
    vrPr.then(function(data){
        console.log(data);
    }, function(err) {
            console.log("An error occurred:", err);
        });
    
    // var requestURL = "https://api.particle.io/v1/devices/" + myId + "/value/?access_token=" + accessToken;
    // $.getJSON(requestURL, function(data) {
    //     //$("#amount").text(data.result);
    //     console.log(data);
            
    //     });
}