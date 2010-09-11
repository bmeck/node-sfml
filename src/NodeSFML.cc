#include <v8.h>
using namespace v8;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <node/node_buffer.h>
#include <stdio.h>
//TODO: make this work
/*
#include <node/node.h>
#include <vector>
using namespace std;
const std::Vector<sf::Window*> event_emitters = new std::Vector<sf::Window*>();

int Window_EventLoop(eio_req req) {
	bool valid;
	sf::Event evt;
	sf::Window* window;
	do {
		valid = false;
		for (vector<sf::Window*>::iterator it = event_emitters.begin(); it!=event_emitters.end(); ++it) {
		 	window = *it;
		 	if(window->IsOpened()) {
		 		valid = true;
		 		while(window->GetEvent(&evt)) {
		 			//emit the event
		 		}
		 	}
		}
	} while (valid);
	ev_unref(EV_DEFAULT_UC);
	return 0;
}

void EventLoop_addEventEmitter(sf::Window window) {
	if(event_emitters.empty()) {
		eio_custom(Window_EventLoop, EIO_PRI_DEFAULT, NULL, window);
	    ev_ref(EV_DEFAULT_UC);
    }
}
*/
//ENDTODO

Persistent<FunctionTemplate> NodeSFMLMusicTemplate;
void NodeSFMLMusicDispose(Persistent<Value> object, void* parameter) {
	((sf::Music*)External::Unwrap(object->ToObject()->GetInternalField(0)))->sf::Music::~Music();
}
Handle<Value> NodeSFMLMusic(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::Music* music = new sf::Music(args[0]->IsUndefined() ? 44100 : args[0]->IntegerValue());
		Handle<Object> m = args.This();
		m->SetInternalField(0,External::New(music));
		Persistent<Object>::New(m).MakeWeak(NULL,NodeSFMLMusicDispose);
		return scope.Close(m);
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}

Handle<Value> NodeSFMLMusic_OpenFromFile(const Arguments &args) {
	HandleScope scope;

	Handle<Boolean> success = Boolean::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->OpenFromFile(*String::Utf8Value(args[0])));
	return scope.Close(success);
}

//@Untested
Handle<Value> NodeSFMLMusic_OpenFromMemory(const Arguments &args) {
	HandleScope scope;
	Handle<Boolean> success = False();
	Handle<Value> buffer = args[0];
	if(node::Buffer::HasInstance(buffer)) {
		node::Buffer* node_buffer = node::ObjectWrap::Unwrap<node::Buffer>(buffer->ToObject());
		 success = Boolean::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->OpenFromMemory(
		 	node_buffer->data(), node_buffer->length()
		 ));
	}
	else {
		 success = Boolean::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->OpenFromMemory(
		 	(char*)args[0]->IntegerValue(), args[1]->IntegerValue()
		 ));
	}
	return scope.Close(success);
}

Handle<Value> NodeSFMLMusic_GetStatus(const Arguments &args) {
	HandleScope scope;
	Handle<Number> status = Number::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetStatus());
	return scope.Close(status);
}

Handle<Value> NodeSFMLMusic_GetChannelsCount(const Arguments &args) {
	HandleScope scope;
	Handle<Number> channels = Number::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetChannelsCount());
	return scope.Close(channels);
}

Handle<Value> NodeSFMLMusic_GetSampleRate(const Arguments &args) {
	HandleScope scope;
	Handle<Number> samples_per_second = Number::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetSampleRate());
	return scope.Close(samples_per_second);
}

Handle<Value> NodeSFMLMusic_GetDuration(const Arguments &args) {
	HandleScope scope;
	Handle<Number> duration = Number::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetDuration());
	return scope.Close(duration);
}

Handle<Value> NodeSFMLMusic_GetPlayingOffset(const Arguments &args) {
	HandleScope scope;
	Handle<Number> offset = Number::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetPlayingOffset());
	return scope.Close(offset);
}

Handle<Value> NodeSFMLMusic_Play(const Arguments &args) {
	HandleScope scope;
	((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->Play();
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLMusic_GetLoop(const Arguments &args) {
	HandleScope scope;
	Handle<Boolean> is_looping = Boolean::New(((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->GetLoop());
	return scope.Close(is_looping);
}
Handle<Value> NodeSFMLMusic_SetLoop(const Arguments &args) {
	HandleScope scope;
	((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->SetLoop(args[0]->IsTrue());
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLMusic_Stop(const Arguments &args) {
	HandleScope scope;
	((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->Stop();
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLMusic_Pause(const Arguments &args) {
	HandleScope scope;
	((sf::Music*)External::Unwrap(args.Holder()->GetInternalField(0)))->Pause();
	return scope.Close(Undefined());
}


Persistent<FunctionTemplate> NodeSFMLVideoModeTemplate;
void NodeSFMLVideoModeDispose(Persistent<Value> object, void* parameter) {
	((sf::VideoMode*)External::Unwrap(object->ToObject()->GetInternalField(0)))->sf::VideoMode::~VideoMode();
}

Handle<Value> NodeSFMLVideoMode(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::VideoMode* video_mode;
		Handle<Object> vm = args.This();
		if(args.Length() == 0) {
			video_mode = new sf::VideoMode();
		}
		else {
			int bits_per_pixel = args[2]->IsUndefined() ? 32 : args[2]->IntegerValue();
			video_mode = new sf::VideoMode(args[0]->IntegerValue(),args[1]->IntegerValue(),bits_per_pixel);
		}
		vm->SetInternalField(0,External::New(video_mode));
		Persistent<Object>::New(vm).MakeWeak(NULL,NodeSFMLVideoModeDispose);
		return scope.Close(vm);
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}

Handle<Value> NodeSFMLVideoMode_IsValid(const Arguments &args) {
	HandleScope scope;
	Handle<Boolean> valid = Boolean::New(((sf::VideoMode*)External::Unwrap(args.Holder()->GetInternalField(0)))->IsValid());
	return scope.Close(valid);
}
Handle<Value> NodeSFMLVideoMode_GetDesktopMode(const Arguments &args) {
	HandleScope scope;
	sf::VideoMode* video_mode = new sf::VideoMode(sf::VideoMode::GetDesktopMode());
	Handle<Object> vm = NodeSFMLVideoModeTemplate->InstanceTemplate()->NewInstance();
	vm->SetInternalField(0,External::New(video_mode));
	Persistent<Object>::New(vm).MakeWeak(NULL,NodeSFMLVideoModeDispose);
	return scope.Close(vm);
}
Handle<Value> NodeSFMLVideoMode_GetMode(const Arguments &args) {
	HandleScope scope;
	sf::VideoMode* video_mode = new sf::VideoMode(sf::VideoMode::GetMode(args[0]->IntegerValue()));
	Handle<Object> vm = NodeSFMLVideoModeTemplate->InstanceTemplate()->NewInstance();
	vm->SetInternalField(0,External::New(video_mode));
	Persistent<Object>::New(vm).MakeWeak(NULL,NodeSFMLVideoModeDispose);
	return scope.Close(vm);
}
Handle<Value> NodeSFMLVideoMode_GetModesCount(const Arguments &args) {
	HandleScope scope;
	return scope.Close(Number::New(sf::VideoMode::GetModesCount()));
}

Handle<Value> NodeSFMLVideoMode__Getter_Width(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> width = Number::New(((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->Width);
	return scope.Close(width);
}
void NodeSFMLVideoMode__Setter_Width(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->Width = value->IntegerValue();
	scope.Close(value);
}
Handle<Value> NodeSFMLVideoMode__Getter_Height(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> height = Number::New(((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->Height);
	return scope.Close(height);
}
void NodeSFMLVideoMode__Setter_Height(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->Height = value->IntegerValue();
	scope.Close(value);
}
Handle<Value> NodeSFMLVideoMode__Getter_BitsPerPixel(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> bits_per_pixel = Number::New(((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->BitsPerPixel);
	return scope.Close(bits_per_pixel);
}
void NodeSFMLVideoMode__Setter_BitsPerPixel(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::VideoMode*)External::Unwrap(info.Holder()->GetInternalField(0)))->BitsPerPixel = value->IntegerValue();
	scope.Close(value);
}



void NodeSFMLRenderWindowDispose(Persistent<Value> object, void* parameter) {
	((sf::RenderWindow*)External::Unwrap(object->ToObject()->GetInternalField(0)))->sf::RenderWindow::~RenderWindow();
	object.Dispose();
}

Handle<Value> NodeSFMLRenderWindow(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::VideoMode*  video_mode = static_cast<sf::VideoMode*>(External::Unwrap(args[0]->ToObject()->GetInternalField(0)));
		char* title = args[1]->IsUndefined() ? (char*)"" : *String::Utf8Value(args[1]);
		int style = args[2]->IsUndefined() ? (sf::Style::Resize|sf::Style::Close) : args[2]->IntegerValue();
		sf::RenderWindow* RenderWindow = new sf::RenderWindow(
			*video_mode
			, title
			, style
		);
		args.This()->SetInternalField(0,External::New(RenderWindow));
		Persistent<Object>::New(args.This()).MakeWeak(NULL,NodeSFMLRenderWindowDispose);
	return scope.Close(args.This());
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}

Handle<Value> NodeSFMLRenderWindow_Close(const Arguments &args) {
	HandleScope scope;
	((sf::RenderWindow*)External::Unwrap(args.Holder()->GetInternalField(0)))->Close();
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLRenderWindow_Display(const Arguments &args) {
	HandleScope scope;
	((sf::RenderWindow*)External::Unwrap(args.Holder()->GetInternalField(0)))->Display();
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLRenderWindow_Draw(const Arguments &args) {
	HandleScope scope;
	sf::Sprite sprite = *((sf::Sprite*)args[0]->ToObject()->GetPointerFromInternalField(0));
	const sf::Image* img = sprite.GetImage();
	((sf::RenderWindow*)External::Unwrap(args.Holder()->GetInternalField(0)))->Draw(
		sprite
	);
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLRenderWindow_Clear(const Arguments &args) {
	HandleScope scope;
	((sf::RenderWindow*)External::Unwrap(args.Holder()->GetInternalField(0)))->Clear();
	return scope.Close(Undefined());
}

Handle<Value> NodeSFMLRenderWindow_IsOpened(const Arguments &args) {
	HandleScope scope;
	Handle<Boolean> is_opened = Boolean::New(((sf::RenderWindow*)External::Unwrap(args.Holder()->GetInternalField(0)))->IsOpened());
	return scope.Close(is_opened);
}


void NodeSFMLColorDispose(Persistent<Value> object, void* parameter) {
	((sf::Color*)object->ToObject()->GetPointerFromInternalField(0))->sf::Color::~Color();
}

Persistent<FunctionTemplate> NodeSFMLColorTemplate;
Persistent<ObjectTemplate> NodeSFMLColorTemplateInstanceTemplate;
Handle<Value> NodeSFMLColor(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::Color* color;
		if(args.Length()) {
			color = new sf::Color(args[0]->IntegerValue(),args[1]->IntegerValue(),args[2]->IntegerValue(),args[3]->IntegerValue());
		}
		else {
			color = new sf::Color();
		}
		args.This()->SetPointerInInternalField(0,color);
		//Persistent<Object>::New(args.This()).MakeWeak(NULL,NodeSFMLColorDispose);
		return scope.Close(args.This());
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}
Handle<Value> NodeSFMLColor__Getter_r(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> red = Number::New(((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->r);
	return scope.Close(red);
}
void NodeSFMLColor__Setter_r(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->r = value->IntegerValue();
	scope.Close(value);
}

Handle<Value> NodeSFMLColor__Getter_g(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> green = Number::New(((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->g);
	return scope.Close(green);
}
void NodeSFMLColor__Setter_g(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->g = value->IntegerValue();
	scope.Close(value);
}

Handle<Value> NodeSFMLColor__Getter_b(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> blue = Number::New(((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->b);
	return scope.Close(blue);
}
void NodeSFMLColor__Setter_b(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->b = value->IntegerValue();
	scope.Close(value);
}

Handle<Value> NodeSFMLColor__Getter_a(Local<String> property, const AccessorInfo& info) {
	HandleScope scope;
	Handle<Number> alpha = Number::New(((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->a);
	return scope.Close(alpha);
}
void NodeSFMLColor__Setter_a(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	HandleScope scope;
	((sf::Color*)info.Holder()->GetPointerFromInternalField(0))->a = value->IntegerValue();
	scope.Close(value);
}
//GetPointerFromInternalField

void NodeSFMLImageDispose(Persistent<Value> object, void* parameter) {
	((sf::Image*)object->ToObject()->GetPointerFromInternalField(0))->sf::Image::~Image();
}
Persistent<FunctionTemplate> NodeSFMLImageTemplate;
Handle<Value> NodeSFMLImage(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::Image* image;
		if(args.Length()) {
			if(NodeSFMLImageTemplate->HasInstance(args[0])) {
				image = new sf::Image(*(sf::Image*)args[0]->ToObject()->GetPointerFromInternalField(0));
			}
			else {
				if(node::Buffer::HasInstance(args[2])) {
					image = new sf::Image();
				}
				else {
					Handle<Object> bg = args[2]->ToObject();
					image = new sf::Image(
						args[0]->IntegerValue()
						,args[1]->IntegerValue()
						,NodeSFMLColorTemplate->HasInstance(bg) ? *((sf::Color*)bg->GetPointerFromInternalField(0)) : sf::Color::Black
					);
				}
			}
		}
		else {
			image = new sf::Image();
		}
		args.This()->SetPointerInInternalField(0,image);
		//Persistent<Object>::New(args.This()).MakeWeak(NULL,NodeSFMLImageDispose);
		return scope.Close(args.This());
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}
/*Handle<Value> NodeSFMLImage_GetPixel(const Arguments &args) {
	HandleScope scope;
	sf::Color* c = new sf::Color(((sf::Image*)args.Holder()->GetPointerFromInternalField(0))->GetPixel(
		args[0]->IsUndefined() ? 0 : args[0]->IntegerValue(),
		args[1]->IsUndefined() ? 0 : args[1]->IntegerValue()
	));
	Handle<Object> jsc = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
	jsc->SetPointerInInternalField(0,c);
	return scope.Close(jsc);
}*/
Handle<Value> NodeSFMLImage_GetPixel(const Arguments &args) {
	HandleScope scope;
	sf::Color* c = new sf::Color(((sf::Image*)args.Holder()->GetPointerFromInternalField(0))->GetPixel(
		args[0]->IsUndefined() ? 0 : args[0]->IntegerValue(),
		args[1]->IsUndefined() ? 0 : args[1]->IntegerValue()
	));
	Handle<Object> jsc = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
	jsc->SetPointerInInternalField(0,c);
	return scope.Close(jsc);
}
Handle<Value> NodeSFMLImage_SetPixel(const Arguments &args) {
	HandleScope scope;
	sf::Color c = *(sf::Color*)args[2]->ToObject()->GetPointerFromInternalField(0);
	sf::Image* img = (sf::Image*)args.Holder()->GetPointerFromInternalField(0);
	int x = args[0]->IntegerValue();
	int y = args[1]->IntegerValue();
	img->SetPixel(x,y,c);
	return scope.Close(Undefined());
}
Handle<Value> NodeSFMLImage_LoadFromFile(const Arguments &args) {
	HandleScope scope;
	Handle<Boolean> success = Boolean::New(((sf::Image*)args.Holder()->GetPointerFromInternalField(0))->LoadFromFile(*String::Utf8Value(args[0])));
	return scope.Close(success);
}

void NodeSFMLSpriteDispose(Persistent<Value> object, void* parameter) {
	((sf::Sprite*)object->ToObject()->GetPointerFromInternalField(0))->sf::Sprite::~Sprite();
}
Persistent<FunctionTemplate> NodeSFMLSpriteTemplate;
Handle<Value> NodeSFMLSprite(const Arguments &args) {
	HandleScope scope;
	if(args.IsConstructCall()) {
		sf::Sprite* sprite;
		if(args.Length()) {
			// (const Image &Img, const Vector2f &Position=Vector2f(0, 0), const Vector2f &Scale=Vector2f(1, 1), float Rotation=0.f, const Color &Col=Color(255, 255, 255, 255))
			sf::Image* img = (sf::Image*)args[0]->ToObject()->GetPointerFromInternalField(0);
			float x;
			float y;
			Handle<Value> position = args[1];
			Handle<Object> arr;
			if(position->IsArray()) {
				arr = position->ToObject();
				x = arr->Get(0)->NumberValue();
				y = arr->Get(0)->NumberValue();
			}
			else {
				x = 0.0;
				y = 0.0;
			}
			float sx;
			float sy;
			Handle<Value> scale = args[2];
			if(scale->IsArray()) {
				arr = scale->ToObject();
				sx = arr->Get(0)->NumberValue();
				sy = arr->Get(0)->NumberValue();
			}
			else {
				sx = 1;
				sy = 1;
			}
			float r = args[3]->IsUndefined() ? 0.0 : args[3]->NumberValue();
			sf::Color c = args[4]->IsUndefined() ? sf::Color::White : *(sf::Color*)args[4]->ToObject()->GetPointerFromInternalField(0);
			sprite = new sf::Sprite(*img,sf::Vector2f(x,y),sf::Vector2f(sx,sy), r, c);
		}
		else {
			sprite = new sf::Sprite();
		}
		args.Holder()->SetPointerInInternalField(0,sprite);
		//Persistent<Object>::New(args.This()).MakeWeak(NULL,NodeSFMLSpriteDispose);
		return scope.Close(args.This());
	}
	else {
		return scope.Close(ThrowException(Exception::Error(String::New("Must use new operator"))));
	}
}
Handle<Value> NodeSFMLSprite_GetPixel(const Arguments &args) {
	HandleScope scope;
	sf::Color* c = new sf::Color(((sf::Sprite*)args.Holder()->GetPointerFromInternalField(0))->GetPixel(
		args[0]->IsUndefined() ? 0 : args[0]->IntegerValue(),
		args[1]->IsUndefined() ? 0 : args[1]->IntegerValue()
	));
	Handle<Object> jsc = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
	jsc->SetPointerInInternalField(0,c);
	return scope.Close(jsc);
}


extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;

  Handle<Object> ModeObject = Object::New();
  ModeObject->Set(String::New("Alpha"),Number::New(sf::Blend::Alpha));
  ModeObject->Set(String::New("Add"),Number::New(sf::Blend::Add));
  ModeObject->Set(String::New("Multiply"),Number::New(sf::Blend::Multiply));
  ModeObject->Set(String::New("None"),Number::New(sf::Blend::None));
  target->Set(String::New("Joy"),ModeObject);

  Handle<Object> ButtonsObject = Object::New();
  ButtonsObject->Set(String::New("Left"),Number::New(sf::Mouse::Left));
  ButtonsObject->Set(String::New("Right"),Number::New(sf::Mouse::Right));
  ButtonsObject->Set(String::New("Middle"),Number::New(sf::Mouse::Middle));
  ButtonsObject->Set(String::New("XButton1"),Number::New(sf::Mouse::XButton1));
  ButtonsObject->Set(String::New("XButton2"),Number::New(sf::Mouse::XButton2));
  ButtonsObject->Set(String::New("ButtonCount"),Number::New(sf::Mouse::ButtonCount));
  target->Set(String::New("Mouse"),ButtonsObject);

  NodeSFMLColorTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New(NodeSFMLColor));
  NodeSFMLColorTemplateInstanceTemplate = Persistent<ObjectTemplate>::New(NodeSFMLColorTemplate->InstanceTemplate());
  NodeSFMLColorTemplateInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLColorTemplateInstanceTemplate->SetAccessor(
  	String::New("r")
  	,NodeSFMLColor__Getter_r
  	,NodeSFMLColor__Setter_r
  );
  NodeSFMLColorTemplateInstanceTemplate->SetAccessor(
  	String::New("g")
  	,NodeSFMLColor__Getter_g
  	,NodeSFMLColor__Setter_g
  );
  NodeSFMLColorTemplateInstanceTemplate->SetAccessor(
  	String::New("b")
  	,NodeSFMLColor__Getter_b
  	,NodeSFMLColor__Setter_b
  );
  NodeSFMLColorTemplateInstanceTemplate->SetAccessor(
  	String::New("a")
  	,NodeSFMLColor__Getter_a
  	,NodeSFMLColor__Setter_a
  );
  Handle<Function> color_f = NodeSFMLColorTemplate->GetFunction();
  Handle<Object> color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Black));
  color_f->Set(String::New("Black"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::White));
  color_f->Set(String::New("White"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Red));
  color_f->Set(String::New("Red"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Green));
  color_f->Set(String::New("Green"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Blue));
  color_f->Set(String::New("Blue"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Yellow));
  color_f->Set(String::New("Yellow"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Magenta));
  color_f->Set(String::New("Magenta"),color);

  color = NodeSFMLColorTemplateInstanceTemplate->NewInstance();
  color->SetPointerInInternalField(0,new sf::Color(sf::Color::Cyan));
  color_f->Set(String::New("Cyan"),color);
  target->Set(String::New("Color"), color_f);

  NodeSFMLImageTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New(NodeSFMLImage));
  Handle<ObjectTemplate> NodeSFMLImageTemplateInstanceTemplate = NodeSFMLImageTemplate->InstanceTemplate();
  NodeSFMLImageTemplateInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLImageTemplateInstanceTemplate->Set("SetPixel", FunctionTemplate::New(NodeSFMLImage_SetPixel));
  NodeSFMLImageTemplateInstanceTemplate->Set("GetPixel", FunctionTemplate::New(NodeSFMLImage_GetPixel));
  NodeSFMLImageTemplateInstanceTemplate->Set("LoadFromFile", FunctionTemplate::New(NodeSFMLImage_LoadFromFile));
  target->Set(String::New("Image"), NodeSFMLImageTemplate->GetFunction());


  NodeSFMLSpriteTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New(NodeSFMLSprite));
  Handle<ObjectTemplate> NodeSFMLSpriteTemplateInstanceTemplate = NodeSFMLSpriteTemplate->InstanceTemplate();
  NodeSFMLSpriteTemplateInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLSpriteTemplateInstanceTemplate->Set("GetPixel", FunctionTemplate::New(NodeSFMLSprite_GetPixel));
  target->Set(String::New("Sprite"), NodeSFMLSpriteTemplate->GetFunction());

  Handle<FunctionTemplate> NodeSFMLRenderWindowTemplate = FunctionTemplate::New(NodeSFMLRenderWindow);
  Handle<ObjectTemplate> NodeSFMLRenderWindowTemplateInstanceTemplate = NodeSFMLRenderWindowTemplate->InstanceTemplate();
  NodeSFMLRenderWindowTemplateInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLRenderWindowTemplateInstanceTemplate->Set("Clear", FunctionTemplate::New(NodeSFMLRenderWindow_Clear));
  NodeSFMLRenderWindowTemplateInstanceTemplate->Set("Close", FunctionTemplate::New(NodeSFMLRenderWindow_Close));
  NodeSFMLRenderWindowTemplateInstanceTemplate->Set("Display", FunctionTemplate::New(NodeSFMLRenderWindow_Display));
  NodeSFMLRenderWindowTemplateInstanceTemplate->Set("Draw", FunctionTemplate::New(NodeSFMLRenderWindow_Draw));
  NodeSFMLRenderWindowTemplateInstanceTemplate->Set("IsOpened", FunctionTemplate::New(NodeSFMLRenderWindow_IsOpened));
  target->Set(String::New("RenderWindow"), NodeSFMLRenderWindowTemplate->GetFunction());

  NodeSFMLVideoModeTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New(NodeSFMLVideoMode));
  NodeSFMLVideoModeTemplate->Set("GetModesCount", FunctionTemplate::New(NodeSFMLVideoMode_GetModesCount));
  NodeSFMLVideoModeTemplate->Set("GetMode", FunctionTemplate::New(NodeSFMLVideoMode_GetMode));
  NodeSFMLVideoModeTemplate->Set("GetDesktopMode", FunctionTemplate::New(NodeSFMLVideoMode_GetDesktopMode));
  Handle<ObjectTemplate> NodeSFMLVideoModeTemplateInstanceTemplate = NodeSFMLVideoModeTemplate->InstanceTemplate();
  NodeSFMLVideoModeTemplateInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLVideoModeTemplateInstanceTemplate->SetAccessor(
  	String::New("Width")
  	,NodeSFMLVideoMode__Getter_Width
  	,NodeSFMLVideoMode__Setter_Width
  );
  NodeSFMLVideoModeTemplateInstanceTemplate->SetAccessor(
  	String::New("Height")
  	,NodeSFMLVideoMode__Getter_Height
  	,NodeSFMLVideoMode__Setter_Height
  );
  NodeSFMLVideoModeTemplateInstanceTemplate->SetAccessor(
  	String::New("BitsPerPixel")
  	,NodeSFMLVideoMode__Getter_BitsPerPixel
  	,NodeSFMLVideoMode__Setter_BitsPerPixel
  );
  NodeSFMLVideoModeTemplateInstanceTemplate->Set("IsValid", FunctionTemplate::New(NodeSFMLVideoMode_IsValid));
  target->Set(String::New("VideoMode"), NodeSFMLVideoModeTemplate->GetFunction());

  Handle<Object> NodeSFMLStyle = Object::New();
  NodeSFMLStyle->Set(String::New("None"),Number::New(sf::Style::None));
  NodeSFMLStyle->Set(String::New("Titlebar"),Number::New(sf::Style::Titlebar));
  NodeSFMLStyle->Set(String::New("Resize"),Number::New(sf::Style::Resize));
  NodeSFMLStyle->Set(String::New("Close"),Number::New(sf::Style::Close));
  NodeSFMLStyle->Set(String::New("Fullscreen"),Number::New(sf::Style::Fullscreen));
  target->Set(String::New("Style"), NodeSFMLStyle);

  Handle<FunctionTemplate> NodeSFMLSoundTemplate = FunctionTemplate::New();
  Handle<ObjectTemplate> NodeSFMLSoundTemplateInstanceTemplate = NodeSFMLSoundTemplate->InstanceTemplate();
  Handle<Object> StatusObject = Object::New();
  StatusObject->Set(String::New("Paused"),Number::New(sf::Sound::Paused));
  StatusObject->Set(String::New("Playing"),Number::New(sf::Sound::Playing));
  StatusObject->Set(String::New("Stopped"),Number::New(sf::Sound::Stopped));
  NodeSFMLSoundTemplate->Set(String::New("Status"),StatusObject);
  target->Set(String::New("Sound"), NodeSFMLSoundTemplate->GetFunction());

  NodeSFMLMusicTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New(NodeSFMLMusic));
  Handle<ObjectTemplate> NodeSFMLMusicInstanceTemplate = NodeSFMLMusicTemplate->InstanceTemplate();
  NodeSFMLMusicInstanceTemplate->SetInternalFieldCount(1);
  NodeSFMLMusicInstanceTemplate->Set("GetChannelsCount", FunctionTemplate::New(NodeSFMLMusic_GetChannelsCount));
  NodeSFMLMusicInstanceTemplate->Set("GetDuration", FunctionTemplate::New(NodeSFMLMusic_GetDuration));
  NodeSFMLMusicInstanceTemplate->Set("GetLoop", FunctionTemplate::New(NodeSFMLMusic_GetLoop));
  NodeSFMLMusicInstanceTemplate->Set("GetPlayingOffset", FunctionTemplate::New(NodeSFMLMusic_GetPlayingOffset));
  NodeSFMLMusicInstanceTemplate->Set("GetSampleRate", FunctionTemplate::New(NodeSFMLMusic_GetSampleRate));
  NodeSFMLMusicInstanceTemplate->Set("GetStatus", FunctionTemplate::New(NodeSFMLMusic_GetStatus));
  NodeSFMLMusicInstanceTemplate->Set("OpenFromFile", FunctionTemplate::New(NodeSFMLMusic_OpenFromFile));
  NodeSFMLMusicInstanceTemplate->Set("Pause", FunctionTemplate::New(NodeSFMLMusic_Pause));
  NodeSFMLMusicInstanceTemplate->Set("Play", FunctionTemplate::New(NodeSFMLMusic_Play));
  NodeSFMLMusicInstanceTemplate->Set("SetLoop", FunctionTemplate::New(NodeSFMLMusic_SetLoop));
  NodeSFMLMusicInstanceTemplate->Set("Stop", FunctionTemplate::New(NodeSFMLMusic_Stop));
  target->Set(String::New("Music"), NodeSFMLMusicTemplate->GetFunction());
}
