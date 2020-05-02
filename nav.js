$(function(){ $(".nav_top").load("nav.html"); });

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

$(window).on('load', function()
{
    console.log(filenameraw);
    document.getElementById(filenameraw).classList.add("nav-current");
})