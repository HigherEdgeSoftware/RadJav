/*
    MIT-LICENSE
    Copyright (c) 2017-2018 Higher Edge Software, LLC

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
    /** @class RadJav.Vector3
     * A Vector3 class.
     * Available on platforms: Windows,Linux,OSX,HTML5
     */
    var Vector3 = /** @class */ (function () {
        function Vector3(x, y, z) {
            if (x == null)
                x = 0;
            if (y == null)
                y = 0;
            if (z == null)
                z = 0;
            if (x instanceof RadJav.Vector2) {
                var temp = x;
                x = temp.x;
                y = temp.y;
            }
            if (x instanceof RadJav.Vector3) {
                var temp_1 = x;
                x = temp_1.x;
                y = temp_1.y;
                z = temp_1.z;
            }
            this.x = x;
            this.y = y;
            this.z = z;
        }
        /** @method toString
         * Convert this object to a string.
         * @return {String} The string representing this object.
         */
        Vector3.prototype.toString = function () {
            return this.x + "," + this.y + "," + this.z;
        };
        /** @method add
         * Add x,y,z values to the x,y,z components of this object.
         * @param {Number} x The X component to add.
         * @param {Number} y The Y component to add.
         * @param {Number} z The Z component to add.
         */
        Vector3.prototype.add = function (vector3) {
            var result = new RadJav.Vector3();
            if (vector3 instanceof RadJav.Vector3) {
                result.x = this.x + vector3.x;
                result.y = this.y + vector3.y;
                result.z = this.z + vector3.z;
            }
            else {
                result.x = this.x + vector3;
                result.y = this.y + vector3;
                result.z = this.z + vector3;
            }
            return result;
        };
        /** @method sub
         * Subtract X and Y values from the X and Y components of this object.
         * @param {Number} x The X component to subtract.
         * @param {Number} y The Y component to subtract.
         * @param {Number} z The Z component to subtract.
         */
        Vector3.prototype.subtract = function (vector3) {
            var result = new RadJav.Vector3();
            if (vector3 instanceof RadJav.Vector3) {
                result.x = this.x - vector3.x;
                result.y = this.y - vector3.y;
                result.z = this.z - vector3.z;
            }
            else {
                result.x = this.x - vector3;
                result.y = this.y - vector3;
                result.z = this.z - vector3;
            }
            return result;
        };
        /** @method multiply
         * Multiply x,y,z values to the x,y,z components of this object.
         * @param {Number} x The X component to subtract.
         * @param {Number} y The Y component to subtract.
         * @param {Number} z The Z component to subtract.
         */
        Vector3.prototype.multiply = function (vector3) {
            var result = new RadJav.Vector3();
            if (vector3 instanceof RadJav.Vector3) {
                result.x = this.x * vector3.x;
                result.y = this.y * vector3.y;
                result.z = this.z * vector3.z;
            }
            else {
                result.x = this.x * vector3;
                result.y = this.y * vector3;
                result.z = this.z * vector3;
            }
            return result;
        };
        /** @method divide
         * Divide this object by another Vector3 object or number.
         * @param {RadJav.Vector3|Number} Vector3 The Vector3 or Number to divide by.
         */
        Vector3.prototype.divide = function (vector3) {
            var result = new RadJav.Vector3();
            if (vector3 instanceof RadJav.Vector3) {
                result.x = this.x / vector3.x;
                result.y = this.y / vector3.y;
                result.z = this.z / vector3.z;
            }
            else {
                result.x = this.x / vector3;
                result.y = this.y / vector3;
                result.z = this.z / vector3;
            }
            return result;
        };
        /** @method dot
         * Perform a dot product on this object.
         * @param {RadJav.Vector3} vector3 The Vector3 to perform the dot product.
         * @return {Number} The result of the dot product.
         */
        Vector3.prototype.dot = function (vector3) {
            var dReturn = this.x * vector3.x + this.y * vector3.y + this.z * vector3.z;
            return dReturn;
        };
        /** @method cross
         * Perform a cross product on this object.
         * @param {RadJav.Vector3} vector3 The Vector3 to perform the dot product.
         * @return {Number} The result of the dot product.
         */
        Vector3.prototype.cross = function (vector3) {
            var result = new RadJav.Vector3();
            result.x = this.y * vector3.z - this.z * vector3.y;
            result.y = this.z * vector3.x - this.x * vector3.z;
            result.z = this.x * vector3.y - this.y * vector3.x;
            return result;
        };
        /** @method length
         * Get the length of this object using a square root. This will use Math.sqrt.
         * @return {Number} The length of this object.
         */
        Vector3.prototype.length = function () {
            var dReturn = Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
            return dReturn;
        };
        /** @method normalize
         * Normalize this object, this will use this object's length method.
         * @return {Number} The normalized length of this object.
         */
        Vector3.prototype.normalize = function () {
            var dReturn = this.divide(this.length());
            return dReturn;
        };
        /** @method squaredLength
         * Normalize this object, this will use this object's length method.
         * @return {Number} The normalized length of this object.
         */
        Vector3.prototype.squaredLength = function () {
            var dReturn = this.x * this.x + this.y * this.y + this.z * this.z;
            return dReturn;
        };
        /** @method absDotProduct
         * Get the dot product as an absolute value.
         * @param {RadJav.Vector3} vector3 The Vector3 to perform the dot product.
         * @return {Number} The absolute value of the dot product.
         */
        Vector3.prototype.absDotProduct = function (vector3) {
            var dReturn = Math.abs(this.dot(vector3));
            return dReturn;
        };
        /** @method angleBetween
         * Get the angle between two vectors.
         * @param {RadJav.Vector3} vector3 The Vector3 to get the angle from.
         * @return {Number} The angle.
         */
        Vector3.prototype.angleBetween = function (vector3) {
            var dTheta = this.dot(vector3) / (this.length() * vector3.length());
            var dReturn = Math.acos(Math.clamp(dTheta, -1, 1));
            return dReturn;
        };
        /** @method distance
         * Get the distance between two vectors.
         * @param {RadJav.Vector3} vector3 The Vector3 to get the distance from.
         * @return {Number} The distance.
         */
        Vector3.prototype.distance = function (vector3) {
            var dX = this.x - vector3.x;
            var dY = this.y - vector3.y;
            var dZ = this.z - vector3.z;
            var dReturn = Math.sqrt(dX * dX + dY * dY + dZ * dZ);
            return dReturn;
        };
        return Vector3;
    }());
    RadJav.Vector3 = Vector3;
})(RadJav || (RadJav = {}));
