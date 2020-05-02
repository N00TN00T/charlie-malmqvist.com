
var segments = window.location.pathname.split('/');
var toDelete = [];
for (var i = 0; i < segments.length; i++) {
    if (segments[i].length < 1) {
        toDelete.push(i);
    }
}
for (var i = 0; i < toDelete.length; i++) {
    segments.splice(i, 1);
}
var filename = segments[segments.length - 1];

var filenameraw = filename.split('.')[0];

function setCurrent()
{
    console.log(filenameraw);
    var e = document.getElementById(filenameraw);

    if (e != null)
    {
        e.classList.add("nav-current")
    }
    else 
    {
        setTimeout(function(){
            setCurrent();
        }, 10);
    }
}

$(function(){ 
    $(".nav_top").load("nav.html"); 

    setCurrent();
});