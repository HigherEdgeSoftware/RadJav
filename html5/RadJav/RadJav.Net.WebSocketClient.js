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
/// <reference path="RadJav.ts" />
var RadJav;
(function (RadJav) {
    var Net;
    (function (Net) {
        /** @class RadJav.Net.WebSocketClient
         * A web socket.
         * Available on platforms: Windows,Linux,OSX,HTML5
         */
        var WebSocketClient = /** @class */ (function () {
            function WebSocketClient(obj) {
                if (obj == null) {
                    obj = {};
                }
                if (typeof obj == "string") {
                    var tempobj = obj;
                    obj = {};
                    obj.url = tempobj;
                }
                this.url = RadJav.setDefaultValue(obj.url, "");
                this._socket = RadJav.setDefaultValue(obj._socket, null);
                this._events = RadJav.setDefaultValue(obj._events, {});
                if (this._init != null)
                    this._init();
            }
            /** @method connect
             * Connect to the URL.
             * @return {Promise} The promise to execute when the connection has completed.
             */
            WebSocketClient.prototype.connect = function (eventName, func) {
                var promise = new Promise(RadJav.keepContext(function (resolve, reject) {
                    if (WebSocket == null) {
                        reject(RadJav._lang.websocketsNotSupported);
                        return;
                    }
                    this._socket = new WebSocket(this.url, ["xmpp"]);
                    this._socket.onopen = RadJav.keepContext(function () {
                        resolve();
                        if (this._events["onopen"] != null) {
                            this._events["onopen"]();
                        }
                    }, this);
                    this._socket.onerror = RadJav.keepContext(function (error) {
                        reject(error);
                        if (this._events["onerror"] != null) {
                            this._events["onerror"](error);
                        }
                    }, this);
                    this._socket.onmessage = RadJav.keepContext(function (message) {
                        if (this._events["onmessage"] != null) {
                            this._events["onmessage"](message);
                        }
                    }, this);
                    this._socket.onclose = RadJav.keepContext(function (message) {
                        if (this._events["onclose"] != null) {
                            this._events["onclose"]();
                        }
                    }, this);
                }, this));
                return promise;
            };
            /** @method send
             * Send a message to the server.
             * @param {String/Object} message The message to send.
             */
            WebSocketClient.prototype.send = function (message) {
                this._socket.send(message);
            };
            /** @method on
             * Call a function when an event is executed.
             * @param {String} eventName The name of the event.
             * @param {Function} func The function to execute when the event has been executed.
             */
            WebSocketClient.prototype.on = function (eventName, func) {
                this._events[eventName] = func;
            };
            return WebSocketClient;
        }());
        Net.WebSocketClient = WebSocketClient;
    })(Net = RadJav.Net || (RadJav.Net = {}));
})(RadJav || (RadJav = {}));
