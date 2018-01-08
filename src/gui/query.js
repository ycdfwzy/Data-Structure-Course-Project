const path = require('path');
const ref = require('ref');
const ffi = require('ffi');
/*var kernel32 = ffi.Library("kernel32", {
'SetDllDirectoryA': ["bool", ["string"]]
})
kernel32Api.SetDllDirectoryA(__dirname);*/
const libquery = ffi.Library(path.join(__dirname, 'DSCPdll'), {
    'init':        [ 'pointer', [] ],
    'destructor':  [ 'void',    [ 'pointer'] ],
    'beforework':  [ 'pointer', [ 'pointer'] ],
    'query':       [ 'pointer', [ 'pointer', 'string'] ],
    'get_Doc':     [ 'pointer', [ 'pointer', 'ulong'] ],
    'divide_words':[ 'pointer', [ 'pointer', 'string'] ],
    'get_str':     [ 'string',  [ 'pointer'] ],
    'free_str':    [ 'void',    [ 'pointer'] ]
});

function json_wrapper(callback) {
    return (err, res) => {
        if (err)
            callback(err, null);
        console.log(libquery.get_str(res));
        let result = JSON.parse(libquery.get_str(res));
        libquery.free_str(res);
        if (result.okay)
            callback(null, result.result);
        else
            callback(new Error(result.message), null);
    };
}

module.exports = class {
    constructor() {
        this.app = libquery.init();
    }
    destroy() {
        libquery.destructor(this.app);
    }
    load(callback) {
        libquery.beforework.async(this.app, json_wrapper(callback));
    }
    query(words, callback) {
        libquery.query.async(this.app, words, json_wrapper(callback))
    }
    get_doc(id, callback) {
        libquery.get_Doc.async(this.app, id, json_wrapper(callback))
    }
    split_words(words, callback) {
        libquery.divide_words.async(this.app, words, json_wrapper(callback))
    }
};