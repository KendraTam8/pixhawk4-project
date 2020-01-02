var particle = new Particle();
var myId = "e00fce682f9153fb1a6ab1b1";
var accessToken = "390f30e183fb700b60b380048bb4b68c7067bd6d";

function callAPI() {
    var value;

    var vrPr = particle.getVariable({deviceId: myId, name: "returnValue", auth: accessToken});
    vrPr.then(function(varData){
        value = "Acquired Value: " + varData.body.result;
        document.getElementById("returnLabel").innerHTML = value;
        console.log(value);
    }, function(err) {
            console.log("An error occurred:", err);
        });
    

}