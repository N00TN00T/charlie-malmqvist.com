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

$(function(){ $(".nav_top").load("nav.html"); });

console.log(filename)
document.getElementById(filename).classList.add("nav-current");