var tips = [
    "Use the arrow keys to walk with your character.",
    "Use spacebar to shoot at your enemies.",
    "Press \"ESC\" to pause the game.",
    "Press \"/\" to see your FPS."
];

var randomNumber = Math.floor((Math.random() * tips.length));
document.getElementsByClassName("tip")[0].innerHTML = tips[randomNumber];

var ads = [
    "ad-1",
    "ad-2",
    "ad-3"
];

var randomNumber = Math.floor((Math.random() * ads.length));
document.getElementsByClassName("ad")[0].src = "../ads/" + ads[randomNumber] + ".jpg";