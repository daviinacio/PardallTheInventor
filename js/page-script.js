var page;
var isOnFrameWork = page != undefined;

if(!isOnFrameWork){
    window.location.href = '/#' + location.pathname.substring(1);
}

function readTextFile(file){
    var rawFile = new XMLHttpRequest();
    var allText;
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function(){
        if(rawFile.readyState === 4){
            if(rawFile.status === 200 || rawFile.status == 0)
                allText = rawFile.responseText;
            else allText = undefined;
        }
    }
    rawFile.send(null);
    return allText;
}
