/*
	DaviApps © copyrigth 2017
	Created 12/02/2017
	By Davi Inácio
	
	Hash Values
	
	************ USES ************
	HASH_FORMAT(setter, newer)
		set hash separator format
	_ADD(name, value)
		  create new variable if not 
		exists, e set default value.
	_REMOVE(name)
		remove variable if exists
	_SET(name, value)
		  set variable value, and create
		if not exists (to avoid errors)
	_GET(name, ifNotFound)
		  get variable value, and return
		'ifNotFound' value ifN...
		
	 **    Other functions    **
	loadHash()
		to load hash informations
	changeHash()
		to change location.hash
	indexOfHash(array, name)
		to get indef of hash var by name
		
*/

var hashes; var setter = ':'; var newer = '&';

function HASH_FORMAT(_setter, _newer){
	if(_setter == undefined){ // Set default
		setter = ':'; newer = '&';
	} else
	if(_newer == undefined)
		setter = _setter;
	else {
		setter = _setter; newer = _newer;
	}
}

function _GET(name, ifNotFound){
	loadHash();
	var indexOf = indexOfHash(hashes, name);
	if(indexOf != undefined)
		return hashes[indexOf].value;
	else
		return undefined;
}

function _SET(name, value){
	loadHash();
	var indexOf = indexOfHash(hashes,name);
	if(indexOf == undefined)
		_ADD(name, value);
	else
		hashes[indexOf].value = value;
	changeHash();
}

function _ADD(name, value){
	loadHash();
	if(indexOfHash(hashes, name) == undefined)
		hashes[hashes.length] = 
		{ name: name, value: value };
	changeHash();
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
	changeHash();
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

function changeHash(){
	var hash = "#";
	for(var i = 0; i < hashes.length; i++){
		hash += hashes[i].name + setter + hashes[i].value;
		if(hashes[i + 1] != undefined)
			hash += newer;
	}
	location.hash = hash;
}
