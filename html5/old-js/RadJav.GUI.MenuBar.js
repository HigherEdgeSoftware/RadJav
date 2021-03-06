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

/** @class RadJav.GUI.MenuBar
* @extends RadJav.GUI.GObject
* A menu Bar.
* Available on platforms: Windows,Linux,OSX,HTML5
*/
RadJav.GUI.MenuBar = (function (_super)
{
	__extends(MenuBar, _super);

	function MenuBar (obj, text, parent)
	{
		if (obj == null)
			obj = {};

		if (typeof (obj) == "string")
		{
			var name = obj;
			obj = { name: name };
		}

		if (obj.size == null)
		{
			obj.size = new RadJav.Vector2 ();
			obj.size.x = 120;
			obj.size.y = 40;
		}

		var _this = _super.call(this, obj, text, parent) || this;

		_this.type = "RadJav.GUI.MenuBar";

		if (obj.htmlElement != null)
			obj._htmlElement = obj.htmlElement;

		/** @property {RadJav.GUI.HTMLElement/String} [_htmlElement=null]
		* @protected
		* If the OS is HTML5, this will be the HTML element that will be attached to.
		* If this property is a string, it will be selected by the HTML DOM's element id 
		* then converted into a RadJav.GUI.HTMLElement.
		*/
		_this._htmlElement = RadJav.setDefaultValue (obj._htmlElement, null);

		if (_this._htmlElement != null)
			_this.setHTMLElement (_this._htmlElement);

		return (_this);
	}

	/** @method setHTMLElement
	* Set the HTML element to use, if the OS being used is HTML5.
	* @param {RadJav.GUI.HTMLElement/String} element The element to be used.
	*/
	MenuBar.prototype.setHTMLElement = function (element)
	{
		var elm = element;

		if (typeof (element) == "string")
			elm = new RadJav.GUI.HTMLElement (this.name);

		this._htmlElement = elm;
	}

	return (MenuBar);
}(RadJav.GUI.GObject));

