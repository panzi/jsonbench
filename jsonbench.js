var fs = require("fs")

function main(args) {
    var repeat = parseInt(args[0],10);
    var filename = args[1];
    var buf = fs.readFileSync(filename, {encoding: 'UTF-8'});
    var duration = 0;
    for (var i = 0; i < repeat; ++ i) {
        var start = Date.now();
        JSON.parse(buf);
        duration += Date.now() - start;
    }
    console.log(Math.floor(duration));
}

main(process.argv.slice(2));
