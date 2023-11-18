var validPageIndex = ["home", "projetos"];
var page = "";

/*              GLOBAL VARIABLES AND FUNCTIONS          */
var CONTENT_FADEOUT_DELAY = 100;
var CONTENT_FADEIN_DELAY  = 500;

var isMobileScale = false;

$(window).resize(function() {
    updateVisual();
});

$(window).load(function() {
    updateAll();
    
    $.ajaxSetup ({
        cache: true
    });
    
    //alert(_GET());
    
    if(_GET() == "")
        _SET("home");
});

window.onhashchange = function(event) {
    updatePageContent();
    hashchange();
    //alert(location.hash);
};

var topBar = $("#topBar");
var topbarLink = $(".topbarLink");
//var topbarLink = document.getElementsByClassName("topbarLink");

/*                  PAGE FUNCTIONS                      */

function isValidPage(page){
    for(var i = 0; i < validPageIndex.length; i++)
        if(page == validPageIndex[i])
            return true;
    return false;
}

function setPage(page){
    _SET(page);
}

function callError(errorId, element, effect){
    if(element == undefined) element = "#content";
    //alert(element + " # " + $(element).html());
    if(effect == true)
        loadContent(element, "/error/" + errorId + ".html", false);
    else $(element).load("/error/" + errorId + ".html");
    //alert(local);
}

function getError(errorId){
    //return $load("/error/" + errorId + ".html");
}

function updateAll(){
    updateVisual();
    updatePageContent();
}

function updateVisual(){
    updateScale();
    updateTopbar();
    var headerHeight = document.getElementById("header").offsetHeight;
    $("#wrap").css("padding-top", headerHeight);
}

/*              PAGE VISUAL FUNCTIONS                   */


function updateScale(){
    isMobileScale = window.innerWidth < 767;
}

function showTopBar(){
    $("#topBar").fadeIn();
    $(".anti-topBar").hide();
}

function hideTopbar(){
    if(isMobileScale)
        topBar.fadeOut();
    
    setTimeout(function(){
        $(".anti-topBar").show();
    }, 400);
}

topbarLink.click(hideTopbar);

$("header").mouseleave(hideTopbar);

//$("#topBarPush").mouseenter(function(){ $("#topBar").fadeIn(); });
$("#topBarPush").click(function(){
    if($("#topBar").css("display") == "none") showTopBar();
    else hideTopbar();
});

function updateTopbar(){
    /*function setTopBarLinkOnClick(i){
        topbarLink[i].onclick = function(){ setPage(topbarLink[i].innerHTML.toLowerCase()); }
    }
    
    for(var i = 0; i < topbarLink.length; i++)
        setTopBarLinkOnClick(i);*/
    
    for(var i = 0; i < topbarLink.length; i++)
        topbarLink[i].href = "#" + topbarLink[i].innerHTML.toLowerCase() + '/';
    
    if(isMobileScale) topBar.hide();
    else              topBar.show();
}

/*                    PAGE CONTENT                      */

function updatePageContent(){
    if(_GET() == "" || _GET() == "/") {
        _SET("home/"); return;
    }
    
    if(page != _GET()){
        _CHANGE_HASH(function(){}); // reset onHashChange
        
        loadContent("#content", _GET());
        
    }
    page = _GET();
    
    updateTopbar();
}

function loadContent(element, url, loading){
    $(element).fadeOut(CONTENT_FADEOUT_DELAY);
    $("footer").fadeOut(CONTENT_FADEOUT_DELAY);
    if(loading)
        $(".ajax_loading").show();
    setTimeout(function(){
        $(element).load(url, function(text, feed){
            console.info(" Load " + feed + ": " + url);
            if(feed == "success"){
                //alert(text);
            } else
            if(feed == "error")
                callError(404);

            if(loading)
                $(".ajax_loading").fadeOut(CONTENT_FADEOUT_DELAY);
            $(element).fadeIn(CONTENT_FADEIN_DELAY);
            $("footer").fadeIn(CONTENT_FADEIN_DELAY);
            //alert(element + " @ " + $(element).html());
        });

    }, $(element).html() == "" ? 0 : CONTENT_FADEOUT_DELAY);
}

/*                       OTHERS                         */


//function createPost(title, subTitle, link){
//    var post = {
//        create(title, subTitle, link){
//            this.title = title;
//            this.subTitle = subTitle;
//            this.link = link;
//        }
//    }
//    
//    post.create(title, subTitle, link);
//    
//    return post;
//}
//
//function printPost(post){
//    
//}