/*
	DaviApps © copyrigth 2017
	Date: 12/02/2017
	Author: Davi Inácio
	Language: JS
	
	Hash Values
	
	========= IMPORTANTE ===========
	O código esta livre para usar,
	citar e compartilhar desde que
	mantida sua fonte e seu autor.
	Obrigado.
	
	========= IMPORTANT ============
	The code is free to use, to quote,
	and to share, as long as you keep
	its source and its author.
	Thanks.
	
	************ USES ************
	HASH_FORMAT(setter, newer)
		set hash separator format
	HASH_FORMAT(function())
		will be called when the hash was changed
	_ADD(name, value)
		  create new variable if not 
		exists, e set default value.
	_REMOVE(name)
		remove variable if exists
	_SET()
		  set the current hashUrl value
	_SET(name, value)
		  set variable value, and create
		if not exists (to avoid errors)
	_GET()
		  get the current hashUrl
	_GET(name, ifNotFound)
		  get variable value, and return
		'ifNotFound' value ifN...
		
	 **    Other functions    **
	hashchange()
		to be putted on the onHashChanged
	loadHash()
		to load hash informations
	changeHash()
		to change location.hash
	indexOfHash(array, name)
		to get indef of hash var by name
		
*/

var hashes; var hash_url = "";
var setter = '='; var newer = '&'; var initter = "?";
function hashchange(variable){};

function HASH_FORMAT(_setter, _newer, _initter){
    if(_setter == undefined){ // Set default
		setter = ':'; newer = '&';
	} else
	if(_newer == undefined)
		setter = _setter;
    else
    if(_initter == undefined){
        setter = _setter; newer = _newer;
    } else {
		setter = _setter; newer = _newer; initter = _initter;
	}
}

function _GET(name, ifNotFound){
	loadHash();
    if(name == undefined || name == "")
        return hash_url;
    
	var indexOf = indexOfHash(hashes, name);
	if(indexOf != undefined)
		return hashes[indexOf].value;
	else
		return undefined;
}

function _SET(name, value){
	loadHash();
    if(value == undefined){
        hash_url = name;
        _CHANGE_HASH();
        return;
    } else
    if(value == ""){
        _REMOVE(name);
        _CHANGE_HASH();
        return;
    }
    
    //alert(name);
	var indexOf = indexOfHash(hashes,name);
	if(indexOf == undefined)
		_ADD(name, value);
	else
		hashes[indexOf].value = value;
	_CHANGE_HASH();
}

function _ADD(name, value){
	loadHash();
	if(indexOfHash(hashes, name) == undefined)
		hashes[hashes.length] = 
		{ name: name, value: value };
	_CHANGE_HASH();
}

function _REMOVE(name){
	loadHash();
	var indexOf = indexOfHash(hashes, name);
	if(indexOf != undefined){
		var _hashes = hashes; hashes = []; var x = 0;
		for(var i = 0; i < _hashes.length; i++){
			if(i != indexOf){
				hashes[x] = { name: _hashes[i].name, value: _hashes[i].value}; x++;
			}
		}
	}
	_CHANGE_HASH();
}

function indexOfHash(array, name){
	for(var i = 0; i < array.length; i++){
		if(array[i].name == name)
			return i;
	}
	return undefined;
}

function loadHash(){
	hashes = []; var x = 0; var word = ""; var _hashe; var hash = location.hash;
    
    
    var temp = hash.replace('#', '').split(initter);
    
    temp[1] = '#' + (temp[1] == undefined ? "" : temp[1]);
    
    hash_url = temp[0];
    hash = '#' + temp[1];
    
	for(var i = 0; i < hash.length + 1; i++){
		if(hash[i] == '#'){
			_hashe = { name: "", value: "" };
		} else
		if(hash[i] == setter){
			_hashe.name = word;
			word = "";
		} else
		if(hash[i] == newer || (hash[i] == undefined && hash.length > 3)){ // New variable
			_hashe.value = word;
			word = "";
			hashes[x] = _hashe;
			_hashe = { name: "", value: "" };
			x++;
		} else {
			if(hash[i] == undefined) continue;
			word += hash[i];
		}
	}
}

function _CHANGE_HASH(func){
    if(func != undefined){ hashchange = func; return; }
	var hash = "";
	for(var i = 0; i < hashes.length; i++){
		hash += hashes[i].name + setter + hashes[i].value;
		if(hashes[i + 1] != undefined)
			hash += newer;
	}
    
    if(hash_url.lastIndexOf('/') == -1) hash_url += '/';
	location.hash = hash_url + (hash != "" ? '?' : '') + hash;
    //hashchange();
}
