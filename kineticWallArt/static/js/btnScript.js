var elements = ["elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9"];
// var clone = $('.modal-body').html();

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
}

for (let x=0; x<elements.length; x++) {

}
function savePattern() {
    //Save values of modal
    var image = {};
    image.listarray = [];

    image.name = "1"; //TODO
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

        var rot =  document.getElementById("rotation"+id).value;
        if(rot == ""){
            rot = "0";
        }

        cross.rotation = rot;

        image.listarray.push(cross);
    }

    console.log(image);

    var xhr = new XMLHttpRequest();
    xhr.open("POST", '/website/savepattern', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(image));
}

//Logic reset pattern button
$( "#resetrotation" ).click(function() {
    $(".rotFix").css({
        "transform": "rotate(0deg)"
    });

    for (let x=0; x<elements.length; x++) {
        var id = elements[x];

        document.getElementById("picker1"+id).value = "#FFFFFF";
        document.getElementById("picker2"+id).value = "#FFFFFF";
        document.getElementById("picker3"+id).value = "#FFFFFF" ;
        document.getElementById("picker4"+id).value = "#FFFFFF";
        document.getElementById("check1"+id).checked = false;
        document.getElementById("check2"+id).checked = false;
        document.getElementById("check3"+id).checked = false;
        document.getElementById("check4"+id).checked = false;
        document.getElementById("lighton"+id).checked = true;
        document.getElementById("lightoff"+id).checked = false;
    }

    location.reload(true);
});
