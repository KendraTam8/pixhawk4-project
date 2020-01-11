'use strict';
// import script from './script.js';
const e = React.createElement;

class getButton extends React.Component {
    constructor(props) {
        super(props);
        this.state = { 
//             getting: false, 
//             text: "Get data",
//             particle: new Particle(),
// // let myId = keys.particleId;
// // let accessToken = keys.particleAuthToken;
                myId: process.env.REACT_APP_PARTICLE_ID,
                accessToken: process.env.REACT_APP_ACCESS_TOKEN,
//             infoList: ["voltage","battery","gpsLat","gpsLong","gpsSatsVis","altitude","roll","pitch","yaw","missionCurrent","airspeed","heading"],
//             listLen: 12,
//             latitiude: 43.6532,
//             longitude: -79.3832,
//             count: 0,
//             validCoordinates: true
        };

    } 

        
    // callAPI() {
    //     this.setState({ count: 0})
    //     //this.setState({ text: "Getting data..."})
    //     // document.getElementById("get").disabled = true;
    //     console.log("Retrieving data...");
    //     //this.callParticleFunc();

    // }

    // callParticleFunc() {
    //     var fnPr = this.state.particle.callFunction({deviceId: this.state.myId, name: 'getMavlink', argument: '1', auth: this.state.accessToken});

    //     fnPr.then(
    //     function() {
    //         console.log('Function called succesfully');
    //         for (let i = 0; i < this.state.listLen; i++) {
    //             let vrPr = particle.getVariable({deviceId: this.state.myId, name: this.state.infoList[i], auth: this.state.accessToken});
    //             this.getParticleVar(vrPr,this.state.infoList[i]);
    //         }    
    //     }, function(err) {
    //         // document.getElementById("get").disabled = false;
    //         this.setState({ text: "Get data" });
    //         this.setState({ count: 0 });
    //         console.log("Error with calling the function");
    //         console.log('An error occurred:', err);
    //     });
    // }

    // getParticleVar(vrPr, info) {
    //     let value;
    //     vrPr.then(function(varData){
    //         value = varData.body.result;
    //         if (info == "gpsLat") {
    //             value = parseInt(value);
    //             if (Number.isNaN(value)) {
    //                 this.setState({ validCoordinates: false });
    //             }
    //             else {
    //                 this.state.latitiude = value;
    //             }
    //         }
    //         else if (info == "gpsLong") {
    //             value = parseInt(value);
    //             if (Number.isNaN(value)) {
    //                 this.setState({ validCoordinates: false });
    //             }
    //             else {
    //                 this.state.longitude = value;
    //             }
    //         }
    //         document.getElementById(info).innerHTML = value;
    //         this.setState({ count: this.state.count++ });
    //         if (this.state.count >= infoList.length-1) {
    //             document.getElementById("get").disabled = false;
    //             document.getElementById("get").innerHTML = "Get data";
    //             this.setState({ count: 0 });
    //             this.refreshMap();
    //             console.log("Successfully retrieved");
    //         }
    //     }, function(err) {
    //         document.getElementById("get").disabled = false;
    //         document.getElementById("get").innerHTML = "Get data";
    //         this.setState({ count: 0 });
    //         document.getElementById(info).innerHTML = "";
    //         console.log("Error with getting ", info);
    //         console.log("An error occurred:", err);
    //     });
    // }

    // refreshMap() {
    //     console.log(latitiude, longitude);
    //     var map = new google.maps.Map(document.getElementById('map'), {
    //         center: {lat: latitiude, lng: longitude},
    //         zoom: 15
    //     });

    //     if (validCoordinates) {
    //         var marker = new google.maps.Marker({
    //             position: {lat: latitiude, lng: longitude},
    //             map: map,
    //             title: 'Drone Location'
    //         });

    //         marker.setMap(map);
    //     }
    //     this.setState({ validCoordinates: true });
    // }

    render() {
        return e(
            'button',
            { 
                onClick: callAPI(this.state.myId, this.state.accessToken),
                className: "getButton hvr-fade",
                id: "get"
            },
            'Get data'
        );
    }
}

const domContainer = document.querySelector('#container');
ReactDOM.render(e(getButton), domContainer);