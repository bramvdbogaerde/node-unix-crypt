/** 
 * Node.js package that provides native bindings to UNIXs crypt(3) function 
 */

let crypt = null;

const SUPPORTED = ["linux_x64"];

const NAME = process.platform+"_"+process.arch
if (SUPPORTED.includes(NAME)) {
   crypt = require("./bin/"+NAME+"/addon.node");
} else {
   throw new Exception("platform not supported. Please open a Github issue if you think this a mistake or want to add support for your platform");
}

module.exports = crypt
