var elements = ["elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9"];
var xhr = new XMLHttpRequest();
var frameId = 0;
var frame = [];

function getCurrentRotation(el){
    var st = window.getComputedStyle(el, null);
    var tm = st.getPropertyValue("-webkit-transform") ||
        st.getPropertyValue("-moz-transform") ||
        st.getPropertyValue("-ms-transform") ||
        st.getPropertyValue("-o-transform") ||
        st.getPropertyValue("transform") ||
        "none";
    if (tm != "none") {
        var values = tm.split('(')[1].split(')')[0].split(',');
        var angle = Math.round(Math.atan2(values[1],values[0]) * (180/Math.PI));
        return (angle < 0 ? angle + 360 : angle);
    }
    return 0;
}

function openModal(id) {
    var elem = document.getElementById(id);
    var rotation = getCurrentRotation(elem);

    $('#modal'+ id ).modal('toggle');
    //pass rotation value according to caller
    $('#rotation'+id).val(rotation);
}

function saveModal(id) {
    var rotval = $("#rotation"+id).val();

    $("#"+id).css({
        "transform": "rotate("+rotval+"deg)"
    });

    $('#modal'+id).modal('hide');

    //Set selected color
    var colarm1 = $("#picker1"+id).val();
    var colarm2 = $("#picker4"+id).val();
    var colarm3 = $("#picker2"+id).val();
    var colarm4 = $("#picker3"+id).val();
    $("#arm1"+id).css({"background-color": colarm1});
    $("#arm2"+id).css({"background-color": colarm2});
    $("#arm3"+id).css({"background-color": colarm3});
    $("#arm4"+id).css({"background-color": colarm4});
}

function savePattern() {
    //Save values of modal
    var pattern = {};
    pattern.listarray = [];

    pattern.name = document.getElementById("inputPatternName").value;
    pattern.checkDB = document.getElementById("inputPatternID").value;

    for (let x=0; x<elements.length; x++) {
        var id = elements[x];
        var cross = {};
        var radios = document.getElementsByName('lightradio'+id);
        var selected_radio;

        for (var i = 0, length = radios.length; i < length; i++) {
            if (radios[i].checked) {
                selected_radio = radios[i].value;
                break;
            }
        }

        cross.name = id;
        cross.color_cross1 = document.getElementById("picker1"+id).value;
        cross.color_cross2 = document.getElementById("picker2"+id).value;
        cross.color_cross3 = document.getElementById("picker3"+id).value;
        cross.color_cross4 = document.getElementById("picker4"+id).value;
        cross.illumination = selected_radio;
        cross.ill_cross1 = document.getElementById("check1"+id).checked;
        cross.ill_cross2 = document.getElementById("check2"+id).checked;
        cross.ill_cross3 = document.getElementById("check3"+id).checked;
        cross.ill_cross4 = document.getElementById("check4"+id).checked;

        var elem = document.getElementById(id);
        var rotation = getCurrentRotation(elem);

        if(rotation === ""){
            rotation = "0";
        }
        cross.rotation = rotation;

        pattern.listarray.push(cross);
    }

    xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200)
       {
            location.reload(true);
       }
    };
    xhr.open("POST", '/website/savepattern', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(pattern));
}

function setPattern(pk){
    var selected = $("#imageSelect"+pk+" :selected").val();
    var text = '{ "image" : ' + selected + ', "pattern" : ' +pk+ '}';

    xhr.open("POST", '/website/setpattern', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(text));
}

function resetModal(id){
    document.querySelector("#picker1"+id).jscolor.fromString('ffffff');
    document.querySelector("#picker2"+id).jscolor.fromString('ffffff');
    document.querySelector("#picker3"+id).jscolor.fromString('ffffff');
    document.querySelector("#picker4"+id).jscolor.fromString('ffffff');
    document.getElementById("check1"+id).checked = false;
    document.getElementById("check2"+id).checked = false;
    document.getElementById("check3"+id).checked = false;
    document.getElementById("check4"+id).checked = false;
    document.getElementById("lighton"+id).checked = true;
    document.getElementById("lightoff"+id).checked = false;
    document.getElementById("rotation"+id).value = "0";

    $("#"+id).css({
        "transform": "rotate(0deg)"
    });

}

//Logic reset pattern button
$( "#resetrotation" ).click(function() {
    location.reload(true);
});


function saveAnimation() {
    var animation = {};
    animation.name = document.getElementById("inputAnimationName").value;
    animation.checkDB = document.getElementById("inputAnimationID").value;
    animation.frames = frame;

    xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200)
       {
            location.reload(true);
       }
    };
    xhr.open("POST", '/website/saveanimation', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(animation));

}


function setAnimation(pk){
    var selected = $("#imageSelectAnimation"+pk+" :selected").val();
    var text = '{ "image" : ' + selected + ', "pattern" : ' +pk+ '}';

    xhr.open("POST", '/website/setanimation', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(text));
}

function saveFrame() {
    //Save values of modal
    var pattern = {};
    pattern.listarray = [];

    for (let x = 0; x < elements.length; x++) {
        var id = elements[x];
        var cross = {};
        var radios = document.getElementsByName('lightradio' + id);
        var selected_radio;

        for (var i = 0, length = radios.length; i < length; i++) {
            if (radios[i].checked) {
                selected_radio = radios[i].value;
                break;
            }
        }

        cross.name = id;
        cross.color_cross1 = document.getElementById("picker1" + id).value;
        cross.color_cross2 = document.getElementById("picker2" + id).value;
        cross.color_cross3 = document.getElementById("picker3" + id).value;
        cross.color_cross4 = document.getElementById("picker4" + id).value;
        cross.illumination = selected_radio;
        cross.ill_cross1 = document.getElementById("check1" + id).checked;
        cross.ill_cross2 = document.getElementById("check2" + id).checked;
        cross.ill_cross3 = document.getElementById("check3" + id).checked;
        cross.ill_cross4 = document.getElementById("check4" + id).checked;

        var elem = document.getElementById(id);
        var rotation = getCurrentRotation(elem);

        if (rotation === "") {
            rotation = "0";
        }
        cross.rotation = rotation;

        pattern.listarray.push(cross);
    }

    frame.push(pattern);
    frameId++;

    document.getElementById("frameCounter").innerHTML= frameId.toString();
}

const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));

const awaitFunction = async (tmp, pk) => {
    for (var l = 0; l < tmp.length; l++) {
        $("#"+tmp[l].name+"preview"+pk).css({"transform": "rotate("+tmp[l].rotation+"deg)"});
        $("#arm1"+tmp[l].name+"preview"+pk).css({"background-color": ""+tmp[l].color_cross1+""});
        $("#arm2"+tmp[l].name+"preview"+pk).css({"background-color": ""+tmp[l].color_cross4+""});
        $("#arm3"+tmp[l].name+"preview"+pk).css({"background-color": ""+tmp[l].color_cross2+""});
        $("#arm4"+tmp[l].name+"preview"+pk).css({"background-color": ""+tmp[l].color_cross3+""});
        console.log(tmp.length);
    }
    await sleep(1000);
};

async function previewAnimation(pk) {
    var results = [];
    var patterns = [];

    for (var j = 0; j < animations.length; j++){
        results = animations.filter(x => x.animation === pk);
    }

    for (var i = 0; i < results.length; i++){
        var test = results[i];
        if(patterns.indexOf(test.pattern) === -1) {
            patterns.push(test.pattern);
        }
    }

    for (var k = 0; k < patterns.length; k++){
        var tmp = results.filter(x => x.pattern === patterns[k]);
        console.log(tmp);
        await awaitFunction(tmp, pk);
    }
}
