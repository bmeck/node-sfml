var sfml = require("../lib/nodesfml.node")
console.log("starting test")
var img = new sfml.Image(120,60,sfml.Color.Green)
//img.LoadFromFile("logo.jpg")

var vm = sfml.VideoMode.GetDesktopMode()
console.log("video mode ok")
console.log("valid "+vm.IsValid())
console.log("Height "+vm.Height)
console.log("Width "+vm.Width)
console.log("BitsPerPixel "+vm.BitsPerPixel)
var app = new sfml.RenderWindow(vm,"test",sfml.Style.None)
console.log(sfml.Style)
for(var i=0;i<60;i++) {
	for(var j=0;j<60;j++) {
		img.SetPixel(i,j,sfml.Color.Red)
		//console.log(img.GetPixel(i,j))
	}
}
console.log("SAVING IMG : "+img.SaveToFile("out.png"))
var sprite = new sfml.Sprite(img)
console.log("sprite :"+JSON.stringify(sprite.GetPixel(5,5)))


/*
var music = new sfml.Music()
music.OpenFromFile("test.wav")
music.Play()
*/
	app.Clear()
var t;t=setInterval(function(){
	app.Display()
	app.Draw(sprite)
},100)
setTimeout(function(){clearInterval(t);console.log('done')},1000)
