/*
	MIT-LICENSE
	Copyright (c) 2017 Higher Edge Software, LLC

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
	and associated documentation files (the "Software"), to deal in the Software without restriction, 
	including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
	and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or substantial 
	portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
	LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "v8/RadJavV8GUIImage.h"

#include "RadJav.h"

#ifdef USE_V8
#include "v8/RadJavV8JavascriptEngine.h"

namespace RadJAV
{
	namespace GUI
	{
		#ifdef GUI_USE_WXWIDGETS
			ImageFrame::ImageFrame(wxWindow *parent, const wxString &file, wxSize fileSize, const wxPoint &pos, const wxSize &size)
				: wxPanel(parent, wxID_ANY, pos, size)
			{
				loadImage(file, fileSize);
			}

			wxBitmapType ImageFrame::getImageType(wxString file)
			{
				String temp = parsewxString (file);
				String ext = "";
				wxBitmapType type;

				temp = temp.toLowerCase();
				RJUINT posext = temp.rfind(".bmp");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_BMP;

				posext = temp.rfind(".jpg");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_JPEG;

				posext = temp.rfind(".jpeg");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_JPEG;

				posext = temp.rfind(".png");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_PNG;

				posext = temp.rfind(".gif");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_GIF;

				posext = temp.rfind(".tga");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_TGA;

				posext = temp.rfind(".tiff");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_TIFF;

				posext = temp.rfind(".pcx");

				if (posext != String::npos)
					type = wxBitmapType::wxBITMAP_TYPE_PCX;

				return (type);
			}

			void ImageFrame::loadImage(wxString file)
			{
				wxBitmapType type = getImageType(file);
				image.LoadFile(file, type);
			}

			void ImageFrame::loadImage(wxString file, wxSize fileSize)
			{
				wxBitmapType type = getImageType(file);
				image.LoadFile(file, type);
				//image = image.Scale(fileSize.GetWidth(), fileSize.GetHeight());
				image.Rescale(fileSize.GetWidth(), fileSize.GetHeight(), wxImageResizeQuality::wxIMAGE_QUALITY_HIGH);
				imageSize = fileSize;
			}

			void ImageFrame::paintEvent(wxPaintEvent &evt)
			{
				wxPaintDC dc(this);
				render(dc);
			}

			void ImageFrame::render(wxDC &dc)
			{
				image.Rescale(imageSize.GetWidth(), imageSize.GetHeight(), wxImageResizeQuality::wxIMAGE_QUALITY_HIGH);
				dc.DrawBitmap(image, 0, 0);
			}
		#endif

		void Image::createV8Callbacks(v8::Isolate *isolate, v8::Local<v8::Object> object)
		{
			V8_CALLBACK(object, "create", Image::create);
			V8_CALLBACK(object, "setFont", Image::setFont);
			V8_CALLBACK(object, "getFont", Image::getFont);
			V8_CALLBACK(object, "setPosition", Image::setPosition);
			V8_CALLBACK(object, "getPosition", Image::getPosition);
			V8_CALLBACK(object, "getX", Image::getX);
			V8_CALLBACK(object, "getY", Image::getY);
			V8_CALLBACK(object, "setSize", Image::setSize);
			V8_CALLBACK(object, "getSize", Image::getSize);
			V8_CALLBACK(object, "getWidth", Image::getWidth);
			V8_CALLBACK(object, "getHeight", Image::getHeight);
			V8_CALLBACK(object, "setText", Image::setText);
			V8_CALLBACK(object, "getText", Image::getText);
			V8_CALLBACK(object, "getParent", Image::getParent);
			V8_CALLBACK(object, "getAppObj", Image::getAppObj);
			V8_CALLBACK(object, "setVisibility", Image::setVisibility);
			V8_CALLBACK(object, "getVisibility", Image::getVisibility);
			V8_CALLBACK(object, "setEnabled", Image::setEnabled);
			V8_CALLBACK(object, "getEnabled", Image::getEnabled);
			V8_CALLBACK(object, "on", Image::on);

			V8_CALLBACK(object, "setImage", Image::setImage);
		}

		void Image::create(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			String name = V8_JAVASCRIPT_ENGINE->v8GetString(args.This(), "name");
			String image = V8_JAVASCRIPT_ENGINE->v8GetString(args.This(), "_image");
			v8::Handle<v8::Object> parent = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_parent");
			v8::Local<v8::Object> transform = V8_JAVASCRIPT_ENGINE->v8GetObject (args.This(), "_transform");
			RJINT x = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "x");
			RJINT y = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "y");
			RJINT width = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "width");
			RJINT height = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "height");
			RJBOOL visible = V8_JAVASCRIPT_ENGINE->v8GetBool(args.This(), "_visible");

			#ifdef GUI_USE_WXWIDGETS
				wxWindow *parentWin = NULL;

				if (V8_JAVASCRIPT_ENGINE->v8IsNull(parent) == false)
					parentWin = (wxWindow *)V8_JAVASCRIPT_ENGINE->v8GetExternal(parent, "_appObj");

				ImageFrame *object = RJNEW ImageFrame(parentWin, image.towxString (), wxSize (width, height), wxPoint(x, y), wxSize(width, height));
				object->Show(visible);

				V8_JAVASCRIPT_ENGINE->v8SetExternal(args.This(), "_appObj", object);
			#endif

			setupFont(args.This());

			v8::Local<v8::Function> _guiFinishedCreatingGObject = V8_JAVASCRIPT_ENGINE->v8GetFunction(V8_RADJAV, "_guiFinishedCreatingGObject");
			v8::Local<v8::Object> promise = V8_JAVASCRIPT_ENGINE->createPromise(args.This(), _guiFinishedCreatingGObject);

			args.GetReturnValue().Set(promise);
		}

		void Image::setFont(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			V8_JAVASCRIPT_ENGINE->v8SetObject(args.This(), "_font", v8::Local<v8::Object>::Cast (args[0]));

			setupFont(args.This());
		}

		void Image::getFont(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			v8::Local<v8::Object> font = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_font");

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
				wxFont wfont = object->GetFont();

				if (wfont.IsOk() == true)
				{
					String fontFamily = parsewxString(wfont.GetFaceName());
					wxColor color = object->GetForegroundColour();
					RJNUMBER r = color.Red () / 255;
					RJNUMBER g = color.Green() / 255;
					RJNUMBER b = color.Blue() / 255;
					RJNUMBER a = color.Alpha() / 255;
					RJINT size = wfont.GetPixelSize ().x;
					RJBOOL underlined = false;
					RJBOOL bold = false;
					RJBOOL italic = false;

					if (wfont.GetUnderlined() == true)
						underlined = true;

					if (wfont.GetWeight() == wxFontWeight::wxFONTWEIGHT_BOLD)
						bold = true;

					if (wfont.GetStyle () == wxFontStyle::wxFONTSTYLE_ITALIC)
						italic = true;

					V8_JAVASCRIPT_ENGINE->v8SetString(font, "fontFamily", fontFamily);

					v8::Local<v8::Object> ocolor = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "color");
					V8_JAVASCRIPT_ENGINE->v8SetNumber(ocolor, "r", r);
					V8_JAVASCRIPT_ENGINE->v8SetNumber(ocolor, "g", g);
					V8_JAVASCRIPT_ENGINE->v8SetNumber(ocolor, "b", b);
					V8_JAVASCRIPT_ENGINE->v8SetNumber(ocolor, "a", a);

					V8_JAVASCRIPT_ENGINE->v8SetNumber(font, "size", size);
					V8_JAVASCRIPT_ENGINE->v8SetBool(font, "underline", underlined);
					V8_JAVASCRIPT_ENGINE->v8SetBool(font, "bold", bold);
					V8_JAVASCRIPT_ENGINE->v8SetBool(font, "italic", italic);
				}
			#endif

			args.GetReturnValue().Set(font);
		}

		void Image::setPosition(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
			#endif
			RJINT x = 0;
			RJINT y = 0;

			if (args.Length() > 1)
			{
				x = V8_JAVASCRIPT_ENGINE->v8ParseInt (args[0]);
				y = V8_JAVASCRIPT_ENGINE->v8ParseInt (args[1]);
			}
			else
			{
				v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast (args[0]);
				x = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "x");
				y = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "y");
			}

			v8::Handle<v8::Object> transform = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_transform");
			v8::Local<v8::Value> *args2 = RJNEW v8::Local<v8::Value>[2];
			args2[0] = v8::Number::New (args.GetIsolate (), x);
			args2[1] = v8::Number::New(args.GetIsolate (), y);
			V8_JAVASCRIPT_ENGINE->v8CallFunction(transform, "setPosition", 2, args2);

			DELETE_ARRAY(args2);

			#ifdef GUI_USE_WXWIDGETS
				if (object != NULL)
					object->SetPosition(wxPoint(x, y));
			#endif
		}

		void Image::getPosition(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
			#endif
			RJINT x = 0;
			RJINT y = 0;

			v8::Handle<v8::Object> transform = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_transform");
			x = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "x");
			y = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "y");

			#ifdef GUI_USE_WXWIDGETS
				if (object != NULL)
				{
					wxPoint pos = object->GetPosition();
					x = pos.x;
					y = pos.y;
				}
			#endif

			v8::Local<v8::Object> vector2 = V8_JAVASCRIPT_ENGINE->v8GetObject(V8_RADJAV, "Vector2");
			v8::Local<v8::Object> vector2obj = V8_JAVASCRIPT_ENGINE->v8CallAsConstructor(vector2, 0, NULL);
			vector2obj->Set(String ("x").toV8String (args.GetIsolate ()), v8::Number::New (args.GetIsolate (), x));
			vector2obj->Set(String ("y").toV8String (args.GetIsolate ()), v8::Number::New (args.GetIsolate (), y));

			args.GetReturnValue().Set(vector2obj);
		}

		void Image::getX(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			getPosition(args);
			v8::ReturnValue<v8::Value> ret = args.GetReturnValue();
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast (ret.Get());

			args.GetReturnValue().Set (V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "x"));
		}

		void Image::getY(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			getPosition(args);
			v8::ReturnValue<v8::Value> ret = args.GetReturnValue();
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(ret.Get());

			args.GetReturnValue().Set(V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "y"));
		}

		void Image::setSize(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
			#endif
			RJINT x = 0;
			RJINT y = 0;

			if (args.Length() > 1)
			{
				x = V8_JAVASCRIPT_ENGINE->v8ParseInt(args[0]);
				y = V8_JAVASCRIPT_ENGINE->v8ParseInt(args[1]);
			}
			else
			{
				v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(args[0]);
				x = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "x");
				y = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "y");
			}

			v8::Handle<v8::Object> transform = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_transform");
			v8::Local<v8::Value> *args2 = RJNEW v8::Local<v8::Value>[2];
			args2[0] = v8::Number::New(args.GetIsolate (), x);
			args2[1] = v8::Number::New(args.GetIsolate (), y);
			V8_JAVASCRIPT_ENGINE->v8CallFunction(transform, "setSize", 2, args2);

			DELETE_ARRAY(args2);

			#ifdef GUI_USE_WXWIDGETS
				if (object != NULL)
					object->SetSize(x, y);
			#endif
		}

		void Image::getSize(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
			#endif
			RJINT x = 0;
			RJINT y = 0;

			v8::Handle<v8::Object> transform = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_transform");
			x = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "width");
			y = V8_JAVASCRIPT_ENGINE->v8GetInt(transform, "height");

			#ifdef GUI_USE_WXWIDGETS
				if (object != NULL)
				{
					wxSize size = object->GetSize ();
					x = size.GetWidth ();
					y = size.GetHeight ();
				}
			#endif

			v8::Local<v8::Object> vector2 = V8_JAVASCRIPT_ENGINE->v8GetObject(V8_RADJAV, "Vector2");
			v8::Local<v8::Object> vector2obj = V8_JAVASCRIPT_ENGINE->v8CallAsConstructor(vector2, 0, NULL);
			vector2obj->Set(String("x").toV8String(args.GetIsolate ()), v8::Number::New(args.GetIsolate (), x));
			vector2obj->Set(String("y").toV8String(args.GetIsolate ()), v8::Number::New(args.GetIsolate (), y));

			args.GetReturnValue().Set(vector2obj);
		}

		void Image::getWidth(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			getSize(args);
			v8::ReturnValue<v8::Value> ret = args.GetReturnValue();
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(ret.Get());

			args.GetReturnValue().Set(V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "x"));
		}

		void Image::getHeight(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			getSize(args);
			v8::ReturnValue<v8::Value> ret = args.GetReturnValue();
			v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(ret.Get());

			args.GetReturnValue().Set(V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "y"));
		}

		void Image::setText(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			v8::Local<v8::String> val = v8::Local<v8::String>::Cast (args[0]);
			String str = parseV8Value(val);
			V8_JAVASCRIPT_ENGINE->v8SetString(args.This(), "_text", str);
		}

		void Image::getText(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			String text = V8_JAVASCRIPT_ENGINE->v8GetString(args.This(), "_text");

			args.GetReturnValue().Set(text.toV8String (args.GetIsolate ()));
		}

		void Image::getParent(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			v8::Handle<v8::Object> obj = V8_JAVASCRIPT_ENGINE->v8GetObject(args.This(), "_parent");
			args.GetReturnValue().Set(obj);
		}

		void Image::getAppObj(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			v8::Handle<v8::External> ext = v8::Handle<v8::External>::Cast(
					args.This()->Get(String ("_appObj").toV8String(args.GetIsolate ())));
			args.GetReturnValue().Set(ext);
		}

		void Image::setVisibility(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			RJBOOL value = V8_JAVASCRIPT_ENGINE->v8ParseBool(args[0]);
			V8_JAVASCRIPT_ENGINE->v8SetBool(args.This(), "_visible", value);

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
				
				if (value == true)
					object->Show();
				else
					object->Hide();
			#endif
		}

		void Image::getVisibility(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			RJBOOL value = V8_JAVASCRIPT_ENGINE->v8GetBool(args.This(), "_visible");

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
				value = object->IsShown();
			#endif

			args.GetReturnValue().Set(v8::Boolean::New (args.GetIsolate (), value));
		}

		void Image::setEnabled(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			RJBOOL value = V8_JAVASCRIPT_ENGINE->v8ParseBool(args[0]);

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");

				if (value == true)
					object->Enable();
				else
					object->Disable ();
			#endif
		}

		void Image::getEnabled(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			RJBOOL value = false;

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");
				value = object->IsEnabled();
			#endif

			args.GetReturnValue().Set(v8::Boolean::New(args.GetIsolate (), value));
		}

		void Image::on(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			String event = parseV8Value (args[0]);
			v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast (args[1]);

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");

				object->addNewEvent(event, object, func);
			#endif
		}

		void Image::setImage(const v8::FunctionCallbackInfo<v8::Value> &args)
		{
			v8::Local<v8::Value> value = v8::Local<v8::Value>::Cast(V8_JAVASCRIPT_ENGINE->v8GetArgument(args, 0));
			args.This()->Set(String ("_image").toV8String (args.GetIsolate ()), value);
			String src = "";
			RJINT width = 0;
			RJINT height = 0;

			if (value->IsString() == true)
				src = parseV8Value (value);

			if (value->IsObject() == true)
			{
				v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast (value);
				src = V8_JAVASCRIPT_ENGINE->v8GetString(obj, "src");
				width = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "width");
				height = V8_JAVASCRIPT_ENGINE->v8GetInt(obj, "height");
			}

			#ifdef GUI_USE_WXWIDGETS
				ImageFrame *object = (ImageFrame *)V8_JAVASCRIPT_ENGINE->v8GetExternal(args.This(), "_appObj");

				if (object != NULL)
					object->loadImage(src.towxString());
			#endif
		}
	}
}

	#ifdef GUI_USE_WXWIDGETS
		wxBEGIN_EVENT_TABLE(RadJAV::GUI::ImageFrame, wxPanel)
			EVT_PAINT(RadJAV::GUI::ImageFrame::paintEvent)
		wxEND_EVENT_TABLE()
	#endif
#endif

