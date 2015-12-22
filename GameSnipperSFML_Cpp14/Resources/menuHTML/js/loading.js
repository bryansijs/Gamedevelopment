function loadTip(tip) {
    document.getElementsByClassName("tip")[0].innerHTML = tip;
}

function loadAd(ad)
{
    document.getElementsByClassName("ad")[0].src = "../ads/" + ad;
}